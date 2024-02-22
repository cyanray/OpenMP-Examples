#include <iostream>
#include <format>
#include <omp.h>
#include <string>

using namespace std;

constexpr int NUM_THREADS{14};
constexpr int N{10000000};
constexpr double dx = 1.0 / N;

int main()
{
    omp_set_num_threads(NUM_THREADS);

    cout << std::format("PI = {}\n", 3.1415926535897932384);

    // 1. use critical
    {
        double sum{0};
#       pragma omp parallel for
        for (int i = 0; i <= N; ++i)
        {
            double tmp = 4.0 / (1 + (i * dx) * (i * dx));
#           pragma omp critical
            sum += tmp;
        }
        sum *= dx;
        cout << std::format("pi: {}\n", sum);
    }

    // 2. use atomic
    {
        double sum{0};
#       pragma omp parallel for
        for (int i = 1; i <= N; ++i)
        {
            double tmp = 4.0 / (1 + (i * dx) * (i * dx));
#           pragma omp atomic
            sum += tmp;
        }
        sum *= dx;
        cout << std::format("pi: {}\n", sum);
    }

    // 3. use reduction
    {
        double sum{0};
#       pragma omp parallel for reduction(+:sum)
        for (int i = 1; i <= N; ++i)
        {
            double tmp = 4.0 / (1 + (i * dx) * (i * dx));
            sum += tmp;
        }
        sum *= dx;
        cout << std::format("pi: {}\n", sum);
    }

    return 0;
}
