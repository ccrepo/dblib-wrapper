#ifndef _PARAMETER_LONG_H
#define _PARAMETER_LONG_H

#include "parameter.h"

namespace cc {

class parameter_long: public parameterT<long> {

public:

  explicit parameter_long(const std::string &name,
      const std::string &description,
      const std::unique_ptr<long> &defauit_value = std::unique_ptr<long>(),
      const std::function<bool(const long&)> &validator = default_validator);

  explicit parameter_long(const std::string &name,
      const std::string &description,
      const std::function<bool(const long&)> &validator);

  virtual ~parameter_long() override {
  }

  bool set_value(const std::string &value, std::vector<std::string> &errors);

private:

  static inline bool default_validator(const long&) {

    return true;
  };

private:

  const std::function<bool(const long &t)> _validator;

};

}

#endif
