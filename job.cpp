//ͷ�ļ�����
#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
//���ݶ���
int ram = 100;               //�ڴ��С
int tape = 4;                //�Ŵ�������
//�ṹ���������Զ���
struct work
{
	char workname[20];                //��������
	int workstarttime;                //��������ʱ��
	int workneedtime;                 //������Ҫʱ��
	int workentertime;                //��ҵ���е�ʱ��
	int workneedram;                  //��ҵ��Ҫ�ڴ�
	int workneedtape;                 //��ҵ��Ҫ�ĴŴ���
	int workflag;                     //��ҵ��־
	int workfinishtime;               //��ҵ���ʱ��
}work;
//��������
void captionFcfs();                                          //�ȵ��ȷ�������
void workFcfsRun(struct work *job,int worknum);              //�ȵ��ȷ���ʵ��
//������ʵ��
void main()
{
	int i = 0;
	int worknum = 0;
	struct work* job;
	printf("��������ҵ����!\n");
	scanf("%d",&worknum);
	job = (struct work*)malloc(worknum*sizeof(struct work));                  //��̬����ṹ������
	for(i = 0; i < worknum;i ++)							                  //ʵ�ֲ�ȷ������ҵ����
	{
		printf("�������ҵ�����Կո�ָ�!\n");
		printf("��ҵ%d������    ����ʱ��    ��������ʱ�䣨�֣�    ��Ҫ�ڴ棨K��  ��Ҫ�Ŵ�����̨��\n" , i+1);
		scanf("%s",&job[i].workname);
		scanf("%d",&job[i].workstarttime);
		scanf("%d",&job[i].workneedtime);
		scanf("%d",&job[i].workneedram);
		scanf("%d",&job[i].workneedtape);
		job[i].workflag = 0;                                    //��������ҵ����
		job[i].workfinishtime = 999;
		system("cls");
	}
		captionFcfs();
		workFcfsRun(job,worknum);                               //��ҵ�����ȵ��ȹ���
}
void welcome()
{
	printf("�������������...\n");
	getch();
	system("cls");
}
void captionFcfs()
{
	
	printf("�����ȷ�������㷨\n");
	getch();
	system("cls");
}
void workFcfsRun(struct work *job,int worknum)
{
	int i = 0;
	int tem = 0;
	int temp = 0;
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
			if(time == job[i].workstarttime)                       //ʱ�����е���ҵ�����ʱ��
				job[i].workflag = 1;                               //��ҵ����׼������
			if((job[i].workflag == 1)&&                            //��ҵ׼��
				((ram - job[i].workneedram) >= 0)&&                //�ڴ��㹻
				((tape - job[i].workneedtape) >= 0))               //�Ŵ����㹻
			{
				ram -= job[i].workneedram;                         //�ڴ����
				tape -= job[i].workneedtape;                       //�Ŵ���ʹ��
				job[i].workflag = 2;                               //��ҵ�������״̬
			}
			if((job[i].workflag == 2)&&(flag == 0))                //��ҵ����
			{
				job[i].workentertime = time;
				flag = 1;
			}
			if((job[i].workflag == 2)&&
				(time == (job[i].workentertime + job[i].workneedtime))&&
				(flag == 1))
			{
				job[i].workflag = 3;                                     //��ҵ�������
				ram += job[i].workneedram;                               //�ڴ��ͷ�
				tape += job[i].workneedtape;                             //�Ŵ�����ԭ
				flag = 0;                                                //cpu�ͷ�
				job[i].workfinishtime = time;
			}
			if((job[i].workflag == 3)&&(time == job[i].workfinishtime))
			{
				printf("��ҵ%s�Ѿ����!\n",job[i].workname);
				printf("��ʼ��ʱ��%d\n",job[i].workentertime);
				printf("���е�ʱ��%d\n",job[i].workfinishtime - job[i].workentertime);
				printf("��ɵ�ʱ��%d\n",job[i].workfinishtime);
			}
		}
		if(flag == 0)                                        //������һ��
		{
			time--;
		}
	}
	printf("���Ϊ:\n");
	for(i = 0;i < worknum;i++)
	{
		printf("%d",job[i].workfinishtime - job[i].workstarttime);
		tem += job[i].workfinishtime - job[i].workstarttime;
		printf("+");
	}
	printf("\b=%d\n",tem);
	printf("ÿ����ҵ��ƽ��ʱ��Ϊ%d\n",tem/worknum);
}
