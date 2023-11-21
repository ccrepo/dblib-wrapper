#ifndef _LOG_H
#define _LOG_H

#include <iostream>
#include <sstream>
#include <memory>
#include <ctime>
#include <iomanip>
#include <chrono>
using namespace std::chrono_literals;

#include "logT.h"

namespace cc {

inline std::string system_clock_as_string_ms() {

thread_local  static struct tm ts_struct;

  thread_local static std::ostringstream os;

  os.str("");

  auto now(std::chrono::system_clock::now());

  std::time_t ts {std::chrono::system_clock::to_time_t(now)};

  localtime_r(&ts, &ts_struct);

  os << std::put_time(&ts_struct, "%Y%m%d %H:%M:%S")
  << "."
  << std::setfill('0')
  << std::setw(3)
  << std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()).count() % 1000;

  return os.str();
}

inline std::string rpad(const std::string &s, uint32_t size) {

  int64_t len(size - s.length());

  if (len <= 0) {

    return s;
  }

  std::string buffer(s);

  return buffer.insert(buffer.size(), len, ' ');
}

inline std::ostringstream& operator<<(std::ostringstream &os,
    const std::ostringstream &s) {

  os << s.str();

  return os;
}

template<typename T>
void log(std::ostringstream &os, const T &t) {

  os << t;
}

template<typename T, typename ... Args>
void log(std::ostringstream &os, const T &t, const Args &... args) {

  os << t;

  log<Args...>(os, args...);
}

template<typename T, typename ... Args>
void log(logT<T> &logger, const char *file, uint32_t lineno,
    const char *function, const Args &... args) {

  static const std::string prefix(rpad(logger.get_prefix(), 5));

  std::ostringstream os;

  os << system_clock_as_string_ms() << " [" << prefix << "]["
      << static_cast<void*>(&logger) << "] " << file << ":" << lineno << "("
      << function << ") ";

  log<Args...>(os, args...);

  os << std::endl;

  logger.write(os.str());
}

constexpr char path_separator = '/';

constexpr const char* str_end(const char *s) {

  return *s ? str_end(s + 1) : s;
}

constexpr bool str_slant(const char *s) {

  return *s == path_separator ? true : (*s ? str_slant(s + 1) : false);
}

constexpr const char* r_slant(const char *s) {

  return *s == path_separator ? (s + 1) : r_slant(s - 1);
}

constexpr const char* basename(const char *s) {

  return str_slant(s) ? r_slant(str_end(s)) : s;
}

}

#define DEBUG(...) {                                   \
  if (cc::logT<cc::Debug>::is_on()) {                  \
    constexpr const char* __b(cc::basename(__FILE__)); \
    thread_local static cc::logT<cc::Debug> __l;       \
    cc::log<cc::Debug>                                 \
    (__l, __b,                                         \
        __LINE__, __FUNCTION__, __VA_ARGS__);          \
  }                                                    \
}

#define INFO(...) {                                    \
  if (cc::logT<cc::Info>::is_on()) {                   \
    constexpr const char* __b(cc::basename(__FILE__)); \
    thread_local static cc::logT<cc::Info> __l;        \
    cc::log<cc::Info>                                  \
    (__l, __b,                                         \
        __LINE__, __FUNCTION__, __VA_ARGS__);          \
  }                                                    \
}

#define WARN(...) {                                    \
  if (cc::logT<cc::Warn>::is_on()) {                   \
    constexpr const char* __b(cc::basename(__FILE__)); \
    thread_local static cc::logT<cc::Warn> __l;        \
    cc::log<cc::Warn>                                  \
    (__l, __b,                                         \
        __LINE__, __FUNCTION__, __VA_ARGS__);          \
  }                                                    \
}

#define ERROR(...) {                                   \
  if (cc::logT<cc::Error>::is_on()) {                  \
    constexpr const char* __b(cc::basename(__FILE__)); \
    thread_local static cc::logT<cc::Error> __l;       \
    cc::log<cc::Error>                                 \
    (__l, __b,                                         \
        __LINE__, __FUNCTION__, __VA_ARGS__);          \
  }                                                    \
}

#endif
