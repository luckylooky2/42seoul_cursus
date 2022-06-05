#include <stdio.h>
#include <stdlib.h>

typedef struct s_a
{
	int i;
	char *ii;
} t_a;

void ccc(t_a *a)
{
	(a)->ii = (char *)malloc(sizeof(char) * 120);
}

void bbb(t_a *a)
{
	a->i = 150;
	printf("%s", a->ii);
	ccc(a);
	(a)->ii[10] = 'A';
	printf("1 : %c\n", a->ii[10]);
}

void aaa(t_a *a)
{
	a->i = 120;
	bbb(a);
}

int main()
{
	t_a a;

	a.i = 0;
	a.ii = NULL;
	aaa(&a);
	printf("2 : %c\n", a.ii[10]);
	printf("%d\n", a.i);
}