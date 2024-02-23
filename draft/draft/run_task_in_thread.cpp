#include "run_task_in_thread.h"
#include <algorithm>
#include <functional>

namespace Threads {

bool is_skipped_task(const Task* _task)
{
    return _task->get_perform() == Task::SKIP_TASK;
}

void TaskRunner::push(Task *task) {
    std::scoped_lock lock(mutex);
    if (!running) {
        delete task;
        return;
    }

    /** task must be nonzero pointer for correct comparing (but we have zero task pointer after "Shutdown" button)*/
    if(task && is_skipped_task(task)){
        /** delete last task with skipped perform status*/
        tasks_t::iterator skipped_task = std::find_if(tasks.begin(), tasks.end(), is_skipped_task);
        if (skipped_task != tasks.end())
        {
            delete *skipped_task;
            tasks.erase(skipped_task);
        }

    }

    tasks.push_back(task);
    cond.notify_one();
}

Task *TaskRunner::pop() {
    std::unique_lock lock(mutex);
    while (tasks.empty()) {
        cond.wait(lock);
    }
    Task * task = tasks.front();
    tasks.pop_front();
    return task;
}

void TaskRunner::run() {
    while (running) {
        Task * task = pop();
        if (!task) {
            break;
        }
        task->process();
        delete task;
    }
}

void TaskRunner::start() {
    {
        std::scoped_lock lock(mutex);
        running = true;
    }

    thread = std::thread(std::bind(&TaskRunner::run, this));
}

void TaskRunner::stop() {
    push(0);

    {
        std::scoped_lock lock(mutex);
        running = false;
    }

    thread.join();

    std::scoped_lock lock(mutex);
    for (tasks_t::iterator it = tasks.begin(); it != tasks.end(); ++it) {
        delete *it;
    }
}

}
