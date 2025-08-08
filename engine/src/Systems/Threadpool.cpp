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



void ThreadPool::ThreadLoop()
{
    while (true)
    {

        {}
        std::function<void()> job;
        {
            std::unique_lock<std::mutex> lock(queueMutex);

            mutex_condition.wait(lock,[this]{

                return !jobs.empty() || terminateThread;
            });
            if (terminateThread && jobs.empty())
            {
                return;
            }
            job=jobs.front();
            jobs.pop();
        }

        ++activeJobs;
        job();
        --activeJobs;

        // After completing job, check if we should pause before next one
        std::unique_lock<std::mutex> pauseLock(queueMutex);
        pause_condition.wait(pauseLock, [this] {
            return !pauseThreadPool.load() || terminateThread.load();
        });

        if (terminateThread.load()) {
            return;
        }
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
    std::unique_lock<std::mutex> lock(queueMutex);
    return !jobs.empty() || activeJobs.load() > 0;
}

void ThreadPool::Stop() {
    {
        std::unique_lock<std::mutex> lock(queueMutex);
        terminateThread.store(true);
    }
    mutex_condition.notify_all();
    pause_condition.notify_all();
    for (std::thread& active_thread : threads) {
        active_thread.join();
    }
    threads.clear();
}

int ThreadPool::GetThreadCount()
{
    return threads.size();
}

void ThreadPool::Pause()
{
    pauseThreadPool.store(true);
}

void ThreadPool::Resume()
{
    pauseThreadPool.store(false);
    pause_condition.notify_all(); //wake up paused threads
}

bool ThreadPool::isPaused() const
{
    return pauseThreadPool.load();
}


ThreadPool::~ThreadPool()
{
    Stop();
}


