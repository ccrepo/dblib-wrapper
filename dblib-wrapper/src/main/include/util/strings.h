#ifndef _STRINGS_H
#define _STRINGS_H

#include <string>

namespace cc {

class strings {

public:

  static std::string rpad(const std::string& s,
      uint32_t size);

};

}

#endif
