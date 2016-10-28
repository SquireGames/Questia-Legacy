#include "ThreadPool_Fixed.h"

ThreadPool_Fixed::ThreadPool_Fixed(unsigned int threads):
    taskBarrier(std::min(threads, std::thread::hardware_concurrency()))
{
    maxThreads = std::min(threads, std::thread::hardware_concurrency());
    for (unsigned int it = 0; it != maxThreads; it++)
    {
        threadPool.emplace_back(std::thread(&ThreadPool_Fixed::threadFunc, this));
    }
}

ThreadPool_Fixed::ThreadPool_Fixed():
    taskBarrier(std::thread::hardware_concurrency())
{
    for (unsigned int it = 0; it != maxThreads; it++)
    {
        threadPool.emplace_back(std::thread(&ThreadPool_Fixed::threadFunc, this));
    }
}

ThreadPool_Fixed::~ThreadPool_Fixed()
{
    kill();
}


void ThreadPool_Fixed::addTask(std::function<void()> task)
{
    taskPool.emplace_back(TaskObj(task));
}


void ThreadPool_Fixed::threadFunc()
{
    while(true)
    {
        //wait until signal to start something
        std::cout << "Waiting for wakeUp or kill" << std::endl;
        while(!wakeUp && !killAll && finished)
        {
            std::this_thread::yield();
        }

        // make sure all threads started
        std::cout << "Starting tasks" << std::endl;
        taskBarrier.wait();
        wakeUp = false;

        if(killAll)
        {
            return;
        }
        for(auto& taskObj : taskPool)
        {
            taskObj.taskMutex->lock();
            if(taskObj.runTask)
            {
                taskObj.runTask = false;
                taskObj.taskMutex->unlock();
                std::cout << "Running task" << std::endl;
                taskObj.task();
            }
            else
            {
                taskObj.taskMutex->unlock();
            }
        }

        //make sure all threads finish
        taskBarrier.wait();
        std::cout << "Tasks finished!" << std::endl;
        finished = true;
    }
}


void ThreadPool_Fixed::runTasks()
{
    // set the tasks to run
    for(auto& taskObj : taskPool)
    {
        taskObj.taskMutex->lock();
        taskObj.runTask = true;
        taskObj.taskMutex->unlock();
    }

    finished = false;
    wakeUp = true;

    // wait for tasks to finish
    while(!finished)
    {
        std::this_thread::yield();
    }

    std::cout << "~All tasks finished! " << std::endl;
}

void ThreadPool_Fixed::kill()
{
    // wait for tasks to finish
    killAll = true;
    for(auto& thread : threadPool)
    {
        thread.join();
    }

    threadPool.clear();
}
