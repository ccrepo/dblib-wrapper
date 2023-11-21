#ifndef _PARAMETER_CHAR_H
#define _PARAMETER_CHAR_H

#include "parameter.h"

namespace cc {

class parameter_char: public parameterT<char> {

public:

  explicit parameter_char(const std::string &name,
      const std::string &description,
      const std::unique_ptr<char> &defauit_value = std::unique_ptr<char>(),
      const std::function<bool(const char&)> &validator = default_validator);

  explicit parameter_char(const std::string &name,
      const std::string &description,
      const std::function<bool(const char&)> &validator);

  virtual ~parameter_char() override {
  }

  bool set_value(const std::string &value, std::vector<std::string> &errors);

private:

  static inline bool default_validator(const char&) {

    return true;
  };

private:

  const std::function<bool(const char &t)> _validator;

};

}

#endif
