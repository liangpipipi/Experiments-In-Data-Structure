/*
    һ�Ѻ��Ӷ��б�ţ������1��2��3 ...m����Ⱥ���ӣ�m��������1-m��˳��Χ��һȦ���ӵ�1��ʼ����ÿ������n�����ú��Ӿ�Ҫ�뿪��Ȧ��
��������������ֱ��Ȧ��ֻʣ�����һֻ���ӣ���ú���Ϊ������
Ҫ��m��nҪ��Ӽ������룬�洢��ʽ�����������������ַ�ʽʵ�ָ�������⡣ 
*/ 

//�������
#include <stdio.h>
void initialize(int Monkey[],int m);
int choose_king(int Monkey[],int m,int n);
void output(int Monkey[],int m); 

int main()
{
	int Monkey[100];
	int m,n,king;
	
	printf("��������Ӹ���m:");
	scanf("%d",&m);
	printf("\n��������n��");
	scanf("%d",&n);
	if(m<=0|n<=0)
	{
		printf("\n����������������룡");
		printf("\n��������Ӹ���m����������n��");
		scanf("%d,%d",&m,&n);
	}
	
	initialize(Monkey,m);//��ʼ������ 
	king=choose_king(Monkey,m,n);//ѡ�� 
	printf("\n���ǵ�%dֻ����\n",king);
	 
	return 0;
}
//��� 
void output(int Monkey[],int m)
{
	int i;
	for(i=0;i<m;i++)
	{
		printf("Monkey[%d]=%d\n",i,Monkey[i]);
	}
}
//��ʼ������Ԫ�� 
void initialize(int Monkey[],int m)
{
	int i;
	for(i=0;i<m;i++)
	{
		Monkey[i]=i+1;//Ϊ�������鸳ֵ����1��ʼ 
	}
	for(i=m;i<sizeof(Monkey);i++)
	{
		Monkey[i]=0;
	}
}
//ѡ��
int choose_king(int Monkey[],int m,int n)
{
	int count=m;//����������¼��ǰ���м�ֻ����
	int i,j=0,king;//jʼ�������ӣ�ͨ��ȡ����ȷ����ֻ����Ӧ���뿪 
	while(count>1)//������������1ʱ��ִ��ѭ�� 
	{
		for(i=0;i<m;i++)//ѭ��m�� 
		{
			if(Monkey[i]!=0)//��ʱ��ֻ���ӻ��ڶ����� 
			{
				j++;//����������һ 
				if(j%n==0)//����Ϊ0����ֻ����Ӧ���뿪 
				{
					Monkey[i]=0;//ԭ�����Ϊi�ĺ����뿪 
					count--;//�����к�������һ 
					if(count==1)//����ʱֻʣ��һֻ����ʱ������ѭ�� 
					{
						break;
					}
				}
			}
		}
	}
	for(i=0;i<m;i++)
	{
		if(Monkey[i]!=0)
		{
			king=i+1;
			break;	
		}
	}
	return king;
} 
/*
�����ڵ�3ֻ�����뿪��,j=3
���ڵ�6ֻ�����뿪��,j=6
���ڵ�4ֻ�����뿪��,j=9
���ڵ�2ֻ�����뿪��,j=12
���ڵ�5ֻ�����뿪��,j=15

���ǵ�1ֻ����
*/
