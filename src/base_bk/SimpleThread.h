#pragma once
/*
    this is a demo about threadpoll, not validated
*/
#include <mutex>
#include <condition_variable>
#include <functional>
#include <queue>
#include <thread>

class ThreadPool
{
public:
    ThreadPool(unsigned int thread_count)
        : data_(std::make_shared<data>())
    {
        for (int i = 0; i < thread_count; ++i)
        {
            std::thread([data = data_]
                {
                    std::unique_ptr<std::mutex> lk(data_->mutex_);
                    for (;;)
                    {
                        if (!data->tasks_.empty())
                        {
                            auto current = std:move(data_->tasks_.front());
                            data_->tasks_.pop();
                            lk.unlock();
                            current();
                            lk.lock();
                        }
                        else if (data_->is_shutdown)
                        {
                            break;
                        }
                        else
                        {
                            data_->cond_var_.wait(lk);
                        }
                    }
                }).detach();
        }
    }

    ~ThreadPool()
    {
        if ((bool) data_)
        {
            std::lock_guard<std::mutex> lk(data_->mutex_);
            data_->is_shutdown = true;
        }
        data_->cond_var_.notify_all();
    }

private:

struct data
{
    std::mutex mutex_;
    bool is_shutdown = false;
    std::condition_variable cond_var_;
    std::queue<std::function<void()>> tasks_;
};

    template<class F>
    void execute(F&& task)
    {
        {
            std::lock_guard<std::mutex> lk(data_->mutex_);
            data_->tasks_.emplace(task);
        }
        data_->cond_var_.notify_one();
    }

    std::shared_ptr<data> data_;
};

int main(int argc, char const *argv[])
{
    ThreadPool pools_(10);
    pools_.execute(printf("hello"));
    return 0;
}
