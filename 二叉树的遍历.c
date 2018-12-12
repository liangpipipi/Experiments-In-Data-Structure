/*
题目8：二叉树的遍历
    二叉树以lson-rson链接方式存储，以菜单方式设计并完成功能任务：
	建立并存储树、输出前序遍历结果、输出中序遍历结果、输出后序遍历结果、交换左右子树、统计高度，
	其中对于中序、后序的遍历运算要求采用非递归方式。
非递归，用栈来做 
分层显示，第二层当做第一层，通过队列实现 
*/

//定义树节点 
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <malloc.h>
#include <stdlib.h>
//定义结点 
typedef  struct TreeNode
{
	char data[10];
	struct TreeNode *rson,*lson;
}TNode,*PTree;
//定义栈
typedef struct Stack{
    int top;
    int tag[50];
    PTree stackdata[50];
}SqStack;
//栈的初始化
void init_stack(SqStack* s)
{
	//memset(s->stackdata,0, sizeof(s->stackdata)); //清空数组extern void *memset(void *buffer, int c, int count) buffer：为指针或是数组,c：是赋给buffer的值,count：是buffer的长度.
	s->top=0;
	//int i;
	/*for(i=0;i<50;i++)
	{
		s->tag[i]=-1;
	}
	printf("栈的初始化\n");*/
}
//压栈
int in_stack(SqStack* s, PTree data)//将data入栈 
{
	if(s->top ==49){  //到顶了 
		printf("the stack is full. \n");
		return 1;  //非正常退出 
	}	
	//正常压栈 
	(s->top)++;
	s->stackdata[s->top] = data;
	return 0;//正常返回 
}
//tag入栈
int in_tag_stack(SqStack* s, int t) 
{
	s->tag[s->top]=t;//需要先入PTree再入tag 
	return 0;
}
//出栈
PTree out_stack(SqStack* s)
{
	PTree tmp;
	if(s->top<=0)//非正常出栈 
	{
		printf("the stack is empty. \n");
		exit(-1);//非正常退出 
	} 
	else //正常出栈 
	{
		tmp = (s->stackdata)[s->top]; 
		(s->top)--;//先出tag,再出PTree 。出栈最后一个元素之后，s->top=-1 
		return tmp;	
	}
}
//tag出栈 
int out_tag_stack(SqStack* s)
{
	int tmp;
	tmp = (s->tag)[s->top];  //需要先出tag，再出PTree 
	return tmp;	
	
}
//递归构造二叉树 
void Create_Tree(PTree *T)//这里T实为指向指针的指针，为双重 
{
	char ch[20];  //暂存输入元素 
	scanf("%s",ch);
	if(ch[0]=='#') //读入#,此节点为空
	{
		*T=NULL;
	 } 
	 else  //建立新节点 
	 {
	 	*T = (PTree)malloc(sizeof(TNode));//开辟空间
	 //	if(!(*T))
	 		//exit(-1);
	 	strcpy((*T)->data,ch); //装入节点数据,string copy（字符串复制）
		printf("\n请输入%s的左子节点:",ch);
		Create_Tree(&(*T)->lson);  //构造左子树 
		printf("\n请输入%s的右子节点:",ch);
		Create_Tree(&(*T)->rson);  //构造右子树 
	 }
}
//前序遍历
void Preorder(PTree T)
{
	if(T==NULL)
		return;
	printf("%s ",T->data);
	Preorder(T->lson);
	Preorder(T->rson);	
 } 
 //非递归中序遍历
 void Inorder(PTree T,SqStack* s) 
 {
 	//printf("this is inorder\n");
 	PTree p=T;
 	while((p!=NULL)||((s->top)>0))//停下时p=NULL且s->top=0
 	{
 		while(p!=NULL)//当还没有找到最小的左儿子 
 		{
 			//printf("入栈%s\n",p->data);
 			if(!in_stack(s,p));//T入栈
			 p=p->lson; 
		 }//跳出循环时p=nil 
		 if(s->top>=0)//栈非空
		 {
		 	p=out_stack(s);//出栈
			printf("%s ",p->data);
			p=p->rson;//继续遍历右子树 
		  } 
		  if((p==NULL)&&((s->top)==0))
		  {
		  	break;
		  }
	 }
	 //printf("inorder is over\n");
 }
 //后续递归遍历
 void  Postorder1(PTree T,SqStack* s)
 {
 	if(T==NULL)
		return;
	
	Preorder(T->lson);
	Preorder(T->rson);
	printf("%s ",T->data);
 }
 //后续非递归    左 右 根 
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
 			if(!in_tag_stack(s,tag));//T和tag入栈
 			
			 p=p->lson; 
		 }//跳出循环时p=nil 
		 if(s->top!=0)//栈非空
		 {
		 	tag=out_tag_stack(s);
		 	p=out_stack(s);//出栈
		 	if(tag==0)//先不处理此节点，去处理右子树 
		 	{
		 		tag=1;
		 		if(!in_stack(s,p));
 				if(!in_tag_stack(s,tag));//T和tag入栈
 				p=p->rson;//继续遍历右子树 
			 }
			 else//tag=1,此时左右子树都访问完了，访问T后返回T的上一个 
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
//递归实现左右子树的交换
void Exchange(PTree *T)                              
{
	PTree *p1,*p2;
	p1=T;
	if ((*T)==NULL) return;                       
	//交换根结点的左右子树
	p2=(*p1)->lson;
	(*p1)->lson=(*p1)->rson;
	(*p1)->rson=p2;
	Exchange(&(*p1)->lson);  //交换左孩子的子树
	Exchange(&(*p1)->rson); //交换右孩子的子树
}
//求二叉树的深度
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
//菜单
int Item()
{
	int input;
	printf("\n——————————菜单——————————\n");
	printf("1.前序遍历二叉树\n");
	printf("2.中序遍历二叉树\n");
	printf("3.后序遍历二叉树\n");
	printf("4.求二叉树深度\n");
	printf("5.交换二叉树左右子树\n");
	printf("0.退出\n");
	printf("请输入你的选择:");
	scanf("%d",&input);
	
	return input;
 } 
//测试 
 int main()
 {
 	SqStack* s;
 	PTree T;
 	PTree *p=(PTree*)malloc(sizeof(PTree));
    s=(SqStack*)malloc(sizeof(SqStack*));
   
 	init_stack(s);
 	printf("请输入第一个结点的值,#表示没有叶结点:");
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
 			case 4:deep=TreeDeep(T);printf("深度是%d\n",deep);break;
 			case 5:Exchange(&T);break;
 			case 0:break;
 			default:break;
		  } 
		  choice=Item();
	 }
	printf("\n—————————程序结束—————————\n\n");
 	return 0;
 }
 //abc##d##e##
