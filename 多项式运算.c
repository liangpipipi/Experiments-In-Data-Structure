/*
A(x)=3*x^100+5*X^2+1      3   3 100   5 2   1 0       4   1 5     2 3   -5 2   2 0 
B(x)=x^5+2*x^3-5*x^2+2    4   1 5     2 3   -5 2   2 0 
C(x)=A(x)+B(x)
D(x)=A(x)*B(x)
* E(x)=A(x)/B(x)+R(x)
*/ 
#include <stdio.h>
#include <stdlib.h>

//������� 
typedef struct Polynomial
{
	float coef;  //ϵ�� 
	int exp; //ָ�� 
	struct Polynomial *next;//����ָ���� 
}DXS,*PDXS;

//�������� 
PDXS read_poly();//���� 
void write_poly(PDXS head);//���
PDXS add_poly(PDXS a,PDXS b);//���
PDXS mult_simple(PDXS ah,PDXS bh);//�򵥵Ķ���ʽ���
PDXS mult_poly(PDXS a,PDXS b);//���
void clear_poly(PDXS head);//��� 

int main()
{
	PDXS a,b,c,d;
	//����a,b 
	printf("�������ʽA(x):\n");
	a=read_poly();
	printf("�������ʽB(x):\n");
	b=read_poly();
	//���a,b 
	printf("\nA(x)=");
	write_poly(a);
	printf("\nB(x)=");
	write_poly(b);
	//�ӷ� 
	c=add_poly(a,b);
	printf("\nA(x)+B(x)=");
	write_poly(c);
	
	printf("\n�ӷ�֮���A(x)=");
	write_poly(a);
	printf("\n�ӷ�֮���B(x)=");
	write_poly(b);
	//�˷� 
	d=mult_poly(a,b);
	printf("\nA(x)*B(x)=");
	write_poly(d);
	
	//���
	clear_poly(a);
	clear_poly(b);
	clear_poly(c);
	clear_poly(d); 
	return 0;
}

//��������
PDXS read_poly() 
{
	PDXS head,current,p,save;//prev����һ����current�ǵ�ǰ�� 
	int i=0,count=0;
	head=(PDXS)malloc(sizeof(DXS));
	head->next=NULL;
	
	printf("���������ʽ����");
	scanf("%d",&count);
	printf("\n����ʽ����%d",count);
	for(i=0;i<count;i++)
	{
		printf("\n�������%d���ϵ����ָ��:",i+1);
		current=(PDXS)malloc(sizeof(DXS));//����ռ�
		current->next=NULL;
		scanf("%f %d",&current->coef,&current->exp);//�����ͷ����
		if(i==0)//����ͷ��� 
		{
			head->next=current;
		//	printf("��ͷ�����ɹ� %.2f %d",head->next->coef,head->next->exp);
		}
		else//����ͷ���ʱ�����б�������������ֵ���뵽���ʵ�λ�� 
		{
			p=head->next;//Ϊ����ָ��p��ֵ 
			if(p->exp>current->exp)//��ͷ���ָ����currentӦ���µı�ͷ 
			{
				current->next=p;
				head->next=current;
			//	printf("\n�µı�ͷ %.2f %d",head->next->coef,head->next->exp);
			 } 
			else
			{
				while((p->exp<current->exp)&&(p->next!=NULL))//current���� 
				{
					save=p;
					p=p->next;//����ָ��p���ƣ���p������save�� 
				}	//ѭ��ͣ��ʱ�����������p->exp>=current->exp,p->next=NULL
				if(p->exp>current->exp) //����current���뵽save��p֮�� 
				{
					save->next=current;
					current->next=p;
				}
				else//current��β��� 
				{
					p->next=current;//current��Ϊ�ڵ㣬����ռ����ѽ�current��next��ʼ��ΪNULL 
				} 
			}
		}
		//printf("��%d�ν������%f,%d\n",i+1,current->coef,current->exp);//���� 
	}
	return head;
}
//���
void write_poly(PDXS head)
{
	PDXS p;
	//��һ�� 
	p=head->next;
	printf("%.2f",p->coef);
    printf("x^");
    printf("%d",p->exp);
    p=p->next;
    //֮����� 
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

//����ʽ���
PDXS add_poly(PDXS a,PDXS b)//���
{
    PDXS head,p;
	head=(PDXS)malloc(sizeof(DXS));
    head->next=NULL;
    p=head;

    //ָ�����ʽ���׽ڵ�
    PDXS pa=a->next;
    PDXS pb=b->next;

    //����ʽ���
    while(pa&&pb)
    {
        //�Ƚϵ�ǰ����ָ����С
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
            //��ָ����ϵ����Ӳ�Ϊ��
            if((pa->coef+pb->coef)!=0)
            {
            	PDXS tmp=(PDXS)malloc(sizeof(DXS));//�½ڵ� 
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

//���

//����Ķ���ʽ���
PDXS mult_simple(PDXS ah,PDXS bh)
{
    PDXS phead=(PDXS)malloc(sizeof(DXS));
    phead->next=NULL;
    PDXS p=phead;
    //bhȥ��ah��ÿһ��
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
        //printf("�˻���%.2f %d",tmp->coef,tmp->exp); 
    }
    return phead;
}
//����ʽ���
PDXS mult_poly(PDXS a,PDXS b)
{
    PDXS head=(PDXS)malloc(sizeof(DXS));
    head->next=NULL;

    //ָ�����ʽ���׽ڵ�
    PDXS pa=a->next;
    PDXS pb=b->next;
    //��Dbh��ÿһ��ȥ��Dah��ÿһ��
    while(pb)
    {
        head=add_poly(head,mult_simple(pa,pb));
        pb=pb->next;
    }
    return head;
}
//���
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
