/*
 ĳ�͵���N���ȼ��ķ��䣬��k���ͷ���A��k������ÿ��������B��k�������˴����Բ˵����÷�ʽ���Ϊ�����ÿͷ��䴲λ�Լ����ʱ��
 �ش�λ�ĳ���Ҫ�����ɹ�ʱ��ӡ���ÿ����������䡢�Ա𡢵������ڡ��ͷ��ȼ�������ż���λ�ţ����䲻�ɹ�ʱ��������ķ���
 �ȼ����������ĵȼ���ӡ��"����"��ʾ��
 ����ȼ�����������λ������λ�ı�ţ��Ѿ�ס�˼�����λ����λ����
 �ṹ�� �ȼ� ������ ��λ�� ָ�� 
*/ 
//�߼��е����⣡���� 
#include <stdio.h>
#include <stdlib.h>

struct Customer
{
	char name[20];
	int age;
	int sex;//�Ա�1�����ԣ�2��Ů�� 
	int data_of_arrival;//��������
};

typedef struct Room
{
	int roomlevel;//�ͷ��ȼ�
	int roomnum;//�ͷ���� 
	int bednum;//��λ�� 
	struct Customer customer; //�˿� 
	struct Room *next;//����ָ���� 
}room,*proom;

 

//��ʼ���õ� 
proom initialize_hotel(int roomlevel_amount)
{
	proom current,prev,head;
	int room_amount[50],bed_amount[50],i,j,k;
	
	printf("����������������������ʼ����������������������\n");
	//printf("�������õ��ж��ٸ���ͬ�ȼ��ķ��䣺");
	//scanf("%d",&roomlevel_amount);
	
	for(i=0;i<roomlevel_amount;i++)
	{
		printf("\n������ȼ�Ϊ%d�ķ��乲�ж��ٸ�:",i+1);
		scanf("%d",&room_amount[i]);
		printf("\n������ȼ�Ϊ%d�ķ���ÿ���ж����Ŵ�:",i+1);
		scanf("%d",&bed_amount[i]);
	}
	head=(proom)malloc(sizeof(room));//����ռ�
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
					//printf("ͷ����ʼ���ɹ�\n");
				}
				else
				{
					prev->next=current;
					prev=current;
				}
				//printf("����%d%d%d�����ɹ�  �ȼ�%d �����%d ����%d\n\n",i,j,k,current->roomlevel,current->roomnum,current->bednum);
				
			}
		}
	 } 
	 current->next=NULL;
	 printf("��������������������������������������������\n\n");
	 return head;
}

//��������ùݵĴ�λ��Ϣ
void inqury(proom head)
{
	printf("��������������������λ��Ϣ������������������\n");
	proom p=head->next;
	while(p!=NULL)//ѭ������β
	{
		if(p->customer.age==0)
		{
			printf("�ȼ�%d �����%d ����%d δ��ס\n",p->roomlevel,p->roomnum,p->bednum);
		}
			
		else
		{
			printf("�ȼ�%d �����%d ����%d ����%d �Ա�",p->roomlevel,p->roomnum,p->bednum,p->customer.age);
			if(p->customer.sex==1)
			{
				printf("��\n"); 
			}
			else
			{
				printf("Ů\n");
			}
		 } 		
		p=p->next;
	}
	printf("������������������λ��Ϣ��������������������\n\n");
}

//��ס
void check_in(proom head,int roomlevel_amount)
{
	printf("����������������������ס��������������������\n");
	int level;
	proom p;
	p=head;
	printf("�װ��Ĺ˿����ã���������Ҫ����ȼ��ķ��䣿���ǹ���%d�ַ��乩��ѡ��\n",roomlevel_amount);
	scanf("%d",&level);
	if(level>roomlevel_amount) 
	{
		printf("�ȼ������������������:\n");
		scanf("%d",&level);
	}
	while(p->roomlevel!=level&&p!=NULL)
	{
		p=p->next;
	}//��ѭ��ͣ��ʱ��p->roomlevel=level�����ǹ˿�Ҫ�ķ���
	while(p->roomlevel==level&&p!=NULL) //�����෿����Ѱ�ҿշ� 
	{
		if(p->customer.age!=0)//����ס�� 
		{
			p=p->next; 
		}
		else//p->customer.age==0 �շ� 
		{
			break; 
		 } 	
	}
	if(p->roomlevel==level&&p->customer.age==0)//p������Ҫ�ҵĵȼ���һ��շ� 
	{
		
		printf("\n����������������");
		scanf("%s",&p->customer.name);
		printf("�������������䣺");
		scanf("%d",&p->customer.age);
		printf("�����������Ա�1�����ԣ���2��Ů�ԣ���");
		scanf("%d",&p->customer.sex);
		printf("���������ĵ������ڣ�(��20181107)");
		scanf("%d",&p->customer.data_of_arrival);
		
		printf("\n�����ɹ������ķ���ȼ���%d,�������%d,��λ����%d\n\n",p->roomlevel,p->roomnum,p->bednum);
	 } 
	 else
	 {
	 	printf("��Ǹ����ѡ��������Ѿ�û�пմ�λ�ˣ�������ѡ��\n\n");
	 }
	 printf("��������������������������������������������\n\n"); 
	//retuen 0;
 } 
 //�˷�
  void check_out(proom head)
{
	printf("���������������������˷���������������������\n");
  	int rolevel,ronum,benum;
  	proom p=head->next;
	printf("\n���������ķ���ȼ�������ż���λ�ţ�");
  	scanf("%d,%d,%d",&rolevel,&ronum,&benum);
  	while((p->roomlevel!=rolevel)||(p->roomnum!=ronum)||(p->bednum!=benum))
  	{
  		p=p->next;
	}
	p->customer.age=0;
	p->customer.sex='m';
	p->customer.data_of_arrival=0;
	printf("�˷��ɹ���\n");
	printf("�������������������˷�����������������������\n\n");
}

//�鿴�˿���Ϣ 
void view_information(proom head)
{
	printf("�����������������鿴�˿���Ϣ����������������\n"); 
	int rolevel,ronum,benum;
  	proom p=head->next;
	printf("\n������˿͵ķ���ȼ�������ż���λ�ţ�");
  	scanf("%d,%d,%d",&rolevel,&ronum,&benum);
  	//printf("%d,%d,%d",rolevel,ronum,benum);
  	while(((p->roomlevel!=rolevel)||(p->roomnum!=ronum)||(p->bednum!=benum))&(p!=NULL))
  	{
  		p=p->next;
  	//	printf("ָ�����\n");
	}
	//printf("�ҵ�");
	if(p->customer.age!=0)
	{
		printf("�˿͵�������%s,�Ա���",p->customer.name);
		if(p->customer.sex==1)
		{
			printf("��"); 
		}
		else
		{
			printf("Ů");
		}
		printf(",����%d,��סʱ����%d\n\n",p->customer.age,p->customer.data_of_arrival);
	}	
	else
	{
		printf("����δ��ס���ˣ�\n\n");
	}
	printf("���������������鿴�˿���Ϣ������������������\n\n");
}

//�˵�
int item()
{
	int i;
	printf("���������������������˵���������������������\n");
	printf("1������ʾ���з�����Ϣ\n");
	printf("2��������\n");
	printf("3�����˷�\n");
	printf("4�����鿴�˿���Ϣ\n");
	printf("0�����˳�ϵͳ\n");
	printf("����ѡ��:");
	scanf("%d",&i);
	printf("�������������������˵�����������������������\n\n");
	return i;
}
  int main()
{
	int i,roomlevel_amount;
		proom head;
  	printf("�������õ��ж��ٸ���ͬ�ȼ��ķ��䣺");
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
	printf("�˳�\n");
	return 0;
}
 
