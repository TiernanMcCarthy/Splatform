//
// Created by tiernan on 7/29/25.
//

#ifndef THREADPOOL_H
#define THREADPOOL_H
#include <atomic>
#include <condition_variable>
#include <functional>
#include <mutex>
#include <queue>
#include <thread>
#include <vector>


/* Example
void EpicFunction(std::atomic<bool>& testBool)
{
    testBool.exchange(!testBool);
}
threadPool = new ThreadPool(4);

std::atomic<bool> testBool=false;
std::atomic<bool> testBool2=true;
std::atomic<bool> testBool3=false;
std::atomic<bool> testBool4=true;
threadPool->QueueJob([&testBool] {EpicFunction(std::ref(testBool));});
threadPool->QueueJob([&testBool2] {EpicFunction(std::ref(testBool2));});
threadPool->QueueJob([&testBool3] {EpicFunction(std::ref(testBool3));});
threadPool->QueueJob([&testBool4] {EpicFunction(std::ref(testBool4));});
    */


//Queue jobs as functions into the job list, example in file
// IsBusy can be used like .join(), can be put in a while loop until we're ready for them
//Borrowed from https://stackoverflow.com/questions/15752659/thread-pooling-in-c11
class ThreadPool
{

public:

    explicit ThreadPool(int numThreads);

    ~ThreadPool();


    void QueueJob(const std::function<void()>& job);

    void Stop();

    bool IsBusy();

    int GetThreadCount();

private:

    void ThreadLoop();

    bool terminateThread=false; //Manages whether the thread should stop looking for jobs

    std::mutex queueMutex; //Prevents a data race for job queue

    std::condition_variable mutex_condition;

    std::vector<std::thread> threads;

    std::queue<std::function<void()>> jobs;

    std::atomic<unsigned int> activeJobs{0};
    //unsigned int activeJobs=0;

};

#endif // THREADPOOL_H