/*对于给定的一个工程施工图，该图以边为单位从键盘输入，编写能够找出该图的关键路径的程序。*/
#include<malloc.h>
#include<stdio.h>
typedef struct Node //邻接点
{
    int vex;//顶点信息
    int weight;//权值
    struct Node *next;
}Node;

struct Hnode //头结点
{
    int vex2;
    int indegree; //入度
    struct Node *link;
}A[20];

void create(struct Hnode A[20],int n,int e)//n为顶点总数,e为边总数 
{
	int i,j,k,l;
    Node * p;
    for(i=1;i<=n;i++)//建立顶点表  ***没有用A[0]*** 
    {
		A[i].vex2=i;
        A[i].indegree=0;
        A[i].link=NULL;
    }

	for(k=1;k<=e;k++)//建图
    {
		printf("\n请输入边及其权值:\n");
        scanf("%d",&i);
        scanf("%d",&j);
		scanf("%d",&l);
        p=(Node *)malloc(sizeof(Node));
        p->vex=j;
        p->weight=l;
        p->next=A[i].link;
        A[i].link=p;//每次都插到头结点之后 
	}

	for(i=1;i<=n;i++)//完善入度
    {
		p=A[i].link;
		while(p!=NULL)
		{
            k=p->vex;//读取连接到的结点 
            A[k].indegree=A[k].indegree+1;//相应结点入度加一 
            p=p->next;
		}
    }
}


void find(struct Hnode A[20],int n)
{
    int i,j,m=0,front,rear;
    int k=0;
	int ve[20],vl[20],e[20],l[20];//j—ai—>k。e(i):活动ai的最早开始时间,l(i):活动ai的最迟发生时间,Ve(j):事件j的最早发生时间,Vl(j):时间j的最迟发生时间 
    int tpord[20];//存放入度为0的结点 
	Node *p;
	for(i=1;i<=n;i++) //初始化顶点（事件）的最早发生时间和最迟发生时间
    {
        ve[i]=0;
        vl[i]=0;
    }
    front=0;
    rear=0;
	for(i=1;i<=n;i++)
    {
        if(A[i].indegree==0)//找到入度为零顶点，准备拓扑排序
        {
            rear++;
            tpord[rear]=i;
        }
    }

    while(front!=rear)//栈不为空
    {
        front++;
        j=tpord[front];
        m++; //记录访问了多少个顶点
		p=A[j].link;
        while(p!=NULL)
        {
            k=p->vex;//后继顶点k 
            A[k].indegree=A[k].indegree-1; //访问之后k入度减一
			
			if(A[k].indegree==0)
            {
                rear++;
                tpord[rear]=k;
            }
            if(ve[j]+(p->weight)>ve[k])//若经由p能增大Ve(k)，则增大 
				ve[k]=ve[j]+(p->weight);
            p=p->next;
        }
    }

	if(m<n)
    {
      printf("\n网中存在回路，不能进行拓扑排序!");
      return;
    }

	for(i=1;i<=n;i++)
		vl[i]=ve[n];//顶点的最早发生时间赋给顶点的最迟发生时间

	for(i=n-1;i>=1;i--)//进行逆拓扑排序  此时m=n=rear+1
    {
        j=tpord[i];//逆序 
        p=A[j].link;
        while(p!=NULL)
        {
            k=p->vex;
            if((vl[k]-p->weight)<vl[j])//若经由k能缩小Vl(p)，则缩小 
				vl[j]=vl[k]-(p->weight);//确定顶点（事件）最迟发生时间
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
			e[i]=ve[j]; //活动最早发生时间
            l[i]=vl[k]-(p->weight);//活动最迟发生时间
            printf("\n <%d ,%d>:",A[j].vex2,A[k].vex2);
            if(l[i]==e[i])
            {
                printf("是关键活动!");

            }
            else
            {
                printf("不是关键活动!");

            }
            p=p->next;
        }
    }
}


void main()
{
    int n,e;
    printf("请输入顶点总数:");
    scanf("%d",&n); 
    printf("\n请输入边的总数: ");
    scanf("%d",&e);
    create(A,n,e);
    find(A,n);
}
