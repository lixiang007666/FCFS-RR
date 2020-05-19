#include <iostream>
#include <queue>
#include <iomanip>
#include <fstream>
using namespace std;

//���ÿ��������Ϣ�Ľṹ��
typedef struct{
    char name;//��������
    int ArrivalTime;//����ʱ��
    int ServiceTime;//����ʱ��
    int FinishedTime;//���ʱ��
    int WholeTime;//��תʱ��
    double WeightWholeTime;//��Ȩ��תʱ��
}RR;

static queue<RR>RRqueue;  //����ģ�����ִ��RR�����㷨�Ķ���
static double SumWT=0,SumWWT=0,AverageWT =0,AverageWWT=0;//ƽ����תʱ�䡢ƽ����Ȩ��תʱ��
static int q;  //ʱ��Ƭ��
static int n;  //���̸���
static RR RRarray[100];  //���̽ṹ��
static RR temp;  //���̽ṹ

void Enter();//����ʱ��Ƭ������ʱ�䡢����ʱ���
void RRfunction();//ִ��RR�����㷨
void display();//��ʾ��ʱ��ִ��������Լ�����ʱ��ֵ

int main(){
    Enter();
    RRfunction();
    display();
    return 0;
}

//����ʱ��Ƭ������ʱ�䡢����ʱ���
void Enter(){
    int i,j;
    cout<<"Enter n: ";
    cin>>n;
    cout<<"Enter TimeSlice q: ";
    cin>>q;

    for (i=0;i<n;i++){
      RRarray[i].name=i+65;//�Զ�����������˳����ΪA��B��C��D��E��
    }

    cout<<"Enter ArrivalTime: ";
    for (i=0;i<n;i++){
      cin>>RRarray[i].ArrivalTime;
    }

    cout<<"Enter ServiceTime: ";
    for (i=0;i<n;i++){
      cin>>RRarray[i].ServiceTime;
    }

    //���ݴ�ʱ������
    for(i=0;i<n;i++) {
        for(j=i+1;j<n;j++) {
            if(RRarray[i].ArrivalTime > RRarray[j].ArrivalTime) {
                temp = RRarray[i];
                RRarray[i] = RRarray[j];
                RRarray[j] = temp;
            }
        }
    }
}

//ִ��RR�����㷨
void RRfunction(){
    char Moment[100];   //�洢ÿ��ʱ��Ƭp��Ӧ�Ľ�������
    RRqueue.push(RRarray[0]);   //��һ�����̽�����

    int MomentPoint = 0;
    int CurrentTime=0;
    int tempTime;   //����CurrentTime���ۼ�ʱ�䣬��ǰ���̵ķ���ʱ��С��ʱ��Ƭq��ʱ������Ҫ����
    int i=1,j,k,p;  //ָ��δ����Ľ��̵��±�
    int finalNumber = 0;   //ִ��RR�㷨�󣬽��̵ĸ���
    int Time[50];

    //�жϵ�һ�����̵ķ���ʱ���Ƿ����ʱ��Ƭ���������CurrentTime=q�����С��CurrentTime=����ʱ��
    if (RRarray[0].ServiceTime>=q)
        CurrentTime = q;
    else
        CurrentTime = RRarray[0].ServiceTime;

    while(!RRqueue.empty()){
        for (j=i;j<n;j++){   //ʹ��������̵ĵ���ʱ��С�ڵ�ǰʱ��Ľ��̶��������
            if (RRarray[j].name!=NULL && CurrentTime >= RRarray[j].ArrivalTime){
                RRqueue.push(RRarray[j]);
                i++;
            }
        }
        if (RRqueue.front().ServiceTime<q)
            tempTime = RRqueue.front().ServiceTime;
        else
            tempTime = q;

        RRqueue.front().ServiceTime -= q;   //����ÿִ��һ�Σ��ͽ������ʱ�� -q

        //�����׽��̵����Ʒ���������
        Moment[MomentPoint] = RRqueue.front().name;
        MomentPoint++;
        Time[finalNumber] = tempTime;
        finalNumber++;


        if (RRqueue.front().ServiceTime <= 0)  //��ִ����Ľ����˳�����
            RRqueue.pop();   //������̵ķ���ʱ��С�ڵ��ڣ����ý����Ѿ��������ˣ�������ջ
        else{
            //�������Ƶ���β
            RRqueue.push(RRqueue.front());
            RRqueue.pop();
        }
        CurrentTime += tempTime;

    }

    //���̸�ʱ�����״̬���������ʱ��
    cout<<"Time 0: ";
    Time[finalNumber]=0;
    int time = Time[0];
    for (i=0;i<finalNumber;i++){
        //�������ʱ��
        for(j=0;j<finalNumber;j++) {
            for(k=j;k<finalNumber;k++){
                if(Moment[j] == Moment[k]){
                    for(p=0;p<n;p++){
                        if(RRarray[p].name == Moment[k])
                            RRarray[p].FinishedTime=k+1;
                    }
                }

            }
        }

        for(j=0;j<n;j++) {
            if(RRarray[j].ArrivalTime == time-1)
                cout<<RRarray[j].name<<" arrived, ";
            if(RRarray[j].FinishedTime == time-1)
                cout<<RRarray[j].name<<" finished, ";

        }
        cout<<Moment[i]<<" executing, ";
        cout<<endl;

        if (i<finalNumber - 1){
            cout<<"Time "<<time<<": ";
            time += Time[i+1];
        }

    }
    cout<<endl;

    //��תʱ�䡢��Ȩ��תʱ�䡢ƽ����תʱ�䡢��Ȩƽ����תʱ��ļ���
    for (i=0;i<n;i++){
        RRarray[i].WholeTime = RRarray[i].FinishedTime - RRarray[i].ArrivalTime;
        RRarray[i].WeightWholeTime = (double)RRarray[i].WholeTime/RRarray[i].ServiceTime;
    }

    for (i=0;i<n;i++){
        SumWT += RRarray[i].WholeTime;
        SumWWT += RRarray[i].WeightWholeTime;
    }
    AverageWT = SumWT/n;
    AverageWWT = SumWWT/n;

}

//��ʾ��ʱ��ִ��������Լ�����ʱ��ֵ
void display(){
    int i;
    //�������ʱ��
    cout<<"ID"<<"\t";
    cout<<"ArrivalTime"<<"\t";
    cout<<"ServiceTime"<<"\t";
    cout<<"FinishTime"<<"\t";
    cout<<"WholeTime"<<"\t";
    cout<<"WeightWholeTime"<<endl;
    for (i=0;i<n;i++){
        cout<<RRarray[i].name<<"\t\t";
        cout<<RRarray[i].ArrivalTime<<"\t\t";
        cout<<RRarray[i].ServiceTime<<"\t\t";
        cout<<RRarray[i].FinishedTime<<"\t\t";
        cout<<RRarray[i].WholeTime<<"\t\t";
        cout<<setprecision(3)<<RRarray[i].WeightWholeTime<<"\t\t"<<endl;;
    }
    cout<<"SumWT = "<<setprecision(3)<<SumWT<<endl;
    cout<<"SumWWT = "<<setprecision(3)<<SumWWT<<endl;
    cout<<"ƽ����תʱ�� = "<<setprecision(3)<<AverageWT<<endl;
    cout<<"ƽ����Ȩ��תʱ�� = "<<setprecision(3)<<AverageWWT<<endl;
}


