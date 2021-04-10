#include "cxxopts.hpp"
#include "vector"
#include "random"
#include "opencv2/core.hpp"

int main(int argc, char **argv) {
  // Parse arguments
  cxxopts::Options opts("1D Test", "Test NSM in 1D situation.");
  opts.add_options()
      ("l,length", "Target length to be tested.",
       cxxopts::value<int>()->default_value("30"))
      ("s,seed", "Seed to generate random numbers.",
       cxxopts::value<int>()->default_value("0"))
      ("r,range", "Random range.",
       cxxopts::value<std::vector<unsigned>>()->default_value("0,100"))
      ("f,fast", "Enable test fast version.")
      ("h,help", "Print help.");
  auto args = opts.parse(argc, argv);
  if (args.count("help")) {
    std::cout << opts.help() << std::endl;
    exit(0);
  }

  // Generate a vector containing randoms
  std::uniform_int_distribution<unsigned>
      ud(args["range"].as<std::vector<unsigned>>()[0],
         args["range"].as<std::vector<unsigned>>()[1]);
  std::default_random_engine e(args["seed"].as<int>());
  std::vector<unsigned> target;
  for (int i = 0; i != args["length"].as<int>(); ++i)
    target.push_back(ud(e));

  // Start test.
  if (args["fast"].as<bool>()) {

  }

  return 0;
}