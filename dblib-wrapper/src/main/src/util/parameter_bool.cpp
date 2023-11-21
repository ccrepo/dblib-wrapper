
#include <sstream>
#include <iostream>

#include "parameter_bool.h"

namespace cc {

parameter_bool::parameter_bool(const std::string &name,
    const std::string &description, const std::unique_ptr<bool> &defauit_value,
    const std::function<bool(const bool&)> &validator) :
    parameterT<bool>(_TYPE_BOOL, name, description, defauit_value), _validator(
        validator) {
}

parameter_bool::parameter_bool(const std::string &name,
    const std::string &description,
    const std::function<bool(const bool&)> &validator) :
    parameterT<bool>(_TYPE_BOOL, name, description, std::unique_ptr<bool>()), _validator(
        validator) {
}

bool parameter_bool::set_value(const std::string &value,
    std::vector<std::string> &errors) {

  bool result(false);

  bool error(false);

  if (value == "true" || value == "t" || value == "") {

    result = true;

  } else if (!(value == "false" || value == "f")) {

    error = true;
  }

  if (error || !_validator(result)) {

    std::ostringstream os;

    os << "failed validate '" << name() << "' with value '" << value << ".";

    errors.push_back(os.str());

    return false;
  }

  return parameter_bool::set(result);
}

}
