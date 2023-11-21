#include <sstream>
#include <iostream>

#include "parameter_double.h"

namespace cc {

parameter_double::parameter_double(const std::string &name,
    const std::string &description,
    const std::unique_ptr<double> &defauit_value,
    const std::function<bool(const double&)> &validator) :
    parameterT<double>(_TYPE_DOUBLE, name, description, defauit_value), _validator(
        validator) {
}

parameter_double::parameter_double(const std::string &name,
    const std::string &description,
    const std::function<bool(const double&)> &validator) :
    parameterT<double>(_TYPE_DOUBLE, name, description,
        std::unique_ptr<double>()), _validator(validator) {
}

bool parameter_double::set_value(const std::string &value,
    std::vector<std::string> &errors) {

  double result(0);

  bool error(false);

  try {

    result = std::stod(value);

  } catch (std::exception &e) {

    error = true;
  }

  if (error || !_validator(result)) {

    std::ostringstream os;

    os << "failed validate '" << name() << "' with value '" << value << ".";

    errors.push_back(os.str());

    return false;
  }

  return parameter_double::set(result);
}

}
