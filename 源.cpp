#include <stdlib.h>
#include <iostream>
#include <queue>
#include <list>

using namespace std;


class User
{
public:
    User();
    User(int id, bool isWait, int ArriveTime, wchar_t type, int ServerTime)  //析构函数定义用户类
        :id(id), isWait(isWait), ArriveTime(ArriveTime), type(type), ServerTime(ServerTime) {};
    ~User() {};

    virtual void getServed();

public:                   //定义客户ID，等待状态，到达时间，客户类型，服务时间
    int id;
    int isWait;         
    int ArriveTime;
    wchar_t type;
private:
    int ServerTime;

};

class NormalUser : public User {   //定义普通用户，继承父类
public:
    NormalUser(int id, bool isWait, int ArriveTime, wchar_t type, int ServerTime)
        :User(id, isWait, ArriveTime, type, ServerTime) {};
    void getServed();
};

class VIPUser : public User {      //定义VIP用户，继承父类
public:
    VIPUser(int id, bool isWait, int ArriveTime, wchar_t type, int ServerTime)
        :User(id, isWait, ArriveTime, type, ServerTime) {};
    void getServed();
};

class OfficialUser : public User {   //定义对公用户，继承父类
public:
    OfficialUser(int id, bool isWait, int ArriveTime, wchar_t type, int ServerTime)
        :User(id, isWait, ArriveTime, type, ServerTime) {};
    void getServed();
};

//构造服务函数，针对不同的用户输出不同反应
void User::getServed() {          
    if (type == 'n') {
        cout << endl << endl << "---普通用户" << id << " 服务完毕！---" << endl;
    }
    if (type == 'v') {
        cout << endl << endl << "--- VIP用户" << id << " 服务完毕！---" << endl;
    }
    if (type == 'o') {
        cout << endl << endl << "---对公用户" << id << " 服务完毕！---" << endl;
    }
}

void NormalUser::getServed() {
    cout << endl << endl << "---普通用户" << id << " 服务完毕！---" << endl;
}

void VIPUser::getServed() {
    cout << endl << endl << "--- VIP用户" << id << " 服务完毕！---" << endl;
}

void OfficialUser::getServed() {
    cout << endl << endl << "---对公用户" << id << " 服务完毕！---" << endl;
}

//服务函数完成

//定义服务窗口类

class BankWindow
{
public:
    BankWindow() {};
    BankWindow(bool isBusy, int id, wchar_t type)
        :isBusy(isBusy), id(id), type(type) {};
    ~BankWindow() {};

    bool isBusy;
    int id;
    User* client;
    wchar_t type;
    int serviceStartTime;

    virtual void HandleUser();
};

class NormalBankWindow : public BankWindow {
public:
    NormalBankWindow(bool isBusy, int id, wchar_t type)
        :BankWindow(isBusy, id, type) {};
    void HandleUser();
};

class VIPBankWindow : public BankWindow {
public:
    VIPBankWindow(bool isBusy, int id, wchar_t type)
        :BankWindow(isBusy, id, type) {};
    void HandleUser();
};

class OfficialBankWindow : public BankWindow {
public:
    OfficialBankWindow(bool isBusy, int id, wchar_t type)
        :BankWindow(isBusy, id, type) {};
    void HandleUser();
};


void BankWindow::HandleUser() {
    cout << endl << "BankWindow handle user." << endl;
}

void NormalBankWindow::HandleUser() {
    cout << endl << "---" << this->id << "号窗口 接收 用户" << client->id << "---" << endl << endl;
}

void VIPBankWindow::HandleUser() {
    cout << endl << "---" << this->id << "号窗口 接收 用户" << client->id << "---" << endl << endl;
}

void OfficialBankWindow::HandleUser() {
    cout << endl << "---" << this->id << "号窗口 接收 用户" << client->id << "---" << endl << endl;
}

class Simulater  //定义模拟程序类
{
public:
    Simulater() {};
    ~Simulater() {};

    queue<NormalUser> NormalUserQueue;
    queue<VIPUser> VIPUserQueue;
    queue<OfficialUser> OfficialUserQueue;

    list<NormalBankWindow> nbw;
    list<VIPBankWindow> vbw;
    list<OfficialBankWindow> obw;

    void customerEnter();
    void simulateCustomerEnter();
    void simulateCallCustomer();
    void Simulate();

    void display();
};

int t = 0;
bool Flag = false;

int customerEnterMatrix[9][3] = { //矩阵模拟每两秒进入银行的各类用户
    {3,1,1},
    {5,0,0},
    {0,0,0},
    {5,1,0},
    {0,0,0},
    {0,0,0},
    {0,0,0},
    {0,0,0},
    {0,0,0}
};

void Simulater::customerEnter() {//模拟用户入队，将矩阵中的数据依次带入类中进行排队
    static int h = 1001;
    int i = 0, j = 0, k = 0;
    i = customerEnterMatrix[t / 2][0];
    j = customerEnterMatrix[t / 2][1];
    k = customerEnterMatrix[t / 2][2];
    for (int n = 0; n < i; n++) {
        NormalUserQueue.push(NormalUser(h++, true, t, 'n', 0));
        cout << "普通客户 进入排队,  编号:" << NormalUserQueue.back().id << endl;
    }
    for (int n = 0; n < j; n++) {
        VIPUserQueue.push(VIPUser(h++, true, t, 'v', 0));
        cout << "VIP客户  进入排队,  编号:" << VIPUserQueue.back().id << endl;
    }
    for (int n = 0; n < k; n++) {
        OfficialUserQueue.push(OfficialUser(h++, true, t, 'o', 0));
        cout << "对公客户 进入排队,  编号:" << OfficialUserQueue.back().id << endl;
    }
}

void Simulater::simulateCustomerEnter() {//银行处理用户序列
    //普通用户窗口
    list<NormalBankWindow>::iterator itor;
    itor = nbw.begin();
    while (itor != nbw.end()) { //遍历所有的普通窗口，查看是否有空位，如果有就进入，如无就等待
        cout << "窗口号:" << itor->id;
        if (itor->isBusy == true) {
            cout << "  -正在服务-  " << " 窗口类型: " << "普通 " << "客户编号: " << itor->client->id;
            if (t - itor->serviceStartTime >= 4) {
                itor->client->getServed();
                Flag = true;
                itor->isBusy = false;//将当前位置的User清空
            }
        }
        else {
            cout << "  -等待服务-  ";
        }
        cout << endl;
        itor++;
    }
    //VIP用户窗口
    cout << "窗口号:" << vbw.begin()->id;
    if (vbw.begin()->isBusy == true) {
        cout << "  -正在服务-  " << " 窗口类型: " << " VIP " << "客户编号: " << vbw.begin()->client->id;
        if (t - vbw.begin()->serviceStartTime >= 4) {
            vbw.begin()->client->getServed();
            Flag = true;
            vbw.begin()->isBusy = false;//将当前位置的User清空
        }
    }
    else {
        cout << "  -等待服务-  ";
    }
    cout << endl;
    //对公用户窗口
    cout << "窗口号:" << obw.begin()->id;
    if (obw.begin()->isBusy == true) {
        cout << "  -正在服务-  " << " 窗口类型: " << "对公 " << "客户编号: " << obw.begin()->client->id;
        if (t - obw.begin()->serviceStartTime >= 4) {
            obw.begin()->client->getServed();
            Flag = true;
            obw.begin()->isBusy = false;//将当前位置的User清空
        }
    }
    else {
        cout << "  -等待服务-  ";
    }
    cout << endl;

}

//银行处理的时间是4秒，占两个周期
void Simulater::simulateCallCustomer() {//呼叫用户,从队列里面呼叫
    //普通用户窗口
    list<NormalBankWindow>::iterator itor;
    itor = nbw.begin();
    while (itor != nbw.end()) {
        if (itor->isBusy == false && !NormalUserQueue.empty()) {
            itor->client = &NormalUserQueue.front();
            cout << itor->client->id << ", 请进入" << itor->id << "号普通窗口服务";
            itor->HandleUser();
            itor->isBusy = true;
            itor->serviceStartTime = t;
            NormalUserQueue.pop();
        }
        itor++;
    }
    //VIP用户窗口
    if (vbw.begin()->isBusy == false) {
        if (!VIPUserQueue.empty()) {
            vbw.begin()->client = &VIPUserQueue.front();
            vbw.begin()->isBusy = true;
            vbw.begin()->serviceStartTime = t;
            VIPUserQueue.pop();
            cout << vbw.begin()->client->id << ", 请进入3号VIP窗口服务";
            vbw.begin()->HandleUser();
        }
        else if (!NormalUserQueue.empty()) {
            vbw.begin()->client = &NormalUserQueue.front();
            vbw.begin()->isBusy = true;
            vbw.begin()->serviceStartTime = t;
            NormalUserQueue.pop();
            cout << vbw.begin()->client->id << ", 请进入3号VIP窗口服务";
            vbw.begin()->HandleUser();
        }
        else {}
    }
    //对公用户窗口
    if (obw.begin()->isBusy == false) {
        if (!OfficialUserQueue.empty()) {
            obw.begin()->client = &OfficialUserQueue.front();
            obw.begin()->isBusy = true;
            obw.begin()->serviceStartTime = t;
            OfficialUserQueue.pop();
            cout << obw.begin()->client->id << ", 请进入4号对公窗口服务";
            obw.begin()->HandleUser();
        }
        else if (!NormalUserQueue.empty()) {
            obw.begin()->client = &NormalUserQueue.front();
            obw.begin()->isBusy = true;
            obw.begin()->serviceStartTime = t;
            NormalUserQueue.pop();
            cout << obw.begin()->client->id << ", 请进入4号对公窗口服务";
            obw.begin()->HandleUser();
        }
        else {}
    }
}

void Simulater::Simulate() {
    nbw.push_back(NormalBankWindow(false, 0, ' '));
    nbw.push_back(NormalBankWindow(false, 1, ' '));
    nbw.push_back(NormalBankWindow(false, 2, ' '));
    vbw.push_back(VIPBankWindow(false, 3, ' '));
    obw.push_back(OfficialBankWindow(false, 4, ' '));
    cout << "------------------------模  拟  开  始---------------------" << endl;

    while (t <= 16) {//模拟时间是否结束
        cout << "当" << t << "s时 :" << endl;
        customerEnter();
        simulateCallCustomer();
        simulateCustomerEnter();
        if (Flag) {
            Flag = false;
            //customerEnter();
            simulateCallCustomer();
            simulateCustomerEnter();
        }
        cout << endl << "**********************************************************" << endl;

        //时间增加
        t += 2;
    }

}

int main() {
    Simulater SSS;
    SSS.Simulate();
    return 0;
}