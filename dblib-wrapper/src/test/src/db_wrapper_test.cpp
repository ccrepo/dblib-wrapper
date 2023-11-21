#include <iostream>
#include <functional>

#include "db_wrapper.h"

#include "logT.h"
#include "log.h"
#include "config.h"

// TODO
// 1. TODO remove maybe_unused.
// 2. TODO NYI/NNN fix in code.
// 3. TODO implement mssql.
// 4. TODO implement mysql.

bool f(int i) {
  return 1 == i;
}

int main(int argc, const char **argv) {

  if (!cc::config::init(argc, argv)) {

    std::cerr << "failed." << std::endl;

    return 1;
  }

  if (cc::config::is_help()) {

    cc::config::do_help();

    return 0;
  }

  if (!cc::config::is_valid()) {

    std::cerr << "parameters/configuration not valid." << std::endl;

    return 1;
  }

  INFO("start.");

  ERROR("log on");
  WARN("log on");
  INFO("log on");
  DEBUG("log on");

  cc::config::get()->dump();

  //std::unique_ptr<cc::connection> connection(cc::connection::get_connection());

  INFO("stop.");

  std::cerr << "." << std::endl;

  return 0;
}
