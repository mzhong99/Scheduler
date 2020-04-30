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
        mapping[AlgorithmType::RMS ] = "Rate-monotonic";
        mapping[AlgorithmType::EDF ] = "Earliest Deadline First";
        mapping[AlgorithmType::PBS ] = "Priority-based";
        mapping[AlgorithmType::HVF ] = "Highest Value First";
        mapping[AlgorithmType::HVDF] = "Highest Value Density First";

        first_call = false;
    }

    return mapping[algo];
}

AlgorithmType string_to_algo(std::string& str)
{
    static std::map<std::string, AlgorithmType> mapping;
    static bool first_call = true;
    
    if (first_call)
    {
        mapping["RMS"] = AlgorithmType::RMS;
        mapping["EDF"] = AlgorithmType::EDF;
        mapping["PBS"] = AlgorithmType::PBS;
        mapping["HVF"] = AlgorithmType::HVF;
        mapping["HVDF"] = AlgorithmType::HVDF;

        first_call = false;
    }

    return mapping[str];
}
