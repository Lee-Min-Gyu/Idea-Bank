#include <stdio.h>
int main (void)
{
	int arr[5] = {1,2,3,4,5}, *ptr=arr;
	for (int i= 0; i<5; i++)
		*ptr+=2, printf("%d\n", *ptr++);
		
	return0;
}
