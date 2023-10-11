#include <stdlib.h>
#include <stdio.h>

int main(int argc, char **argv) {
	// int arr[3][3] = {
	// 	{1, 2, 3},
	// 	{1, 2, 3},
	// 	{1, 2, 3}
	// };
	int **arr = malloc(sizeof(int *) * 3);
	for (int i = 0; i < 3; i++) {
		arr[i] = malloc(sizeof(int) * 3);
	}
	arr[0][0] = 1;
	arr[0][1] = 2;
	arr[0][2] = 3;
	//..
	printf("%lu\n", sizeof(arr) + sizeof(arr[0]) * 3 + sizeof(int) * 9);
	
	for (int i = 0; i < 3; i++) {
		free(arr[i]);
		arr[i] = NULL;
	}
	free(arr);
	arr = NULL;

	return (0);
}