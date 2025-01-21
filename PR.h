#pragma once
#include "Linklist.h"
#include <iostream>
using namespace std;

int Min(int a, int b) {
    return (a < b) ? a : b;
}
class PR {
public:
    //���캯��
    PR(NodeList& n) : list(n) {
        list.ComparePCB(SortPCB_ARRIVETIME);
        list.SortList();
    }
    //�Զ�̬���ȼ������㷨��ʵ��
    void realize(std::ostream& output);
private:
    NodeList& list;
};

//�Զ�̬���ȼ������㷨��ʵ��
void PR::realize(std::ostream& output) {
    output << "��ǰ���У����յ���ʱ�����򣩣�" << endl;
    list.Print(output);
    if (list.getLength() == 0) {
        output << "��ǰû����Ҫ����Ľ��̣�" << endl;
        return;
    }
    unsigned int now = 1;
    NodeList ready_List; // ���þ������У���ʼΪ�գ�
    ready_List.ComparePCB(SortPCB_PRIORITY); // �������а��ս��̵���ʱ���������
    output << "****************************��ʼִ�ж�̬���ȼ������㷨��PR��************************************" << endl;
    output << "**************************���̵ĳ�ʼ���ȼ�����Ϊ50��ʱ��Ƭ��С����Ϊ1****************************" << endl;
    while (list.getLength() > 0 || ready_List.getLength() > 0) {
        // �������ڵ�ǰʱ�䵽��Ľ��̷����������
        for (int i = 1; i <= list.getLength(); ) {
            PCB p;
            list.get_X_PCB(i, p);
            if (p.ARRIVETIME <= now) {
                list.Delete_X_PCB(i);
                p.STATE = 0; // ����̬
                ready_List.InsertData(ready_List.getLength(), p, false);//������������ǣ���ʱ�����򡢡�����
            }
            else {
                break; // ��������δ����
            }
        }

        // �����������Ϊ�գ�������һ������Ľ���ʱ��
        if (ready_List.getLength() == 0) {
            if (list.getLength() > 0) {
                PCB p;
                list.get_X_PCB(1, p);
                unsigned int p_now = now;
                now = p.ARRIVETIME;
                for (unsigned int i = p_now; i < now; i++) {
                    output << "��" << i << "��ʱ��Ƭ�ڵĽ���״̬��" << endl;
                    output << "��ǰִ�У���" << endl;
                    output << "�������У�" << endl;
                    ready_List.SortList();
                    if (ready_List.getLength()) {
                        ready_List.Print(output);
                    }
                    else {
                        output << "��" << endl;
                    }
                    output << endl;
                }
            }
            else {
                break;
            }
        }

        // ȡ���������еĵ�һ������ִ��
        PCB current;
        if (!ready_List.isEmpty()) {
            ready_List.get_X_PCB(1, current);
            ready_List.Delete_X_PCB(1);
            current.STATE = 1; // ִ��̬
            // ִ�е�ǰ����
            int execTime = Min(1, current.ALLTIME - current.CPUTIME); // ʹ�� std::min
            output << "��" << now << "��ʱ��Ƭ�ڵĽ���״̬��" << endl;
            output << "��ǰִ�У�" << current << endl;
            if (!ready_List.isEmpty()) {
                output << "�������У�" << endl;
                ready_List.Print(output);
            }
            else {
                output << "�������У���" << endl;
            }
            output << endl;
            now += 1;
            current.CPUTIME += 1;//��ǰʱ��Ƭִ�н���

            //���¸����������ȼ�
            current.PRIORITY -= 3;
            Node data; // ����һ��Node����,���ڴ洢get_X_Node�������صĽڵ�����
            Node* d = ready_List.getHeadNode();
            d = d->pNext;
            for (int i = 1; i <= ready_List.getLength(); i++) {
                if (ready_List.get_X_Node(i, data)) {
                    PCB& p = d->data;
                    p.PRIORITY += 1;
                    d = d->pNext;
                }
                else {
                    cout << "�������δ�ܻ�ȡ��" << i << "���ڵ�" << endl;
                    break;
                }
            }

            // ��鵱ǰ�����Ƿ����
            if (current.CPUTIME < current.ALLTIME) {
                // δ��ɣ��Żؾ�������ĩβ
                current.STATE = 0; // ����̬
                ready_List.InsertData(ready_List.getLength(), current, false);
            }
            else {
                // ���
                output << "**����ɽ���**��" << current << endl;
                output << endl;
            }

            //�Ծ������������н��̽�������
            ready_List.SortList();
            if (ready_List.getLength()) {
                output << "********************************************************************" << endl;
                output << "     -------ʱ��Ƭ�����󣬶Ծ���������������------                  " << endl;
                ready_List.Print(output);
                output << "********************************************************************" << endl;
                output << endl;
            }
        }
    }

}
