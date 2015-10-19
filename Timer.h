#ifndef TIMER_H
#define TIMER_H

#include <chrono>

class Timer
{
    public:
        Timer() :
            start_(std::chrono::steady_clock::now())
        {

        }

        double elapsed()
        {
            elapsed_ = std::chrono::steady_clock::now() - start_;
            start_ = std::chrono::steady_clock::now();

            return std::chrono::duration_cast<std::chrono::milliseconds>(elapsed_).count() / 1000.0;
        }

    private:
        std::chrono::time_point<std::chrono::steady_clock> start_;
        std::chrono::steady_clock::duration elapsed_;
};

#endif // TIMER_H
