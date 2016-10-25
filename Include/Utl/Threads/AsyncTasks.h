#ifndef THREADPOOL_H
#define THREADPOOL_H

#include <future>
#include <functional> // std::function
#include <vector>

#include <iostream>

class AsyncTasks
{
public:
    AsyncTasks();
    ~AsyncTasks();

    void addTask(std::function<void()> task);
    void runTasks();
private:
    //task pool
    std::vector <std::function <void()> > taskPool;
};

#endif // THREADPOOL_H
