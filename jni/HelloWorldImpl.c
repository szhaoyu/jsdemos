#include "HelloWorld.h"  
#include <stdio.h>  
#include <string.h>  
#include <stdlib.h>  
#include <jni.h>  
/* 
 * Class:     HelloWorld 
 * Method:    displayHelloWorld 
 * Signature: ()V 
 */  
JNIEXPORT void JNICALL Java_HelloWorld_displayHelloWorld  
  (JNIEnv *jEnv, jobject jobj)  
{  
    printf("Hello World!\n");  
    char* buffer = (char*)malloc(1024*1024*258);
    memset(buffer, 0, 100);
    char* buffer1 = (char*)malloc(1024*1024*258);
    memset(buffer1, 0, 100);
    getchar();
    return;  
}  

