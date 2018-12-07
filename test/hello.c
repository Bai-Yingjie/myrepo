#include <stdio.h>

int main(void)
{
	srand((int)time(0));
	int r=rand()%10;
	printf("%d Hello ARMv8 world!\n", r);
	
	int i;
	int a[r];
	for(i=0; i<=r; i++)
	{
		a[i]=i;
		printf("a[%d]=%d\n", a[i], i);
	}
}
