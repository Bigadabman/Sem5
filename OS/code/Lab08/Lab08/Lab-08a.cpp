#include <stdio.h>

int fibonacci(int num)
{
    int someLocalInt = 15;
    int someNoValInt;

    static int someIntStaticLocal = 20;
    static int someNoValStaticLocal;

    if (num == 5)
    {
        printf("someLocalInt address: %p\n", (void*)&someLocalInt);
        printf("someNoValInt address: %p\n", (void*)&someNoValInt);
        printf("someIntStaticLocal address: %p\n", (void*)&someIntStaticLocal);
        printf("someNoValStaticLocal address: %p\n", (void*)&someNoValStaticLocal);
    }

    if (num < 2)
        return 1;

    return fibonacci(num - 1) + fibonacci(num - 2);
}

char GlobalVal = 5;
int  GlobalNoVal;

static int someIntStatic = 10;
static int someNoValStatic;

int main(int argc, char* argv[])
{
    printf("Function fibonacci address: %p\n", (void*)&fibonacci);

    printf("GlobalVal address: %p\n", (void*)&GlobalVal);
    printf("GlobalNoVal address: %p\n", (void*)&GlobalNoVal);

    printf("someIntStatic address: %p\n", (void*)&someIntStatic);
    printf("someNoValStatic address: %p\n", (void*)&someNoValStatic);

    printf("argc address: %p\n", (void*)&argc);
    printf("argv address: %p\n", (void*)&argv);

    fibonacci(5);

    getchar();
    return 0;
}
