#ifndef _PARAMETER_STRING_H
#define _PARAMETER_STRING_H

#include "parameter.h"

namespace cc {

class parameter_string: public parameterT<std::string> {

public:

  explicit parameter_string(const std::string &name,
      const std::string &description,
      const std::unique_ptr<std::string> &defauit_value = std::unique_ptr<
          std::string>(),
      const std::function<bool(const std::string&)> &validator =
          default_validator);

  explicit parameter_string(const std::string &name,
      const std::string &description,
      const std::function<bool(const std::string&)> &validator);

  virtual ~parameter_string() override {
  }

  bool set_value(const std::string &value, std::vector<std::string> &errors);

private:

  static inline bool default_validator(const std::string&) {

    return true;
  };

private:

  const std::function<bool(const std::string &t)> _validator;

};

}

#endif
