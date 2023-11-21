#include <sstream>
#include <iostream>

#include "parameter_bool.h"
#include "parameter_char.h"
#include "parameter_double.h"
#include "parameter_long.h"
#include "parameter_string.h"

namespace cc {

bool paramaterB::set_value(const std::string &value,
    std::vector<std::string> &errors) {

  std::ostringstream os;

  switch (this->type()) {

  case _TYPE_STRING: {

    return set_string(value, errors);
  }

  case _TYPE_LONG: {

    return set_long(value, errors);
  }

  case _TYPE_DOUBLE: {

    return set_double(value, errors);
  }

  case _TYPE_BOOL: {

    return set_bool(value, errors);
  }

  case _TYPE_CHAR: {

    return set_char(value, errors);
  }

  default: {

    os << "parameter '" << this->name() << "' type unknown.";

    errors.push_back(os.str());

    return false;
  }

  }

  return true;
}

bool paramaterB::set_string(const std::string &value,
    std::vector<std::string> &errors) {

  parameter_string *parameter(dynamic_cast<parameter_string*>(this));

  if (!parameter) {

    std::ostringstream os;

    os << "'" << name() << "' type mismatch.";

    errors.push_back(os.str());

    return false;
  }

  return parameter->set_value(value, errors);
}

bool paramaterB::set_long(const std::string &value,
    std::vector<std::string> &errors) {

  parameter_long *parameter(dynamic_cast<parameter_long*>(this));

  if (!parameter) {

    std::ostringstream os;

    os << "'" << name() << "' type mismatch.";

    errors.push_back(os.str());

    return false;
  }

  return parameter->set_value(value, errors);
}

bool paramaterB::set_double(const std::string &value,
    std::vector<std::string> &errors) {

  parameter_double *parameter(dynamic_cast<parameter_double*>(this));

  if (!parameter) {

    std::ostringstream os;

    os << "'" << name() << "' type mismatch.";

    errors.push_back(os.str());

    return false;
  }

  return parameter->set_value(value, errors);
}

bool paramaterB::set_bool(const std::string &value,
    std::vector<std::string> &errors) {

  parameter_bool *parameter(dynamic_cast<parameter_bool*>(this));

  if (!parameter) {

    std::ostringstream os;

    os << "'" << name() << "' type mismatch.";

    errors.push_back(os.str());

    return false;
  }

  return parameter->set_value(value, errors);
}

bool paramaterB::set_char(const std::string &value,
    std::vector<std::string> &errors) {

  parameter_char *parameter(dynamic_cast<parameter_char*>(this));

  if (!parameter) {

    std::ostringstream os;

    os << "'" << name() << "' type mismatch.";

    errors.push_back(os.str());

    return false;
  }

  return parameter->set_value(value, errors);
}

}
