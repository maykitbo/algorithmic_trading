#pragma once

#include <boost/icl/interval_map.hpp>
#include <limits>

#include "cubic_spline/cubic_spline.h"
#include "data_struct.h"
#include "newton_polynomial/newton_polynomial.h"
#include "utility/m_time.h"

namespace s21 {

/**
 * @brief Class for comparing the speed of Newton's Polynomial and Cubic Spline
 * interpolation approaches.
 *
 * This class provides a method to compare the performance of Newton's
 * Polynomial and Cubic Spline interpolation methods. The results of the
 * comparison are provided through a callback function.
 */
class InterpolationTime {
 public:
  /**
   * @brief Type definition for the result data of the comparison.
   */
  using result_data = std::vector<std::pair<int64_t, unsigned>>;

  /**
   * @brief Type definition for the callback function that receives the
   * comparison results.
   */
  using result_proc = std::function<void(const result_data &)>;

  /**
   * @brief Compares the speed of Newton's Polynomial and Cubic Spline
   * interpolation methods.
   *
   * @param points A vector of 2D points with arbitrary precision floating-point
   * coordinates.
   * @param cubic_spline A boolean flag indicating whether to include Cubic
   * Spline interpolation in the comparison.
   * @param newtons_degree A vector of unsigned integers representing the
   * degrees of Newton's Polynomial for comparison.
   * @param points_count Maximum number of interpolated points to be generated.
   * @param partitions Number of times the comparison is performed.
   * @param func Callback function that receives the comparison results.
   * @note The 'points_count' parameter must be greater than or equal to
   * 'points.size() + partitions'.
   */
  static void Compare(const PointsDec &points, bool cubic_spline,
                      const std::vector<unsigned> &newtons_degree,
                      unsigned points_count, unsigned partitions,
                      const result_proc &func);

 private:
  static unsigned OptimalIterations(unsigned size, unsigned k);
};

}  // namespace s21
