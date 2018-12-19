/*
A(x)=3*x^100+5*X^2+1      3   3 100   5 2   1 0       4   1 5     2 3   -5 2   2 0 
B(x)=x^5+2*x^3-5*x^2+2    4   1 5     2 3   -5 2   2 0 
C(x)=A(x)+B(x)
D(x)=A(x)*B(x)
* E(x)=A(x)/B(x)+R(x)
*/ 
#include <stdio.h>
#include <stdlib.h>

//创建结点 
typedef struct Polynomial
{
	float coef;  //系数 
	int exp; //指数 
	struct Polynomial *next;//结点的指针域 
}DXS,*PDXS;

//函数声明 
PDXS read_poly();//创建 
void write_poly(PDXS head);//输出
PDXS add_poly(PDXS a,PDXS b);//相加
PDXS mult_simple(PDXS ah,PDXS bh);//简单的多项式相乘
PDXS mult_poly(PDXS a,PDXS b);//相乘
void clear_poly(PDXS head);//清除 

int main()
{
	PDXS a,b,c,d;
	//创建a,b 
	printf("输入多项式A(x):\n");
	a=read_poly();
	printf("输入多项式B(x):\n");
	b=read_poly();
	//输出a,b 
	printf("\nA(x)=");
	write_poly(a);
	printf("\nB(x)=");
	write_poly(b);
	//加法 
	c=add_poly(a,b);
	printf("\nA(x)+B(x)=");
	write_poly(c);
	
	printf("\n加法之后的A(x)=");
	write_poly(a);
	printf("\n加法之后的B(x)=");
	write_poly(b);
	//乘法 
	d=mult_poly(a,b);
	printf("\nA(x)*B(x)=");
	write_poly(d);
	
	//清除
	clear_poly(a);
	clear_poly(b);
	clear_poly(c);
	clear_poly(d); 
	return 0;
}

//创建链表
PDXS read_poly() 
{
	PDXS head,current,p,save;//prev是上一个，current是当前的 
	int i=0,count=0;
	head=(PDXS)malloc(sizeof(DXS));
	head->next=NULL;
	
	printf("请输入多项式项数");
	scanf("%d",&count);
	printf("\n多项式项数%d",count);
	for(i=0;i<count;i++)
	{
		printf("\n请输入第%d项的系数和指数:",i+1);
		current=(PDXS)malloc(sizeof(DXS));//申请空间
		current->next=NULL;
		scanf("%f %d",&current->coef,&current->exp);//输入表头数据
		if(i==0)//建立头结点 
		{
			head->next=current;
		//	printf("表头建立成功 %.2f %d",head->next->coef,head->next->exp);
		}
		else//不是头结点时将进行遍历搜索，将数值插入到合适的位置 
		{
			p=head->next;//为工作指针p赋值 
			if(p->exp>current->exp)//表头结点指数大，current应做新的表头 
			{
				current->next=p;
				head->next=current;
			//	printf("\n新的表头 %.2f %d",head->next->coef,head->next->exp);
			 } 
			else
			{
				while((p->exp<current->exp)&&(p->next!=NULL))//current向后插 
				{
					save=p;
					p=p->next;//工作指针p后移，将p储存在save中 
				}	//循环停下时有两种情况，p->exp>=current->exp,p->next=NULL
				if(p->exp>current->exp) //即将current插入到save与p之间 
				{
					save->next=current;
					current->next=p;
				}
				else//current做尾结点 
				{
					p->next=current;//current作为节点，申请空间是已将current的next初始化为NULL 
				} 
			}
		}
		//printf("第%d次建立结点%f,%d\n",i+1,current->coef,current->exp);//测试 
	}
	return head;
}
//输出
void write_poly(PDXS head)
{
	PDXS p;
	//第一项 
	p=head->next;
	printf("%.2f",p->coef);
    printf("x^");
    printf("%d",p->exp);
    p=p->next;
    //之后的项 
	while(p!=NULL)
	{
		if(p->coef==0)
		{
			p=p->next;
		}
		if(p->coef>0)
        {
            printf("+");
        }
        printf("%.2f",p->coef);
    	printf("x^");
        printf("%d",p->exp);
        p=p->next;
	}
}

//多项式相加
PDXS add_poly(PDXS a,PDXS b)//相加
{
    PDXS head,p;
	head=(PDXS)malloc(sizeof(DXS));
    head->next=NULL;
    p=head;

    //指向多项式的首节点
    PDXS pa=a->next;
    PDXS pb=b->next;

    //多项式相加
    while(pa&&pb)
    {
        //比较当前结点的指数大小
        if(pa->exp<pb->exp)
        {
            p->next=pa;
            p=pa;
            pa=pa->next;
            p->next=NULL;
        }
        else if(pa->exp>pb->exp)
        {
            p->next=pb;
            p=pb;
            pb=pb->next;
            p->next=NULL;
        }
        else
        {
            //当指数的系数相加不为零
            if((pa->coef+pb->coef)!=0)
            {
            	PDXS tmp=(PDXS)malloc(sizeof(DXS));//新节点 
            	tmp->exp=pa->exp;
                tmp->coef=pa->coef+pb->coef;
                p->next=tmp;
                p=tmp;
                p->next=NULL;
            }
            else
            {
                p->next=NULL;
            }
            pa=pa->next;
            pb=pb->next;
        }
    }
    if (pa!=NULL)
    {
        p=pa;
    }
    else// pb!=NULL
    {
        p=pb;
    }
    return head;
}

//相乘

//单项的多项式相乘
PDXS mult_simple(PDXS ah,PDXS bh)
{
    PDXS phead=(PDXS)malloc(sizeof(DXS));
    phead->next=NULL;
    PDXS p=phead;
    //bh去乘ah的每一项
    while(ah)
    {
        PDXS tmp=(PDXS)malloc(sizeof(DXS));
        tmp->next=NULL;
        p->next=tmp;
        p=tmp;
        //printf("\na:%.2f %d  b:%.2f %d",ah->coef,ah->exp,bh->coef,bh->exp);
        tmp->coef=ah->coef*bh->coef;
        tmp->exp=ah->exp+bh->exp;
        ah=ah->next;
        //printf("乘积：%.2f %d",tmp->coef,tmp->exp); 
    }
    return phead;
}
//多项式相乘
PDXS mult_poly(PDXS a,PDXS b)
{
    PDXS head=(PDXS)malloc(sizeof(DXS));
    head->next=NULL;

    //指向多项式的首节点
    PDXS pa=a->next;
    PDXS pb=b->next;
    //用Dbh的每一项去乘Dah的每一项
    while(pb)
    {
        head=add_poly(head,mult_simple(pa,pb));
        pb=pb->next;
    }
    return head;
}
//清除
void clear_poly(PDXS head)
{
	struct Polynomial *p;
 	
 	while(p->next!=NULL)
 	{
 		p=head;
 		head=head->next;
 		free(p);
	 }
}
