#pragma once
#include "Linklist.h"
#include <iostream>
#include <iomanip> 
#include <cmath> 
using namespace std;

class HRRN {
public:
    //���캯��
    HRRN(NodeList& n) : list(n) {
        list.ComparePCB(SortPCB_ARRIVETIME);//���list�д�����н��̣����յ���ʱ��arriveTime��������
        list.SortList();
    }
    //�Ը���Ӧ�������㷨��ʵ��
    void realize(std::ostream& output);
private:
    NodeList& list;
};

//�Ը���Ӧ�������㷨��ʵ��
void HRRN::realize(std::ostream& output) {
    output << "��ǰ���У����յ���ʱ�����򣩣�" << endl;
    list.Print(output);
    if (list.getLength() == 0) {
        output << "��ǰû����Ҫ����Ľ��̣�" << endl;
        return;
    }
    unsigned int now = 0;
    NodeList ready_List;
    ready_List.ComparePCB(SortPCB_Res_Ratio);//�������а�����Ӧ�Ƚ�������
    PCB p;
    list.get_X_PCB(1, p);//ȡ��list�еĵ�һ�����̲�ִ��
    p.STATE = 1; //״̬����Ϊִ��̬
    output << "****************************��ʼִ�и���Ӧ�������㷨��HRRN��************************************" << endl;
    while (list.getLength() > 0 || ready_List.getLength() > 0) {
        cout << endl;
        if (p.ARRIVETIME > now) {
            unsigned int p_now = now;
            if (p_now == 0) {
                p_now += 1;
            }
            now = p.ARRIVETIME;
            for (unsigned int i = p_now; i < now; i++) {
                output << "��" << i << "��ʱ��Ƭ�ڵĽ���״̬��" << endl;
                output << "��ǰִ�У���" << endl;
                output << "�������У�" << endl;
                if (ready_List.getLength()) {
                    ready_List.Print(output);
                }
                else {
                    output << "��" << endl;
                }
                output << endl;
            }
        }

        //�������ڵ�ǰִ�н��̵� [ARRIVETIME, ARRIVETIME + ALLTIME] �ڵ���Ľ��̷����������
        Node nn;
        list.get_X_Node(1, nn);//�ҵ�list�еĵ�һ������
        Node* test = nn.pNext;//testָ��̵�ǰ�ڵ�֮�󵽴�ĵڶ����ڵ㣨���յ���ʱ������

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
            }//ֻ�����ھ��������еĽڵ�����������
            if ((!isInReadyList) && (test->data.ProcessId != p.ProcessId) && (test->data.ARRIVETIME < (now + p.ALLTIME))) {
                ready_List.InsertData(ready_List.getLength(), test->data, false); //�����������Ľڵ�����������ready_List�����ܲ���Ŀǰִ�еĽڵ㣡��
                //ע����ʱ��ʱ���������򣬵ȵ�Ҫ��ѡһ�����̽���ִ��ʱ��������Ϊwait_time����֪�������ܼ�����Ӧ��
            }
            test = test->pNext;
        }
        unsigned int pre_now = now;
        now += p.ALLTIME; // ���µ�ǰʱ��

        //���ִ�н׶�ʱ��Ƭ״̬
        for (unsigned int i = pre_now; i < now; i++) {
            output << "��" << i << "��ʱ��Ƭ�ڵĽ���״̬��" << endl;
            output << "��ǰִ�У�" << p << endl;
            output << "�������У�" << endl;
            if (ready_List.getLength()) {
                ready_List.Print(output);
            }
            else {
                output << "��" << endl;
            }
            output << endl;
        }
        cout << "****����" << p.ProcessId << "ִ�����****" << endl;
        list.Delete_X_PCB(1); //��list������ĵ�һ���ڵ�ɾ�����Ѿ�ִ����ϣ�
        // ������������е���̽���(��������Ϊִ��̬)
        Node data; // ����һ��Node����,���ڴ洢get_X_Node�������صĽڵ�����
        Node* d = ready_List.getHeadNode();
        d = d->pNext;

        for (int i = 1; i <= ready_List.getLength(); i++) {
            if (ready_List.get_X_Node(i, data)) {
                PCB& p = d->data;
                p.Wait_Time = (now - 1 - p.ARRIVETIME);
                /*cout << "����ʱ�䣺" << now << "  ����" << p.ProcessId << "����ʱ�䣺" << p.ARRIVETIME << "  �ȴ�ʱ�䣺" << p.Wait_Time << endl;*/
                d = d->pNext;
            }
            else {
                cout << "�������δ�ܻ�ȡ��" << i << "���ڵ�" << endl;
                break;
            }
        }
        //�Ծ������н��������������ݣ���Ӧ��,����Ӧ�ȵ�����ִ�У�
        ready_List.SortList();
        PCB pp;
        if (ready_List.getLength()) {
            cout << "****��ʱ���������и�������Ӧ�ȣ�****" << endl;
        }
        for (int i = 1; i <= ready_List.getLength(); i++) {
            ready_List.get_X_PCB(i, pp);
            output << pp << " \t�ȴ�ʱ��:" << pp.Wait_Time << "\tִ��ʱ�䣺" << pp.ALLTIME << "\t��Ӧ�ȣ�" << fixed << setprecision(2) << pp.Res_Ratio << endl;
        }
        if (ready_List.getLength() > 0) {
            ready_List.get_X_PCB(1, p); // �ҵ����������еĵ�һ������
            p.STATE = 1;  // ִ�иý���
            ready_List.Delete_X_PCB(1); // ������ִ�еĽ��̴Ӿ���������ɾ��
        }
        else if (list.getLength() > 0) {
            list.get_X_PCB(1, p); // �����������Ϊ�գ���list��ȡ����һ������
        }
    }
}