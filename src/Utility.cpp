#include <Utility.hpp>

bool file_exists(std::string& filename)
{
    std::ifstream file(filename);
    return file.good();
}

std::string algo_to_string(AlgorithmType algo)
{
    static std::map<AlgorithmType, std::string> mapping;
    static bool first_call = true;
    
    if (first_call)
    {
        mapping[AlgorithmType::RMS] = "Rate-monotonic";
        mapping[AlgorithmType::EDF] = "Earliest Deadline First";
        mapping[AlgorithmType::PBS] = "Priority-based";

        first_call = false;
    }

    return mapping[algo];
}
