//
// Created by benny on 2022/3/10.
//
#include <iostream>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <thread>

inline char separator() {
#ifdef _WIN32
  return '\\';
#else
  return '/';
#endif
}

const char *file_name(const char *path) {
  const char *file = path;
  while (*path) {
    if (*path++ == separator()) {
      file = path;
    }
  }
  return file;
}

void PrintTime() {
  using namespace std;
  using namespace std::chrono;

  auto now = system_clock::now();
  auto in_time_t = system_clock::to_time_t(now);

  // get number of milliseconds for the current second
  // (remainder after division into seconds)
  auto ms = duration_cast<milliseconds>(now.time_since_epoch()) % 1000;

  cout << std::put_time(std::localtime(&in_time_t), "%T")
       << '.' << std::setfill('0') << std::setw(3) << ms.count();
}

void PrintThread() {
  using namespace std;
  cout << " [Thread-" << this_thread::get_id() << "] ";
}

void SetIndentAndColor() {
  using namespace std;
  static vector<thread::id> threadIds;
  const array<const char* const, 4> colors = {"\033[0m", "\033[31m", "\033[32m", "\033[33m"};
  auto id = this_thread::get_id();
  auto it = find(threadIds.begin(), threadIds.end(), id);
  if (it == threadIds.end()) {
    threadIds.push_back(id);
    it = threadIds.end() - 1;
  }
  for (auto i = threadIds.begin(); i != it; ++i) {
    cout << "\t";
  }
  cout << colors[(it - threadIds.begin()) % colors.size()];
}

void ResetColor() {
  std::cout << "\033[0m";
}