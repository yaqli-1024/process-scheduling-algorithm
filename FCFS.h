#pragma once
#pragma once
#include "Linklist.h"
#include <iostream>
using namespace std;

class FCFS {
public:
    //构造函数
    FCFS(NodeList& n) : list(n) {
        if (list.getLength() > 0) {
            list.ComparePCB(SortPCB_ARRIVETIME);  // 排序依据：按到达时间排序(用于先来先服务算法FCFS)
            list.SortList(); // 将所有作业根据“到达时间”进行排序
        }
        else {
            cout << "无元素！" << endl;
        }
    }
    //对先来先服务算法的实现
    void realize(std::ostream& output);

private:
    NodeList& list;  // list 是一个链表，用于存储一系列的 PCB 对象,每个 PCB 对象代表一个待处理的作业。
};

//对先来先服务算法的实现
//进程PCB的状态：共三种状态state:就绪态【0】，执行态【1】，阻塞态【2】
void FCFS::realize(std::ostream& output) {
    output << "当前队列：" << endl;
    list.Print(output);
    if (list.getLength() == 0) {
        output << "当前没有需要处理的进程！" << endl;
        return;
    }
    unsigned int now = 0; // 初始化：令当前时间now为0

    output << "****************************开始执行先来先服务算法（FCFS）************************************" << endl;
    while (list.getLength() > 0) {
        PCB p;
        list.get_X_PCB(1, p); // 找到链表上的第一个节点（p1）  list是就绪队列
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
                if (list.getLength()) {
                    list.Print(output);
                }
                else {
                    output << "无" << endl;
                }
                output << endl;
            }
        }
        p.STATE = 1; // P将状态改为执行态
        list.Delete_X_PCB(1); // 将第一个任务（p）从就绪队列中删除
        unsigned int pre_now = now;
        now += p.ALLTIME; // 此时第一个任务执行完毕 //now的更新

        for (unsigned int i = pre_now; i < now; i++) {
            output << "第" << i << "个时间片内的进程状态：" << endl;
            output << "当前执行：" << p << endl;
            output << "就绪队列：" << endl;
            if (list.getLength()) {
                list.Print(output);
            }
            else {
                output << "无" << endl;
            }
            output << endl;
        }
        output << "**已完成进程**：" << p << endl;
        output << endl;
    }
}

