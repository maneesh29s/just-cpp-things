#include <chrono>
#include <string>

template <typename T>
class Timer {
   private:
    std::chrono::time_point<std::chrono::high_resolution_clock> start;
    std::chrono::time_point<std::chrono::high_resolution_clock> end;

   public:
    void start_timer() {
        this->start = std::chrono::high_resolution_clock::now();
    }
    void stop_timer() {
        this->end = std::chrono::high_resolution_clock::now();
    }

    std::string time_elapsed() {
        auto time_taken = std::chrono::duration_cast<T>(this->end - this->start).count();

        std::string unit = "";
        if (std::is_same<T, std::chrono::seconds>::value)
            unit = "s";
        else if (std::is_same<T, std::chrono::milliseconds>::value)
            unit = "ms";
        else if (std::is_same<T, std::chrono::microseconds>::value)
            unit = "us";
        else if (std::is_same<T, std::chrono::nanoseconds>::value)
            unit = "ns";

        return std::to_string(time_taken) + " " + unit;
    }
};
