#ifndef __SCHEDULER_HPP__
#define __SCHEDULER_HPP__

#include <algorithm>

#include <cstdio>
#include <vector>
#include <string>
#include <iostream>

#include <Utility.hpp>
#include <Task.hpp>
#include <Logger.hpp>

class Scheduler
{
    private:
        std::vector<Task> m_tasks;
        AlgorithmType m_algorithm;
        int m_timestep = 1;
        int m_simtime = 0;
        int m_duration = 0;

        Logger m_logger;

        void setup_for_rms();
        void setup_for_edf();
        void setup_for_pbs();

        void execute_one_step();

        int compute_priority_for_task(Task& task);

        void preprocess_tasks();
        void preprocess_hvdf();

        Task& determine_next_task();

    public:
        void set_timestep(int timestep);
        void set_duration(int duration);
        void set_algorithm(AlgorithmType algo);
        void add_task(Task& task);

        void execute();

        friend std::ostream& operator<<(std::ostream& out, Scheduler& scheduler);
};


#endif
