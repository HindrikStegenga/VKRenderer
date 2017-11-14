//
// Created by hindrik on 14-11-17.
//

#ifndef VKRENDERER_THREADPOOL_H
#define VKRENDERER_THREADPOOL_H


#include <thread>
#include <mutex>
#include <iostream>
#include <vector>
#include <deque>
#include <condition_variable>
#include <functional>

class ThreadPool final
{
public:
    explicit ThreadPool(size_t threads);
    template<class F> void enqueue(F f);
    ~ThreadPool();
private:
    friend class ThreadWorker;

    std::vector<std::thread> workers;
    std::deque<std::function<void()>> tasks;
    std::condition_variable cond;
    std::mutex queue_mutex;
    bool stop;
};

template<class F>
void ThreadPool::enqueue(F f)
{
    std::unique_lock<std::mutex> lock(queue_mutex);
    tasks.push_back(std::function<void()>(f));
    lock.unlock();
    cond.notify_one();
}


#endif //VKRENDERER_THREADPOOL_H
