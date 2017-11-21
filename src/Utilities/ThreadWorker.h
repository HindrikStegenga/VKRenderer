//
// Created by hindrik on 14-11-17.
//

#ifndef VKRENDERER_THREADWORKER_H
#define VKRENDERER_THREADWORKER_H

#include <functional>
#include <mutex>


class ThreadPool;

class ThreadWorker final
{
public:
    explicit ThreadWorker(ThreadPool &s) : pool(&s) { }
    void operator()();

    ThreadWorker()  = delete;
    ~ThreadWorker() = default;

    ThreadWorker(const ThreadWorker&)       = delete;
    ThreadWorker(ThreadWorker&&) noexcept   = default;

    ThreadWorker& operator=(const ThreadWorker&)        = delete;
    ThreadWorker& operator=(ThreadWorker&&) noexcept    = default;
private:
    ThreadPool* pool;
};


#endif //VKRENDERER_THREADWORKER_H
