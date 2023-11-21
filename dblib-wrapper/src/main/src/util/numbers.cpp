
#include "numbers.h"

namespace cc {

bool numbers::is_long(const std::string &s) {

  try {

    long result [[maybe_unused]] = std::stol(s);

  } catch (std::exception& e) {

    return false;
  }

  return true;
}

bool numbers::is_double(const std::string &s) {

  try {

    long result [[maybe_unused]] = std::stod(s);

  } catch (std::exception& e) {

    return false;
  }

  return true;
}



}
