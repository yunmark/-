#include <stdlib.h>
#include <iostream>
#include <queue>
#include <list>

using namespace std;


class User
{
public:
    User();
    User(int id, bool isWait, int ArriveTime, wchar_t type, int ServerTime)  //�������������û���
        :id(id), isWait(isWait), ArriveTime(ArriveTime), type(type), ServerTime(ServerTime) {};
    ~User() {};

    virtual void getServed();

public:                   //����ͻ�ID���ȴ�״̬������ʱ�䣬�ͻ����ͣ�����ʱ��
    int id;
    int isWait;         
    int ArriveTime;
    wchar_t type;
private:
    int ServerTime;

};

class NormalUser : public User {   //������ͨ�û����̳и���
public:
    NormalUser(int id, bool isWait, int ArriveTime, wchar_t type, int ServerTime)
        :User(id, isWait, ArriveTime, type, ServerTime) {};
    void getServed();
};

class VIPUser : public User {      //����VIP�û����̳и���
public:
    VIPUser(int id, bool isWait, int ArriveTime, wchar_t type, int ServerTime)
        :User(id, isWait, ArriveTime, type, ServerTime) {};
    void getServed();
};

class OfficialUser : public User {   //����Թ��û����̳и���
public:
    OfficialUser(int id, bool isWait, int ArriveTime, wchar_t type, int ServerTime)
        :User(id, isWait, ArriveTime, type, ServerTime) {};
    void getServed();
};

//�������������Բ�ͬ���û������ͬ��Ӧ
void User::getServed() {          
    if (type == 'n') {
        cout << endl << endl << "---��ͨ�û�" << id << " ������ϣ�---" << endl;
    }
    if (type == 'v') {
        cout << endl << endl << "--- VIP�û�" << id << " ������ϣ�---" << endl;
    }
    if (type == 'o') {
        cout << endl << endl << "---�Թ��û�" << id << " ������ϣ�---" << endl;
    }
}

void NormalUser::getServed() {
    cout << endl << endl << "---��ͨ�û�" << id << " ������ϣ�---" << endl;
}

void VIPUser::getServed() {
    cout << endl << endl << "--- VIP�û�" << id << " ������ϣ�---" << endl;
}

void OfficialUser::getServed() {
    cout << endl << endl << "---�Թ��û�" << id << " ������ϣ�---" << endl;
}

//���������

//������񴰿���

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
    cout << endl << "---" << this->id << "�Ŵ��� ���� �û�" << client->id << "---" << endl << endl;
}

void VIPBankWindow::HandleUser() {
    cout << endl << "---" << this->id << "�Ŵ��� ���� �û�" << client->id << "---" << endl << endl;
}

void OfficialBankWindow::HandleUser() {
    cout << endl << "---" << this->id << "�Ŵ��� ���� �û�" << client->id << "---" << endl << endl;
}

class Simulater  //����ģ�������
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

int customerEnterMatrix[9][3] = { //����ģ��ÿ����������еĸ����û�
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

void Simulater::customerEnter() {//ģ���û���ӣ��������е��������δ������н����Ŷ�
    static int h = 1001;
    int i = 0, j = 0, k = 0;
    i = customerEnterMatrix[t / 2][0];
    j = customerEnterMatrix[t / 2][1];
    k = customerEnterMatrix[t / 2][2];
    for (int n = 0; n < i; n++) {
        NormalUserQueue.push(NormalUser(h++, true, t, 'n', 0));
        cout << "��ͨ�ͻ� �����Ŷ�,  ���:" << NormalUserQueue.back().id << endl;
    }
    for (int n = 0; n < j; n++) {
        VIPUserQueue.push(VIPUser(h++, true, t, 'v', 0));
        cout << "VIP�ͻ�  �����Ŷ�,  ���:" << VIPUserQueue.back().id << endl;
    }
    for (int n = 0; n < k; n++) {
        OfficialUserQueue.push(OfficialUser(h++, true, t, 'o', 0));
        cout << "�Թ��ͻ� �����Ŷ�,  ���:" << OfficialUserQueue.back().id << endl;
    }
}

void Simulater::simulateCustomerEnter() {//���д����û�����
    //��ͨ�û�����
    list<NormalBankWindow>::iterator itor;
    itor = nbw.begin();
    while (itor != nbw.end()) { //�������е���ͨ���ڣ��鿴�Ƿ��п�λ������оͽ��룬���޾͵ȴ�
        cout << "���ں�:" << itor->id;
        if (itor->isBusy == true) {
            cout << "  -���ڷ���-  " << " ��������: " << "��ͨ " << "�ͻ����: " << itor->client->id;
            if (t - itor->serviceStartTime >= 4) {
                itor->client->getServed();
                Flag = true;
                itor->isBusy = false;//����ǰλ�õ�User���
            }
        }
        else {
            cout << "  -�ȴ�����-  ";
        }
        cout << endl;
        itor++;
    }
    //VIP�û�����
    cout << "���ں�:" << vbw.begin()->id;
    if (vbw.begin()->isBusy == true) {
        cout << "  -���ڷ���-  " << " ��������: " << " VIP " << "�ͻ����: " << vbw.begin()->client->id;
        if (t - vbw.begin()->serviceStartTime >= 4) {
            vbw.begin()->client->getServed();
            Flag = true;
            vbw.begin()->isBusy = false;//����ǰλ�õ�User���
        }
    }
    else {
        cout << "  -�ȴ�����-  ";
    }
    cout << endl;
    //�Թ��û�����
    cout << "���ں�:" << obw.begin()->id;
    if (obw.begin()->isBusy == true) {
        cout << "  -���ڷ���-  " << " ��������: " << "�Թ� " << "�ͻ����: " << obw.begin()->client->id;
        if (t - obw.begin()->serviceStartTime >= 4) {
            obw.begin()->client->getServed();
            Flag = true;
            obw.begin()->isBusy = false;//����ǰλ�õ�User���
        }
    }
    else {
        cout << "  -�ȴ�����-  ";
    }
    cout << endl;

}

//���д����ʱ����4�룬ռ��������
void Simulater::simulateCallCustomer() {//�����û�,�Ӷ����������
    //��ͨ�û�����
    list<NormalBankWindow>::iterator itor;
    itor = nbw.begin();
    while (itor != nbw.end()) {
        if (itor->isBusy == false && !NormalUserQueue.empty()) {
            itor->client = &NormalUserQueue.front();
            cout << itor->client->id << ", �����" << itor->id << "����ͨ���ڷ���";
            itor->HandleUser();
            itor->isBusy = true;
            itor->serviceStartTime = t;
            NormalUserQueue.pop();
        }
        itor++;
    }
    //VIP�û�����
    if (vbw.begin()->isBusy == false) {
        if (!VIPUserQueue.empty()) {
            vbw.begin()->client = &VIPUserQueue.front();
            vbw.begin()->isBusy = true;
            vbw.begin()->serviceStartTime = t;
            VIPUserQueue.pop();
            cout << vbw.begin()->client->id << ", �����3��VIP���ڷ���";
            vbw.begin()->HandleUser();
        }
        else if (!NormalUserQueue.empty()) {
            vbw.begin()->client = &NormalUserQueue.front();
            vbw.begin()->isBusy = true;
            vbw.begin()->serviceStartTime = t;
            NormalUserQueue.pop();
            cout << vbw.begin()->client->id << ", �����3��VIP���ڷ���";
            vbw.begin()->HandleUser();
        }
        else {}
    }
    //�Թ��û�����
    if (obw.begin()->isBusy == false) {
        if (!OfficialUserQueue.empty()) {
            obw.begin()->client = &OfficialUserQueue.front();
            obw.begin()->isBusy = true;
            obw.begin()->serviceStartTime = t;
            OfficialUserQueue.pop();
            cout << obw.begin()->client->id << ", �����4�ŶԹ����ڷ���";
            obw.begin()->HandleUser();
        }
        else if (!NormalUserQueue.empty()) {
            obw.begin()->client = &NormalUserQueue.front();
            obw.begin()->isBusy = true;
            obw.begin()->serviceStartTime = t;
            NormalUserQueue.pop();
            cout << obw.begin()->client->id << ", �����4�ŶԹ����ڷ���";
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
    cout << "------------------------ģ  ��  ��  ʼ---------------------" << endl;

    while (t <= 16) {//ģ��ʱ���Ƿ����
        cout << "��" << t << "sʱ :" << endl;
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

        //ʱ������
        t += 2;
    }

}

int main() {
    Simulater SSS;
    SSS.Simulate();
    return 0;
}