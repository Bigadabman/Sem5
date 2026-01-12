#include <stdio.h>
#include <unistd.h>
#include <sys/mman.h>

int main()
{

    long pageSize = sysconf(_SC_PAGESIZE);

    printf("Page size: %ld bytes\n\n", pageSize);


    printf("-------- 1 stage ------------\n\n");

    void* baseAddr = mmap(
        NULL,
        pageSize * 256,
        PROT_NONE,
        MAP_PRIVATE | MAP_ANONYMOUS,
        -1,
        0
    );

    if (baseAddr == MAP_FAILED)
    {
        perror("mmap failed");
        return 1;
    }

    printf("Reserved virtual memory address: %p\n\n", baseAddr);
    getchar();


    printf("\n-------- 2 stage ------------\n\n");

    void* secondHalf = (char*)baseAddr + pageSize * 128;

    if (mprotect(
        secondHalf,
        pageSize * 128,
        PROT_READ | PROT_WRITE) != 0)
    {
        perror("mprotect failed");
        return 1;
    }

    printf("Physical memory committed for second half (READ | WRITE)\n\n");
    getchar();


    printf("\n-------- 3 stage ------------\n\n");

    int* ptr = (int*)secondHalf;
    int count = (pageSize * 128) / sizeof(int);

    for (int i = 0; i < count; i++)
        ptr[i] = i;

    printf("Second half filled with integers\n\n");
    getchar();


    printf("\n-------- 4 stage ------------\n\n");

    if (mprotect(
        secondHalf,
        pageSize * 128,
        PROT_READ) != 0)
    {
        perror("mprotect failed");
        return 1;
    }

    printf("Protection changed to READ ONLY\n\n");
    getchar();


    printf("\n-------- 5 stage ------------\n\n");

    if (munmap(secondHalf, pageSize * 128) != 0)
    {
        perror("munmap failed");
        return 1;
    }

    printf("Second half (128 pages) unmapped\n\n");
    getchar();

    printf("\n-------- 6 stage ------------\n\n");

    if (munmap(baseAddr, pageSize * 128) != 0)
    {
        perror("munmap failed");
        return 1;
    }

    printf("First half (128 pages) unmapped\n\n");
    getchar();

    return 0;
}
