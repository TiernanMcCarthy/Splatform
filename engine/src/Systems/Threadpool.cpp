//
// Created by tiernan on 7/29/25.
//
#include "Systems/ThreadPool.h"

//https://stackoverflow.com/questions/15752659/thread-pooling-in-c11

ThreadPool::ThreadPool(int numThreads)
{
     for (uint32_t ii = 0; ii < numThreads; ++ii) {
         threads.emplace_back(std::thread(&ThreadPool::ThreadLoop,this));
     }
}


void ThreadPool::Start()
{

}

void ThreadPool::ThreadLoop()
{
    while (true)
    {
        std::function<void()> job;
        {
            std::unique_lock<std::mutex> lock(queueMutex);

            mutex_condition.wait(lock,[this]{

                return !jobs.empty() || terminateThread;
            });
            if (terminateThread)
            {
                return;
            }
            job=jobs.front();
            jobs.pop();
        }
        job();
    }
}

void ThreadPool::QueueJob(const std::function<void()>& job) {
    {
        std::unique_lock<std::mutex> lock(queueMutex);
        jobs.push(job);
    }
    mutex_condition.notify_one();
}

bool ThreadPool::IsBusy() {
    bool poolbusy;
    {
        std::unique_lock<std::mutex> lock(queueMutex);
        poolbusy = !jobs.empty();
    }
    return poolbusy;
}

void ThreadPool::Stop() {
    {
        std::unique_lock<std::mutex> lock(queueMutex);
        terminateThread = true;
    }
    mutex_condition.notify_all();
    for (std::thread& active_thread : threads) {
        active_thread.join();
    }
    threads.clear();
}


