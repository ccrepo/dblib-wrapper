
#include "logT.h"
#include "config.h"

namespace cc {

template<>
const char* logT<Debug>::prefix() const {

  return C_LOG_DEBUG;
}

template<>
const char* logT<Error>::prefix() const {

  return C_LOG_ERROR;
}

template<>
const char* logT<Info>::prefix() const {

  return C_LOG_INFO;
}

template<>
const char* logT<Warn>::prefix() const {

  return C_LOG_WARN;
}

template<>
bool logT<Debug>::is_on() {

  static bool is_on(std::string(cc::config::get()->log()) == C_LOG_DEBUG);

  return is_on;
}

template<>
bool logT<Info>::is_on() {

  static bool is_on(
      std::string(cc::config::get()->log()) == C_LOG_INFO
          || logT<Debug>::is_on());

  return is_on;
}

template<>
bool logT<Warn>::is_on() {

  static bool is_on(
      std::string(cc::config::get()->log()) == C_LOG_WARN
          || logT<Info>::is_on());

  return is_on;
}

template<>
bool logT<Error>::is_on() {

  static bool is_on(
      std::string(cc::config::get()->log()) == C_LOG_ERROR
          || logT<Warn>::is_on());

  return is_on;
}

}
