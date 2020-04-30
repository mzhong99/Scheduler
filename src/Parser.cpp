#include <Parser.hpp>

Parser::Parser(std::string& filename)
{
    m_scheduler_p = std::shared_ptr<Scheduler>(new Scheduler());

    m_input_file.open(filename);
    if (!m_input_file.fail())
    {
        std::string token;
        while (m_input_file >> token)
        {
            if      (token == "TASKS"    ) { this->parse_tasks();     }
            else if (token == "ALGORITHM") { this->parse_algorithm(); }
            else if (token == "DURATION" ) { this->parse_duration();  }
            else if (token == "TIMESTEP" ) { this->parse_timestep();  }
        }
    }
}

void Parser::parse_tasks()
{
    size_t num_keys, num_tasks;
    m_input_file >> num_keys >> num_tasks;

    std::vector<std::string> keys;
    for (size_t key_idx = 0; key_idx < num_keys; key_idx++) 
    {
        std::string token; m_input_file >> token;
        keys.push_back(token);
    }

    for (size_t task_idx = 0; task_idx < num_tasks; task_idx++)
    {
        Task task;
        for (std::string& key : keys)
        {
            if      (key == "NAME"    ) { m_input_file >> task.name;           }
            else if (key == "WCET"    ) { m_input_file >> task.wcet;           }
            else if (key == "PERIOD"  ) { m_input_file >> task.period;         }
            else if (key == "DEADLINE") { m_input_file >> task.rel_deadline;   }
            else if (key == "PRIORITY") { m_input_file >> task.fixed_priority; }
        }
        
        task.finalize();
        m_scheduler_p->add_task(task);
    }
}

void Parser::parse_algorithm()
{
    std::string token; m_input_file >> token;

    if      (token == "RMS") { m_scheduler_p->set_algorithm(AlgorithmType::RMS); }
    else if (token == "EDF") { m_scheduler_p->set_algorithm(AlgorithmType::EDF); }
    else if (token == "PBS") { m_scheduler_p->set_algorithm(AlgorithmType::PBS); }
}

void Parser::parse_duration()
{
    int duration; m_input_file >> duration;
    m_scheduler_p->set_duration(duration);
}

void Parser::parse_timestep()
{
    int timestep; m_input_file >> timestep;
    m_scheduler_p->set_timestep(timestep);
}

std::shared_ptr<Scheduler> Parser::build_scheduler()
{
    return m_scheduler_p;
}
