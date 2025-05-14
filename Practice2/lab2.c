#include <stdio.h>
#include <pthread.h>
#include <sys/neutrino.h>
#include <sched.h>
#include <errno.h>

pthread_t thread_id1;
pthread_t thread_id2;

void configure_thread_attributes(pthread_attr_t *attr, int policy, int priority) {
    pthread_attr_init(attr);
    struct sched_param param;
    param.sched_priority = priority;
    pthread_attr_setinheritsched(attr, PTHREAD_EXPLICIT_SCHED);
    pthread_attr_setschedpolicy(attr, policy);
    pthread_attr_setschedparam(attr, &param);
}

void* long_thread1(void* notused) {
    int n;
    for (n = 0; n < 5; n++) {
        printf("Flow 1, TID %lu - step %d\n", thread_id1, n);
        sleep(2);
    }
}

void* long_thread2(void* notused) {
    int n;
    for (n = 0; n < 5; n++) {
        printf("Flow 2, TID %lu - step %d\n", thread_id2, n);
        sleep(1);
    }
}

int main() {
    printf("Group i913b\nStudent: Prikhodko Mikhail\n");
    pthread_attr_t attr1, attr2;
    // установка значений атрибутов для потоков
    configure_thread_attributes(&attr1, SCHED_RR, 16);
    configure_thread_attributes(&attr2, SCHED_FIFO, 11);
    // Создание потоков с настроенными атрибутами
    pthread_create(&thread_id1, &attr1, long_thread1, NULL);
    pthread_create(&thread_id2, &attr2, long_thread2, NULL);
    // Освобождение ресурсов атрибутов
    pthread_attr_destroy(&attr1);
    pthread_attr_destroy(&attr2);
    sleep(40);
    return 0;
}
