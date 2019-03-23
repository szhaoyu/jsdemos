#1. 观察进程中内存地址分配的工具

pmap <pid>

#2. jvm heap空间新生代、永久代，young old
JVM进程地址中，java的堆地址从低地址开始分配.

如：byte[] data=new byte[100]

在低地址空间分配对应的块儿。假如设置-Xms256M -Xmx256M，则对应如下的地址空间段，从高地址0x0000000100080000超低地址空间申请了256M.

00000000f0000000 262656K rw---   [ anon ]
0000000100080000 1048064K -----   [ anon ]


#3. jni native动态库中malloc内存

从高地址向低地址空间分配。

如：申请了256M，下一段即时对应空间
00007f20b3bfe000 528392K rw---   [ anon ]
00007f20d4000000    132K rw---   [ anon ]


#4. 使用munmap在卸载动态库后释放native代码申请的jvm堆外内存空间


#5. 卸载native动态库会释放native对jvm堆中jni层的内存引用，包括localReference、globalReference


