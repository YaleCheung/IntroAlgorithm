/*@@
  @Program:quick_sort
  @Author:zhangyi
  @Date:2013.5.3
  @Version:1.0
  @@*/
#ifdef QSort_HHH
#define QSort_HHH
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
using std::endl;
using std::cout;
int Swap(int* First,int* Second)
{
	int tmp = *First;
	*First = *Second;
	*Second = tmp;
}
int RandInRange(const int& start,const int& end)
{
	return rand() % (end - start + 1) + start;
}
void Patition(int* Array,const int& begin,const int& end)
{
	int start = begin;
	int final = end;
	index = RandInRange(begin,end);
	Swap(Array + start,Array + final);
	small = index - 1;
	int i = begin;
	while(i < end)
	{
		if(Array[i] < Array[end])
		{
			small ++;
			Swap(&Array[i],&Array[small]);
		}
		i ++;
	}
	small ++;
	Swap(&Array[small],&Array[end]);
	return small;
}
void QSort(*Array,begin,end)
{
	if(Array != NULL && begin >= 0 && end >=0)
	{
		index = Patition(Array,begin,end);
		if(index < end)
			QSort(Array,index,end);
		if(index > begin)
			QSort(Array,begin,index);
	}
}
#endif

