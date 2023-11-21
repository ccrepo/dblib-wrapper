#include "strings.h"

namespace cc {

std::string strings::rpad(const std::string &s, uint32_t size) {

  int64_t len(size - s.length());

  if (len <= 0) {

    return s;
  }

  std::string buffer(s);

  return buffer.insert(buffer.size(), len, ' ');
}

}
