#include "Linklist.h"
#include <iostream>
#include <iomanip> 
#include <cmath> 
#include "HRRN.h"
#include "FCFS.h"
#include "SJF.h"
#include "PR.h"
#include "RR.h"
using namespace std;

//int Min(int a, int b) {
//    return (a < b) ? a : b;
//}
int main() {
    //测试数据
    PCB p1(1, 10, 50, 2);
    PCB p2(2, 15, 50, 4);
    PCB p3(3, 4, 50, 8);
    PCB p4(4, 3, 50, 1);
    PCB p5(5, 12, 50, 3);
    PCB p6(6, 7, 50, 5);
    NodeList nodelist;
    nodelist.ComparePCB(SortPCB_ARRIVETIME);
    nodelist.InsertData(nodelist.getLength(), p1, true); // 向尾部插入数据
    nodelist.InsertData(nodelist.getLength(), p2, true);
    nodelist.InsertData(nodelist.getLength(), p3, true);
    nodelist.InsertData(nodelist.getLength(), p4, true);
    nodelist.InsertData(nodelist.getLength(), p5, true);
    nodelist.InsertData(nodelist.getLength(), p6, true);
    cout << "****************请输入数字,选择一种进程调度算法****************" << endl;
    cout << "1、先来先服务（FCFS）" << endl;
    cout << "2、短进程优先（SJF）" << endl;
    cout << "3、时间片轮转调度（RR）" << endl;
    cout << "4、高响应比优先（HRRN）" << endl;
    cout << "5、动态优先级调度（PR）" << endl;
    cout << "请输入：";
    int number;
    cin >> number;
    switch (number) {
    case 1: {
        FCFS fcfs(nodelist);
        fcfs.realize(std::cout);
        break;
    }
    case 2: {
        SJF sjf(nodelist);
        sjf.realize(std::cout);
        break;
    }
    case 3: {
        RR rr(nodelist);
        rr.realize(std::cout);
        break;
    }
    case 4: {
        HRRN hrrn(nodelist);
        hrrn.realize(std::cout);
        break;
    }
    case 5: {
        PR pr(nodelist);
        pr.realize(std::cout);
        break;
    }
    default:
        cout << "输入的数字无效！" << endl;
        break;
    }
    return 0;
}
