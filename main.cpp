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
    //��������
    PCB p1(1, 10, 50, 2);
    PCB p2(2, 15, 50, 4);
    PCB p3(3, 4, 50, 8);
    PCB p4(4, 3, 50, 1);
    PCB p5(5, 12, 50, 3);
    PCB p6(6, 7, 50, 5);
    NodeList nodelist;
    nodelist.ComparePCB(SortPCB_ARRIVETIME);
    nodelist.InsertData(nodelist.getLength(), p1, true); // ��β����������
    nodelist.InsertData(nodelist.getLength(), p2, true);
    nodelist.InsertData(nodelist.getLength(), p3, true);
    nodelist.InsertData(nodelist.getLength(), p4, true);
    nodelist.InsertData(nodelist.getLength(), p5, true);
    nodelist.InsertData(nodelist.getLength(), p6, true);
    cout << "****************����������,ѡ��һ�ֽ��̵����㷨****************" << endl;
    cout << "1�������ȷ���FCFS��" << endl;
    cout << "2���̽������ȣ�SJF��" << endl;
    cout << "3��ʱ��Ƭ��ת���ȣ�RR��" << endl;
    cout << "4������Ӧ�����ȣ�HRRN��" << endl;
    cout << "5����̬���ȼ����ȣ�PR��" << endl;
    cout << "�����룺";
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
        cout << "�����������Ч��" << endl;
        break;
    }
    return 0;
}
