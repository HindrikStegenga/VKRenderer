//
// Created by hindrik on 14-11-17.
//

#ifndef VKRENDERER_AWAITABLETASK_H
#define VKRENDERER_AWAITABLETASK_H


#include <functional>
#include <mutex>
#include <condition_variable>

class ThreadPool;

class AwaitableTask
{
private:
    std::function<void()>   m_Func;
    std::mutex              m_Mutex;
    std::condition_variable m_Condition;
    bool                    m_IsDone        = false;
public:
    explicit AwaitableTask(std::function<void()> func);
    ~AwaitableTask() = default;

    AwaitableTask(AwaitableTask&&)      = delete;
    AwaitableTask(const AwaitableTask&) = delete;

    AwaitableTask& operator=(const AwaitableTask&) = delete;
    AwaitableTask& operator=(AwaitableTask&&)      = delete;
public:
    void enqueue(ThreadPool& pool);
    void wait();
    bool isTaskDone();
    void resetCurrentTask();
    void assignNewTask(std::function<void()> func);
};



#endif //VKRENDERER_AWAITABLETASK_H
