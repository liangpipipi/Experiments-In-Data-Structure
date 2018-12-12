/*���ڸ�����һ������ʩ��ͼ����ͼ�Ա�Ϊ��λ�Ӽ������룬��д�ܹ��ҳ���ͼ�Ĺؼ�·���ĳ���*/
#include<malloc.h>
#include<stdio.h>
typedef struct Node //�ڽӵ�
{
    int vex;//������Ϣ
    int weight;//Ȩֵ
    struct Node *next;
}Node;

struct Hnode //ͷ���
{
    int vex2;
    int indegree; //���
    struct Node *link;
}A[20];

void create(struct Hnode A[20],int n,int e)//nΪ��������,eΪ������ 
{
	int i,j,k,l;
    Node * p;
    for(i=1;i<=n;i++)//���������  ***û����A[0]*** 
    {
		A[i].vex2=i;
        A[i].indegree=0;
        A[i].link=NULL;
    }

	for(k=1;k<=e;k++)//��ͼ
    {
		printf("\n������߼���Ȩֵ:\n");
        scanf("%d",&i);
        scanf("%d",&j);
		scanf("%d",&l);
        p=(Node *)malloc(sizeof(Node));
        p->vex=j;
        p->weight=l;
        p->next=A[i].link;
        A[i].link=p;//ÿ�ζ��嵽ͷ���֮�� 
	}

	for(i=1;i<=n;i++)//�������
    {
		p=A[i].link;
		while(p!=NULL)
		{
            k=p->vex;//��ȡ���ӵ��Ľ�� 
            A[k].indegree=A[k].indegree+1;//��Ӧ�����ȼ�һ 
            p=p->next;
		}
    }
}


void find(struct Hnode A[20],int n)
{
    int i,j,m=0,front,rear;
    int k=0;
	int ve[20],vl[20],e[20],l[20];//j��ai��>k��e(i):�ai�����翪ʼʱ��,l(i):�ai����ٷ���ʱ��,Ve(j):�¼�j�����緢��ʱ��,Vl(j):ʱ��j����ٷ���ʱ�� 
    int tpord[20];//������Ϊ0�Ľ�� 
	Node *p;
	for(i=1;i<=n;i++) //��ʼ�����㣨�¼��������緢��ʱ�����ٷ���ʱ��
    {
        ve[i]=0;
        vl[i]=0;
    }
    front=0;
    rear=0;
	for(i=1;i<=n;i++)
    {
        if(A[i].indegree==0)//�ҵ����Ϊ�㶥�㣬׼����������
        {
            rear++;
            tpord[rear]=i;
        }
    }

    while(front!=rear)//ջ��Ϊ��
    {
        front++;
        j=tpord[front];
        m++; //��¼�����˶��ٸ�����
		p=A[j].link;
        while(p!=NULL)
        {
            k=p->vex;//��̶���k 
            A[k].indegree=A[k].indegree-1; //����֮��k��ȼ�һ
			
			if(A[k].indegree==0)
            {
                rear++;
                tpord[rear]=k;
            }
            if(ve[j]+(p->weight)>ve[k])//������p������Ve(k)�������� 
				ve[k]=ve[j]+(p->weight);
            p=p->next;
        }
    }

	if(m<n)
    {
      printf("\n���д��ڻ�·�����ܽ�����������!");
      return;
    }

	for(i=1;i<=n;i++)
		vl[i]=ve[n];//��������緢��ʱ�丳���������ٷ���ʱ��

	for(i=n-1;i>=1;i--)//��������������  ��ʱm=n=rear+1
    {
        j=tpord[i];//���� 
        p=A[j].link;
        while(p!=NULL)
        {
            k=p->vex;
            if((vl[k]-p->weight)<vl[j])//������k����СVl(p)������С 
				vl[j]=vl[k]-(p->weight);//ȷ�����㣨�¼�����ٷ���ʱ��
            p=p->next;
        }
    }
	i=0;
	for(j=1;j<=n;j++)
	{
        p=A[j].link;
        while(p!=NULL)
        {
            k=p->vex;
            i++;
			e[i]=ve[j]; //����緢��ʱ��
            l[i]=vl[k]-(p->weight);//���ٷ���ʱ��
            printf("\n <%d ,%d>:",A[j].vex2,A[k].vex2);
            if(l[i]==e[i])
            {
                printf("�ǹؼ��!");

            }
            else
            {
                printf("���ǹؼ��!");

            }
            p=p->next;
        }
    }
}


void main()
{
    int n,e;
    printf("�����붥������:");
    scanf("%d",&n); 
    printf("\n������ߵ�����: ");
    scanf("%d",&e);
    create(A,n,e);
    find(A,n);
}
