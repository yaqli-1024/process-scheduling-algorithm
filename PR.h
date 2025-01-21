#pragma once
#include "Linklist.h"
#include <iostream>
using namespace std;

int Min(int a, int b) {
    return (a < b) ? a : b;
}
class PR {
public:
    //构造函数
    PR(NodeList& n) : list(n) {
        list.ComparePCB(SortPCB_ARRIVETIME);
        list.SortList();
    }
    //对动态优先级调度算法的实现
    void realize(std::ostream& output);
private:
    NodeList& list;
};

//对动态优先级调度算法的实现
void PR::realize(std::ostream& output) {
    output << "当前队列（按照到达时间排序）：" << endl;
    list.Print(output);
    if (list.getLength() == 0) {
        output << "当前没有需要处理的进程！" << endl;
        return;
    }
    unsigned int now = 1;
    NodeList ready_List; // 设置就绪队列（初始为空）
    ready_List.ComparePCB(SortPCB_PRIORITY); // 就绪队列按照进程到达时间进行排序
    output << "****************************开始执行动态优先级调度算法（PR）************************************" << endl;
    output << "**************************进程的初始优先级设置为50，时间片大小设置为1****************************" << endl;
    while (list.getLength() > 0 || ready_List.getLength() > 0) {
        // 将所有在当前时间到达的进程放入就绪队列
        for (int i = 1; i <= list.getLength(); ) {
            PCB p;
            list.get_X_PCB(i, p);
            if (p.ARRIVETIME <= now) {
                list.Delete_X_PCB(i);
                p.STATE = 0; // 就绪态
                ready_List.InsertData(ready_List.getLength(), p, false);//放入就绪进程是，暂时不排序、、、、
            }
            else {
                break; // 后续进程未到达
            }
        }

        // 如果就绪队列为空，跳到下一个到达的进程时间
        if (ready_List.getLength() == 0) {
            if (list.getLength() > 0) {
                PCB p;
                list.get_X_PCB(1, p);
                unsigned int p_now = now;
                now = p.ARRIVETIME;
                for (unsigned int i = p_now; i < now; i++) {
                    output << "第" << i << "个时间片内的进程状态：" << endl;
                    output << "当前执行：无" << endl;
                    output << "就绪队列：" << endl;
                    ready_List.SortList();
                    if (ready_List.getLength()) {
                        ready_List.Print(output);
                    }
                    else {
                        output << "无" << endl;
                    }
                    output << endl;
                }
            }
            else {
                break;
            }
        }

        // 取出就绪队列的第一个进程执行
        PCB current;
        if (!ready_List.isEmpty()) {
            ready_List.get_X_PCB(1, current);
            ready_List.Delete_X_PCB(1);
            current.STATE = 1; // 执行态
            // 执行当前进程
            int execTime = Min(1, current.ALLTIME - current.CPUTIME); // 使用 std::min
            output << "第" << now << "个时间片内的进程状态：" << endl;
            output << "当前执行：" << current << endl;
            if (!ready_List.isEmpty()) {
                output << "就绪队列：" << endl;
                ready_List.Print(output);
            }
            else {
                output << "就绪队列：无" << endl;
            }
            output << endl;
            now += 1;
            current.CPUTIME += 1;//当前时间片执行结束

            //更新各个进程优先级
            current.PRIORITY -= 3;
            Node data; // 创建一个Node对象,用于存储get_X_Node函数返回的节点数据
            Node* d = ready_List.getHeadNode();
            d = d->pNext;
            for (int i = 1; i <= ready_List.getLength(); i++) {
                if (ready_List.get_X_Node(i, data)) {
                    PCB& p = d->data;
                    p.PRIORITY += 1;
                    d = d->pNext;
                }
                else {
                    cout << "处理错误，未能获取第" << i << "个节点" << endl;
                    break;
                }
            }

            // 检查当前进程是否完成
            if (current.CPUTIME < current.ALLTIME) {
                // 未完成，放回就绪队列末尾
                current.STATE = 0; // 就绪态
                ready_List.InsertData(ready_List.getLength(), current, false);
            }
            else {
                // 完成
                output << "**已完成进程**：" << current << endl;
                output << endl;
            }

            //对就绪队列中所有进程进行排序
            ready_List.SortList();
            if (ready_List.getLength()) {
                output << "********************************************************************" << endl;
                output << "     -------时间片结束后，对就绪队列重新排序------                  " << endl;
                ready_List.Print(output);
                output << "********************************************************************" << endl;
                output << endl;
            }
        }
    }

}
