#include <iostream>
#include <format>
#include <omp.h>
#include <unordered_map>
#include <string>

using namespace std;

std::string GetOpenMPVersion()
{
    unordered_map<unsigned, std::string> map
    {
        {199810, "1.0"},
        {200203, "2.0"},
        {200505, "2.5"},
        {200805, "3.0"},
        {201107, "3.1"},
        {201307, "4.0"},
        {201511, "4.5"},
        {201811, "5.0"},
        {202011, "5.1"},
        {202111, "5.2"}
    };
    return map.at(_OPENMP);
}

int main()
{
    cout << std::format("OpenMP version: ({}, {})\n", _OPENMP, GetOpenMPVersion());
    cout << std::format("Max threads: {}\n", omp_get_max_threads());
#   pragma omp parallel num_threads(8)
    {
        int thread_num = omp_get_num_threads();
        int thread_id = omp_get_thread_num();
        cout << std::format("Id/Num: {}/{}\n", thread_id, thread_num - 1);
    }
    return 0;
}
