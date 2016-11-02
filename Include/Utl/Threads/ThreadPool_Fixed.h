#ifndef THREADPOOL_FIXED_H
#define THREADPOOL_FIXED_H

#include <thread>
#include <memory>
#include <atomic>
#include <boost/thread/barrier.hpp>
#include <functional>
#include <vector>
#include <mutex>

#include <iostream>

class ThreadPool_Fixed
{
public:
    ThreadPool_Fixed(unsigned int threads);
    ThreadPool_Fixed();
    ~ThreadPool_Fixed();

    void addTask(std::function<void()> task);

    void runTasks();

    void kill();

private:
    unsigned int maxThreads = std::thread::hardware_concurrency();
    std::vector<std::thread> threadPool;

    struct TaskObj
    {
        TaskObj(std::function<void()> _task):task(_task) {};
        std::unique_ptr<std::mutex> taskMutex = {std::unique_ptr <std::mutex> (new std::mutex())};
        std::function<void()> task;
        bool runTask = false;
    };
    std::vector<TaskObj> taskPool;

    boost::barrier taskBarrier;

    std::atomic <bool> killAll  = {false};
    std::atomic <bool> wakeUp   = {false};
    std::atomic <bool> finished = {false};

    void threadFunc();
};

#endif // THREADPOOL_FIXED_H
