#pragma once
#include "Linklist.h"
#include <iostream>
using namespace std;

//int Min(int a, int b) {
//    return (a < b) ? a : b;
//}


class RR {
public:
    //构造函数
    RR(NodeList& n) : list(n) {
        list.ComparePCB(SortPCB_ARRIVETIME); //这个函数用于比较作业的到达时间。
        list.SortList();  //根据到达时间对作业进行排序
    }
    //对时间片轮转调度算法的实现
    void realize(std::ostream& output);
private:
    NodeList& list;
};

//对时间片轮转调度算法的实现 
void RR::realize(std::ostream& output) {
    output << "当前队列（按照到达时间排序）：" << endl;
    list.Print(output);
    if (list.getLength() == 0) {
        output << "当前没有需要处理的进程！" << endl;
        return;
    }
    output << "***********************开始执行时间片轮转调度算法（RR），时间片大小设置为1********************************" << endl;
    unsigned int now = 1;
    NodeList ready_List; // 设置就绪队列（初始为空）
    ready_List.ComparePCB(SortPCB_ARRIVETIME); // 就绪队列按照进程到达时间进行排序

    while (list.getLength() > 0 || ready_List.getLength() > 0) {
        // 将所有在当前时间到达的进程放入就绪队列
        for (int i = 1; i <= list.getLength(); ) {
            PCB p;
            list.get_X_PCB(i, p);
            if (p.ARRIVETIME <= now) {
                list.Delete_X_PCB(i);
                p.STATE = 0; // 就绪态
                ready_List.InsertData(ready_List.getLength(), p, false);
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
            /*int a = 1;*/
            int b = current.ALLTIME - current.CPUTIME;
            int execTime = (1 < b) ? 1 : b;
            //int execTime = Min(1, current.ALLTIME - current.CPUTIME); // 使用 std::min
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
            current.CPUTIME += 1;
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

        }
    }
}



