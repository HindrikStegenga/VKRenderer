//
// Created by hindrik on 14-11-17.
//

#include "Threadpool.h"
#include "ThreadWorker.h"

Threadpool::Threadpool(size_t threads) : stop(false)
{
    for (size_t i = 0; i < threads; ++i)
        workers.emplace_back(ThreadWorker(*this));
}

Threadpool::~Threadpool()
{
    stop = true;
    cond.notify_all();
    for (auto &thread : workers)
        thread.join();
}