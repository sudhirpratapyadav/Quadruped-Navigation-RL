#include<iostream>
using namespace std;

int main(){
	int *p1;
	int *p2;

	p1 = (int *)malloc(10 * sizeof(int));
	p2 = (int *)malloc(10 * sizeof(int));

	for (int i = 0; i < 10; i++)
	{
		p1[i] = i + 1;
		p2[i] = i + 15;
	}

	for (int i = 0; i < 10; i++)
	{
		printf("%d\t%d\n", p1[i],p2[i]);
	}
	
	int *temp;
	temp = p1;
	p1 = p2;
	p2 = temp;
	
	for (int i = 0; i < 10; i++)
	{
		printf("%d\t%d\n", p1[i], p2[i]);
	}



	
	return 0;
}