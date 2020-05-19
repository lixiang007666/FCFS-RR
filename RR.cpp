#include <iostream>
#include <queue>
#include <iomanip>
#include <fstream>
using namespace std;

//存放每个进程信息的结构体
typedef struct{
    char name;//进程名字
    int ArrivalTime;//到达时间
    int ServiceTime;//服务时间
    int FinishedTime;//完成时间
    int WholeTime;//周转时间
    double WeightWholeTime;//带权周转时间
}RR;

static queue<RR>RRqueue;  //用来模拟进程执行RR调度算法的队列
static double SumWT=0,SumWWT=0,AverageWT =0,AverageWWT=0;//平均周转时间、平均带权周转时间
static int q;  //时间片数
static int n;  //进程个数
static RR RRarray[100];  //进程结构体
static RR temp;  //进程结构

void Enter();//输入时间片、到达时间、服务时间等
void RRfunction();//执行RR调度算法
void display();//显示各时间执行情况，以及各个时间值

int main(){
    Enter();
    RRfunction();
    display();
    return 0;
}

//输入时间片、到达时间、服务时间等
void Enter(){
    int i,j;
    cout<<"Enter n: ";
    cin>>n;
    cout<<"Enter TimeSlice q: ";
    cin>>q;

    for (i=0;i<n;i++){
      RRarray[i].name=i+65;//自动将进程名字顺序编号为A、B、C、D、E等
    }

    cout<<"Enter ArrivalTime: ";
    for (i=0;i<n;i++){
      cin>>RRarray[i].ArrivalTime;
    }

    cout<<"Enter ServiceTime: ";
    for (i=0;i<n;i++){
      cin>>RRarray[i].ServiceTime;
    }

    //根据达时间排序
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

//执行RR调度算法
void RRfunction(){
    char Moment[100];   //存储每个时间片p对应的进程名称
    RRqueue.push(RRarray[0]);   //第一个进程进队列

    int MomentPoint = 0;
    int CurrentTime=0;
    int tempTime;   //控制CurrentTime的累加时间，当前进程的服务时间小于时间片q的时候，起到重要作用
    int i=1,j,k,p;  //指向还未处理的进程的下标
    int finalNumber = 0;   //执行RR算法后，进程的个数
    int Time[50];

    //判断第一个进程的服务时间是否大于时间片，如果大于CurrentTime=q，如果小于CurrentTime=服务时间
    if (RRarray[0].ServiceTime>=q)
        CurrentTime = q;
    else
        CurrentTime = RRarray[0].ServiceTime;

    while(!RRqueue.empty()){
        for (j=i;j<n;j++){   //使得满足进程的到达时间小于当前时间的进程都进入队列
            if (RRarray[j].name!=NULL && CurrentTime >= RRarray[j].ArrivalTime){
                RRqueue.push(RRarray[j]);
                i++;
            }
        }
        if (RRqueue.front().ServiceTime<q)
            tempTime = RRqueue.front().ServiceTime;
        else
            tempTime = q;

        RRqueue.front().ServiceTime -= q;   //进程每执行一次，就将其服务时间 -q

        //将队首进程的名称放入数组中
        Moment[MomentPoint] = RRqueue.front().name;
        MomentPoint++;
        Time[finalNumber] = tempTime;
        finalNumber++;


        if (RRqueue.front().ServiceTime <= 0)  //把执行完的进程退出队列
            RRqueue.pop();   //如果进程的服务时间小于等于，即该进程已经服务完了，将其退栈
        else{
            //将队首移到队尾
            RRqueue.push(RRqueue.front());
            RRqueue.pop();
        }
        CurrentTime += tempTime;

    }

    //进程各时间进程状态，计算完成时间
    cout<<"Time 0: ";
    Time[finalNumber]=0;
    int time = Time[0];
    for (i=0;i<finalNumber;i++){
        //计算完成时间
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

    //周转时间、带权周转时间、平均周转时间、带权平均周转时间的计算
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

//显示各时间执行情况，以及各个时间值
void display(){
    int i;
    //输出各个时间
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
    cout<<"平均周转时间 = "<<setprecision(3)<<AverageWT<<endl;
    cout<<"平均带权周转时间 = "<<setprecision(3)<<AverageWWT<<endl;
}


