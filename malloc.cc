#include <iostream>
#include <cassert>
#include "./malloc.h"
#include <cstdlib>
NginxMalloc::NginxMalloc(size_t data_size) : large_sz_limit(data_size/8) 
{
    size_t total_sz = size + sizeof(NginxMalloc);
    Pool *pool = (Pool *)malloc(total_sz);
    assert(pool != NULL);
    pool->msg.last = pool + sizeof(NginxMalloc);
    pool->msg->end = pool + data_size;
    pool->msg->next = NULL;
    pool->msg->failed = 0;

    pool->current = pool;
    pool->large = NULL; 

    _pool = pool;
}
void *NginxMalloc::allocate(size_t n)
{
    if (n <= large_sz_limit)
    {
        ControlMsg *p = static_cast<ControlMsg *>(_pool);
        while (p != NULL)
        {
            size_t left_sz = getSize(p->end, p->last);
            /*can get mem*/
            if (left_sz >= n)
            {
                //todo
            }
            p = p->next;
        }
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
        if (p->alloc == NULL) 
        {
            p->alloc = newMem;
            return newMem;
        }
        if (++n > 3) break;
    }
    LargeMalloc *newLarge = (LargeMalloc *)allocate(sizeof(LargeMalloc));
    if (newLarge == NULL) 
    {
        large_free(newMem);
        return NULL;
    }
    newLarge->alloc = newMem;
    newLarge->next = _pool->large;
    _pool->large = newLarge;
    return newMem;
}
void NginxMalloc::large_free(void *arg)
{
    for (LargeMalloc *p=_pool->large; p!=NULL; p=p->next)
    {
        if (arg == p->alloc) {
            free(arg);
            p->alloc = NULL;
        }
    }
}
