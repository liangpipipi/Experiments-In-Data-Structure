/*
��Ŀ8���������ı���
    ��������lson-rson���ӷ�ʽ�洢���Բ˵���ʽ��Ʋ���ɹ�������
	�������洢�������ǰ������������������������������������������������������ͳ�Ƹ߶ȣ�
	���ж������򡢺���ı�������Ҫ����÷ǵݹ鷽ʽ��
�ǵݹ飬��ջ���� 
�ֲ���ʾ���ڶ��㵱����һ�㣬ͨ������ʵ�� 
*/

//�������ڵ� 
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <malloc.h>
#include <stdlib.h>
//������ 
typedef  struct TreeNode
{
	char data[10];
	struct TreeNode *rson,*lson;
}TNode,*PTree;
//����ջ
typedef struct Stack{
    int top;
    int tag[50];
    PTree stackdata[50];
}SqStack;
//ջ�ĳ�ʼ��
void init_stack(SqStack* s)
{
	//memset(s->stackdata,0, sizeof(s->stackdata)); //�������extern void *memset(void *buffer, int c, int count) buffer��Ϊָ���������,c���Ǹ���buffer��ֵ,count����buffer�ĳ���.
	s->top=0;
	//int i;
	/*for(i=0;i<50;i++)
	{
		s->tag[i]=-1;
	}
	printf("ջ�ĳ�ʼ��\n");*/
}
//ѹջ
int in_stack(SqStack* s, PTree data)//��data��ջ 
{
	if(s->top ==49){  //������ 
		printf("the stack is full. \n");
		return 1;  //�������˳� 
	}	
	//����ѹջ 
	(s->top)++;
	s->stackdata[s->top] = data;
	return 0;//�������� 
}
//tag��ջ
int in_tag_stack(SqStack* s, int t) 
{
	s->tag[s->top]=t;//��Ҫ����PTree����tag 
	return 0;
}
//��ջ
PTree out_stack(SqStack* s)
{
	PTree tmp;
	if(s->top<=0)//��������ջ 
	{
		printf("the stack is empty. \n");
		exit(-1);//�������˳� 
	} 
	else //������ջ 
	{
		tmp = (s->stackdata)[s->top]; 
		(s->top)--;//�ȳ�tag,�ٳ�PTree ����ջ���һ��Ԫ��֮��s->top=-1 
		return tmp;	
	}
}
//tag��ջ 
int out_tag_stack(SqStack* s)
{
	int tmp;
	tmp = (s->tag)[s->top];  //��Ҫ�ȳ�tag���ٳ�PTree 
	return tmp;	
	
}
//�ݹ鹹������� 
void Create_Tree(PTree *T)//����TʵΪָ��ָ���ָ�룬Ϊ˫�� 
{
	char ch[20];  //�ݴ�����Ԫ�� 
	scanf("%s",ch);
	if(ch[0]=='#') //����#,�˽ڵ�Ϊ��
	{
		*T=NULL;
	 } 
	 else  //�����½ڵ� 
	 {
	 	*T = (PTree)malloc(sizeof(TNode));//���ٿռ�
	 //	if(!(*T))
	 		//exit(-1);
	 	strcpy((*T)->data,ch); //װ��ڵ�����,string copy���ַ������ƣ�
		printf("\n������%s�����ӽڵ�:",ch);
		Create_Tree(&(*T)->lson);  //���������� 
		printf("\n������%s�����ӽڵ�:",ch);
		Create_Tree(&(*T)->rson);  //���������� 
	 }
}
//ǰ�����
void Preorder(PTree T)
{
	if(T==NULL)
		return;
	printf("%s ",T->data);
	Preorder(T->lson);
	Preorder(T->rson);	
 } 
 //�ǵݹ��������
 void Inorder(PTree T,SqStack* s) 
 {
 	//printf("this is inorder\n");
 	PTree p=T;
 	while((p!=NULL)||((s->top)>0))//ͣ��ʱp=NULL��s->top=0
 	{
 		while(p!=NULL)//����û���ҵ���С������� 
 		{
 			//printf("��ջ%s\n",p->data);
 			if(!in_stack(s,p));//T��ջ
			 p=p->lson; 
		 }//����ѭ��ʱp=nil 
		 if(s->top>=0)//ջ�ǿ�
		 {
		 	p=out_stack(s);//��ջ
			printf("%s ",p->data);
			p=p->rson;//�������������� 
		  } 
		  if((p==NULL)&&((s->top)==0))
		  {
		  	break;
		  }
	 }
	 //printf("inorder is over\n");
 }
 //�����ݹ����
 void  Postorder1(PTree T,SqStack* s)
 {
 	if(T==NULL)
		return;
	
	Preorder(T->lson);
	Preorder(T->rson);
	printf("%s ",T->data);
 }
 //�����ǵݹ�    �� �� �� 
void Postorder(PTree T,SqStack* s)
{
	PTree p=T;
	int tag=0;
	while((p!=NULL)||(s->top>=0))
 	{
 		while(p!=NULL)
 		{
 			tag=0;
 			if(!in_stack(s,p));
 			if(!in_tag_stack(s,tag));//T��tag��ջ
 			
			 p=p->lson; 
		 }//����ѭ��ʱp=nil 
		 if(s->top!=0)//ջ�ǿ�
		 {
		 	tag=out_tag_stack(s);
		 	p=out_stack(s);//��ջ
		 	if(tag==0)//�Ȳ�����˽ڵ㣬ȥ���������� 
		 	{
		 		tag=1;
		 		if(!in_stack(s,p));
 				if(!in_tag_stack(s,tag));//T��tag��ջ
 				p=p->rson;//�������������� 
			 }
			 else//tag=1,��ʱ�����������������ˣ�����T�󷵻�T����һ�� 
			 {
			 	printf("%s ",p->data);
			 	p=NULL;
			  } 
		  } 
		  if((p==NULL)&&(s->top==0))
		  {
		  	break;
		  }
	 }
	 
 } 
//�ݹ�ʵ�����������Ľ���
void Exchange(PTree *T)                              
{
	PTree *p1,*p2;
	p1=T;
	if ((*T)==NULL) return;                       
	//������������������
	p2=(*p1)->lson;
	(*p1)->lson=(*p1)->rson;
	(*p1)->rson=p2;
	Exchange(&(*p1)->lson);  //�������ӵ�����
	Exchange(&(*p1)->rson); //�����Һ��ӵ�����
}
//������������
int TreeDeep(PTree T)
{
  int deep = 0;
  int leftdeep,rightdeep;
  if(T)
  {
    leftdeep=TreeDeep(T->lson);
    rightdeep=TreeDeep(T->rson);
    deep=leftdeep>=rightdeep?leftdeep+1:rightdeep+1;
  }
  return deep;
}
//�˵�
int Item()
{
	int input;
	printf("\n���������������������˵���������������������\n");
	printf("1.ǰ�����������\n");
	printf("2.�������������\n");
	printf("3.�������������\n");
	printf("4.����������\n");
	printf("5.������������������\n");
	printf("0.�˳�\n");
	printf("���������ѡ��:");
	scanf("%d",&input);
	
	return input;
 } 
//���� 
 int main()
 {
 	SqStack* s;
 	PTree T;
 	PTree *p=(PTree*)malloc(sizeof(PTree));
    s=(SqStack*)malloc(sizeof(SqStack*));
   
 	init_stack(s);
 	printf("�������һ������ֵ,#��ʾû��Ҷ���:");
 	Create_Tree(&T);
 	int choice=Item();
 	int deep;
 	while(choice!=0)
 	{
 		switch(choice)
 		{
 			case 1:Preorder(T);break;
 			case 2:Inorder(T,s);break;
 			case 3:Postorder(T,s);break;
 			case 4:deep=TreeDeep(T);printf("�����%d\n",deep);break;
 			case 5:Exchange(&T);break;
 			case 0:break;
 			default:break;
		  } 
		  choice=Item();
	 }
	printf("\n�������������������������������������������\n\n");
 	return 0;
 }
 //abc##d##e##
