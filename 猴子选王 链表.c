//链表求解
#include<stdio.h>
#include<stdlib.h>
typedef struct monkey
{
	int num;
	struct monkey *next;
 } Monkey,*PMon;
//函数声明
PMon creat(int m,int n);
PMon choose_king(PMon head,int m,int n);
void output(PMon head);
//主函数 
int main()
{
	int m,n;
	PMon head,king; 
	printf("请输入猴子个数m:");
	scanf("%d",&m);
	printf("\n报数规则n：");
	scanf("%d",&n);
	
	head=creat(m,n);
	king=choose_king(head,m,n);
	printf("\n王是第%d只猴子",king->num);
	
	return 0;
 } 
 //创建链表 
PMon creat(int m,int n)
{
	PMon head,current,prev;
	int i;
	head=(PMon)malloc(sizeof(Monkey));
	for(i=0;i<m;i++)
	{
		current=(PMon)malloc(sizeof(Monkey));//申请空间
		current->next=NULL;
		current->num=i+1;
		if(i==0)
		{
			head->next=current;
		}
		else
		{
			prev->next=current;
		}
		prev=current;
	}
	current->next=head->next;//建立循环 
	return head;
}
//找王
PMon choose_king(PMon head,int m,int n)
{
	int count,j;//count是圈中还在的猴子数，j是用来取余的报数变量 
	PMon p,prev;//prev是前一个结点，p是当前结点 
	j=0;
	prev=head;
	p=head->next;
	count=m;
	//printf("%d",p->num);
	while(count>1)//当圈中的猴子数大于1的时候，继续循环 
	{
		j++;//累加报数变量，这是第多少只猴子报数 
		if(j%n==0)//约等于这只猴子报到3 ，他出去 
		{
			count--;//队伍中猴子数量减一 
			if(count>=2)// 队伍中有两只及以上的猴子，可以继续 
			{
				prev->next=p->next;
				free(p);
				
				p=prev->next;
			}
			else//count=1
			{
				free(p);//王是prev 
				break;
			}
		}
		else
		{
			prev=p;
			p=p->next;
		}
		
	}
	return prev;
 } 
 //输出 
 void output(PMon head)
 {
 	PMon p;
 	p=head;
 	while(p->next!=NULL)
 	{
 		printf("num=%d\n",p->next->num);
 		p=p->next;
	 }
  } 

