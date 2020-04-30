#include <memory>
#include <iostream>

#include <Parser.hpp>
#include <Scheduler.hpp>

int main(int argc, char** argv)
{
    if (argc != 2)
    {
        std::cout << "Usage: " << argv[0] << " <input_file>" << std::endl;
        return EXIT_FAILURE;
    }

    std::string filename = argv[1];

    if (!file_exists(filename))
    {
        std::cout << "Error: file " << filename << " does not exist." << std::endl;
        return EXIT_FAILURE;
    }

    Parser parser(filename);
    std::shared_ptr<Scheduler> scheduler_p = parser.build_scheduler();

    std::cout << *scheduler_p << std::endl;

    scheduler_p->execute();

    return EXIT_SUCCESS;
}
