#include <Task.hpp>

Task Task::IDLE_TASK = Task("IDLE_TASK");

std::ostream& operator<<(std::ostream& out, Task& task)
{
    out << "Name: " << task.name << std::endl
        << "    WCET:              " << task.wcet         << std::endl
        << "    Period:            " << task.period       << std::endl
        << "    Relative Deadline: " << task.rel_deadline << std::endl
        << "    Absolute Deadline: " << task.abs_deadline << std::endl
        << "    Priority:          " << task.priority     << std::endl;

    return out;
}

bool operator<(Task& lhs, Task& rhs)
{
    return lhs.priority > rhs.priority;
}

bool operator==(Task& lhs, Task& rhs)
{
    return lhs.name == rhs.name;
}

bool operator!=(Task& lhs, Task& rhs)
{
    return !(lhs == rhs);
}

void Task::finalize()
{
    if (this->rel_deadline == 0) {
        this->rel_deadline = this->period;
    }

    this->abs_deadline = this->rel_deadline;
}

bool Task::needs_servicing()
{
    return this->time_to_fulfillment() > 0;
}

int Task::time_to_fulfillment()
{
    return this->wcet - this->fulfillment;
}

int Task::time_until_deadline(int simtime)
{
    return this->abs_deadline - simtime;
}

void Task::service_for_timestep(int timestep)
{
    this->fulfillment += timestep;
}

bool Task::deadline_missed(int simtime)
{
    return this->time_until_deadline(simtime) <= 0 && this->needs_servicing();
}

bool Task::rerelease_is_ready(int simtime)
{
    return this->release_time + this->period <= simtime;
}

void Task::rerelease()
{
    this->fulfillment = 0;
    this->release_time += this->period;
    this->abs_deadline = this->release_time + this->rel_deadline;
}
