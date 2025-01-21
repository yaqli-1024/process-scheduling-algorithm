#pragma once
#include "Linklist.h"
#include <iostream>
using namespace std;

class SJF {
public:
    //构造函数
    SJF(NodeList& n) : list(n) {
        list.ComparePCB(SortPCB_ARRIVETIME);//这个list中存放所有进程，按照到达时间arriveTime进行排序。
        list.SortList();
    }
    //对短进程优先算法的实现
    void realize(std::ostream& output);
private:
    NodeList& list;
};

//对短进程优先算法的实现
void SJF::realize(std::ostream& output) {
    output << "当前队列（按照到达时间排序）：" << endl;
    list.Print(output);
    if (list.getLength() == 0) {
        output << "当前没有需要处理的进程！" << endl;
        return;
    }
    output << "****************************开始执行短进程优先算法（SJF）************************************" << endl;
    unsigned int now = 0;
    NodeList ready_List;
    ready_List.ComparePCB(SortPCB_ALLTIME);
    PCB p;
    list.get_X_PCB(1, p);

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
        p.STATE = 1; //将当前节点的状态置为1（执行态）

        // 将所有在当前执行进程的 [ARRIVETIME, ARRIVETIME + ALLTIME] 内到达的进程放入就绪队列
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
            if ((!isInReadyList) && (test->data.ProcessId != p.ProcessId) && (test->data.ARRIVETIME <= (now + p.ALLTIME))) {
                ready_List.InsertData(ready_List.getLength(), test->data, true); //将符合条件的节点插入就绪队列ready_List【不能插入目前执行的节点！】
            }
            test = test->pNext;
        }
        unsigned int pre_now = now;
        now += p.ALLTIME; // 更新当前时间
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
        output << "**已完成进程**：" << p << endl;
        list.Delete_X_PCB(1);
        // 处理就绪队列中的最短进程(将其设置为执行态)
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

