/*
������һ����������Ϊ���͵�һά����A��A �е�����Ԫ�س�����״̬����дһ�����ö����򷨽�A�е�����Ԫ�ذ���С�����������ĳ���
*/
#include <stdio.h>
#include <stdlib.h>
//������� 
void  swap(int *a,int *b)
{
	int temp =*b;
	*b=*a;
	*a=temp;
}
//��start��end��Χ�ڹ������� 
void max_heapify(int arr[],int start,int end)
{
	int father=start;
	int son=father*2+1;//���Ӻ��� 
	while(son<=end)//���ӽڵ��ڱȽϷ�Χ�ڣ�����бȽ� 
	{
		if(son+1<=end&&arr[son]<arr[son+1])//��son+1�������ȽϷ�Χ���������Ӻ��ӣ��Ƚ��������ӽڵ�ıȽϣ��ȽϽ�����son��������һ�� 
			son++;
		if(arr[father]>arr[son])//������ڵ�����ӽڵ���������ϣ�ֱ������
			return;
		else//���򽻻��������ݣ��ټ����ӽڵ������ıȽ� 
		{
			swap(&arr[father],&arr[son]);
			father=son;
			son=father*2+1;
		 } 
		
	 } 
}
//������ 
void heap_sort(int arr[],int len)
{
	int i;
	for(i=len/2-1;i>=0;i--)	//��ʼ���������һ�����ڵ㿪ʼ����
	{
		max_heapify(arr,i,len-1);
	}
	for(i=len-1;i>0;i--)//�Ƚ���һ��Ԫ�غ����ź�Ԫ�ص�ǰһλ�������������µ�����ֱ��������� 
	{
		swap(&arr[0],&arr[i]);//���ΰѴ�ʱ�����������ֵ�ŵ�������� 
		max_heapify(arr,0,i-1);
	}
}
int main()
{
	int arr[]={16,7,3,10,17,8};
	int len=(int)sizeof(arr)/sizeof(*arr);
	heap_sort(arr,len);//��ʱ�������Ѿ����ź����Ԫ���� 
	int i;
	for(i=0;i<len;i++)
	{
		printf("%d ",arr[i]);
	}
	printf("\n");
	return 0;
 } 
