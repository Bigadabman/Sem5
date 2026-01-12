#include <stdio.h>
#include <stdlib.h>

int main()
{
    const int BLOCK_COUNT = 10;
    const size_t BLOCK_SIZE = 512 * 1024;   

    void* blocks[BLOCK_COUNT] = { 0 };


    printf("-------- 1 stage --------\n\n");

    for (int i = 0; i < BLOCK_COUNT; i++)
    {
        blocks[i] = malloc(BLOCK_SIZE);
        if (blocks[i] == NULL)
        {
            printf("malloc failed at block %d\n", i);
            return 1;
        }

        printf("Allocated block %d at address %p\n", i, blocks[i]);
    }

    getchar();


    printf("\n-------- 2 stage --------\n\n");

    for (int i = 0; i < BLOCK_COUNT; i++)
    {
        int* arr = (int*)blocks[i];
        int count = BLOCK_SIZE / sizeof(int);

        for (int j = 0; j < count; j++)
            arr[j] = j;
    }

    printf("All blocks filled with integers\n");
    getchar();


    printf("\n-------- 3 stage --------\n\n");

    for (int i = 0; i < BLOCK_COUNT; i++)
    {
        free(blocks[i]);
        printf("Freed block %d\n", i);
    }

    getchar();

    printf("\n-------- 4 stage --------\n\n");

    printf("Heap destroyed\n");
    getchar();

    return 0;
}
