#cc -I /Library/Java/JavaVirtualMachines/jdk1.8.0_161.jdk/Contents/Home/include -c HelloWorldImpl.cc
#gcc -I /usr/lib/jvm/java-1.8.0-openjdk-1.8.0.201.b09-2.el7_6.x86_64/include/ -fPIC -c HelloWorldImpl.c
#gcc -shared -Wl,-soname,libhello.so.1 -o libhello.so.1.0.1 HelloWorldImpl.o -lc
cc -I /usr/lib/jvm/java-1.8.0-openjdk-1.8.0.201.b09-2.el7_6.x86_64/include/ -fPIC -shared -o libhello.so HelloWorldImpl.c
cc -I /usr/lib/jvm/java-1.8.0-openjdk-1.8.0.201.b09-2.el7_6.x86_64/include/ -fPIC -shared -o libutil.so freeUtil.c 

