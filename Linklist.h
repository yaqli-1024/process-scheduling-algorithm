#pragma once
#pragma once
#include <iostream>
#include <cmath> 
//Ϊ���̿��ƿ�PCB����һ���ṹ��
struct PCB {
    //���̱�ʶ��ID
    unsigned int ProcessId;
    //���̵���ʱ��ARRIVETIME
    unsigned int ARRIVETIME;
    //�������ȼ�  ������Խ��Խ���ȣ�
    unsigned int PRIORITY;
    //����������ʱ��ALLTIME
    unsigned int ALLTIME;
    //����������ʱ��CPUTIME
    unsigned int CPUTIME;
    //���̵ȴ�ʱ��Wait_Time
    unsigned int Wait_Time;
    //������Ӧ��Res_Ratio
    double Res_Ratio;
    //����״̬ STATE(һ������״̬������̬������̬������̬)
    unsigned int STATE;

    // Ĭ�Ϲ��캯���������г�Ա������Ϊ0
    PCB() : ProcessId(0), ARRIVETIME(0), PRIORITY(0), ALLTIME(0),
        CPUTIME(0), Wait_Time(0), Res_Ratio(0), STATE(0) {}

    // �������Ĺ��캯����ֻ��ʼ���ض��ĳ�Ա������������Ա����ʹ��Ĭ��ֵ
    PCB(unsigned int id, unsigned int arrive, unsigned int priority, unsigned int allTime)
        : ProcessId(id), ARRIVETIME(arrive), PRIORITY(priority), ALLTIME(allTime),
        CPUTIME(0), Wait_Time(0), Res_Ratio(0), STATE(0) {}//STATEĬ�ϳ�ʼֵΪ0������̬
};

//���������(ʹ�� std::cout ֱ����� PCB �ṹ���ʵ��)
std::ostream& operator<<(std::ostream& output, PCB& pcb) {
    output << "����ID��:" << pcb.ProcessId
        << "\t���̵���ʱ��:" << pcb.ARRIVETIME
        << "\t ���ȼ�:" << pcb.PRIORITY
        << "\t��������CPU��ʱ��Ƭ��:" << pcb.ALLTIME;
    return output;
}

//������ʱ�������� (���������ȷ����㷨FCFS)
int SortPCB_ARRIVETIME(PCB& p1, PCB& p2) {
    int x = p1.ARRIVETIME - p2.ARRIVETIME;
    return x < 0 ? -1 : x > 0 ? 1 : 0;  //x < 0,�ͷ���-1��x = 0���ͷ���0��x > 0���ͷ���1��
}

//��ִ��ʱ�䳤�������� (���ڶ̽��������㷨SJF)
int  SortPCB_ALLTIME(PCB& p1, PCB& p2) {
    int x = p1.ALLTIME - p2.ALLTIME;
    return x < 0 ? -1 : x > 0 ? 1 : 0; //x < 0,�ͷ���-1��x = 0���ͷ���0��x > 0���ͷ���1��
}

//�����ȼ������� �����ڶ�̬���ȼ������㷨PR�� ���ȼ�Խ�ߣ�Խ��ǰִ��
//������ȼ���ͬ�����ս��̵���ʱ������
int  SortPCB_PRIORITY(PCB& p1, PCB& p2) {
    int x = p1.PRIORITY - p2.PRIORITY;
    if (x < 0) {
        return 1;
    }
    else if (x > 0) {
        return -1;
    }
    else {
        //������ȼ���ͬ�����ս��̵���ʱ������
        int y = p1.ARRIVETIME - p2.ARRIVETIME;
        return y < 0 ? -1 : x > 0 ? 1 : 0;
    }
}

//����Ӧ�������������ڸ���Ӧ�������㷨HRRN��
int SortPCB_Res_Ratio(PCB& p1, PCB& p2) {
    // ȷ������ʱʹ�ø�����
    p1.Res_Ratio = round(((p1.Wait_Time + p1.ALLTIME) / static_cast<double>(p1.ALLTIME)) * 100) / 100;
    p2.Res_Ratio = round(((p2.Wait_Time + p2.ALLTIME) / static_cast<double>(p2.ALLTIME)) * 100) / 100;

    double x = p1.Res_Ratio - p2.Res_Ratio;
    return x < 0 ? 1 : x > 0 ? -1 : 0;
}

//ʱ��Ƭ��ת�����㷨������Ҫ����
//---------------------------------------------------------------------------------------------------------------------
//��������ж���
struct Node {
    PCB data;//�洢�ڵ������  (�Ѿ���������������أ�PCB�����ݿ���ͨ��coutֱ�����)
    Node* pNext;//ָ����һ���ڵ��ָ��f
    // Ĭ�Ϲ��캯��
    Node() : data(0, 0, 0, 0), pNext(nullptr) {} // �������PCB��һ�������ĸ�0�����Ĺ��캯��
    // �������Ĺ��캯��
    Node(const PCB& p) : data(p), pNext(nullptr) {}
};

class NodeList { //����һ�������С��࣬���ڱ�ʾ���������д�ŵ��ǽ��̿��ƿ�PCB
private:
    Node* head; //ͷ���
    int length; //����
    int(*compare)(PCB& p1, PCB& p2);//�ȽϺ���compare
public:
    //1�����캯������ʼ����
    NodeList();

    //2���������캯��
    NodeList(const NodeList& other);

    //3��������������������
    ~NodeList();

    //4�������Ƿ�Ϊ��
    bool isEmpty();

    //5����ȡ������
    int getLength();

    //6����������ĵ�x��PCB 
    bool get_X_PCB(int x, PCB& data); //���ص�Ԫ�ش�����data��

    //7����������ĵ�x��Node
    bool get_X_Node(int x, Node& data); //���ص�Ԫ�ش�����data��

    //8����ӡ��������
    std::ostream& Print(std::ostream& out);

    //9���������е�x��λ�ò������ݣ��������Ƿ�����������������
    NodeList& InsertData(int x, PCB value, bool ifReSort);

    //10��ɾ������ĵ�x��Ԫ��
    NodeList& Delete_X_PCB(int x); //ɾ����Ԫ�ش�����data��

    //11��������
    NodeList& SortList();

    //12�����ñȽϺ���
    void ComparePCB(int(*function)(PCB& p1, PCB& p2));

    //13������ͷ���
    Node* getHeadNode() const;
};

//�Թ����ӿڵ�ʵ�֣�
//1�����캯������ʼ����  [����ͨ����]
NodeList::NodeList() {
    head = new Node();
    head->pNext = nullptr;
    length = 0;
    compare = nullptr;
}

//2���������캯��
NodeList::NodeList(const NodeList& other) {   //[����ͨ����]
    head = new Node();
    head->data = other.head->data;
    length = other.length;
    compare = other.compare;
}

//3��������������������
NodeList::~NodeList() {
    while (head != nullptr) {
        Node* n = head;
        head = head->pNext;
        delete n;
        length--;
    }
}

//4�������Ƿ�Ϊ��  //[����ͨ����]
bool NodeList::isEmpty() {
    if (length == 0) {
        return true;
    }
    else {
        return false;
    }
}

//5����ȡ������  //[����ͨ����]
int NodeList::getLength() {
    return length;
}

//6����������ĵ�x��PCB    //[����ͨ����]
bool NodeList::get_X_PCB(int x, PCB& ret) {
    //�ж�x��ֵ�Ƿ����
    if (x < 1 || x > length) {
        return false;
    }
    x = x - 1;
    Node* test = head->pNext;
    for (int i = 0; i < x; i++) {
        test = test->pNext;
    }
    ret = test->data;
    return true;
}


//7����������ĵ�x��Node   //[����ͨ����]
bool NodeList::get_X_Node(int x, Node& data) {
    //�ж�x��ֵ�Ƿ����
    if (x < 1 || x > length) {
        return false;
    }
    x = x - 1;
    Node* test = head->pNext;
    for (int i = 0; i < x; i++) {
        test = test->pNext;
    }
    data = *test;  // ʹ�ý����ò�����(*)������testָ���Node���������
    return true;
}


//8����ӡ��������  //[����ͨ����]
std::ostream& NodeList::Print(std::ostream& out) {
    Node* p = head->pNext; //ָ���׽ڵ�
    for (int i = 0; i < length && p != nullptr; i++) {
        //out << p->data << '\n'; //��ӡ���PCB���������
        out << p->data << '\n'; //��ӡ���PCB���������
        p = p->pNext;
    }
    return out;
}

//9���������еĵ�x��λ�ú�������ݣ��������Ƿ�����������������  //[����ͨ����]
NodeList& NodeList::InsertData(int x, PCB value, bool ifReSort) {
    //�ж�λ��x�Ƿ����
    if (x < 0 || x > length) {
        x = length; //���x�ṩ��������������ĩβ��������
    }
    //��ԭ���ĵ�x���ڵ�
    Node* p = head;
    for (int i = 0; i < x; i++) {
        p = p->pNext;
    }//ѭ���˳�ʱ��pָ���x���ڵ�
    Node* new_node = new Node();
    new_node->data = value;
    new_node->pNext = p->pNext; // �½ڵ�ָ��ԭ��x���ڵ����һ���ڵ�
    p->pNext = new_node; // ԭ��x���ڵ�ָ���½ڵ�
    length++;
    if (ifReSort) {
        SortList(); // �����Ҫ�������������Sort����
    }
    return *this;
}

//10��ɾ������ĵ�x��Ԫ��   //[����ͨ����]
NodeList& NodeList::Delete_X_PCB(int x) {
    //�ж�x��ֵ�Ƿ����
    if (x < 1 || x > length) {
        return *this;
    }
    x = x - 1;
    // ���������ɾ����һ���ڵ�
    if (x == 0) {
        Node* toDelete = head->pNext;
        if (toDelete != nullptr) {
            head->pNext = toDelete->pNext;
            delete toDelete;
            length--;
        }
        return *this;
    }

    Node* test = head->pNext;
    Node* test_pre = head;
    for (int i = 0; i < x && test != nullptr; i++) {
        test_pre = test;
        test = test->pNext;
    }

    // ���test�Ƿ�Ϊnullptr
    if (test == nullptr) {
        // ���test��nullptr��˵��x�����������ȣ������κβ���
        return *this;
    }

    // ��ʱtestָ���x��PCB��test_preָ���x-1��PCB
    test_pre->pNext = test->pNext;
    delete test;
    length--;
    return *this;
}

//11��������   //[����ͨ����]
//��compareΪ���ݣ�ʹ��ð�ݷ�����������
NodeList& NodeList::SortList() {
    if (length < 2) {
        // ���������С��2����������
        return *this;
    }

    bool finish = false;
    Node* temp = head->pNext;  // ȷ��temp��Ϊnullptr
    if (temp == nullptr) {
        // ���tempΪnullptr������ֻ��һ���ڵ㣬��������
        return *this;
    }

    for (int i = 0; i < length - 1; i++) {
        finish = true;
        Node* current = temp;
        Node* prev = head;  // ���ڸ���current��ǰһ���ڵ�

        for (int j = 0; j < length - 1 - i; j++) {
            if (current == nullptr || current->pNext == nullptr) {
                // ���current��current->pNextΪnullptr������ṹ����������
                break;
            }

            if (compare(current->data, current->pNext->data) > 0) {
                std::swap(current->data, current->pNext->data);
                finish = false;
            }
            prev = current;
            current = current->pNext;
        }
        if (finish) break;
    }
    return *this;
}

//12�����ñȽϺ���  //[����ͨ����]
void NodeList::ComparePCB(int(*function)(PCB& p1, PCB& p2)) {
    compare = function; //������ĺ���ָ�� function ��ֵ�����˽�г�Ա compare����ʱcompareָ��һ���ȽϺ�����
}

//13������ͷ���
Node* NodeList::getHeadNode() const {
    return head;
}