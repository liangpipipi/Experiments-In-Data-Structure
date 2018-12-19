/*
 某客店有N个等级的房间，第k级客房有A（k）个，每个房间有B（k）个单人床，以菜单调用方式设计为单身旅客分配床位以及离店时收
 回床位的程序。要求分配成功时，印出旅客姓名、年龄、性别、到达日期、客房等级、房间号及床位号；分配不成功时，允许更改房间
 等级，若不更改等级，印出"满客"提示。
 房间等级的描述，床位数，床位的编号，已经住了几个床位，床位主任
 结构体 等级 房间数 床位数 指针 
*/ 
//逻辑有点问题！！！ 
#include <stdio.h>
#include <stdlib.h>

struct Customer
{
	char name[20];
	int age;
	int sex;//性别，1是男性，2是女性 
	int data_of_arrival;//到达日期
};

typedef struct Room
{
	int roomlevel;//客房等级
	int roomnum;//客房编号 
	int bednum;//床位号 
	struct Customer customer; //顾客 
	struct Room *next;//结点的指针域 
}room,*proom;

 

//初始化旅店 
proom initialize_hotel(int roomlevel_amount)
{
	proom current,prev,head;
	int room_amount[50],bed_amount[50],i,j,k;
	
	printf("——————————初始化——————————\n");
	//printf("请输入旅店有多少个不同等级的房间：");
	//scanf("%d",&roomlevel_amount);
	
	for(i=0;i<roomlevel_amount;i++)
	{
		printf("\n请输入等级为%d的房间共有多少个:",i+1);
		scanf("%d",&room_amount[i]);
		printf("\n请输入等级为%d的房间每间有多少张床:",i+1);
		scanf("%d",&bed_amount[i]);
	}
	head=(proom)malloc(sizeof(room));//申请空间
	for(i=0;i<roomlevel_amount;i++)
	{
		for(j=0;j<room_amount[i];j++)
		{
			for(k=0;k<bed_amount[i];k++)
			{
				current=(proom)malloc(sizeof(room));
				
				current->roomlevel=i+1;
				current->roomnum=j+1;
				current->bednum=k+1;
				current->customer.age=0;
				current->customer.sex=0;
				current->customer.data_of_arrival=0;
				if(i==0&&j==0&&k==0) 
				{
					head->next=current;
					prev=current; 
					//printf("头结点初始化成功\n");
				}
				else
				{
					prev->next=current;
					prev=current;
				}
				//printf("房间%d%d%d建立成功  等级%d 房间号%d 床号%d\n\n",i,j,k,current->roomlevel,current->roomnum,current->bednum);
				
			}
		}
	 } 
	 current->next=NULL;
	 printf("——————————结束——————————\n\n");
	 return head;
}

//输出整个旅馆的床位信息
void inqury(proom head)
{
	printf("—————————床位信息—————————\n");
	proom p=head->next;
	while(p!=NULL)//循环至表尾
	{
		if(p->customer.age==0)
		{
			printf("等级%d 房间号%d 床号%d 未入住\n",p->roomlevel,p->roomnum,p->bednum);
		}
			
		else
		{
			printf("等级%d 房间号%d 床号%d 年龄%d 性别",p->roomlevel,p->roomnum,p->bednum,p->customer.age);
			if(p->customer.sex==1)
			{
				printf("男\n"); 
			}
			else
			{
				printf("女\n");
			}
		 } 		
		p=p->next;
	}
	printf("————————床位信息结束————————\n\n");
}

//入住
void check_in(proom head,int roomlevel_amount)
{
	printf("——————————入住——————————\n");
	int level;
	proom p;
	p=head;
	printf("亲爱的顾客您好，请问您需要哪类等级的房间？我们共有%d种房间供您选择。\n",roomlevel_amount);
	scanf("%d",&level);
	if(level>roomlevel_amount) 
	{
		printf("等级输入错误！请重新输入:\n");
		scanf("%d",&level);
	}
	while(p->roomlevel!=level&&p!=NULL)
	{
		p=p->next;
	}//当循环停下时，p->roomlevel=level，这是顾客要的房间
	while(p->roomlevel==level&&p!=NULL) //在这类房间中寻找空房 
	{
		if(p->customer.age!=0)//有人住了 
		{
			p=p->next; 
		}
		else//p->customer.age==0 空房 
		{
			break; 
		 } 	
	}
	if(p->roomlevel==level&&p->customer.age==0)//p是我们要找的等级的一间空房 
	{
		
		printf("\n请输入您的姓名：");
		scanf("%s",&p->customer.name);
		printf("请输入您的年龄：");
		scanf("%d",&p->customer.age);
		printf("请输入您的性别，1（男性）或2（女性）：");
		scanf("%d",&p->customer.sex);
		printf("请输入您的到达日期：(如20181107)");
		scanf("%d",&p->customer.data_of_arrival);
		
		printf("\n订房成功，您的房间等级是%d,房间号是%d,床位号是%d\n\n",p->roomlevel,p->roomnum,p->bednum);
	 } 
	 else
	 {
	 	printf("抱歉，您选择的类型已经没有空床位了，请重新选择\n\n");
	 }
	 printf("—————————订房结束—————————\n\n"); 
	//retuen 0;
 } 
 //退房
  void check_out(proom head)
{
	printf("——————————退房——————————\n");
  	int rolevel,ronum,benum;
  	proom p=head->next;
	printf("\n请输入您的房间等级，房间号及床位号：");
  	scanf("%d,%d,%d",&rolevel,&ronum,&benum);
  	while((p->roomlevel!=rolevel)||(p->roomnum!=ronum)||(p->bednum!=benum))
  	{
  		p=p->next;
	}
	p->customer.age=0;
	p->customer.sex='m';
	p->customer.data_of_arrival=0;
	printf("退房成功！\n");
	printf("—————————退房结束—————————\n\n");
}

//查看顾客信息 
void view_information(proom head)
{
	printf("————————查看顾客信息————————\n"); 
	int rolevel,ronum,benum;
  	proom p=head->next;
	printf("\n请输入顾客的房间等级，房间号及床位号：");
  	scanf("%d,%d,%d",&rolevel,&ronum,&benum);
  	//printf("%d,%d,%d",rolevel,ronum,benum);
  	while(((p->roomlevel!=rolevel)||(p->roomnum!=ronum)||(p->bednum!=benum))&(p!=NULL))
  	{
  		p=p->next;
  	//	printf("指针后移\n");
	}
	//printf("找到");
	if(p->customer.age!=0)
	{
		printf("顾客的姓名是%s,性别是",p->customer.name);
		if(p->customer.sex==1)
		{
			printf("男"); 
		}
		else
		{
			printf("女");
		}
		printf(",年龄%d,入住时间是%d\n\n",p->customer.age,p->customer.data_of_arrival);
	}	
	else
	{
		printf("房间未入住客人！\n\n");
	}
	printf("———————查看顾客信息结束———————\n\n");
}

//菜单
int item()
{
	int i;
	printf("——————————菜单——————————\n");
	printf("1——显示所有房间信息\n");
	printf("2——订房\n");
	printf("3——退房\n");
	printf("4——查看顾客信息\n");
	printf("0——退出系统\n");
	printf("输入选择:");
	scanf("%d",&i);
	printf("—————————菜单结束—————————\n\n");
	return i;
}
  int main()
{
	int i,roomlevel_amount;
		proom head;
  	printf("请输入旅店有多少个不同等级的房间：");
	scanf("%d",&roomlevel_amount);
	
	head=initialize_hotel(roomlevel_amount);
	i=item();
	while(i!=0)
	{
		switch(i)
		{
		case 1:inqury(head);break;
		case 2:check_in(head,roomlevel_amount);break;
		case 3:check_out(head);break;
		case 4:view_information(head);break; 
		case 0:{return 0;};break;
		default:break;
		}
		i=item();
	}
	printf("退出\n");
	return 0;
}
 
