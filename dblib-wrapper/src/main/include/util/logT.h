#ifndef _LOGT_H
#define _LOGT_H

#include <iostream>
#include <sstream>

namespace cc {

class Error;
class Warn;
class Info;
class Debug;

class logB {

public:

  static constexpr const char *C_LOG_DEBUG { "debug" };

  static constexpr const char *C_LOG_ERROR { "error" };

  static constexpr const char *C_LOG_INFO { "info" };

  static constexpr const char *C_LOG_WARN { "warn" };

protected:
  logB() {
  }

  virtual ~logB() {
  }

};

template<typename T>
class logT final : private logB {

  using value_type [[maybe_unused]] = typename std::enable_if<
  std::is_same<Error, T>::value ||
  std::is_same<Warn, T>::value ||
  std::is_same<Info, T>::value ||
  std::is_same<Debug, T>::value>::type;

public:
  logT() :
      logB() {
  }

  virtual ~logT() override {
  }

  static bool is_on();

public:
  void write(const std::string &s) {

    const static bool on(is_on());

    if (on && !s.empty()) {

      std::cout << s;

      std::cout.flush();

    }

  }

  const char* get_prefix() const {

    static const char *p(prefix());

    return p;

  }

private:
  logT(const logT<T>&) = delete;

  logT<T>& operator=(const logT<T>&) = delete;

private:
  const char* prefix() const;

};

}

#endif
