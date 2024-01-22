// File:   sort.c
// Author: Gregory K. Bowne
// Date:   15 DEC 2020
// Time:   13:56:21
// Brief:  This program sorts a set of numbers entered by the user

#include <stdio.h>
#define MAX 10

int how_many()
{
	int n;
	n = MAX + 1;

	while (n > MAX)
	{
		printf("How many numbers? ");
		scanf("%d", &n);
		printf("\n\n");
	}
	return n;
}

void getnums(int n, int v[])
{
	int x, num;

	for (x = 0; x < n; ++x)
	{
		printf("Enter number %d: ", x + 1);
		scanf("%d", &num);
		v[x] = num;
		printf("\n");
	}
}

void sort(int n, int v[])
{
	int swtch, x, temp;

	swtch = 1;
	while (swtch == 1)
	{
		swtch = 0;
		for (x = 0; x < n - 1; ++x)
			if (v[x] > v[x + 1])
			{
				temp = v[x];
				v[x] = v[x + 1];
				v[x + 1] = temp;
				swtch = 1;
			}
	}
}

void output(int n, int v[])
{
	int x;

	printf("Sort complete!\n\n");
	for (x = 0; x < n; ++x)
		printf("%d ", v[x]);
	printf("\n\n");
}

int main()
{
	int num;
	int val[MAX];

	num = how_many();
	getnums(num, val);
	sort(num, val);
	output(num, val);

	return 0;
}