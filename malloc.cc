#include <iostream>
#include <cassert>
#include "./malloc.h"
#include <cstdlib>
NginxMalloc::NginxMalloc(size_t data_size) 
{
    size_t total_sz = size + sizeof(NginxMalloc);
    Pool *pool = (Pool *)malloc(total_sz);
    assert(pool != NULL);
    pool->msg.last = pool + sizeof(NginxMalloc);
    pool->msg->end = pool + data_size;
    pool->msg->next = NULL;
    pool->msg->failed = 0;

    pool->left_size = data_size;
    pool->current = pool;
    pool->large = NULL; 

    _pool = pool;
}
void *NginxMalloc::allocate(size_t n)
{
    if (n <= _pool->left_size)
    {

    }
    return large_malloc(n);
}
void *NginxMalloc::large_malloc(size_t n)
{
    void *newMem = malloc(n);
    assert (newMem != NULL);
    int n = 0;
    for (LargeMalloc *p=_pool->large; p!=NULL; p=p->next)
    {
        if (p->alloc == NULL) p->alloc = newMem;
        if (++n > 3) break;
    }
    LargeMalloc *newLarge = (LargeMalloc *)allocate(sizeof(LargeMalloc));
    assert(newLarge != NULL);
    newLarge->alloc = newMem;
    newLarge->next = _pool->large;
    _pool->large = newLarge;
}
