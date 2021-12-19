#include <stdio.h>
#include <stdlib.h>
#include "list.h"

void addToList(int arr[], int x, int val) {
	arr[x]=val;
}

int inList(int arr[], int x, int val)
{
    for (int i = 0; i < x; i++)
    {
        if (arr[i] == val)
        {
            return 0;
        }
    }
    return 1;
}

void printList(int arr[], int x)
{
    printf("CallList: ");
    for (int i = 0; i < x; i++)
    {
        if (arr[i] <= 15)
        {
            if (arr[i] < 10)
            {
                printf("L0%d ", arr[i]);
            }
            else
            {
                printf("L%d ", arr[i]);
            }
        }
        else if (arr[i] > 15 && arr[i] <= 30)
        {
            printf("I%d ", arr[i]);
        }
        else if (arr[i] > 30 && arr[i] <= 45)
        {
            printf("N%d ", arr[i]);
        }
        else if (arr[i] > 45 && arr[i] <= 60)
        {
            printf("U%d ", arr[i]);
        }
        else
        {
            printf("X%d ", arr[i]);
        }
    }
    printf("\n");
}
