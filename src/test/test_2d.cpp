#include "opencv2/core.hpp"
#include "random"
#include "opencv2/core/hal/interface.h"
#include "cxxopts.hpp"

unsigned long len_decimal(unsigned long n) {
  unsigned long ret(1);
  while (n /= 10)
    ++ret;
  return ret;
}

// Only valid for OpenCV Mat filled with positive integers.
void print_mat(const cv::Mat &mtx, const unsigned &margin = 2) {
  double min, max;
  cv::minMaxLoc(mtx, &min, &max);
  printf("Min: %d\nMax: %d\n", static_cast<int>(min), static_cast<int>(max));

  auto len = len_decimal(static_cast<unsigned long>(max));
  printf("Max length: %d\n", static_cast<int>(len));

  for (int i = 0; i != mtx.size().height; ++i) {
    for (int j = 0; j != mtx.size().width; ++j)
      printf("%*d", static_cast<int>(-(len + margin)), mtx.at<int>(i, j));
    putchar('\n');
  }
}

int main(int argc, char **argv) {
  // Parse args.
  cxxopts::Options parser("nms_2d", "Test NMS in 2D situation.");
  parser.add_options()
      ("h,help", "Print help.")
      ("s,seed", "Random seed.", cxxopts::value<unsigned>()->default_value("0"))
      ("r,range", "Random range.",
       cxxopts::value<std::vector<unsigned>>()->default_value("0,100"))
      ("S,size", "Target size.",
       cxxopts::value<std::vector<unsigned>>()->default_value("20,20"))
      ("R,radius", "Search region's radius (exclude the centre point).",
       cxxopts::value<unsigned>()->default_value("3"));
  auto args = parser.parse(argc, argv);
  if (args.count("help")) {
    std::cout << parser.help() << std::endl;
    exit(0);
  }
  const auto &seed = args["seed"].as<unsigned>();
  const auto &range = args["range"].as<std::vector<unsigned>>();
  const auto &size = args["size"].as<std::vector<unsigned>>();
  const auto &radius = args["radius"].as<unsigned>();

  // Generate target.
  cv::Mat target(static_cast<int>(size[0]),
                 static_cast<int>(size[1]),
                 CV_16UC1);
  std::uniform_int_distribution<unsigned> ud(range[0], range[1]);
  std::default_random_engine e(seed);
  for (int i = 0; i != size[0]; ++i)
    for (int j = 0; j != size[1]; ++j) {
      target.at<unsigned>(i, j) = ud(e);
    }

  print_mat(target, 2);

  return 0;
}