#ifndef _PARAMETER_H
#define _PARAMETER_H

#include <memory>
#include <string>
#include <functional>

namespace cc {

class paramaterB {

public:
  enum _TYPE {

    _TYPE_STRING, _TYPE_LONG, _TYPE_DOUBLE, _TYPE_BOOL, _TYPE_CHAR
  };

  enum _SERVER {

    _SERVER_NONE, _SERVER_SQLITE, _SERVER_MYSQL, _SERVER_MSSQL
  };

public:

  static constexpr const char *const _PARAM_LOG { "log" };

  static constexpr const char *const _PARAM_SERVER_TYPE { "server-type" };

  static constexpr const char *const _PARAM_SERVER_TYPE_MSSQL { "mssql" };

  static constexpr const char *const _PARAM_SERVER_TYPE_MYSQL { "mysql" };

  static constexpr const char *const _PARAM_SERVER_TYPE_SQLITE { "sqlite" };

public:

  virtual _TYPE type() const = 0;

  virtual const std::string& name() const = 0;

  virtual const std::string& description() const = 0;

  virtual bool mandatory() const = 0;

  virtual bool is_valid() const = 0;

  virtual bool apply_default() = 0;

  virtual std::string to_string() const = 0;

  bool set_value(const std::string &value, std::vector<std::string> &errors);

  virtual ~paramaterB() {
  }

protected:

  paramaterB() {
  }

  bool set_string(const std::string &value, std::vector<std::string> &errors);

  bool set_long(const std::string &value, std::vector<std::string> &errors);

  bool set_double(const std::string &value, std::vector<std::string> &errors);

  bool set_bool(const std::string &value, std::vector<std::string> &errors);

  bool set_char(const std::string &value, std::vector<std::string> &errors);
};

template<typename T>
class parameterT: public paramaterB {

  using value_type [[maybe_unused]] = typename std::enable_if<
  std::is_same<std::string, T>::value ||
  std::is_same<long, T>::value ||
  std::is_same<char, T>::value ||
  std::is_same<bool, T>::value ||
  std::is_same<double, T>::value>::type;

public:

  parameterT(_TYPE type, const std::string &name,
      const std::string &description, const std::unique_ptr<T> &default_value) :
      _type(type), _name(name), _description(description), _mandatory(
          static_cast<bool>(!default_value.get())), _default_value(
          default_value.get() ? (new T(*default_value.get())) : nullptr), _value(), _is_valid(
          false) {
  }

public:

  virtual ~parameterT() override {
  }

  virtual _TYPE type() const override {

    return _type;
  }

  virtual const std::string& name() const override {

    return _name;
  }

  virtual const std::string& description() const override {

    return _description;
  }

  virtual bool mandatory() const override {

    return _mandatory;
  }

  virtual const std::unique_ptr<T>& default_value() const {

    return _default_value;
  }

  virtual const T& value() const {

    return *_value.get();
  }

  virtual bool is_valid() const override {

    return _is_valid;
  }

  virtual bool apply_default() override {

    if (this->mandatory()) {
      return false;
    }

    if (!this->default_value().get()) {
      return false;
    }

    _value.reset(new T(*this->default_value().get()));

    _is_valid = true;

    return _is_valid;
  }

  virtual std::string to_string() const override {

    std::ostringstream os;

    os << "["
        << name()
        << "] = '"
        << value()
        << "'";

    return os.str();
  }

private:

  const _TYPE _type;

  const std::string _name;

  const std::string _description;

  const bool _mandatory;

  std::unique_ptr<T> _default_value;

  std::unique_ptr<T> _value;

  bool _is_valid;

protected:

  bool set(const T &value) {

    _value.reset(new T(value));

    _is_valid = true;

    return _is_valid;
  }

private:

  parameterT(const parameterT&) = delete;

  parameterT& operator=(const parameterT&) = delete;

};

}

#endif
