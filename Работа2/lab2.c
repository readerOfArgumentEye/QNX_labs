#include <stdio.h>
#include <pthread.h>
#include <sys/neutrino.h>
#include <sched.h>
#include <errno.h>

pthread_t thread_id1;
pthread_t thread_id2;

void set_thread_policy_and_priority(pthread_t thread_id, int policy, int priority){
    struct sched_param param;
    param.sched_priority = priority;
    if (pthread_setchedparam(thread_id, policy, &param) != 0)
        perror("pthread_setshedparam");
}

void* long_thread1(void* notused){
    int n;
    for (n = 0; n < 5; n++){
        printf("Flow 1, TID %lu - step %d\n", thread_id1, n);
        sleep(2);
    }
}

void* long_thread2(void* notused){
    int n;
    for (n = 0; n < 5; n++){
        printf("Flow 2, TID %lu - step %d\n", thread_id2, n);
        sleep(1);
    }
}

int main(){
    pthread_create(&thread_id1, NULL, long_thread1, NULL);
    pthread_create(&thread_id2, NULL, long_thread2, NULL);
    set_thread_policy_and_priority(thread_id1, SCHED_RR, 16);
    set_thread_policy_and_priority(thread_id2, SCHED_FIFO, 11);
    sleep(40);
    return 0;
}
