#pragma warning(disable:4996)
#pragma warning(disable:2001)
#include<iostream>
#include<string.h>
#include<stdio.h>
using namespace std;
#define N 6 // 航班数
// 航班信息
typedef struct flight
{
	char flight_number[10]; // 航班号
	char start_address[30]; // 起飞站
	char arrived_address[30]; // 终点站
	char work_date[20]; // 班期
	char start_time[6]; // 起飞时间
	char arrived_time[6]; // 到达时间
	char FlightType[4]; // 机型
	int fare; // 票价
}DataType;
struct flight Flight[N];//定义航班数组
//按航班号进行基数排序
typedef char KeyType;
#define D 7    // D 为排序码的最大位数
#define R 'a' // R 为基数 , 这里为小于字母 'a' 代表的整型值
struct Node; // 单链表结点类型
typedef struct Node RadixNode;
struct Node
{
	KeyType key[D]; // 关键字
	DataType info; // 数据信息
	RadixNode* next;
};
typedef RadixNode* RadixList;
typedef struct QueueNode //队列指针
{
	RadixNode* f; // 对列的头指针
	RadixNode* e; // 对列的尾指针
}Queue;
Queue queue[R];// 用队列表示桶
void radixSort(RadixList* plist, int d, int r)
{
	int i, j, k;
	RadixNode* p, * head;
	head = (*plist)->next;
	for (j = d - 1; j >= 0; j--) // 进行 d 次分配和收集
	{
		p = head;
		for (i = 0; i < r; i++)
		{
			queue[i].f = NULL; queue[i].e = NULL; // 清队列
		}
		while (p != NULL)
		{
			k = p->key[j]; // 按排序码的第 j 个分量进行分配
			if (queue[k].f == NULL) queue[k].f = p; //  若第 k 个堆为空，则当前记录为队头
			else (queue[k].e)->next = p; //  否则当前记录链接到第 k 队的队尾
			queue[k].e = p;
			p = p->next;
		}
		i = 0;
		while (queue[i].f == NULL) i++; //  从 r 个队列中找出第一个非空的队列
		p = queue[i].e; head = queue[i].f; //head 为收集链表的头指针
		for (i++; i < r; i++)
			if (queue[i].f != NULL)
			{
				p->next = queue[i].f; p = queue[i].e;
			} //  收集非空队列
		p->next = NULL;
	}
	(*plist)->next = head;
}
// 初始化航班信息
struct Node element[N + 1] = {
 " "," "," "," "," "," "," "," ",0,NULL,// 表头
 "CA1544","CA1544","合肥","北京"," 1.2.4.5 ","1055","1240","733",960,NULL,
 "MU5341","MU5341","上海","广州","  每 日  ","1420","1615","M90",1280,NULL,
 "CZ3869","CZ3869","重庆","深圳","  2.4.6  ","0855","1035","733",1010,NULL,
 "MU3682","MU3682","桂林","南京","2.3.4.6.7","2050","2215","M90",1380,NULL,
 "HU1836","HU1836","上海","北京","  每 日  ","0940","1120","738",1250,NULL,
 "CZ3528","CZ3528","成都","厦门","1.3.4.5.7","1510","1650","CRJ",1060,NULL,
};

//信   息   显   示
//显示主体信息
void Cout_info2_1(Node p[])//方式一
{
	cout << "   " << p->info.flight_number;
	cout << "   " << p->info.start_time;
	cout << "   " << p->info.arrived_time;
	cout << "   " << p->info.start_address;
	cout << "   " << p->info.arrived_address;
	cout << "   " << p->info.work_date;
	cout << "   " << p->info.FlightType;
	cout << "   " << p->info.fare << "元" << endl;
}
void Cout_info2_2(flight F[], int i)//方式二
{
	cout << "   " << F[i].flight_number;
	cout << "   " << F[i].start_time; 
	cout << "   " << F[i].arrived_time;
	cout << "   " << F[i].start_address;
	cout << "   " << F[i].arrived_address;
	cout << "   " << F[i].work_date;
	cout << "   " << F[i].FlightType;
	cout << "   " << F[i].fare << "元" << endl;
}

//显示所有航班信息
void output_ALL_info1(Node element[])//方式一
{
	cout << "   航班号  起飞时间 到达时间 起飞站 终点站     航班期     机型   票价  " << endl;
	RadixList p = element;
	p = p->next;
	while (p != NULL)
	{
		Cout_info2_1(p);
		p = p->next;
	}
	cout << endl;
}
void output_ALL_info2(flight F[])//方式二
{
	for (int i = 0; i < N; i++)
	{
		Cout_info2_2(F, i);
	}
	cout << endl;
}
//信息复制
//将排好的序列（链表）转化为顺序存储形式
void copy(flight F[], Node element[])
{
	RadixList p = element;
	p = p->next;
	int i;
	for (i = 0; i < N && p != NULL; i++)
	{
		strcpy(F[i].flight_number, p->info.flight_number); 
		strcpy(F[i].start_time, p->info.start_time);
		strcpy(F[i].arrived_time, p->info.arrived_time); 
		strcpy(F[i].start_address, p->info.start_address); 
		strcpy(F[i].arrived_address, p->info.arrived_address); 
		strcpy(F[i].work_date, p->info.work_date);
		strcpy(F[i].FlightType, p->info.FlightType); 
		F[i].fare = p->info.fare;
		p= p->next;
	}
}

//查询系统
//通过航班号实现二分查找
void F_By_FN(flight F[])
{
	int low = 0, high = N, mid;
	char Num[10];
	cout << "请输入你要查询的航班号：";
	cin >> Num;
	while (low <= high)
	{
		mid = (low + high) / 2;
		if (strcmp(Num, F[mid].flight_number) == 0)
		{
			Cout_info2_2(F, mid);
			break;
		}
		else if (strcmp(Num, F[mid].flight_number) < 0)
			high = mid - 1;
		else 
			low = mid + 1;
	}
}
//顺序查找
//通过起飞/到达时间查询
void F_By_Time(flight F[], int Time)
{
	int i;
	char T[6];
	cout << "请输入您要查询的航班的起飞/抵达时间：";
	cin >> T;
	for (i = 0; i < N; i++)
	{
		if (Time == 1)//按起飞时间查询
		{
			if (strcmp(T, F[i].start_time) == 0)
				Cout_info2_2(F, i);
			/*else if ((strcmp(T, F[i].start_time) > 0) || (strcmp(T, F[i].start_time) < 0))
				cout << "无此航班信息，可能是输入错误" << endl;
			break;*/
		}
		if (Time == 2)//按抵达时间查询
		{
			if (strcmp(T, F[i].arrived_time) == 0)
				Cout_info2_2(F, i);
			/*else if ((strcmp(T, F[i].arrived_time)) > 0 || (strcmp(T, F[i].arrived_time)) < 0)
			    cout << "无此航班信息，可能是输入错误" << endl;
			break;*/
		}
	}
}
void F_By_Address(flight F[], int AD)
{
	int i;
	char str[30];
	cout << "请输入你要查询的航班的起飞/到达地点：";
	cin >> str;
	for (i = 0; i < N+1; i++)
	{
		if (AD == 1)
		{
			if (strcmp(str, F[i].start_address) == 0)
				Cout_info2_2(F, i);
			/*else if ((strcmp(str, F[i].start_address) > 0) || (strcmp(str, F[i].start_address) < 0))
				cout << "无此航班信息，可能是输入错误" << endl;
			break;*/
		}
		if (AD == 2)
		{
			if (strcmp(str, F[i].arrived_address) == 0)
				Cout_info2_2(F, i);
			/*else if ((strcmp(str, F[i].arrived_address) > 0) || (strcmp(str, F[i].arrived_address) < 0))
				cout << "无此航班信息，可能是输入错误" << endl;
			break;*/
		}
	}
}
//通过票价范围查询
void F_By_fare(flight F[])
{
	int T1, T2, i;
	cout << "请输入你要查询航班的最低票价:";
	cin >> T1;
	cout << "请输入你要查询航班的最高票价:";
	cin >> T2;
	for (i = 0; i < N; i++)
	{
		if (T1 <= F[i].fare && T2 >= F[i].fare)
			Cout_info2_2(F,i);
	}
	//cout << "对不起，没有找到合适您的航班，重新尝试" << endl;
}

//服务菜单
void mainmenu()
{
	char ch;
	int y;
	cout << "          航班信息的查询与检索          " << endl;
	cout << "========================================" << endl;
	cout << "=                主菜单                =" << endl;
	cout << "=            1.按航班号查询            =" << endl;
	cout << "=           2.按起飞时间查询           =" << endl;
	cout << "=           3.按到达时间查询           =" << endl;
	cout << "=           4.按起飞地点查询           =" << endl;
	cout << "=           5.按目的地点查询           =" << endl;
	cout << "=           6.按票价范围查询           =" << endl;
	cout << "=            7.查询所有航班            =" << endl;
	cout << "=                0.退出                =" << endl;
	cout << "========================================" << endl;
	while (1)
	{
		cout << "请输入服务命令：" << endl;
		cin >> y;
		switch (y)
		{
		case 1:
			F_By_FN(Flight);
			break;
		case 2:
			F_By_Time(Flight, 1);
			break;
		case 3:
			F_By_Time(Flight, 2);
			break;
		case 4:
			F_By_Address(Flight, 1);
			break;
		case 5:
			F_By_Address(Flight, 2);
			break;
		case 6:
			F_By_fare(Flight);
			break;
		case 7:
			output_ALL_info1(element);
			break;
		case 0:
			cout << "感谢使用" << endl;
			return;
		}
		cout << "是否继续?(Y/N)：";
		cin >> ch;
		if (ch == 'N' || ch == 'n')
			break;
	}
}
int main()
{
	RadixList p = element;
	for (int i = 0; i < N; i++)
		element[i].next = &element[i + 1];
	element[6].next = NULL;
	radixSort(&p, D, R);
	copy(Flight, element);
	cout << "单击任意键进入系统" << endl;
	getchar();
	cout << endl;
	mainmenu();
	return 0;
 }