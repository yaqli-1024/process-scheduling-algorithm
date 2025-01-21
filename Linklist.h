#pragma once
#pragma once
#include <iostream>
#include <cmath> 
//为进程控制块PCB定义一个结构体
struct PCB {
    //进程标识数ID
    unsigned int ProcessId;
    //进程到达时间ARRIVETIME
    unsigned int ARRIVETIME;
    //进程优先级  （数字越大越优先）
    unsigned int PRIORITY;
    //进程运行总时间ALLTIME
    unsigned int ALLTIME;
    //进程已运行时间CPUTIME
    unsigned int CPUTIME;
    //进程等待时间Wait_Time
    unsigned int Wait_Time;
    //进程响应比Res_Ratio
    double Res_Ratio;
    //进程状态 STATE(一共三种状态：就绪态、运行态、阻塞态)
    unsigned int STATE;

    // 默认构造函数，将所有成员变量置为0
    PCB() : ProcessId(0), ARRIVETIME(0), PRIORITY(0), ALLTIME(0),
        CPUTIME(0), Wait_Time(0), Res_Ratio(0), STATE(0) {}

    // 带参数的构造函数，只初始化特定的成员变量，其他成员变量使用默认值
    PCB(unsigned int id, unsigned int arrive, unsigned int priority, unsigned int allTime)
        : ProcessId(id), ARRIVETIME(arrive), PRIORITY(priority), ALLTIME(allTime),
        CPUTIME(0), Wait_Time(0), Res_Ratio(0), STATE(0) {}//STATE默认初始值为0：就绪态
};

//输出流重载(使用 std::cout 直接输出 PCB 结构体的实例)
std::ostream& operator<<(std::ostream& output, PCB& pcb) {
    output << "进程ID号:" << pcb.ProcessId
        << "\t进程到达时间:" << pcb.ARRIVETIME
        << "\t 优先级:" << pcb.PRIORITY
        << "\t运行所需CPU总时间片数:" << pcb.ALLTIME;
    return output;
}

//按到达时间排序函数 (用于先来先服务算法FCFS)
int SortPCB_ARRIVETIME(PCB& p1, PCB& p2) {
    int x = p1.ARRIVETIME - p2.ARRIVETIME;
    return x < 0 ? -1 : x > 0 ? 1 : 0;  //x < 0,就返回-1。x = 0，就返回0。x > 0，就返回1。
}

//按执行时间长短排序函数 (用于短进程优先算法SJF)
int  SortPCB_ALLTIME(PCB& p1, PCB& p2) {
    int x = p1.ALLTIME - p2.ALLTIME;
    return x < 0 ? -1 : x > 0 ? 1 : 0; //x < 0,就返回-1。x = 0，就返回0。x > 0，就返回1。
}

//按优先级排序函数 （用于动态优先级调度算法PR） 优先级越高，越提前执行
//如果优先级相同，则按照进程到达时间排序
int  SortPCB_PRIORITY(PCB& p1, PCB& p2) {
    int x = p1.PRIORITY - p2.PRIORITY;
    if (x < 0) {
        return 1;
    }
    else if (x > 0) {
        return -1;
    }
    else {
        //如果优先级相同，则按照进程到达时间排序
        int y = p1.ARRIVETIME - p2.ARRIVETIME;
        return y < 0 ? -1 : x > 0 ? 1 : 0;
    }
}

//按响应比排序函数（用于高响应比优先算法HRRN）
int SortPCB_Res_Ratio(PCB& p1, PCB& p2) {
    // 确保计算时使用浮点数
    p1.Res_Ratio = round(((p1.Wait_Time + p1.ALLTIME) / static_cast<double>(p1.ALLTIME)) * 100) / 100;
    p2.Res_Ratio = round(((p2.Wait_Time + p2.ALLTIME) / static_cast<double>(p2.ALLTIME)) * 100) / 100;

    double x = p1.Res_Ratio - p2.Res_Ratio;
    return x < 0 ? 1 : x > 0 ? -1 : 0;
}

//时间片轮转调度算法：不需要排序
//---------------------------------------------------------------------------------------------------------------------
//对链表进行定义
struct Node {
    PCB data;//存储节点的数据  (已经对输出流进行重载，PCB的数据可以通过cout直接输出)
    Node* pNext;//指向下一个节点的指针f
    // 默认构造函数
    Node() : data(0, 0, 0, 0), pNext(nullptr) {} // 这里假设PCB有一个接受四个0参数的构造函数
    // 带参数的构造函数
    Node(const PCB& p) : data(p), pNext(nullptr) {}
};

class NodeList { //定义一个“队列”类，用于表示链表，链表中存放的是进程控制块PCB
private:
    Node* head; //头结点
    int length; //链表长
    int(*compare)(PCB& p1, PCB& p2);//比较函数compare
public:
    //1、构造函数（初始化）
    NodeList();

    //2、拷贝构造函数
    NodeList(const NodeList& other);

    //3、销毁链表（析构函数）
    ~NodeList();

    //4、链表是否为空
    bool isEmpty();

    //5、获取链表长度
    int getLength();

    //6、返回链表的第x个PCB 
    bool get_X_PCB(int x, PCB& data); //返回的元素储存在data里

    //7、返回链表的第x个Node
    bool get_X_Node(int x, Node& data); //返回的元素储存在data里

    //8、打印链表数据
    std::ostream& Print(std::ostream& out);

    //9、在链表中第x个位置插入数据，并决定是否对链表进行重新排序
    NodeList& InsertData(int x, PCB value, bool ifReSort);

    //10、删除链表的第x个元素
    NodeList& Delete_X_PCB(int x); //删除的元素储存在data里

    //11、排序函数
    NodeList& SortList();

    //12、设置比较函数
    void ComparePCB(int(*function)(PCB& p1, PCB& p2));

    //13、返回头结点
    Node* getHeadNode() const;
};

//对公共接口的实现：
//1、构造函数（初始化）  [测试通过！]
NodeList::NodeList() {
    head = new Node();
    head->pNext = nullptr;
    length = 0;
    compare = nullptr;
}

//2、拷贝构造函数
NodeList::NodeList(const NodeList& other) {   //[测试通过！]
    head = new Node();
    head->data = other.head->data;
    length = other.length;
    compare = other.compare;
}

//3、销毁链表（析构函数）
NodeList::~NodeList() {
    while (head != nullptr) {
        Node* n = head;
        head = head->pNext;
        delete n;
        length--;
    }
}

//4、链表是否为空  //[测试通过！]
bool NodeList::isEmpty() {
    if (length == 0) {
        return true;
    }
    else {
        return false;
    }
}

//5、获取链表长度  //[测试通过！]
int NodeList::getLength() {
    return length;
}

//6、返回链表的第x个PCB    //[测试通过！]
bool NodeList::get_X_PCB(int x, PCB& ret) {
    //判断x的值是否合理
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


//7、返回链表的第x个Node   //[测试通过！]
bool NodeList::get_X_Node(int x, Node& data) {
    //判断x的值是否合理
    if (x < 1 || x > length) {
        return false;
    }
    x = x - 1;
    Node* test = head->pNext;
    for (int i = 0; i < x; i++) {
        test = test->pNext;
    }
    data = *test;  // 使用解引用操作符(*)来复制test指向的Node对象的内容
    return true;
}


//8、打印链表数据  //[测试通过！]
std::ostream& NodeList::Print(std::ostream& out) {
    Node* p = head->pNext; //指向首节点
    for (int i = 0; i < length && p != nullptr; i++) {
        //out << p->data << '\n'; //打印这个PCB的相关数据
        out << p->data << '\n'; //打印这个PCB的相关数据
        p = p->pNext;
    }
    return out;
}

//9、在链表中的第x个位置后插入数据，并决定是否对链表进行重新排序  //[测试通过！]
NodeList& NodeList::InsertData(int x, PCB value, bool ifReSort) {
    //判断位置x是否合理
    if (x < 0 || x > length) {
        x = length; //如果x提供不合理，则在链表末尾插入数据
    }
    //找原来的第x个节点
    Node* p = head;
    for (int i = 0; i < x; i++) {
        p = p->pNext;
    }//循环退出时，p指向第x个节点
    Node* new_node = new Node();
    new_node->data = value;
    new_node->pNext = p->pNext; // 新节点指向原第x个节点的下一个节点
    p->pNext = new_node; // 原第x个节点指向新节点
    length++;
    if (ifReSort) {
        SortList(); // 如果需要重新排序，则调用Sort方法
    }
    return *this;
}

//10、删除链表的第x个元素   //[测试通过！]
NodeList& NodeList::Delete_X_PCB(int x) {
    //判断x的值是否合理
    if (x < 1 || x > length) {
        return *this;
    }
    x = x - 1;
    // 特殊情况：删除第一个节点
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

    // 检查test是否为nullptr
    if (test == nullptr) {
        // 如果test是nullptr，说明x超出了链表长度，不做任何操作
        return *this;
    }

    // 此时test指向第x个PCB，test_pre指向第x-1个PCB
    test_pre->pNext = test->pNext;
    delete test;
    length--;
    return *this;
}

//11、排序函数   //[测试通过！]
//以compare为依据，使用冒泡方法进行排序
NodeList& NodeList::SortList() {
    if (length < 2) {
        // 如果链表长度小于2，无需排序
        return *this;
    }

    bool finish = false;
    Node* temp = head->pNext;  // 确保temp不为nullptr
    if (temp == nullptr) {
        // 如果temp为nullptr，链表只有一个节点，无需排序
        return *this;
    }

    for (int i = 0; i < length - 1; i++) {
        finish = true;
        Node* current = temp;
        Node* prev = head;  // 用于跟踪current的前一个节点

        for (int j = 0; j < length - 1 - i; j++) {
            if (current == nullptr || current->pNext == nullptr) {
                // 如果current或current->pNext为nullptr，链表结构可能有问题
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

//12、设置比较函数  //[测试通过！]
void NodeList::ComparePCB(int(*function)(PCB& p1, PCB& p2)) {
    compare = function; //将传入的函数指针 function 赋值给类的私有成员 compare。此时compare指向一个比较函数。
}

//13、返回头结点
Node* NodeList::getHeadNode() const {
    return head;
}