#include <sstream>
#include <iostream>

#include "parameter_long.h"

namespace cc {

parameter_long::parameter_long(const std::string &name,
    const std::string &description, const std::unique_ptr<long> &defauit_value,
    const std::function<bool(const long&)> &validator) :
    parameterT<long>(_TYPE_BOOL, name, description, defauit_value), _validator(
        validator) {
}

parameter_long::parameter_long(const std::string &name,
    const std::string &description,
    const std::function<bool(const long&)> &validator) :
    parameterT<long>(_TYPE_BOOL, name, description, std::unique_ptr<long>()), _validator(
        validator) {
}

bool parameter_long::set_value(const std::string &value,
    std::vector<std::string> &errors) {

  long result(0);

  bool error(false);

  if (value.find_first_not_of("0123456789") != std::string::npos) {

    error = true;
  }

  try {

    result = std::stol(value);

  } catch (std::exception &e) {

    error = true;

  }

  if (error || !_validator(result)) {

    std::ostringstream os;

    os << "failed validate '" << name() << "' with value '" << value << ".";

    errors.push_back(os.str());

    return false;
  }

  return parameter_long::set(result);
}

}
