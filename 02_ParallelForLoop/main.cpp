#include <iostream>
#include <format>
#include <omp.h>
#include <string>

using namespace std;


int main()
{
    double sum{0};
#   pragma omp parallel for num_threads(8)
    for (int i = 1; i <= 10000; ++i)
    {
        double tmp = 1.0 / (i * i);
#       pragma omp atomic
        // or # pragma omp critical
        sum += tmp;
    }
    cout << std::format("sum: {}", sum);
    // sum = pi^2/6 = 1.64493

    return 0;
}
