#pragma once
#include "Linklist.h"
#include <iostream>
#include <iomanip> 
#include <cmath> 
using namespace std;

class HRRN {
public:
    //构造函数
    HRRN(NodeList& n) : list(n) {
        list.ComparePCB(SortPCB_ARRIVETIME);//这个list中存放所有进程，按照到达时间arriveTime进行排序。
        list.SortList();
    }
    //对高响应比优先算法的实现
    void realize(std::ostream& output);
private:
    NodeList& list;
};

//对高响应比优先算法的实现
void HRRN::realize(std::ostream& output) {
    output << "当前队列（按照到达时间排序）：" << endl;
    list.Print(output);
    if (list.getLength() == 0) {
        output << "当前没有需要处理的进程！" << endl;
        return;
    }
    unsigned int now = 0;
    NodeList ready_List;
    ready_List.ComparePCB(SortPCB_Res_Ratio);//就绪队列按照响应比进行排序
    PCB p;
    list.get_X_PCB(1, p);//取出list中的第一个进程并执行
    p.STATE = 1; //状态设置为执行态
    output << "****************************开始执行高响应比优先算法（HRRN）************************************" << endl;
    while (list.getLength() > 0 || ready_List.getLength() > 0) {
        cout << endl;
        if (p.ARRIVETIME > now) {
            unsigned int p_now = now;
            if (p_now == 0) {
                p_now += 1;
            }
            now = p.ARRIVETIME;
            for (unsigned int i = p_now; i < now; i++) {
                output << "第" << i << "个时间片内的进程状态：" << endl;
                output << "当前执行：无" << endl;
                output << "就绪队列：" << endl;
                if (ready_List.getLength()) {
                    ready_List.Print(output);
                }
                else {
                    output << "无" << endl;
                }
                output << endl;
            }
        }

        //将所有在当前执行进程的 [ARRIVETIME, ARRIVETIME + ALLTIME] 内到达的进程放入就绪队列
        Node nn;
        list.get_X_Node(1, nn);//找到list中的第一个任务
        Node* test = nn.pNext;//test指向继当前节点之后到达的第二个节点（按照到达时间排序）

        while (test != nullptr) {
            bool isInReadyList = false;
            Node readyNode;
            ready_List.get_X_Node(1, readyNode);
            Node* readyNodePtr = &readyNode;
            while (readyNodePtr != nullptr) {
                if (readyNodePtr->data.ProcessId == test->data.ProcessId) {
                    isInReadyList = true;
                }
                readyNodePtr = readyNodePtr->pNext;
            }//只将不在就绪队列中的节点加入就绪队列
            if ((!isInReadyList) && (test->data.ProcessId != p.ProcessId) && (test->data.ARRIVETIME < (now + p.ALLTIME))) {
                ready_List.InsertData(ready_List.getLength(), test->data, false); //将符合条件的节点插入就绪队列ready_List【不能插入目前执行的节点！】
                //注：此时暂时不考虑排序，等到要挑选一个进程进行执行时才排序。因为wait_time还不知道，不能计算响应比
            }
            test = test->pNext;
        }
        unsigned int pre_now = now;
        now += p.ALLTIME; // 更新当前时间

        //输出执行阶段时间片状态
        for (unsigned int i = pre_now; i < now; i++) {
            output << "第" << i << "个时间片内的进程状态：" << endl;
            output << "当前执行：" << p << endl;
            output << "就绪队列：" << endl;
            if (ready_List.getLength()) {
                ready_List.Print(output);
            }
            else {
                output << "无" << endl;
            }
            output << endl;
        }
        cout << "****进程" << p.ProcessId << "执行完毕****" << endl;
        list.Delete_X_PCB(1); //将list队列里的第一个节点删除（已经执行完毕）
        // 处理就绪队列中的最短进程(将其设置为执行态)
        Node data; // 创建一个Node对象,用于存储get_X_Node函数返回的节点数据
        Node* d = ready_List.getHeadNode();
        d = d->pNext;

        for (int i = 1; i <= ready_List.getLength(); i++) {
            if (ready_List.get_X_Node(i, data)) {
                PCB& p = d->data;
                p.Wait_Time = (now - 1 - p.ARRIVETIME);
                /*cout << "现在时间：" << now << "  进程" << p.ProcessId << "到达时间：" << p.ARRIVETIME << "  等待时间：" << p.Wait_Time << endl;*/
                d = d->pNext;
            }
            else {
                cout << "处理错误，未能获取第" << i << "个节点" << endl;
                break;
            }
        }
        //对就绪队列进行排序（排序依据：响应比,高响应比的优先执行）
        ready_List.SortList();
        PCB pp;
        if (ready_List.getLength()) {
            cout << "****此时就绪队列中各进程响应比：****" << endl;
        }
        for (int i = 1; i <= ready_List.getLength(); i++) {
            ready_List.get_X_PCB(i, pp);
            output << pp << " \t等待时间:" << pp.Wait_Time << "\t执行时间：" << pp.ALLTIME << "\t响应比：" << fixed << setprecision(2) << pp.Res_Ratio << endl;
        }
        if (ready_List.getLength() > 0) {
            ready_List.get_X_PCB(1, p); // 找到就绪队列中的第一个进程
            p.STATE = 1;  // 执行该进程
            ready_List.Delete_X_PCB(1); // 将正在执行的进程从就绪队列中删除
        }
        else if (list.getLength() > 0) {
            list.get_X_PCB(1, p); // 如果就绪队列为空，从list中取出下一个进程
        }
    }
}