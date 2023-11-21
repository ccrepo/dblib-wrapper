#ifndef _CONTAINERS_H
#define _CONTAINERS_H

#include <string>
#include <map>
#include <vector>
#include <sstream>

namespace cc {

class containers {

public:

  template<typename T, typename U>
  static inline std::vector<T> keys(const std::map<T, U> &m) {

    std::vector<T> buffer;

    std::transform(m.begin(), m.end(), std::back_inserter(buffer),
        [](const auto &p) {
          return p.first;
        });

    return buffer;
  }

  template<typename T>
  static inline void errors(const std::string &pre, const std::vector<T> &vs,
      const std::string &post, std::vector<std::string> &errors) {

    for (const auto &v : vs) {

      std::ostringstream os;

      os << pre << v << post;

      errors.push_back(os.str());
    }
  }

};

}

#endif
