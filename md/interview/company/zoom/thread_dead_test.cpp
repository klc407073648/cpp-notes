#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

using namespace std;

#define NUM_THREADS 5

void* proca(void*)
{
    printf("In ProcA\n");
    sleep(5);
    printf("ProcA: Try Throw...\n");
    throw 3;
}
void* procb(void*)
{
    printf("In ProcB\n");
    //printf("ProcA: Try Throw...\n");
    //throw 4;
}

int main()
{
    pthread_t tids[NUM_THREADS];
    printf("In Main Thread.\n");
    int ret = pthread_create( &tids[0], NULL, proca, NULL);
    printf("ProcA Started.\n");
    ret = pthread_create( &tids[1], NULL, procb, NULL);
    printf("ProcB Started.\n");

    sleep(10);
    printf("Start joining A\n");
    pthread_join(tids[0], NULL);
    printf("Start joining B\n");
    pthread_join(tids[1], NULL);

    return 0;
}

/*
[root@VM-16-6-centos test]# g++ -g -o test test.cpp -lpthread
[root@VM-16-6-centos test]# ./test
In Main Thread.
ProcA Started.
ProcB Started.
In ProcA
In ProcB
ProcA: Try Throw...
terminate called after throwing an instance of 'int'
Aborted


*/