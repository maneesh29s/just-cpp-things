template <typename T>
class Timer {
private:
  std::chrono::time_point<std::chrono::high_resolution_clock> start;
  std::chrono::time_point<std::chrono::high_resolution_clock> end;

public:
  void start_timer() { this->start = std::chrono::high_resolution_clock::now(); }
  void stop_timer() { this->end = std::chrono::high_resolution_clock::now(); }

  std::string time_elapsed() {
    auto time_taken =
        std::chrono::duration_cast<T>(this->end - this->start).count();

    return std::to_string(time_taken);
  }
};