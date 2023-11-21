#ifndef _PARAMETER_BOOL_H
#define _PARAMETER_BOOL_H

#include "parameter.h"

namespace cc {

class parameter_bool: public parameterT<bool> {

public:

  explicit parameter_bool(const std::string &name,
      const std::string &description,
      const std::unique_ptr<bool> &defauit_value = std::unique_ptr<bool>(),
      const std::function<bool(const bool&)> &validator = default_validator);

  explicit parameter_bool(const std::string &name,
      const std::string &description,
      const std::function<bool(const bool&)> &validator);

  virtual ~parameter_bool() override {
  }

  bool set_value(const std::string &value, std::vector<std::string> &errors);

private:

  static inline bool default_validator(const bool&) {

    return true;
  };

private:

  const std::function<bool(const bool &t)> _validator;
};

}

#endif
