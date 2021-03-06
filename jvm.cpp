//
// Created by xyzjiao on 11/9/21.
//

#include "./include/common.h"
#include "./thread/oop/JavaThread.h"

int JavaMain(void* args) {
    JavaThread* t1 = new JavaThread("t1");
    JavaThread* t2 = new JavaThread("t2");

    t1->run();
    t2->run();

    t1->join();
    t2->join();

    return 100;
}

int ContinueInNewThread0(void* args) {
    int rslt;

    pthread_t  tid;
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

    if (pthread_create(&tid, &attr, reinterpret_cast<void *(*)(void *)>(JavaMain), (void*) args) == 0) {
        void* tmp;
        pthread_join(tid, &tmp);
        rslt = (int)(long)tmp;
    }

    pthread_attr_destroy(&attr);

    return rslt;
}

int continueInNewThread() {
    int rslt;

    rslt = ContinueInNewThread0(NULL);

    return rslt;

}