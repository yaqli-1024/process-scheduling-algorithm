#pragma once
#include "Linklist.h"
#include <iostream>
using namespace std;

class SJF {
public:
    //���캯��
    SJF(NodeList& n) : list(n) {
        list.ComparePCB(SortPCB_ARRIVETIME);//���list�д�����н��̣����յ���ʱ��arriveTime��������
        list.SortList();
    }
    //�Զ̽��������㷨��ʵ��
    void realize(std::ostream& output);
private:
    NodeList& list;
};

//�Զ̽��������㷨��ʵ��
void SJF::realize(std::ostream& output) {
    output << "��ǰ���У����յ���ʱ�����򣩣�" << endl;
    list.Print(output);
    if (list.getLength() == 0) {
        output << "��ǰû����Ҫ����Ľ��̣�" << endl;
        return;
    }
    output << "****************************��ʼִ�ж̽��������㷨��SJF��************************************" << endl;
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
        p.STATE = 1; //����ǰ�ڵ��״̬��Ϊ1��ִ��̬��

        // �������ڵ�ǰִ�н��̵� [ARRIVETIME, ARRIVETIME + ALLTIME] �ڵ���Ľ��̷����������
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
            if ((!isInReadyList) && (test->data.ProcessId != p.ProcessId) && (test->data.ARRIVETIME <= (now + p.ALLTIME))) {
                ready_List.InsertData(ready_List.getLength(), test->data, true); //�����������Ľڵ�����������ready_List�����ܲ���Ŀǰִ�еĽڵ㣡��
            }
            test = test->pNext;
        }
        unsigned int pre_now = now;
        now += p.ALLTIME; // ���µ�ǰʱ��
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
        output << "**����ɽ���**��" << p << endl;
        list.Delete_X_PCB(1);
        // ������������е���̽���(��������Ϊִ��̬)
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

