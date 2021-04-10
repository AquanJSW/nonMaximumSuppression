/**
 * 1D NMS for (2n+1)-neighborhood.
 *
 * Refer to: Alexander Neubeck. Efficient Non-Maximum Suppression
 */

#include <cstdio>
#include "vector"
#include "memory"

using namespace std;

vector<unsigned> target;
unsigned W;
vector<unsigned> pmax;

unsigned CompPartialMax(unsigned from, unsigned to) {
  pmax[to] = target[to];
  unsigned best = to;
  while (to > from) {
    if (target[--to] <= target[best])
      pmax[to] = target[best];
    else {
      pmax[to] = target[to];
      best = to;
    }
  }
  return best;
}

std::vector<unsigned>
nms_1d_fast(const std::vector<unsigned> &_target, const unsigned _n) {

  target = _target;
  W = target.size();
  pmax = vector<unsigned>(W, 0);
  // The number of adjacent numbers to be compared at one side.
  unsigned n = _n;
  // Maximum positions.
  std::vector<unsigned> ret = std::vector<unsigned>();
//  std::vector<unsigned> ret;

  unsigned i = n;
  CompPartialMax(0, i - 1);
  int chkpt = -1;

  while (i < W - 2 * n) {
    /// 在i的右邻域寻找极大值的位置
    unsigned j = CompPartialMax(i, i + n);
    /**
     * 寻找 j 的右扩展域中极大值的位置
     *
     * Cause j ∈ [i, i + n]
     * 所以第二参数 j + n ∈ [i + n, i + n + n]
     * - 当取 i + n 时，此时 i = j，pmax也没有改变，k = i + n, 此时用不到 k 值;
     * - 当取 i + n + 1 时，同上理，用不到 k 值；
     * - 当取 > i + n + 1 时，相当于在 j 的右邻域的 “扩展域” 寻找极大值的位置;
     */
    unsigned k = CompPartialMax(i + n + 1, j + n);
    /**
     * Checker if j locate the maximum in its right adjacent field(RAF).
     *
     * - i = j:
     *  显然成立;
     * - i != j：
     *  即 i < j，若扩展域的极大值仍小于 j，then j is its RAF.
     */
    if (i == j || target[j] > target[k]) {
      /**
       * Check if j locate the maximum in its left adjacent field(LAF).
       * 由于断点的存在，对LAF(i.e. [j - n, i - 1]的考察将分两个子域分别进行：
       * - 后段[chkpt, i - 1]
       * - 前段[j - n, chkpt - 1]
       *
       * 首先针对后段
       * - chkpt <= j - n || target[j] >= pmax[chkpt]
       *  - chkpt <= j - n
       *   j 的左邻域是否包含断点？
       *  - target[j] >= pmax[chkpt]
       *   若包含，则先将 [chkpt, i - 1] 中的极大值与 target[j] 对比
       *
       * 然后针对前段
       * - j - n == i || target[j] >= pmax[j - n]:
       *  Cause j ∈ [i, i + n]:
       *  - j < i + n:
       *   The maximum in field [j - n, i - 1], which is pmax[j - n],
       *   (注意这里的pmax[j - n]实际针对的是 [j - n, chkpt - 1],
       *   如果 chkpt != -1 的话)
       *   hasn't been compared with target[j] yet, if target[j] is still the larger
       *   one, maximum is found, i.e. target[j].
       *  - j == i + n:
       *   Now, j's left adjacent field is equals to i's right adjacent
       *   field, which has already been checked in j's definition.
       */
      if ((chkpt <= j - n || target[j] >= pmax[chkpt])
          && (j - n == i || target[j] >= pmax[j - n]))
//        printf("MaximumAt %d\n", j);
        ret.push_back(j);
      /**
       * chkpt 是扩展域（新域）的起始点
       *
       * CompPartialMax函数自右向左生成极大值序列pmax，这就导致了：如果 j > i，即
       * 生扩展，那么下一轮循环中 i、j 的左邻域的pmax可能不连续，必须记录本轮循环中扩
       * 展域的起始点 i + n + 1
       */
      if (i < j)
        chkpt = i + n + 1;
      i = j + n + 1;
      /**
       * 若扩展域中的极大值比 target[j] 更大
       */
    } else {
      /**
       * 直接将扩展域中极大值位置 k 当作候选点，注意此时候选点已经与左邻域比较过了
       */
      i = k;
      /**
       * pmax 在 chkpt 及其之后的数据尚未计算，故当作断点（新域的起始点）
       */
      chkpt = j + n + 1;
      while (i < W - n) {
        j = CompPartialMax(chkpt, i + n);
        /**
         * 如果极大值在旧域，则找到极大值 target[i]
         * 同时，在将 i = i + n + 1 后，下一轮循环需要考虑左邻域，故退出本循环，
         * 返回外层循环
         */
        if (target[i] > target[j]) {
//          printf("MaximumAt %d\n", i);
          ret.push_back(i);
          i = i + n + 1;
          break;
          /**
           * 如果极大值在扩展域
           *
           * 相当于将第一次进入上层 else 时的工作又重复一遍
           */
        } else {
          chkpt = i + n + 1;
          i = j;
        }
      }
    }
  }
  return ret;
}
