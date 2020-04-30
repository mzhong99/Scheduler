#ifndef __LOGGER_HPP__
#define __LOGGER_HPP__

#include <climits>

#include <vector>
#include <string>

#include <fstream>
#include <iostream>
#include <iomanip>

#include <sstream>

#include <Task.hpp>

class Logger
{
    private:
        std::ofstream m_output_file;
        std::ostream* m_out_p = nullptr;

        std::vector<Task> m_static_tasks;
        int m_timestep;

        std::vector<int> m_task_offsets;
        int m_tasks_start_offset;
        int m_exec_progress_offset;
        int m_remark_offset;

        std::string m_time_entry;
        std::string m_task_entry;

        std::stringstream m_remarks;
        void flush_remarks();

        void compute_offsets();

    public:
        Logger();

        void initialize(std::vector<Task> tasks, int timestep);

        void set_output_file(std::string& filename);

        void log_start();
        void log_simtime(int simtime);
        void log_task_execution(Task& task);
        std::stringstream& remarks();

        void log_eol();
};

#endif // __LOGGER_HPP__
