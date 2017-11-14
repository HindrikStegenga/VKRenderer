//
// Created by hindrik on 14-11-17.
//

#include "AwaitableTask.h"

#include <utility>
#include "Logger.h"
#include "Threadpool.h"

AwaitableTask::AwaitableTask(std::function<void()> func) : m_Func(std::move(func))
{
}

void AwaitableTask::wait()
{
    std::unique_lock<std::mutex> lk(m_Mutex);
    m_Condition.wait(lk, [&]{ return m_IsDone; });
}

void AwaitableTask::enqueue(ThreadPool &pool)
{
    if(!m_Func)
        Logger::error("No task assigned to execute!");

    pool.enqueue([this](){

        std::unique_lock<std::mutex> lk(m_Mutex);
        m_Func();
        m_IsDone = true;
        lk.unlock();
        m_Condition.notify_one();
    });
}

bool AwaitableTask::isTaskDone()
{
    return m_IsDone;
}

void AwaitableTask::resetCurrentTask()
{
    m_IsDone = false;
}

void AwaitableTask::assignNewTask(std::function<void()> func)
{
    m_Func = std::move(func);
}