#ifndef __TASK_HPP__
#define __TASK_HPP__

#include <climits>

#include <string>
#include <iostream>

struct Task
{
    static const int IDLE_PRIORITY = INT_MIN / 2;
    static Task IDLE_TASK;

    std::string name;

    int wcet = 0;
    int fulfillment = 0;

    int period = 0;
    int rel_deadline = 0;
    int abs_deadline = 0;

    // higher is better
    int priority = 0;       
    int fixed_priority = 0;

    int release_time = 0;

    Task() {};
    Task(std::string name): name(name) {}

    void finalize();

    bool needs_servicing();
    void service_for_timestep(int timestep);

    int time_to_fulfillment();
    int time_until_deadline(int simtime);

    bool deadline_missed(int simtime);
    bool rerelease_is_ready(int simtime);
    void rerelease();
};

std::ostream& operator<<(std::ostream& out, Task& task);
bool operator<(Task& lhs, Task& rhs);
bool operator==(Task& lhs, Task& rhs);
bool operator!=(Task& lhs, Task& rhs);

#endif
