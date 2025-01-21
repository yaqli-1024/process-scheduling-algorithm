#pragma once
#pragma once
#include "Linklist.h"
#include <iostream>
using namespace std;

class FCFS {
public:
    //���캯��
    FCFS(NodeList& n) : list(n) {
        if (list.getLength() > 0) {
            list.ComparePCB(SortPCB_ARRIVETIME);  // �������ݣ�������ʱ������(���������ȷ����㷨FCFS)
            list.SortList(); // ��������ҵ���ݡ�����ʱ�䡱��������
        }
        else {
            cout << "��Ԫ�أ�" << endl;
        }
    }
    //�������ȷ����㷨��ʵ��
    void realize(std::ostream& output);

private:
    NodeList& list;  // list ��һ���������ڴ洢һϵ�е� PCB ����,ÿ�� PCB �������һ�����������ҵ��
};

//�������ȷ����㷨��ʵ��
//����PCB��״̬��������״̬state:����̬��0����ִ��̬��1��������̬��2��
void FCFS::realize(std::ostream& output) {
    output << "��ǰ���У�" << endl;
    list.Print(output);
    if (list.getLength() == 0) {
        output << "��ǰû����Ҫ����Ľ��̣�" << endl;
        return;
    }
    unsigned int now = 0; // ��ʼ�����ǰʱ��nowΪ0

    output << "****************************��ʼִ�������ȷ����㷨��FCFS��************************************" << endl;
    while (list.getLength() > 0) {
        PCB p;
        list.get_X_PCB(1, p); // �ҵ������ϵĵ�һ���ڵ㣨p1��  list�Ǿ�������
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
                if (list.getLength()) {
                    list.Print(output);
                }
                else {
                    output << "��" << endl;
                }
                output << endl;
            }
        }
        p.STATE = 1; // P��״̬��Ϊִ��̬
        list.Delete_X_PCB(1); // ����һ������p���Ӿ���������ɾ��
        unsigned int pre_now = now;
        now += p.ALLTIME; // ��ʱ��һ������ִ����� //now�ĸ���

        for (unsigned int i = pre_now; i < now; i++) {
            output << "��" << i << "��ʱ��Ƭ�ڵĽ���״̬��" << endl;
            output << "��ǰִ�У�" << p << endl;
            output << "�������У�" << endl;
            if (list.getLength()) {
                list.Print(output);
            }
            else {
                output << "��" << endl;
            }
            output << endl;
        }
        output << "**����ɽ���**��" << p << endl;
        output << endl;
    }
}

