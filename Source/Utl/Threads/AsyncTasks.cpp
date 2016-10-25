#include "AsyncTasks.h"

AsyncTasks::AsyncTasks()
{

}
AsyncTasks::~AsyncTasks()
{

}

void AsyncTasks::addTask(std::function<void()> task)
{
    taskPool.push_back(task);
}

void AsyncTasks::runTasks()
{
    std::vector <std::future <void> > futures;

    for(auto& task : taskPool)
    {
        futures.push_back(std::async(task));
    }

    for(auto& future : futures)
    {
        future.get();
    }
}
