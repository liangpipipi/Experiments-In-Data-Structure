/*
假设有一个数据类型为整型的一维数组A，A 中的数据元素呈无序状态，编写一个采用堆排序法将A中的数据元素按由小到大进行排序的程序。
*/
#include <stdio.h>
#include <stdlib.h>
//交换结点 
void  swap(int *a,int *b)
{
	int temp =*b;
	*b=*a;
	*a=temp;
}
//在start和end范围内构造大根堆 
void max_heapify(int arr[],int start,int end)
{
	int father=start;
	int son=father*2+1;//左子孩子 
	while(son<=end)//若子节点在比较范围内，则进行比较 
	{
		if(son+1<=end&&arr[son]<arr[son+1])//若son+1不超出比较范围，则是右子孩子，先进行两个子节点的比较，比较结束后son是最大的那一个 
			son++;
		if(arr[father]>arr[son])//如果父节点大于子节点代表调整完毕，直接跳出
			return;
		else//否则交换父子内容，再继续子节点和孙结点的比较 
		{
			swap(&arr[father],&arr[son]);
			father=son;
			son=father*2+1;
		 } 
		
	 } 
}
//堆排序 
void heap_sort(int arr[],int len)
{
	int i;
	for(i=len/2-1;i>=0;i--)	//初始化，从最后一个父节点开始调整
	{
		max_heapify(arr,i,len-1);
	}
	for(i=len-1;i>0;i--)//先将第一个元素和已排好元素的前一位作交换，在重新调整，直到排序完毕 
	{
		swap(&arr[0],&arr[i]);//依次把此时二叉树中最大值放到数组最后 
		max_heapify(arr,0,i-1);
	}
}
int main()
{
	int arr[]={16,7,3,10,17,8};
	int len=(int)sizeof(arr)/sizeof(*arr);
	heap_sort(arr,len);//此时数组中已经是排好序的元素了 
	int i;
	for(i=0;i<len;i++)
	{
		printf("%d ",arr[i]);
	}
	printf("\n");
	return 0;
 } 
