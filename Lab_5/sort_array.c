// Run as gcc -pthread sort_array.c then ./a.out

#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#define SIZE 10

// Global array declaration
int arr[SIZE] = {7, 12, 19, 3, 18, 4, 2, 6, 15, 8};

// Structure to store data that is provided to threads
typedef struct thread_data
{
    int thread_num;
    int left;
    int right;
} thread_data;

void *bubble_sort(void *ptr)
{
    thread_data *data;
    data = (thread_data *)ptr;
    int left = data->left;
    int right = data->right;
    int length = right - left + 1;
    for (int i = 0; i < length; i++)
    {
        for (int j = left; j < right - i; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                // swapping unsorted elements in bubble sort
                int temp = arr[j + 1];
                arr[j + 1] = arr[j];
                arr[j] = temp;
            }
        }
    }
}

void *merge_array(void *ptr)
{
    thread_data *data;
    data = (thread_data *)ptr;

    int i = 0, j = SIZE / 2;
    int temp[SIZE];
    for (int i = 0; i < SIZE; i++)
    {
        temp[i] = arr[i];
    }

    int k = 0;

    while (i < SIZE / 2 && j < SIZE)
    {
        if (temp[i] < temp[j])
        {
            arr[k] = temp[i];
            i++;
        }
        else
        {
            arr[k] = temp[j];
            j++;
        }
        k++;
    }

    while (i < SIZE / 2)
    {
        arr[k] = temp[i];
        i++;
        k++;
    }
    while (j < SIZE)
    {
        arr[k] = temp[j];
        j++;
        k++;
    }
}

int main()
{
    pthread_t thread1, thread2, thread3;
    thread_data data1, data2, data3;

    data1.thread_num = 1;
    data1.left = 0;
    data1.right = SIZE / 2 - 1;

    data2.thread_num = 2;
    data2.left = SIZE / 2;
    data2.right = SIZE - 1;

    data3.thread_num = 3;
    data3.left = 0;
    data3.right = SIZE - 1;

    pthread_create(&thread1, NULL, bubble_sort, &data1);
    pthread_create(&thread2, NULL, bubble_sort, &data2);
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    pthread_create(&thread3, NULL, merge_array, &data3);
    pthread_join(thread3, NULL);

    for (int i = 0; i < SIZE; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
    return 0;
}