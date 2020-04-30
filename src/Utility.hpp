#ifndef __UTILITY_HPP__
#define __UTILITY_HPP__

#include <iostream>
#include <fstream>
#include <string>
#include <map>

enum class AlgorithmType { RMS, EDF, PBS };
bool file_exists(std::string& filename);
std::string algo_to_string(AlgorithmType algo);

#endif
