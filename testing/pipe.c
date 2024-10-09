#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

int main()
{
	char *comm[10][10] = {
	{"ls", NULL},
	{"grep", "i", NULL},
	{NULL}};
/*	char *comm[10][10] = {{"cat", NULL}, {"cat", NULL}, {"ls", NULL}, NULL};*/

	int i, j = 0;
	for (i = 0; comm[i]; i++)
	{
		for (j = 0; comm[i][j]; j++)
		{
			printf("%s, ", comm[i][j]);
		}
		printf("\n");
	}
	return (0);
}
