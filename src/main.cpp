/**
 * @file main.cpp
 * @brief Main file in this project.
 *
 * @author Maxim <john.jasper.doe@gmail.com>
 * @date 2020
 */

/* See the license in the file "LICENSE.txt" in the root directory. */

#include <fstream>
#include <iostream>
#include <boost/program_options.hpp>

namespace {

struct param {
  std::size_t k_means{0};
};

using param_t = param;

void get_param(const int argc, const char* const argv[], param_t& param) {
  namespace po = boost::program_options;

  // clang-format off
  po::options_description desc("Options: ");
  desc.add_options()
      ("help,h", "this help")
      ("k", po::value<std::size_t>(), "number of clusters for k-means algorithm");
  // clang-format on

  po::variables_map vm;
  try {
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);
  }
  catch (boost::program_options::error& err) {
    throw std::invalid_argument(err.what());
  }

  if (vm.count("help") || vm.count("h")) {
    std::cout << desc << "\n";
    exit(0);
  }

  if (vm.count("k"))
    param.k_means = vm["k"].as<std::size_t>();
  else
    throw std::invalid_argument("Number of clusters was not set");
}

} /* :: */

/** @brief Main entry point */
int main(int argc, const char* argv[]) {
  param_t prm;

  try {
    get_param(argc, argv, prm);
  }
  catch (const std::invalid_argument& e) {
    std::cerr << e.what() << std::endl;
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
