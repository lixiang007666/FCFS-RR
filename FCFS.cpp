#include<iostream>
#include <iomanip>
using namespace std;
#define MaxNum 100
//static int MaxNum=100; ///???????
int ArrivalTime[MaxNum];
int ServicesTime[MaxNum];
int FinishTime[MaxNum];
int WholeTime[MaxNum];
double WeightWholeTime[MaxNum];
double AverageWT_FCFS,AverageWT_SJF;
double AverageWWT_FCFS,AverageWWT_SJF;
////ѭ������
int i;
int j;
int k;
//
int NowTime;
///������Ŀ
int ProcessNumber;

struct Process{
	int arrival_Time;
	int services_Time;
	int key;
};
//
double sumWT;
double sumWWT;


void FCFS();
void init();
void print();

int main(){
	init();
	FCFS();
	print();
	return 0;
}
void init(){
	cout<<"�������������"<<endl;
	cin>>ProcessNumber;
	cout<<"��������̵���ʱ�䣺"<<endl;
	for(int i=0;i<ProcessNumber;i++)
	{
		cin>>ArrivalTime[i];
	}
	cout<<"���������ʱ�䣺"<<endl;
	for(i=0;i<ProcessNumber;i++)
	{
		cin>>ServicesTime[i];
	}
    NowTime=0;
	sumWT=0;
	sumWWT=0;

}


void FCFS(){
	cout<<"----�����ȷ�������㷨(FCFS)----"<<endl;
    
  
	
   /*  //���ݵ���ʱ������
     Process p[ProcessNumber];
	for(i=0;i<ProcessNumber;i++)
	{
		p[i].arrival_Time=ArrivalTime[i];
		p[i].services_Time=ServicesTime[i];
		p[i].key=i;
	}
   int temp;
	for(int i=0;i<ProcessNumber;i++)
		for(int j=i;j<ProcessNumber;j++)
			if(p[i].arrival_Time>p[j].arrival_Time)
			{	
				temp=p[i].arrival_Time;
				p[i].arrival_Time=p[j].arrival_Time;
				p[j].arrival_Time=temp;

				temp=p[i].services_Time;
				p[i].services_Time=p[j].services_Time;
				p[j].services_Time=temp;

				temp=p[i].key;
				p[i].key=p[j].key;
				p[j].key=temp;
                
			}
      */
	for(i=0;i<ProcessNumber;i++){
		if(NowTime>=ArrivalTime[i])
		{
			FinishTime[i]=NowTime+ServicesTime[i];
			NowTime=FinishTime[i];
		}
		else
		{
			NowTime=ArrivalTime[i]+ServicesTime[i];
			FinishTime[i]=NowTime;
		}

		WholeTime[i]=FinishTime[i]-ArrivalTime[i];
		WeightWholeTime[i]=(double)WholeTime[i]/ArrivalTime[i];
        sumWT+=WholeTime[i];
		sumWWT+=WeightWholeTime[i];
	}

	AverageWT_FCFS=sumWT/ProcessNumber;
	AverageWWT_FCFS=sumWWT/ProcessNumber;

}

void print(){
	cout.width(20);
	cout<<setw(10)<<"���ʱ��"<<setw(10)<<"��תʱ��"<<setw(10)<<"��Ȩ��תʱ��"<<endl;
	for(i=0;i<ProcessNumber;i++)
	{
		cout.width(20);
		cout<<setw(10)<<FinishTime[i]<<setw(10)<<WholeTime[i]<<setw(10)<<WeightWholeTime[i]<<endl;
	}

	cout<<"ƽ����תʱ��"<<AverageWT_FCFS<<endl<<"��Ȩƽ����תʱ��"<<AverageWWT_FCFS<<endl;
}
