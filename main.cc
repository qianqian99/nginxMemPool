#include "./malloc.h"
int main(int argc, char *argv[])
{
    NginxMalloc MemPool;
    char *p = (char *)MemPool.allocate(10);
    return 0;
}
