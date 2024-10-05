//
// Created by benny on 2022/3/10.
//
#include <iostream>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <thread>
#include <sstream>

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

std::stringstream &PrintTime(std::stringstream &ss) {
  using namespace std;
  using namespace std::chrono;

  auto now = system_clock::now();
  auto in_time_t = system_clock::to_time_t(now);

  // get number of milliseconds for the current second
  // (remainder after division into seconds)
  auto ms = duration_cast<milliseconds>(now.time_since_epoch()) % 1000;

  ss << std::put_time(std::localtime(&in_time_t), "%T")
     << '.' << std::setfill('0') << std::setw(3) << ms.count();
  return ss;
}

std::stringstream &PrintThread(std::stringstream &ss) {
  using namespace std;
  ss << " [Thread-" << setw(5) << this_thread::get_id() << "] ";
  return ss;
}

void SetIndentAndColor(std::stringstream& ss) {
  using namespace std;
  static vector<thread::id> threadIds;
  const array<const char* const, 8> colors = {"\033[0m", "\033[31m", "\033[32m", "\033[33m", "\033[34m", "\033[35m", "\033[36m", "\033[37m"};
  auto id = this_thread::get_id();
  auto it = find(threadIds.begin(), threadIds.end(), id);
  if (it == threadIds.end()) {
    threadIds.push_back(id);
    it = threadIds.end() - 1;
  }
  for (auto i = threadIds.begin(); i != it; ++i) {
    ss << "\t";
  }
  ss << colors[(it - threadIds.begin()) % colors.size()];
}