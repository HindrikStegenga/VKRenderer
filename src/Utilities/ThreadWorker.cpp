//
// Created by hindrik on 14-11-17.
//

#include "ThreadWorker.h"
#include "Threadpool.h"

void ThreadWorker::operator()()
{
    std::function<void()> task;
    while (true)
    {
        std::unique_lock<std::mutex> locker(pool.queue_mutex);
        pool.cond.wait(locker, [this]() -> bool { return !pool.tasks.empty() || pool.stop; });
        if (pool.stop) { locker.unlock(); return; };
        if (!pool.tasks.empty())
        {
            task = pool.tasks.front();
            pool.tasks.pop_front();
            locker.unlock();
            task();
        }
        else {
            locker.unlock();
        }
    }
}