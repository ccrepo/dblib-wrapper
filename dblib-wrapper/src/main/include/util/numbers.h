#ifndef _NUMBERS_H
#define _NUMBERS_H

#include <string>

namespace cc {

class numbers {

public:

  static bool is_long(const std::string &s);

  static bool is_double(const std::string &s);

  static bool is_number(const std::string &s) {

    return is_long(s) || is_number(s);
  }

};

}

#endif
