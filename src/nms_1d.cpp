#include "vector"
#include "memory"

unsigned find_max(const std::shared_ptr<unsigned> &i,
                  const unsigned n,
                  const std::vector<unsigned> &target) {
  unsigned max_pos = *i - n;
  for (unsigned j = *i - n + 1; j != *i + n + 1; ++j)
    if (target[max_pos] < target[j])
      max_pos = j;

//  if (*i == max_pos) {
//    *i += n + 1;
//    return true;
//  } else if (*i > max_pos) {
//    *i = n + max_pos + 1;
//  } else {
//    *i = max_pos;
//  }
//  return false;
  return max_pos;
}

std::vector<unsigned> nms_1d(const std::vector<unsigned> &target,
                             const unsigned n) {
  std::vector<unsigned> ret;

  auto i = std::make_shared<unsigned>(n);
  while (*i < target.size() - n) {
    auto max_pos = find_max(i, n, target);
    if (*i == max_pos) {
      ret.push_back(*i);
      *i += n + 1;
    } else if (*i > max_pos) {
      *i = n + max_pos + 1;
    } else {
      *i = max_pos;
    }
  }

  return ret;
}