# nginxMemPool
开始学习nginx内存池<br>
## 总结
看完了nginx 的代码之后， 自己仿照源码用cpp写了一个
类似的内存池， 和malloc比较了了申请的快慢， 在基数是1024B的池单位中，
反复申请内存30240000次自己写的用了
./main  11.45s user 6.68s system 22% cpu 1:20.50 total
而malloc却只用了21秒./demo  4.52s user 4.33s system 40% cpu 21.791 total
<br><br>
总结来说， 性能上没有差别， 但是却从根本上减少了内存碎片的产生， 大块内存的申请。
另外nginx上的内存池没有free内存的函数，这也是其应用场所决定的，
事实上，nginx会不止建立一个内存池，nginx给内存池分了不同的等级，
进程级的内存池 connection级的内存池，
request级别的内存池 模块也可以有自己的内存池。所以等到connect或者是request结束
后进行destory就可以。此外， 这个内存池并不会利用内存很完全，
池中会存在小块内存无法使用到。
