//�������
#include<stdio.h>
#include<stdlib.h>
typedef struct monkey
{
	int num;
	struct monkey *next;
 } Monkey,*PMon;
//��������
PMon creat(int m,int n);
PMon choose_king(PMon head,int m,int n);
void output(PMon head);
//������ 
int main()
{
	int m,n;
	PMon head,king; 
	printf("��������Ӹ���m:");
	scanf("%d",&m);
	printf("\n��������n��");
	scanf("%d",&n);
	
	head=creat(m,n);
	king=choose_king(head,m,n);
	printf("\n���ǵ�%dֻ����",king->num);
	
	return 0;
 } 
 //�������� 
PMon creat(int m,int n)
{
	PMon head,current,prev;
	int i;
	head=(PMon)malloc(sizeof(Monkey));
	for(i=0;i<m;i++)
	{
		current=(PMon)malloc(sizeof(Monkey));//����ռ�
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
	current->next=head->next;//����ѭ�� 
	return head;
}
//����
PMon choose_king(PMon head,int m,int n)
{
	int count,j;//count��Ȧ�л��ڵĺ�������j������ȡ��ı������� 
	PMon p,prev;//prev��ǰһ����㣬p�ǵ�ǰ��� 
	j=0;
	prev=head;
	p=head->next;
	count=m;
	//printf("%d",p->num);
	while(count>1)//��Ȧ�еĺ���������1��ʱ�򣬼���ѭ�� 
	{
		j++;//�ۼӱ������������ǵڶ���ֻ���ӱ��� 
		if(j%n==0)//Լ������ֻ���ӱ���3 ������ȥ 
		{
			count--;//�����к���������һ 
			if(count>=2)// ����������ֻ�����ϵĺ��ӣ����Լ��� 
			{
				prev->next=p->next;
				free(p);
				
				p=prev->next;
			}
			else//count=1
			{
				free(p);//����prev 
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
 //��� 
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

