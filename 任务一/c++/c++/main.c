#include<iostream>
#include<cstring>
#include<windows.h>
#include<cmath> 
#include<time.h>
#include<conio.h>
#include<stdio.h>
#include<stdlib.h>
 
#define WM_MYMSG	WM_USER+100	//线程消息 
using namespace std;
 
const char space=' ';
const int TOP=15;
const int LEFT=50;
const int X=0;		//	光标默认横坐标
const int Y=4;		//	光标默认纵坐标 
int randomFlag = 1; //随机数标志 
 
char arr[TOP][LEFT];	//地图
 
int gwArrTop[TOP];	//怪物纵坐标 
int gwArrLeft[TOP];	//怪物的横坐标 
int gwTot;	//怪物数 
int fjTOP;	//飞机的纵坐标 
int fjLeft; 	//飞机的横坐标 
int Score=0;	//得分
int Life=100;//生命 
int oldLife=100;//旧的生命
int oldScore=0;	//得分
 
extern "C"
{
	WINBASEAPI HWND WINAPI GetConsoleWindow();
}
 void SetPosition(int x,int y)	//设置光标位置 （列，行） 
{
    HANDLE winHandle;//句柄
    COORD pos = {x,y};
    winHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    //设置光标位置 
    SetConsoleCursorPosition(winHandle,pos); 
 }
 
int sjs(int a, int b) {			//返回[x,y]的随机数 
	if (randomFlag) {
		randomFlag = 0;
		srand((unsigned int)time(NULL));
	}
 
	return (int)((double)rand() / ((RAND_MAX + 1.0) / (b - a + 1.0)) + a);
}
 
void print(){			//打印地图 -边界内的 
	SetPosition(X,Y); 
	gwTot=0;//怪物统计
	int gw_i=0,gw_j=0;	 
	 
	for(int i=0;i<TOP;i++){	 
		for(int j=0;j<LEFT;j++){
			//计算 
			if(arr[i][j]=='N'){	//击中怪物 
				if(arr[i-1][j]=='Y'){
					Score++;
					arr[i-1][j]=space;
					gwTot--;
				}
			} 
			
			
			if(arr[i][j]=='*'){		// arr[t][l]
				if(arr[i+1][j]=='1')
					Life--;
			}else if(arr[i][j]=='O'){	//右斜线 
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
			 
			 //颜色控制
			if(arr[i][j]=='Y'){
				//红字黑底
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY |FOREGROUND_RED);
				gwArrTop[gw_i++]=i;		//怪物坐标 
				gwArrLeft[gw_j++]=j;
				gwTot++;				//怪物数统计
				
				cout<<arr[i][j];
			}else if(arr[i][j]=='O'||arr[i][j]=='0'){
				//蓝色黑底
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY |FOREGROUND_BLUE);
				cout<<arr[i][j]; 
			}else if(arr[i][j]=='*'){
				//黄字黑底
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY |FOREGROUND_RED | FOREGROUND_GREEN); 
				cout<<arr[i][j];
			}
			else{
			//白色黑底
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY |FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
				cout<<arr[i][j];
			}
			
		} 
		cout<<endl;
	}
}
 
void print_border(){			//打印地图边界 
 
	SetPosition(0,0);
	cout<<"得分:"<<Score<<"\t"<<"剩余生命值:"<<Life<<endl;
	SetPosition(X,Y-1);
	cout<<"--------------------------------------------------"<<endl;
 
	SetPosition(X,Y); 
	  
	for(int i=0;i<TOP+2;i++){	 
		for(int j=0;j<LEFT+1;j++){
			//边界 
			if(i==TOP||j==LEFT){
				cout<<'-';
				continue;
			}
			if(i==TOP+1){
				cout<<"说明:上下左右键移动，回车键攻击"<<endl;
				break; 
			}
			cout<<arr[i][j];  
		}
		cout<<endl;
	}
}
 
void FJ(){		//飞机坐标初始化 
	int FJ_TOP=14; 
	int FJ_LEFT=24;
	
	fjTOP=FJ_TOP;
	fjLeft=FJ_LEFT;
	arr[FJ_TOP][FJ_LEFT]='1';
	arr[FJ_TOP-1][FJ_LEFT]='1';
	arr[FJ_TOP][FJ_LEFT+1]='1';
	arr[FJ_TOP][FJ_LEFT-1]='1';
}
void GW(){	//随机怪物初始化 
	int tot=sjs(1,4);	//随机一到四个个怪物
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
 
 
int gwAct(){			//怪物随机动
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
		//怪物移动到边界的处理 
		if(t1>=TOP-2||l1<=0||l1==LEFT-1){
			arr[t1][l1]=space;
			gwTot--;
		}
		 
	}
}
int input(){			//处理键盘输入 
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
					break;//上 
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
				 	break;//下 
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
					break;//左 
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
					break;//右
				case 13:
					arr[fjTOP-2][fjLeft]='N'; 
					break;//enter  飞机子弹 
        		default:
               		return 0;
   			}	
   		return 1;
}
void sczd(){	//生成随机子弹 
	for(int i=0;i<gwTot;i++){
		int t1=gwArrTop[i];		//TOP
		int l1=gwArrLeft[i];	//Left
		int a=sjs(1,7);
		switch(a){			//随机子弹 
			case 1:
				arr[t1+1][l1]='*';		//直线 
				break;
			case 2:arr[t1+1][l1+1]='O';	//右斜线 
				break;
			case 3:arr[t1+1][l1-1]='0';	//左斜线
				break;
			case 4:arr[t1+1][l1]='*';		//直线 
				   arr[t1+1][l1+1]='O';	//右斜线
				break;
			case 5:arr[t1+1][l1]='*';		//直线
				   arr[t1+1][l1-1]='0';	//左斜线
				break;
			case 6:arr[t1+1][l1+1]='O';	//右斜线 
				   arr[t1+1][l1-1]='0';	//左斜线
				break;
			case 7:arr[t1+1][l1]='*';		//直线 
					arr[t1+1][l1+1]='O';	//右斜线 
					arr[t1+1][l1-1]='0';	//左斜线
				break;
			default:
				arr[t1+1][l1]='*';		//直线
				break;
		}
	}
	
}
void zddel(){	//子弹处理   
	for(int i=TOP-1;i>=0;i--){	 
		for(int j=LEFT-1;j>=0;j--){
			if(arr[i][j]=='*'&&arr[i+1][j]!='Y'){		//怪物直线子弹 
				if(i<TOP-1&&j>0&&j<LEFT-1){
					arr[i][j]=space;
					arr[i+1][j]='*';
				}else{				//子弹消失 
					arr[i][j]=space;
				}
			}else if(arr[i][j]=='O'&&arr[i+1][j+1]!='Y'){	//右斜线子弹 
				if(i<TOP-1&&j<LEFT-1){
					arr[i][j]=space;
					arr[i+1][j+1]='O';
				}else{				//子弹消失 
					arr[i][j]=space;
				}	
			}else if(arr[i][j]=='0'&&arr[i+1][j]!='Y')	//左斜线子弹
			{
				if(i<TOP-1&&j>0){
					arr[i][j]=space;
					arr[i+1][j-1]='0';
				}else{				//子弹消失 
					arr[i][j]=space;
				}
			}
		} 
	}
	for(int i=0;i<TOP;i++){	 
		for(int j=0;j<LEFT;j++){
			if(arr[i][j]=='N'){	//飞机子弹 
				if(i>1&&j>1&&j<LEFT-2){
					arr[i][j]=space;
					arr[i-1][j]='N';
				}else{				//子弹消失 
					arr[i][j]=space;
				}
			}
		} 
	}
}
 
 
//多线程
DWORD WINAPI func4(LPVOID LpParameter)	//即使用户不操作，也产生子弹 
{
	while(1)
	{
		sczd(); 
		Sleep(12000);	//12秒	 
	}
	
	return 0;
}
 
DWORD WINAPI func3(LPVOID LpParameter)	//怪物、子弹移动 
{
	while(1)
	{
		gwAct();//怪物随机动
		zddel();//子弹处理
		Sleep(800);		//怪物、子弹速度控制 
	}
	
	return 0;
}
 
DWORD WINAPI func2(LPVOID LpParameter)	//捕捉键盘 
{
	DWORD id = *(int*)LpParameter;
	while(1)
	{
		int ap=0;
		ap=input();
		if(ap==1)		//按键
		{
			PostThreadMessage(id, WM_MYMSG, 0, 0);	
		}
	}
	return 0;
}
 
DWORD WINAPI func1(LPVOID LpParameter)	//怪物、子弹生成 
{
	MSG msg;
	HWND hwnd = GetConsoleWindow();
	while(1)
	{
		GetMessage(&msg,NULL,0,0);
		sczd();	//生成子弹
		if (msg.message == WM_MYMSG)	//按键  添加怪物
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
 
 
//多线程 
int contrl(){
	DWORD id;
	HANDLE hthrd1 = CreateThread(NULL, 0, func1, NULL, 0, &id);
	HANDLE hthrd2 = CreateThread(NULL, 0, func2, &id, 0, 0);
	HANDLE hthrd3 = CreateThread(NULL, 0, func3, NULL, 0, 0);
	HANDLE hthrd4 = CreateThread(NULL, 0, func4, NULL, 0, 0);
	
	while(1){		
		print();//打印地图
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
			system("cls");//清空屏幕
			cout<<"你自杀了！"<<"\t"<<"生命值:"<<Life<<endl;
			Sleep(3000);
			return 0; 
		} 
		Sleep(1);		//速度控制 
	} 
}
int main(){
	memset(arr,space,sizeof(arr));	//地图初始化
	 
	FJ();//飞机坐标初始化 
	GW(); //随机怪物初始化
	sczd();//生成子弹 
	print_border();//边界 
	contrl();//总体控制 
	system("cls");//清空屏幕
	cout<<"游戏结束！得分:"<<Score<<endl;
	Sleep(6000);
	return 0;
}