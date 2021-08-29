#include "FrameTimer.h"



FrameTimer::FrameTimer()
{
    last = std::chrono::steady_clock::now();
}

double FrameTimer::Mark()
{
    const auto old = last;
    last = std::chrono::steady_clock::now();
    const std::chrono::duration<double> frameTime = last - old;
    return frameTime.count();
}
