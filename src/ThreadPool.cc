#include "ThreadPool.h"

// some static definition, like c, not c++11, will improve.
// first version just to learn

pthread_mutex_t ThreadPool::mutex_ = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t ThreadPool::notify_ = PTHREAD_COND_INITIALIZER;
std::vector<pthread_t> ThreadPool::threads_;
std::vector<ThreadPoolTask> ThreadPool::queues_;
int ThreadPool::threadCounts_ = 0;
int ThreadPool::queueSizes_ = 0;
int ThreadPool::head_ = 0;
int ThreadPool::tail_ = 0;
int ThreadPool::count_ = 0;
int ThreadPool::shutDown_ = 0;
int ThreadPool::started_ = 0;

int ThreadPool::createThreadPool(int threadCounts, int queueSizes)
{
    bool err;

    if (threadCounts < 0 || threadCounts > MAX_THREADS || queueSizes > MAX_QUEUE || queueSizes < 0)
    {
        threadCounts = 4;
        queueSizes_ = 1024;
    }

    threadCounts_ = threadCounts;
    queueSizes_ = queueSizes;
    head_ = tail_;
    count_ = shutDown_ = started_ = 0;

    do
    {
        for (int i = 0; i < threadCounts; ++i)
        {
            if (pthread_create(&threads_[i], NULL, threadPoolThread, (void *)(0)))
            {
                return -1;
            }
            started_ ++;
            threadCounts_++;
        }
    }
    while (false);

    if (err)
    {
        return -1;
    }

    return 0;
}

int ThreadPool::addToThreadPool(std::function<void(std::shared_ptr<void>)> task, std::shared_ptr<void> args) {

    int next, err = 0;

    do {
        if (pthread_mutex_lock(&mutex_) != 0) {
            return THREADPOOL_LOCK_FAILURE;
        }

        next = (tail_ + 1) % queueSizes_;

        // queue is full
        if (count_ == queueSizes_)
        {
            return THREADPOOL_QUEUE_FULL;
        }

        // shutdown
        if (shutDown_)
            return THREADPOOL_SHUTDOWN;

        queues_[tail_].func = task;
        queues_[tail_].args = args;
        tail_ = next;
        count_++;

        // pthread_cond_broadcast, notify a thread
        if (pthread_cond_signal(&notify_) != 0)
        {
            return THREADPOOL_LOCK_FAILURE;
        }

    } while (false);

    if (pthread_mutex_unlock(&mutex_))
        return THREADPOOL_LOCK_FAILURE;

    return err;
}

int ThreadPool::destroyThread(ShutDownOption shutDownOption) {
    printf("thread poll destroy\n");
    int i, err = 0;

    if (pthread_mutex_lock(&mutex_) != 0)
    {
        return -1;
    }

    do
    {
        if (shutDown_)
        {
            err = THREADPOOL_SHUTDOWN;
            break;
        }

        shutDown_ = shutDownOption;

        if ((pthread_cond_broadcast(&notify_) != 0)
            || pthread_mutex_unlock(&mutex_))
        {
            err = THREADPOOL_LOCK_FAILURE;
            break;
        }

        for (int i = 0; i < threadCounts_; ++i)
        {
            if (pthread_join(threads_[i], NULL) != 0)
            {
                err = THREADPOOL_THREAD_FAILURE;
            }
        }
    }
    while(false);

    if (!err)
    {
        freeThread();
    }
    return 0;
}

int ThreadPool::freeThread() {
    if (started_) return -1;

    pthread_mutex_lock(&mutex_);
    pthread_mutex_unlock(&mutex_);
    pthread_cond_destroy(&notify_);
    return 0;
}

void *ThreadPool::threadPoolThread(void *args) {
    do
    {
        ThreadPoolTask task;
        pthread_mutex_lock(&mutex_);

        task.func = queues_[head_].func;
        task.args = queues_[head_].args;
        head_ = (head_ + 1) % queueSizes_;
        // execute task
        pthread_mutex_unlock(&mutex_);
        (task.func)(task.args);

    } while (false);

//    pthread_mutex_unlock(&mutex_);
    printf("This threadpool thread finishs!\n");
//    pthread_exit(NULL);
    return NULL;
}
