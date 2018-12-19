/*
    一堆猴子都有编号，编号是1，2，3 ...m，这群猴子（m个）按照1-m的顺序围坐一圈，从第1开始数，每数到第n个，该猴子就要离开此圈，
这样依次下来，直到圈中只剩下最后一只猴子，则该猴子为大王。
要求：m及n要求从键盘输入，存储方式采用向量及链表两种方式实现该问题求解。 
*/ 

//向量求解
#include <stdio.h>
void initialize(int Monkey[],int m);
int choose_king(int Monkey[],int m,int n);
void output(int Monkey[],int m); 

int main()
{
	int Monkey[100];
	int m,n,king;
	
	printf("请输入猴子个数m:");
	scanf("%d",&m);
	printf("\n报数规则n：");
	scanf("%d",&n);
	if(m<=0|n<=0)
	{
		printf("\n输入错误！请重新输入！");
		printf("\n请输入猴子个数m及报数规则n：");
		scanf("%d,%d",&m,&n);
	}
	
	initialize(Monkey,m);//初始化数组 
	king=choose_king(Monkey,m,n);//选王 
	printf("\n王是第%d只猴子\n",king);
	 
	return 0;
}
//输出 
void output(int Monkey[],int m)
{
	int i;
	for(i=0;i<m;i++)
	{
		printf("Monkey[%d]=%d\n",i,Monkey[i]);
	}
}
//初始化数组元素 
void initialize(int Monkey[],int m)
{
	int i;
	for(i=0;i<m;i++)
	{
		Monkey[i]=i+1;//为猴子数组赋值，从1开始 
	}
	for(i=m;i<sizeof(Monkey);i++)
	{
		Monkey[i]=0;
	}
}
//选王
int choose_king(int Monkey[],int m,int n)
{
	int count=m;//计数器，记录当前还有几只猴子
	int i,j=0,king;//j始终在增加，通过取余来确定哪只猴子应该离开 
	while(count>1)//当猴子数大于1时，执行循环 
	{
		for(i=0;i<m;i++)//循环m次 
		{
			if(Monkey[i]!=0)//当时这只猴子还在队伍中 
			{
				j++;//计数变量加一 
				if(j%n==0)//余数为0，这只猴子应该离开 
				{
					Monkey[i]=0;//原本编号为i的猴子离开 
					count--;//队伍中猴子数减一 
					if(count==1)//当此时只剩下一只猴子时，结束循环 
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
现现在第3只猴子离开了,j=3
现在第6只猴子离开了,j=6
现在第4只猴子离开了,j=9
现在第2只猴子离开了,j=12
现在第5只猴子离开了,j=15

王是第1只猴子
*/
