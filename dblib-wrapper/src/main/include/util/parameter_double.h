#ifndef _PARAMETER_DOUBLE_H
#define _PARAMETER_DOUBLE_H

#include "parameter.h"

namespace cc {

class parameter_double: public parameterT<double> {

public:

  explicit parameter_double(const std::string &name,
      const std::string &description,
      const std::unique_ptr<double> &defauit_value = std::unique_ptr<double>(),
      const std::function<bool(const double&)> &validator = default_validator);

  explicit parameter_double(const std::string &name,
      const std::string &description,
      const std::function<bool(const double&)> &validator);

  virtual ~parameter_double() override {
  }

  bool set_value(const std::string &value, std::vector<std::string> &errors);

private:

  static inline bool default_validator(const double&) {

    return true;
  };

private:

  const std::function<bool(const double &t)> _validator;

};

}

#endif
