//https://stackoverflow.com/a/27137877
#include <chrono>
#include <ctime>
#include <sstream>

struct tm getTm(time_t &time)
{
    struct tm timeinfo;
    localtime_s(&timeinfo, &time);
    return timeinfo;
}

template <typename T>
std::string printTime(std::chrono::time_point<T> time)
{
    using namespace std::chrono;

    auto curr_time = T::to_time_t(time);
    struct tm timeinfo = getTm(curr_time);

    char timeStamp[100];
    strftime(timeStamp, sizeof(timeStamp), "%Y-%m-%dT%H:%M:%S", &timeinfo);

    auto time_epoch = time.time_since_epoch();
    auto left_time = time_epoch - duration_cast<seconds>(time_epoch);

    // milliseconds milli = duration_cast<milliseconds>(left_time);
    microseconds micro = duration_cast<microseconds>(left_time);

    std::stringstream ss;
    ss << timeStamp << "." << micro.count();

    return ss.str();
}
