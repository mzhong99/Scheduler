#ifndef __PARSER_HPP__
#define __PARSER_HPP__

#include <memory>

#include <string>
#include <vector>

#include <iostream>
#include <fstream>

#include <Task.hpp>
#include <Scheduler.hpp>

class Parser
{
    private:
        std::ifstream m_input_file;
        std::shared_ptr<Scheduler> m_scheduler_p;

        void parse_tasks();
        void parse_algorithm();
        void parse_duration();
        void parse_timestep();

    public:
        Parser(std::string& filename);
        std::shared_ptr<Scheduler> build_scheduler();
};

#endif // __PARSER_HPP__

