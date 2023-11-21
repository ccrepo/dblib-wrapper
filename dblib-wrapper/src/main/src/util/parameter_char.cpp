#include <sstream>
#include <iostream>

#include "parameter_char.h"

namespace cc {

parameter_char::parameter_char(const std::string &name,
    const std::string &description, const std::unique_ptr<char> &defauit_value,
    const std::function<bool(const char&)> &validator) :
    parameterT<char>(_TYPE_CHAR, name, description, defauit_value), _validator(
        validator) {
}

parameter_char::parameter_char(const std::string &name,
    const std::string &description,
    const std::function<bool(const char&)> &validator) :
    parameterT<char>(_TYPE_CHAR, name, description, std::unique_ptr<char>()), _validator(
        validator) {
}

bool parameter_char::set_value(const std::string &value,
    std::vector<std::string> &errors) {

  if (value.length() != 1 || !_validator(value[0])) {

    std::ostringstream os;

    os << "could not set '" << name() << "'.";

    errors.push_back(os.str());

    return false;
  }

  return parameter_char::set(value[0]);
}

}
