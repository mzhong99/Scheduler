#include <Scheduler.hpp>

void Scheduler::set_timestep(int timestep) 
{ 
    if (timestep > 0) { m_timestep = timestep; }
}

void Scheduler::set_duration(int duration) { m_duration = duration; }
void Scheduler::set_algorithm(AlgorithmType algo) { m_algorithm = algo; }

void Scheduler::add_task(Task& task) 
{ 
    m_tasks.push_back(task); 
}

std::ostream& operator<<(std::ostream& out, Scheduler& scheduler)
{
    out << "Scheduler: "                                             << std::endl;
    out << " - Timestep:  " << scheduler.m_timestep                  << std::endl;
    out << " - Duration:  " << scheduler.m_duration                  << std::endl;
    out << " - Algorithm: " << algo_to_string(scheduler.m_algorithm) << std::endl;
    out                                                              << std::endl;

    out << "Tasks inside Scheduler: " << std::endl;
    
    for (Task& task : scheduler.m_tasks) { out << task << std::endl; }

    return out;
}

int Scheduler::compute_priority_for_task(Task& task)
{
    switch (m_algorithm)
    {
        case AlgorithmType::EDF: return -1 * task.time_until_deadline(m_simtime);
        case AlgorithmType::RMS: return -1 * task.period;
        case AlgorithmType::PBS: return task.fixed_priority;
    }

    return Task::IDLE_PRIORITY;
}

Task& Scheduler::determine_next_task()
{
    for (Task& task : m_tasks)
    {
        task.priority = Task::IDLE_PRIORITY;
        if (task.needs_servicing()) {
            task.priority = this->compute_priority_for_task(task);
        }
    }

    std::sort(m_tasks.begin(), m_tasks.end());

    for (Task& task : m_tasks) {
        if (task.needs_servicing()) {
            return task;
        }
    }

    return Task::IDLE_TASK;
}

void Scheduler::execute_one_step()
{
    std::string rerelease_label = "Re-released tasks: ";
    std::string deadline_label = "Deadlines missed: ";
    std::string comma_separator = ", ";

    for (Task& task : m_tasks)
    {
        if (task.deadline_missed(m_simtime))
        {
            m_logger.remarks() << deadline_label << task.name;
            deadline_label = comma_separator;
        }
    }

    if (deadline_label == comma_separator) { m_logger.remarks() << std::endl; }

    for (Task& task : m_tasks) 
    {
        if (task.rerelease_is_ready(m_simtime)) 
        {
            task.rerelease();
            m_logger.remarks() << rerelease_label << task.name;
            rerelease_label = comma_separator;
        }
    }

    if (rerelease_label == comma_separator) { m_logger.remarks() << std::endl; }

    m_logger.log_simtime(m_simtime);

    Task& next_task = this->determine_next_task();
    m_logger.log_task_execution(next_task);
    next_task.service_for_timestep(m_timestep);

    m_logger.log_eol();
}

void Scheduler::execute()
{
    m_logger.initialize(m_tasks, m_timestep);
    m_logger.log_start();

    for (m_simtime = 0; m_simtime < m_duration; m_simtime += m_timestep) {
        this->execute_one_step();
    }
}
