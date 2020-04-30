#include <Logger.hpp>

#define TASKS_START_OFFSET      15
#define COLUMN_SPACING          4
#define EXEC_PROGRESS_LENGTH    31

void Logger::flush_remarks()
{
    std::string line;
    std::stringstream ss(m_remarks.str());

    int offset = 0;
    while (std::getline(ss, line))
    {
        if (offset > 0) { *m_out_p << std::endl; }
        for (int i = 0; i < offset; i++) { *m_out_p << ' '; }

        *m_out_p << line;
        offset = m_remark_offset;
    }

    m_remarks = std::stringstream();
}

void Logger::compute_offsets()
{
    m_tasks_start_offset = TASKS_START_OFFSET;

    int task_offset = m_tasks_start_offset;
    for (Task& task : m_static_tasks) 
    {
        m_task_offsets.push_back(task_offset);
        task_offset += task.name.length() + 1;
    }

    m_exec_progress_offset = task_offset + COLUMN_SPACING;
    m_remark_offset = m_exec_progress_offset + EXEC_PROGRESS_LENGTH;
}

Logger::Logger() 
{
    m_out_p = &std::cout;
}

void Logger::initialize(std::vector<Task> tasks, int timestep)
{
    m_out_p = &std::cout;
    m_static_tasks = tasks;
    m_timestep = timestep;

    this->compute_offsets();
}

void Logger::set_output_file(std::string& filename)
{
    if (m_output_file.is_open()) {
        m_output_file.close();
    }

    m_output_file.open(filename);
    m_out_p = &m_output_file;
}

void Logger::log_start()
{
    *m_out_p << std::setw(TASKS_START_OFFSET) << std::left << "TIMESTEP";

    *m_out_p << std::setw(m_exec_progress_offset - m_tasks_start_offset) 
             << std::left << "TASKS";

    *m_out_p << std::setw(EXEC_PROGRESS_LENGTH) 
             << std::left << "EXECUTION PROGRESS";

    *m_out_p << "REMARKS";

    *m_out_p << std::endl;

    for (int i = 0; i < TASKS_START_OFFSET; i++) { *m_out_p << ' '; }
    for (Task& task : m_static_tasks) { *m_out_p << task.name << " "; }

    *m_out_p << std::endl;
}

void Logger::log_simtime(int simtime)
{
    char smallbuf[15];
    snprintf(smallbuf, 15, "Time: %3d ", simtime);

    m_time_entry = smallbuf;
}

void Logger::log_task_execution(Task& task)
{
    std::stringstream ss;

    for (Task& static_task : m_static_tasks)
    {
        ss << (task == static_task ? '*' : ' ');
        
        int length = static_task.name.length();
        while (length --> 0) { ss << ' '; }
    }

    for (int i = 0; i < COLUMN_SPACING; i++) { ss << ' '; }

    if (task != Task::IDLE_TASK)
    {
        char buffer[EXEC_PROGRESS_LENGTH + 1];
        snprintf(buffer, EXEC_PROGRESS_LENGTH + 1, "[ %3d / %3d -> %3d / %3d ]     ", 
                task.fulfillment, task.wcet,
                task.fulfillment + m_timestep, task.wcet);

        ss << buffer;
    }
    else
    {
        for (int i = 0; i < EXEC_PROGRESS_LENGTH; i++) { ss << ' '; }
    }

    m_task_entry = ss.str();
}

std::stringstream& Logger::remarks() { return m_remarks; }

void Logger::log_eol() 
{ 
    *m_out_p << std::setw(TASKS_START_OFFSET) << m_time_entry;
    *m_out_p << m_task_entry;

    this->flush_remarks();

    *m_out_p << std::endl; 
}
