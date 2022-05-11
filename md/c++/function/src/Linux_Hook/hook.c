#include <stdio.h>
#include <string.h>
#include <dlfcn.h>
#include <stdlib.h>

/*
hook的目标是strcmp，所以typedef了一个STRCMP函数指针
hook的目的是要控制函数行为，从原库libc.so.6中拿到strcmp指针，保存成old_strcmp以备调用
*/
typedef int(*STRCMP)(const char*, const char*);
 
int strcmp(const char *s1, const char *s2)
{
  static void *handle = NULL;
  static STRCMP old_strcmp = NULL;
    
  handle = dlopen ("libc.so.6", RTLD_LAZY);  
  if (!handle) {  
     fprintf (stderr, "%s ", dlerror());  
     exit(1);  
  }
  else
  {
     old_strcmp = (STRCMP)dlsym(handle, "strcmp"); 
  }
   
  printf("oops!!! hack function invoked. s1=<%s> s2=<%s>\n", s1, s2);
  dlclose(handle);
  return old_strcmp(s1, s2);
}