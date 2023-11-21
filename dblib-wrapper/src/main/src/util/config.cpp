#include <algorithm>
#include <string>
#include <iostream>
#include <map>
#include <list>
#include <vector>
#include <sstream>
#include <ctype.h>

#include "logT.h"
#include "log.h"

#include "config.h"
#include "strings.h"
#include "numbers.h"
#include "containers.h"

#include "parameter_bool.h"
#include "parameter_char.h"
#include "parameter_double.h"
#include "parameter_long.h"
#include "parameter_string.h"

#define _CONFIG_H_DISABLE_TEST_CODE
//#undef _CONFIG_H_DISABLE_TEST_CODE

namespace cc {

std::shared_ptr<config> config::_config;

bool config::_is_help(false);

std::map<std::string, std::unique_ptr<paramaterB>> config::_parameters;

config::config(std::vector<std::string> &errors) :
    _is_valid(false), _log(), _server_type(paramaterB::_SERVER_NONE) {

  if (!std::all_of(_parameters.begin(), _parameters.end(), [](const auto &p) {
    return p.second->is_valid();
  })) {

    errors.push_back("parameters not set.");

    return;
  }

  _is_valid = set_log(errors) && set_server_type(errors);
}

bool config::init(int32_t argc, const char *argv[]) {

  static std::vector<std::string> errors;

  static const bool inited(config::load(argc, argv, errors));

  if (!inited) {

    for (const auto &error : errors) {
      std::cerr << error << std::endl;
    }
  }

  return inited;
}

bool config::load_parameters() {

  _parameters[paramaterB::_PARAM_LOG] = std::unique_ptr < paramaterB
      > (new parameter_string(paramaterB::_PARAM_LOG,
          "log level (debug|info|warn|error)",
          std::make_unique < std::string > (logB::C_LOG_INFO)));

  _parameters[paramaterB::_PARAM_SERVER_TYPE] = std::unique_ptr < paramaterB
      > (new parameter_string(paramaterB::_PARAM_SERVER_TYPE,
          "server type (mysql|sqlite|mssql)"));

#ifndef _CONFIG_H_DISABLE_TEST_CODE

  _parameters["s"] = std::unique_ptr < paramaterB
      > (new parameter_double("s", "test string"));

  _parameters["d"] = std::unique_ptr < paramaterB
      > (new parameter_double("d", "test double"));

  _parameters["l"] = std::unique_ptr < paramaterB
      > (new parameter_long("l", "test long"));

  _parameters["c"] = std::unique_ptr<paramaterB>(
      new parameter_char("c", "test char", [](const char& c) { return c == 'b'; } ));

  _parameters["b"] = std::unique_ptr<paramaterB>(
      new parameter_bool("b", "test bool", std::make_unique<bool>(true)));

#endif

  return true;
}

void config::do_help() {

  std::cout << std::endl << "help:" << std::endl << std::endl
      << "***************************************************************************************************************"
      << std::endl
      << "* progname: dblib-wrapperTest                                                                                *"
      << std::endl
      << "* description: demo database library wrapper                                                                  *"
      << std::endl
      << "***************************************************************************************************************"
      << std::endl
      << "* parameter name  |  mandatory  | boolean flag | description                       | environment alternative  *"
      << std::endl
      << "***************************************************************************************************************"
      << std::endl
      << "* -h              |  no         | yes          | display this help menu            | N/A                      *"
      << std::endl;

  for (const auto &parameter : _parameters) {

    std::cout << "* " << strings::rpad(parameter.first, 16) << "|  "
        << strings::rpad(parameter.second->mandatory() ? "yes" : "no", 11)
        << "| "
        << strings::rpad(
            parameter.second->type() == paramaterB::_TYPE_BOOL ? "yes" : "no",
            13) << "| " << strings::rpad(parameter.second->description(), 34)
        << "| " << strings::rpad("N/A", 25) << "*" << std::endl;
  }

  std::cout
      << "***************************************************************************************************************"
      << std::endl
      << "* notes:                                                                                                      *"
      << std::endl
      << "*   parameters can be supplied either at the command line or via the indicated environment variable.          *"
      << std::endl
      << "*   the values supplied at the command line override those in the environment, to use environment             *"
      << std::endl
      << "*   setting you need to supply the -env parameter. environment functionality coming soon.                     *"
      << std::endl
      << "***************************************************************************************************************"
      << std::endl
      << "* examples:                                                                                                   *"
      << std::endl
      << "*   dblib-wrapperTest -h # display this help menu                                                             *"
      << std::endl
      << "***************************************************************************************************************"
      << std::endl << std::endl;
}

bool config::load(int32_t argc, const char *argv[], // TODO tidy
    std::vector<std::string> &errors) {

  if (!config::load_parameters()) {

    return false;
  }

  std::map < std::string, std::string > arguments;

  if (!config::load_arguments(argc, argv, arguments, errors)) {

    return false;
  }

  if (_is_help) {

    return true;
  }

  auto argument_names(containers::keys (arguments));

  auto parameter_names(containers::keys(_parameters));

  bool result(
      process_arguments(arguments, argument_names, parameter_names, errors));

  if (!process_parameters(parameter_names, errors)) {

    result = false;
  }

  containers::errors("unknown '", argument_names, "'.", errors);

  containers::errors("parameter '", parameter_names, "' is mandatory.", errors);

  if (!result || !argument_names.empty() || !parameter_names.empty()) {

    return false;
  }

  _config.reset(new config(errors));

  return _config->is_valid();
}

bool config::process_arguments(std::map<std::string, std::string> &arguments,
    std::vector<std::string> &argument_names,
    std::vector<std::string> &parameter_names,
    std::vector<std::string> &errors) {

  bool result(true);

  for (auto arguments : arguments) {

    auto i = std::find(parameter_names.begin(), parameter_names.end(),
        arguments.first);

    if (i != parameter_names.end()) {

      argument_names.erase(
          std::remove(argument_names.begin(), argument_names.end(),
              arguments.first), argument_names.end());

      parameter_names.erase(i);

      if (!set_param(arguments.first, arguments.second, errors)) {

        result = false;
      }

    } else {

      result = false;
    }
  }

  return result;
}

bool config::process_parameters(std::vector<std::string> &parameter_names,
    std::vector<std::string> &errors) {

  bool result(true);

  for (const auto &parameter : _parameters) {

    auto i = std::find(parameter_names.begin(), parameter_names.end(),
        parameter.first);

    if (i != parameter_names.end()) {

      if (!parameter.second->mandatory()) {

        parameter_names.erase(i);

        if (!parameter.second->apply_default()) {

          std::ostringstream os;

          os << "parameter '" << parameter.first << "' could not be defaulted.";

          errors.push_back(os.str());
        }
      }
    }
  }

  return result;
}

bool config::load_arguments(int32_t argc, const char *argv[],
    std::map<std::string, std::string> &arguments,
    std::vector<std::string> &errors) {

  for (auto i(1); i < argc; ++i) {

    std::string name(argv[i]);

    std::transform(name.begin(), name.end(), name.begin(), ::tolower);

    if (name == "-h") {

      _is_help = true;

      return true;
    }

    if (name.length() < 2 || name[0] != '-' || !std::isalpha(name[1])
        || name[1] == '.') {

      std::ostringstream os;

      os << "invalid token '" << name << "'";

      errors.push_back(os.str());

      return false;
    }

    if ((i + 1) >= argc) {

      arguments[name.substr(1)] = std::string();

      return true;
    }

    std::string value(argv[i + 1]);

    if (value.empty() || value[0] != '-'
        || (value[0] == '-' && numbers::is_number(value))) {

      arguments[name.substr(1)] = value;

      ++i;
    }
  }

  return true;
}

bool config::set_param(const std::string &name, const std::string &value,
    std::vector<std::string> &errors) {

  if (!_parameters.contains(name)) {

    std::ostringstream os;

    os << "parameter name '" << name << "' not unknown.";

    errors.push_back(os.str());

    return false;
  }

  return _parameters[name]->set_value(value, errors);
}

bool config::set_log(std::vector<std::string> &errors) {

  auto i = _parameters.find(paramaterB::_PARAM_LOG);

  if (i == _parameters.end()) {

    std::ostringstream os;

    os << "'" << paramaterB::_PARAM_LOG
        << "' value not in configured parameters.";

    errors.push_back(os.str());

    return false;
  }

  parameter_string *parameter(dynamic_cast<parameter_string*>(i->second.get()));

  if (!parameter) {

    std::ostringstream os;

    os << "'" << paramaterB::_PARAM_LOG << "' failed dynamic cast.";

    errors.push_back(os.str());

    return false;
  }

  std::string value(parameter->value());

  if (value == logB::C_LOG_DEBUG) {

    _log = logB::C_LOG_DEBUG;

  } else if (value == logB::C_LOG_INFO) {

    _log = logB::C_LOG_INFO;

  } else if (value == logB::C_LOG_WARN) {

    _log = logB::C_LOG_WARN;

  } else if (value == logB::C_LOG_ERROR) {

    _log = logB::C_LOG_ERROR;

  } else {

    return false;
  }

  return true;
}

bool config::set_server_type(std::vector<std::string> &errors) {

  auto i = _parameters.find(paramaterB::_PARAM_SERVER_TYPE);

  if (i == _parameters.end()) {

    std::ostringstream os;

    os << "'" << paramaterB::_PARAM_SERVER_TYPE
        << "' value not in configured parameters.";

    errors.push_back(os.str());

    return false;
  }

  parameter_string *parameter(dynamic_cast<parameter_string*>(i->second.get()));

  if (!parameter) {

    std::ostringstream os;

    os << "'" << paramaterB::_PARAM_SERVER_TYPE << "' failed dynamic cast.";

    errors.push_back(os.str());

    return false;
  }

  std::string value(parameter->value());

  if (value == paramaterB::_PARAM_SERVER_TYPE_SQLITE) {

    _server_type = paramaterB::_SERVER_SQLITE;

  } else if (false && value == paramaterB::_PARAM_SERVER_TYPE_MYSQL) { // TODO implement option

    _server_type = paramaterB::_SERVER_MYSQL;

  } else if (false && value == paramaterB::_PARAM_SERVER_TYPE_MSSQL) { // TODO implement option

    _server_type = paramaterB::_SERVER_MSSQL;

  } else {

    return false;
  }

  return true;
}

void config::dump() const {

  if (!_is_valid) {

    return;
  }

  for (const auto &parameter : _parameters) {

    INFO("parameter: ", parameter.second->to_string());
  }
}

}
