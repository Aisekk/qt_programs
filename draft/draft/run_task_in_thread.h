#ifndef RUN_TASK_IN_THREAD_H
#define RUN_TASK_IN_THREAD_H

#include <thread>
#include <mutex>
#include <condition_variable>
#include <list>
#include <iostream>
#include <string>
#include <functional>
#include <queue>

namespace Threads {

class Task;

class TaskRunner {
public:
    bool running;

    std::thread thread;
    std::mutex mutex;
    std::condition_variable cond;

    typedef std::list < Task * > tasks_t;
    tasks_t tasks;

    TaskRunner(): running(false) {}

    ~TaskRunner() {
        stop();
    }

    void push(Task * task);

    Task * pop();

    void run();
    void start();
    void stop();
};

class Task {
public:
    Task() {}
    virtual ~Task() {}
    virtual void process() = 0;

    enum PERFORM{ DO_TASK = 0, SKIP_TASK = 1 };
    virtual PERFORM get_perform() const = 0;
};

template < typename T >
class GenericTask: public Task {
public:
    T func;

    GenericTask(const T & t, PERFORM perform_): func(t), perform(perform_) {}

    void process() {
        func();
    }

    PERFORM get_perform() const {
        return perform;
    }

private:
    PERFORM perform;
};

template < typename T >
Task * make_generic_task(const T & t, Task::PERFORM perform = Task::DO_TASK)
{
    return new GenericTask < T > (t, perform);
}


class A {
public:
    A();
    ~A();
    void run_tasks();
private:
    static void task(int n);

    TaskRunner* task_runner;
};

void runner();

}

#endif // RUN_TASK_IN_THREAD_H
