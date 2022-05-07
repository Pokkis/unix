/**
   @ 建立线性顺序表
   @ 2017.7.07
   @ author 陈德勇
*/
#include <stdio.h>
#include <stdlib.h>
#define MAXSISE 50  //线性顺序表的最大长度
typedef struct
{	int num;
	char cityName[20];
	char cityIntroduce[50];
}cityIinformasion;
typedef struct
{	cityIinformasion date[MAXSISE];
	int length;
}SqList;
void InitList(SqList *&L); //线性表的初始化，构建一个长度为零的线性表
void DestroyList(SqList *&L); //摧毁线性表，释放所占的内存空间
void ListEmpty(SqList *L);  //检查线性表是否为空，为空输出0
void ListLength(SqList *L);//查看当前线性表长度
void DispList(SqList *L);   //将线性表的值域和序号打印出来
void GetElem(SqList *L,int n);  //根据序号查找元素，并打印出来
void ListIsert(SqList *L,int n,cityIinformasion e);  //插入一个元素
void ListDelete(SqList *&L,int n); //删除一个元素
int main()
{	printf("##############################################\n");
    printf("               线性表                  \n" );
	printf("1.初始化       2.销毁	3.判断是否为空表\n");
	printf("4.表长度       5.输出	6.按序号查找	\n");
	printf("7.插入         8.删除	9.退出	  \n");
	printf("##############################################\n");
	int choice;
	int index;
	int tuichu=0;
	SqList *Q;
	cityIinformasion s;
	while(1)
	{
		printf("请选择你做的操作\n");
		scanf("%d",&choice);
		switch(choice)
		{	
			case 1:InitList(Q);break;


			case 2:DestroyList(Q);break;	


			case 3:ListEmpty(Q);break;

				
			case 4:ListLength(Q);break;	


			case 5:DispList(Q);break;


			case 6:printf("请输入你要查找的序号");
				   scanf("%d",&index);
			       GetElem(Q,index);break;


			case 7:printf("请输入你要添加的位置\n");
				   scanf("%d",&index);
				   if(Q->length!=0){
					   if(index<0||index>Q->length){printf("您输入的操作有误，请重新输入");break;}}
				   else
					   if(index!=1){printf("此表为空您需要在1的位置插入一个元素哦！");break;}
				   printf("请输入你添加城市的区号，城市名，说明，以空格隔开\n");
				   scanf("%d %s %s",&s.num,&s.cityName,&s.cityIntroduce);
				   ListIsert(Q,index,s);break;


			case 8:printf("请输入你要删除的序号");
				   scanf("%d",&index);
				   if(index<1||index>Q->length){printf("您输入的操作有误，请重新输入");break;}
				   ListDelete(Q,index);break;

			case 9:tuichu=1;break;
			default :printf("您输入的操作有误，请重新输入");
		}
		if(tuichu==1)break;
	}

	return 0;
}
/*
线性表的初始化，构建一个长度为零的线性表
*/
void InitList(SqList *&L)
{
 L=(SqList *)malloc(sizeof(SqList));
 L->length=0;
 printf("初始化成功\n");
}
/*
  摧毁线性表，释放所占的内存空间
*/
void DestroyList(SqList *&L)
{
	free(L);printf("此表成功摧毁\n");
}
/*
    检查线性表是否为空，为空输出1
*/
void ListEmpty(SqList *L)
{
	(L->length==0)?printf("此表是空表\n"):printf("此表不是空表\n");
}
/*
    查看当前线性表长度
*/
void ListLength(SqList *L)
{
   printf("当前线性顺序表长度为%d\n",L->length);
}
/*
    将线性表的值域和序号打印出来
*/
void DispList(SqList *L)
{
	int i;
    if(L->length==0)printf("此表为空，您还不能打印哦!");
	else
	{	   printf("序号		区号		城市名		说明\n");
	     for(i=0;i<L->length;i++)
		{
		   
		   printf("%d		%d		%s		%s\n",i+1,L->date[i].num,L->date[i].cityName,L->date[i].cityIntroduce);
		
		}
    }

}
/*
    根据序号查找元素，并打印出来
*/
void GetElem(SqList *L,int n)
{if(n-1>L->length||n-1<0)printf("您输入的序号有误，请重新选择操作\n");
 else
printf("序号：%d 区号：%d 城市名：%s 说明：%s\n",n,L->date[n-1].num,L->date[n-1].cityName,L->date[n-1].cityIntroduce);
}
/*
   插入一个元素
*/
void ListIsert(SqList *L,int n,cityIinformasion e)
{
	int i;
	for(i=L->length;i>n;i--)
	{
	   L->date[i]=L->date[i-1];
	}
	L->date[n-1]=e;
	L->length++;
	printf("插入第%d个元素成功\n",n);
}
/*
   删除一个元素
*/
void ListDelete(SqList *&L,int n)
{
	int i;
	for(i=n;i<L->length;i++)
	{
	   L->date[i-1]=L->date[i];
	}
    L->length--;
	printf("删除第%d个元素成功\n",&n);
}
