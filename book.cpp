//头文件包含
#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
//数据定义
int ram = 100;
int tape = 4;
//函数声明
struct work
{
	char workname[20];   //工作名称
	int workstarttime;   //工作进入时间
	int workneedtime;    //工作需要时间
	int workentertime;   //作业运行的时间
	int workneedram;     //作业需要内存
	int workneedtape;     //作业需要的磁带机
	int workflag;         //作业标志
	int workfinishtime;    //作业完成时间
}work;

void welcome()
{
	printf(" 操作系统实验1多道程序的模拟实现程序\n");
	printf("先来先服务调度算法\n");
	printf("短作业优先算法\n");
	printf("首先请输入作业数据，然后选择工作方式\n");
	printf("按下任意键继续...\n");
	getch();
	system("cls");
}
void workSjfRun(struct work *job,int worknum)
{
}
void workFcfsRun(struct work *job,int worknum)
{
	int i = 0;
	int tem = 0;
	int flag = 0;
	int time = -1;
	int sum = 2;
	for(i = 0;i < worknum;i++)
	{
		sum += job[i].workneedtime;
	}
	while(sum--)
	{
		time++;
		for(i = 0; i < worknum; i++)
		{
			if(time == job[i].workstarttime)             //运行到作业进入的时间
				job[i].workflag = 1;                     //作业进入准备队列
			if((job[i].workflag == 1)&&                  //作业准备
				((ram - job[i].workneedram) >= 0)&&      //内存足够
				((tape - job[i].workneedtape) >= 0))     //磁带机足够
			{
				ram -= job[i].workneedram;                //内存分配
				tape -= job[i].workneedtape;              //磁带机使用
				job[i].workflag = 2;                      //作业进入就绪状态
			}
			if((job[i].workflag == 2)&&(flag == 0))        //作业运行
			{
				job[i].workentertime = time;
				flag = 1;
			}
			if((job[i].workflag == 2)&&
				(time == (job[i].workentertime + job[i].workneedtime))&&
				(flag == 1))
			{
				job[i].workflag = 3;                      //作业运行完毕
				ram += job[i].workneedram;                //内存释放
				tape += job[i].workneedtape;              //磁带机还原
				flag = 0;                                 //u释放
				job[i].workfinishtime = time;
			}
			if((job[i].workflag == 3)&&(time == job[i].workfinishtime))
			{
				printf("作业%s已经完成!\n",job[i].workname);
				printf("开始的时间%d\n",job[i].workentertime);
				printf("运行的时间%d\n",job[i].workfinishtime - job[i].workentertime);
				printf("完成的时间%d\n",job[i].workfinishtime);
			}
		}
	}
	printf("结果为:\n");
	for(i = 0;i < worknum;i++)
	{
		printf("%d",job[i].workfinishtime - job[i].workstarttime);
		tem += job[i].workfinishtime - job[i].workstarttime;
		printf("+");
	}
	printf("\b=%d\n",tem);
	printf("每个作业的平均时间为%d\n",tem/worknum);
}
void main()
{
	int i = 0;
	int worktype = 0;                        //默认先到先工作方式
	int worknum = 0;
	struct work* job;
	welcome();
	printf("请输入作业数量!\n");
	scanf("%d",&worknum);
	job = (struct work*)malloc(worknum*sizeof(struct work));
	for(i = 0; i < worknum;i ++)
	{
		printf("输入的作业数据以空格分隔!\n");
		printf("作业%d的名称 进入时间 估计运行时间（分）需要内存（K）需要磁带机（台）\n" , i+1);
		scanf("%s",&job[i].workname);
		scanf("%d",&job[i].workstarttime);
		scanf("%d",&job[i].workneedtime);
		scanf("%d",&job[i].workneedram);
		scanf("%d",&job[i].workneedtape);
		job[i].workflag = 0;                      //刚载入作业数据
		job[i].workfinishtime = 999;
		system("cls");
	}
	printf("请选择工作方式:\n");
	printf("\n\n1.先来先服务调度算法\n\n");
	printf("2.短作业优先算法\n\n");
	scanf("%d",&worktype);
	system("cls");
	
	if(worktype == 1)                            //1表示先到先工作，2表示短作业工作
	{
		workFcfsRun(job,worknum);                //先到先工作
	}
	else if(worktype == 2)
	{
		workSjfRun(job,worknum);                 //短作业优先
	}
	else
	{
		printf("哎呀!\n出错了!\n请重新启动!\n");
		getch();
		return;
	}
}