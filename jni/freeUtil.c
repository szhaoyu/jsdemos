#include "freeUtil.h"  
#include <stdio.h>  
#include <string.h>  
#include <stdlib.h>  
#include <jni.h>  
#include <fcntl.h>
#include <sys/types.h>
#include <sys/mman.h>

/* 
 * Class:     HelloWorld 
 * Method:    displayHelloWorld 
 * Signature: ()V 
 */  
JNIEXPORT void JNICALL Java_HelloWorld_unmapMemory
  (JNIEnv *jEnv, jobject jobj, jlong address, jlong len)  
{  
	munmap( (void*)address, len );
    return;  
}  

