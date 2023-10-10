#pragma once

#include <limits>

#include "../../common/data_struct.h"

namespace s21 {

/**
 * @brief Class for solving interpolation problems using the Cubic Spline
 * method.
 *
 * This class provides methods to create a cubic spline interpolation from a set
 * of 2D points.
 */
class CubicSpline {
 public:
  /**
   * @brief Constructs a CubicSpline object from a set of 2D points.
   *
   * @param points A vector of 2D points. For more information, see the
   * documentation for the PointsDec type.
   */
  CubicSpline(const PointsDec &points);

  /**
   * @brief Solves the interpolation problem and returns a vector of
   * interpolated points.
   *
   * @param N Number of interpolated points to generate. If N is less than the
   * size of input data, returns input data.
   * @return Vector of interpolated points. For more information, see the
   * documentation for the PointsDec type.
   */
  PointsDec Solve(unsigned int N);

  /**
   * @brief Calculates the Y value corresponding to the given X value using the
   * cubic spline interpolation.
   *
   * @param time X value for which the Y value needs to be calculated.
   * @return Y value calculated using the cubic spline interpolation.
   * @throws returns std::numeric_limits<Real>::quiet_NaN() If the input X value
   * is outside the range of the input data.
   */
  Real Calc(Real time);

  /**
   * @brief Static method to solve the interpolation problem and return a vector
   * of interpolated points.
   *
   * @param points A vector of 2D points. For more information, see the
   * documentation for the PointsDec type.
   * @param N Number of interpolated points to generate. If N is less than the
   * size of input data, returns input data.
   * @return Vector of interpolated points. For more information, see the
   * documentation for the PointsDec type.
   */
  static PointsDec Solve(const PointsDec &points, unsigned int N);

  /**
   * @brief Static method to calculate the Y value corresponding to the given X
   * value using the cubic spline interpolation.
   *
   * @param points A vector of 2D points with arbitrary precision floating-point
   * coordinates.
   * @param time X value for which the Y value needs to be calculated.
   * @return Y value calculated using the cubic spline interpolation.
   * @throws std::out_of_range If the input X value is outside the range of the
   * input data.
   */
  static Real Calc(const PointsDec &points, Real time);

 private:
  Real PointCalc();
  const PointsDec &points_;
  unsigned size_;

  unsigned current_index_;
  Real time_;

  std::vector<Real> b_;
  std::vector<Real> c_;
  std::vector<Real> d_;
};

}  // namespace s21
