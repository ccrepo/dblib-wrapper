#include <sstream>
#include <iostream>

#include "parameter_string.h"

namespace cc {

parameter_string::parameter_string(const std::string &name,
    const std::string &description,
    const std::unique_ptr<std::string> &defauit_value,
    const std::function<bool(const std::string&)> &validator) :
    parameterT<std::string>(_TYPE_STRING, name, description, defauit_value), _validator(
        validator) {
}

parameter_string::parameter_string(const std::string &name,
    const std::string &description,
    const std::function<bool(const std::string&)> &validator) :
    parameterT<std::string>(_TYPE_STRING, name, description,
        std::unique_ptr<std::string>()), _validator(validator) {
}

bool parameter_string::set_value(const std::string &value,
    std::vector<std::string> &errors) {

  if (!_validator(value)) {

    std::ostringstream os;

    os << "failed validate '" << name() << "'.";

    errors.push_back(os.str());

    return false;
  }

  return parameter_string::set(value);
}

}
