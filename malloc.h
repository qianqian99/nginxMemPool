#include <iostream>
class NginxMalloc;
class LargeMalloc;
class ControlMsg;
class Pool;
class LargeMalloc
{
    public:
        LargeMalloc *next;
        void *alloc;
};
class ControlMsg
{
    public:
        char *last;
        char *end;
        ControlMsg *next;
        char failed;
        int getSize()
        {
            return end - last;
        }
};
class Pool
{
    public:
        ControlMsg msg;
        Pool *current;
        LargeMalloc *large;
};
class NginxMalloc
{
    private:
        Pool *_pool;
        const size_t large_sz_limit;
    public:
        NginxMalloc(size_t data_size=1024);
        void *allocate(size_t n);
        void *large_malloc(size_t n);
        void large_free(void *p);
        void *allocate_block(size_t n, size_t data_size=1024);
        ~NginxMalloc();
};
