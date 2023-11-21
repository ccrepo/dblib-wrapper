#ifndef _CONFIG_H
#define _CONFIG_H

#include <memory>
#include <string>
#include <map>
#include <vector>
#include <atomic>

#include "parameter_bool.h"

namespace cc {

class config final : public std::enable_shared_from_this<config> {

public:
  static bool init(int32_t argc, const char *argv[]);

  static void do_help();

  static bool is_help() {

    return _is_help;
  }

  static const config* get() {

    return _config.get();
  }

  static bool is_valid() {

    return _config.get() && _config.get()->_is_valid;
  }

public:

  const std::string& log() const {

    return _log;
  }

  paramaterB::_SERVER server_type() const {

    return _server_type;
  }

public:

  void dump() const;

public:

  ~config() {
  }

private:

  static bool load(int32_t argc, const char *argv[],
      std::vector<std::string> &errors);

  static bool load_parameters();

  static bool load_arguments(int32_t argc, const char *argv[],
      std::map<std::string, std::string> &arguments,
      std::vector<std::string> &errors);

  static bool set_param(const std::string &name, const std::string &value,
      std::vector<std::string> &errors);

  static bool process_arguments(std::map<std::string, std::string> &arguments,
      std::vector<std::string> &argument_names,
      std::vector<std::string> &parameter_names,
      std::vector<std::string> &errors);

  static bool process_parameters(std::vector<std::string> &parameter_names,
      std::vector<std::string> &errors);

private:

  static std::shared_ptr<config> _config;

  static bool _is_help;

  static std::map<std::string, std::unique_ptr<paramaterB>> _parameters;

private:
  std::atomic<bool> _is_valid;

private:

  config(std::vector<std::string> &errors);

  bool set_log(std::vector<std::string> &errors);

  bool set_server_type(std::vector<std::string> &errors);

private:

  std::string _log;

  paramaterB::_SERVER _server_type;

private:

  config& operator=(const config&) = delete;

  config(const config&) = delete;

};

}

#endif
