#include<iostream>
#include<cstring>
#include<windows.h>
#include<cmath> 
#include<time.h>
#include<conio.h>
#include<stdio.h>
#include<stdlib.h>
 
#define WM_MYMSG	WM_USER+100	//�߳���Ϣ 
using namespace std;
 
const char space=' ';
const int TOP=15;
const int LEFT=50;
const int X=0;		//	���Ĭ�Ϻ�����
const int Y=4;		//	���Ĭ�������� 
int randomFlag = 1; //�������־ 
 
char arr[TOP][LEFT];	//��ͼ
 
int gwArrTop[TOP];	//���������� 
int gwArrLeft[TOP];	//����ĺ����� 
int gwTot;	//������ 
int fjTOP;	//�ɻ��������� 
int fjLeft; 	//�ɻ��ĺ����� 
int Score=0;	//�÷�
int Life=100;//���� 
int oldLife=100;//�ɵ�����
int oldScore=0;	//�÷�
 
extern "C"
{
	WINBASEAPI HWND WINAPI GetConsoleWindow();
}
 void SetPosition(int x,int y)	//���ù��λ�� ���У��У� 
{
    HANDLE winHandle;//���
    COORD pos = {x,y};
    winHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    //���ù��λ�� 
    SetConsoleCursorPosition(winHandle,pos); 
 }
 
int sjs(int a, int b) {			//����[x,y]������� 
	if (randomFlag) {
		randomFlag = 0;
		srand((unsigned int)time(NULL));
	}
 
	return (int)((double)rand() / ((RAND_MAX + 1.0) / (b - a + 1.0)) + a);
}
 
void print(){			//��ӡ��ͼ -�߽��ڵ� 
	SetPosition(X,Y); 
	gwTot=0;//����ͳ��
	int gw_i=0,gw_j=0;	 
	 
	for(int i=0;i<TOP;i++){	 
		for(int j=0;j<LEFT;j++){
			//���� 
			if(arr[i][j]=='N'){	//���й��� 
				if(arr[i-1][j]=='Y'){
					Score++;
					arr[i-1][j]=space;
					gwTot--;
				}
			} 
			
			
			if(arr[i][j]=='*'){		// arr[t][l]
				if(arr[i+1][j]=='1')
					Life--;
			}else if(arr[i][j]=='O'){	//��б�� 
				if(arr[i+1][j+1]=='1')
					Life--; 
			}else if(arr[i][j]=='0'){
				if(arr[i+1][j-1]=='1')
					Life--;
			}else if(arr[i][j]=='Y'){
				if(arr[i+1][j]=='1'||arr[i+1][j+1]=='1'||arr[i+1][j-1]=='1'||arr[i][j+1]=='1'||arr[i][j-1]=='1'){
					arr[i][j]=space;
					Life--;
				}
			}
			 
			 //��ɫ����
			if(arr[i][j]=='Y'){
				//���ֺڵ�
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY |FOREGROUND_RED);
				gwArrTop[gw_i++]=i;		//�������� 
				gwArrLeft[gw_j++]=j;
				gwTot++;				//������ͳ��
				
				cout<<arr[i][j];
			}else if(arr[i][j]=='O'||arr[i][j]=='0'){
				//��ɫ�ڵ�
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY |FOREGROUND_BLUE);
				cout<<arr[i][j]; 
			}else if(arr[i][j]=='*'){
				//���ֺڵ�
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY |FOREGROUND_RED | FOREGROUND_GREEN); 
				cout<<arr[i][j];
			}
			else{
			//��ɫ�ڵ�
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY |FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
				cout<<arr[i][j];
			}
			
		} 
		cout<<endl;
	}
}
 
void print_border(){			//��ӡ��ͼ�߽� 
 
	SetPosition(0,0);
	cout<<"�÷�:"<<Score<<"\t"<<"ʣ������ֵ:"<<Life<<endl;
	SetPosition(X,Y-1);
	cout<<"--------------------------------------------------"<<endl;
 
	SetPosition(X,Y); 
	  
	for(int i=0;i<TOP+2;i++){	 
		for(int j=0;j<LEFT+1;j++){
			//�߽� 
			if(i==TOP||j==LEFT){
				cout<<'-';
				continue;
			}
			if(i==TOP+1){
				cout<<"˵��:�������Ҽ��ƶ����س�������"<<endl;
				break; 
			}
			cout<<arr[i][j];  
		}
		cout<<endl;
	}
}
 
void FJ(){		//�ɻ������ʼ�� 
	int FJ_TOP=14; 
	int FJ_LEFT=24;
	
	fjTOP=FJ_TOP;
	fjLeft=FJ_LEFT;
	arr[FJ_TOP][FJ_LEFT]='1';
	arr[FJ_TOP-1][FJ_LEFT]='1';
	arr[FJ_TOP][FJ_LEFT+1]='1';
	arr[FJ_TOP][FJ_LEFT-1]='1';
}
void GW(){	//��������ʼ�� 
	int tot=sjs(1,4);	//���һ���ĸ�������
	int gwTOP;
	int gwLEFT;
	
	gwTot=tot;
	for(int i=0;i<tot;i++){
		gwTOP=sjs(0,5);
		gwLEFT=sjs(0,48);
		
		gwArrTop[i]=gwTOP;
		gwArrLeft[i]=gwLEFT;
		
		arr[gwTOP][gwLEFT]='Y';
		
	} 
}
 
 
int gwAct(){			//���������
	for(int i=0;i<gwTot;i++){
		int t1=gwArrTop[i];		//TOP
		int l1=gwArrLeft[i];	//Left
		arr[t1][l1]=space;
		int t=sjs(1,5);
		switch(t){
			case 1:
				if(t1<TOP-1){
					t1+=1;
					break;
				}
			case 2:
				if(l1<LEFT-1){
					l1+=1;
					break;
				}
			case 3:
				if(l1>0){
					l1-=1;
					break;
				}
			case 4:
				if(t1<TOP-1&&l1<LEFT-1){
					t1++;
					l1++;
					break;
				}
			case 5:
				if(t1<TOP-1&&l1>0){
					t1++;
					l1--;
					break;
				}
			default:
				if(t1<TOP-1){
					t1+=1;}
				break;
		}
		gwArrTop[i]=t1;
		gwArrLeft[i]=l1;
		arr[t1][l1]='Y';
		//�����ƶ����߽�Ĵ��� 
		if(t1>=TOP-2||l1<=0||l1==LEFT-1){
			arr[t1][l1]=space;
			gwTot--;
		}
		 
	}
}
int input(){			//����������� 
		int ch;
		ch=getch();	
			switch(ch)
			{
        		case 72:
					arr[fjTOP][fjLeft]=space;
					arr[fjTOP-1][fjLeft]=space;
					arr[fjTOP][fjLeft-1]=space;
					arr[fjTOP][fjLeft+1]=space;
					fjTOP-=1;
					arr[fjTOP][fjLeft]='1';
					arr[fjTOP-1][fjLeft]='1'; 
					arr[fjTOP][fjLeft-1]='1';
					arr[fjTOP][fjLeft+1]='1';
					break;//�� 
        		case 80:
					arr[fjTOP][fjLeft]=space;
					arr[fjTOP-1][fjLeft]=space;
					arr[fjTOP][fjLeft-1]=space;
					arr[fjTOP][fjLeft+1]=space;
					fjTOP+=1;
					arr[fjTOP][fjLeft]='1';
					arr[fjTOP-1][fjLeft]='1'; 
					arr[fjTOP][fjLeft-1]='1';
					arr[fjTOP][fjLeft+1]='1';
				 	break;//�� 
        		case 75:
					arr[fjTOP][fjLeft]=space;
					arr[fjTOP-1][fjLeft]=space;
					arr[fjTOP][fjLeft-1]=space;
					arr[fjTOP][fjLeft+1]=space;
					fjLeft-=1;
					arr[fjTOP][fjLeft]='1';
					arr[fjTOP-1][fjLeft]='1'; 
					arr[fjTOP][fjLeft-1]='1';
					arr[fjTOP][fjLeft+1]='1';
					break;//�� 
        		case 77:
					arr[fjTOP][fjLeft]=space;
					arr[fjTOP-1][fjLeft]=space;
					arr[fjTOP][fjLeft-1]=space;
					arr[fjTOP][fjLeft+1]=space;
					fjLeft+=1;
					arr[fjTOP][fjLeft]='1';
					arr[fjTOP-1][fjLeft]='1'; 
					arr[fjTOP][fjLeft-1]='1';
					arr[fjTOP][fjLeft+1]='1';
					break;//��
				case 13:
					arr[fjTOP-2][fjLeft]='N'; 
					break;//enter  �ɻ��ӵ� 
        		default:
               		return 0;
   			}	
   		return 1;
}
void sczd(){	//��������ӵ� 
	for(int i=0;i<gwTot;i++){
		int t1=gwArrTop[i];		//TOP
		int l1=gwArrLeft[i];	//Left
		int a=sjs(1,7);
		switch(a){			//����ӵ� 
			case 1:
				arr[t1+1][l1]='*';		//ֱ�� 
				break;
			case 2:arr[t1+1][l1+1]='O';	//��б�� 
				break;
			case 3:arr[t1+1][l1-1]='0';	//��б��
				break;
			case 4:arr[t1+1][l1]='*';		//ֱ�� 
				   arr[t1+1][l1+1]='O';	//��б��
				break;
			case 5:arr[t1+1][l1]='*';		//ֱ��
				   arr[t1+1][l1-1]='0';	//��б��
				break;
			case 6:arr[t1+1][l1+1]='O';	//��б�� 
				   arr[t1+1][l1-1]='0';	//��б��
				break;
			case 7:arr[t1+1][l1]='*';		//ֱ�� 
					arr[t1+1][l1+1]='O';	//��б�� 
					arr[t1+1][l1-1]='0';	//��б��
				break;
			default:
				arr[t1+1][l1]='*';		//ֱ��
				break;
		}
	}
	
}
void zddel(){	//�ӵ�����   
	for(int i=TOP-1;i>=0;i--){	 
		for(int j=LEFT-1;j>=0;j--){
			if(arr[i][j]=='*'&&arr[i+1][j]!='Y'){		//����ֱ���ӵ� 
				if(i<TOP-1&&j>0&&j<LEFT-1){
					arr[i][j]=space;
					arr[i+1][j]='*';
				}else{				//�ӵ���ʧ 
					arr[i][j]=space;
				}
			}else if(arr[i][j]=='O'&&arr[i+1][j+1]!='Y'){	//��б���ӵ� 
				if(i<TOP-1&&j<LEFT-1){
					arr[i][j]=space;
					arr[i+1][j+1]='O';
				}else{				//�ӵ���ʧ 
					arr[i][j]=space;
				}	
			}else if(arr[i][j]=='0'&&arr[i+1][j]!='Y')	//��б���ӵ�
			{
				if(i<TOP-1&&j>0){
					arr[i][j]=space;
					arr[i+1][j-1]='0';
				}else{				//�ӵ���ʧ 
					arr[i][j]=space;
				}
			}
		} 
	}
	for(int i=0;i<TOP;i++){	 
		for(int j=0;j<LEFT;j++){
			if(arr[i][j]=='N'){	//�ɻ��ӵ� 
				if(i>1&&j>1&&j<LEFT-2){
					arr[i][j]=space;
					arr[i-1][j]='N';
				}else{				//�ӵ���ʧ 
					arr[i][j]=space;
				}
			}
		} 
	}
}
 
 
//���߳�
DWORD WINAPI func4(LPVOID LpParameter)	//��ʹ�û���������Ҳ�����ӵ� 
{
	while(1)
	{
		sczd(); 
		Sleep(12000);	//12��	 
	}
	
	return 0;
}
 
DWORD WINAPI func3(LPVOID LpParameter)	//����ӵ��ƶ� 
{
	while(1)
	{
		gwAct();//���������
		zddel();//�ӵ�����
		Sleep(800);		//����ӵ��ٶȿ��� 
	}
	
	return 0;
}
 
DWORD WINAPI func2(LPVOID LpParameter)	//��׽���� 
{
	DWORD id = *(int*)LpParameter;
	while(1)
	{
		int ap=0;
		ap=input();
		if(ap==1)		//����
		{
			PostThreadMessage(id, WM_MYMSG, 0, 0);	
		}
	}
	return 0;
}
 
DWORD WINAPI func1(LPVOID LpParameter)	//����ӵ����� 
{
	MSG msg;
	HWND hwnd = GetConsoleWindow();
	while(1)
	{
		GetMessage(&msg,NULL,0,0);
		sczd();	//�����ӵ�
		if (msg.message == WM_MYMSG)	//����  ��ӹ���
		{
			int t=0;
			for(int i=0;i<TOP;i++){	 
				for(int j=0;j<LEFT;j++){
					if(arr[i][j]=='Y')
						t++;
				}
			}
			if(t<=1){
				GW();
			} 		
		}
		Sleep(1000);
	}
	
	return 0;
}
 
 
//���߳� 
int contrl(){
	DWORD id;
	HANDLE hthrd1 = CreateThread(NULL, 0, func1, NULL, 0, &id);
	HANDLE hthrd2 = CreateThread(NULL, 0, func2, &id, 0, 0);
	HANDLE hthrd3 = CreateThread(NULL, 0, func3, NULL, 0, 0);
	HANDLE hthrd4 = CreateThread(NULL, 0, func4, NULL, 0, 0);
	
	while(1){		
		print();//��ӡ��ͼ
		if(oldScore!=Score){
			oldScore=Score;
			print_border();
			continue;
		}
		if(oldLife!=Life){
			oldLife=Life;
			print_border();
			continue;
		} 
		if(Life<=0){
			break;
		}
		if(fjTOP<=0||fjTOP>TOP-1||fjLeft<=0||fjLeft>=LEFT-1){
			system("cls");//�����Ļ
			cout<<"����ɱ�ˣ�"<<"\t"<<"����ֵ:"<<Life<<endl;
			Sleep(3000);
			return 0; 
		} 
		Sleep(1);		//�ٶȿ��� 
	} 
}
int main(){
	memset(arr,space,sizeof(arr));	//��ͼ��ʼ��
	 
	FJ();//�ɻ������ʼ�� 
	GW(); //��������ʼ��
	sczd();//�����ӵ� 
	print_border();//�߽� 
	contrl();//������� 
	system("cls");//�����Ļ
	cout<<"��Ϸ�������÷�:"<<Score<<endl;
	Sleep(6000);
	return 0;
}