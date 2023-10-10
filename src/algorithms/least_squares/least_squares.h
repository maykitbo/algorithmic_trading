#pragma once

#include <math.h>

#include <algorithm>
#include <boost/multiprecision/cpp_dec_float.hpp>

#include "../../common/data_struct.h"
#include "../matrix/matrix.h"

namespace s21 {

/**
 * @brief Class for solving approximation tasks using the Least Squares method.
 *
 * This class provides methods to approximate a sequence of points using the
 * Least Squares method.
 */
class LeastSquares {
 public:
  /**
   * @brief Constructs a LeastSquares object from a set of 2D points.
   *
   * @param points A vector of 2D points. For more information, see the
   * documentation for the PointsDec type.
   */
  LeastSquares(const PointsDec &points);

  /**
   * @brief Solves the approximation problem and returns a vector of
   * approximated points using the Least Squares method.
   *
   * @param points Number of points to be approximated in the sequence.
   * @param degree Degree of the polynomial used for approximation.
   * @param weights A vector of arbitrary precision floating-point weights
   * corresponding to input points.
   * @return Vector of approximated points PointsDec. The size of the vector
   *         will be greater than or equal to 'points.size() + count'.
   */
  PointsDec Solve(unsigned points, unsigned degree, const WeightsDec &weights);

  /**
   * @brief Static method to solve the approximation problem and return a vector
   * of approximated points using the Least Squares method.
   *
   * See the documentation for the Solve method for more information.
   */
  static PointsDec Solve(const PointsDec &points, unsigned degree,
                         unsigned points_count, const WeightsDec &weights);

 private:
  using matrix = Matrix<Real>;
  const PointsDec &points_;
  unsigned degree_;
  std::vector<Real> weights_;
  std::vector<Real> coef_;

  bool CreatePolynomial(unsigned degree, const WeightsDec &weights);

  void MulXTW2X(const matrix &X, matrix &A);
  void MulCW2Y(const matrix &C);
};

}  // namespace s21
