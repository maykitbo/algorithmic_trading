#pragma once

#include <algorithm>
#include <boost/multiprecision/cpp_dec_float.hpp>
#include <ctime>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

namespace s21 {

/**
 * @brief Typedef for double precision floating-point numbers.
 *
 * This typedef defines the alias 'fp_type' for double precision floating-point
 * numbers.
 */
typedef double fp_type;

/**
 * @brief Typedef for arbitrary precision floating-point numbers using
 * boost::multiprecision::cpp_dec_float_50.
 *
 * This typedef defines the alias 'Real' for arbitrary precision floating-point
 * numbers with 50 decimal digits of precision.
 */
typedef boost::multiprecision::cpp_dec_float_50 Real;

/**
 * @brief Typedef for a 2D point using double precision floating-point
 * coordinates.
 *
 * This typedef defines the alias 'Point' for a 2D point represented by a pair
 * of 'fp_type' values.
 */
typedef std::pair<fp_type, fp_type> Point;

/**
 * @brief Typedef for a 2D point using arbitrary precision floating-point
 * coordinates.
 *
 * This typedef defines the alias 'PointDec' for a 2D point represented by a
 * pair of 'Real' values.
 */
typedef std::pair<Real, Real> PointDec;

/**
 * @brief Typedef for a vector of 2D points using double precision
 * floating-point coordinates.
 *
 * This typedef defines the alias 'Points' for a vector of 2D points, where each
 * point is represented by a pair of 'fp_type' values.
 */
typedef std::vector<std::pair<fp_type, fp_type>> Points;

/**
 * @brief Typedef for a vector of 2D points using arbitrary precision
 * floating-point coordinates.
 *
 * This typedef defines the alias 'PointsDec' for a vector of 2D points, where
 * each point is represented by a pair of 'Real' values.
 */
typedef std::vector<std::pair<Real, Real>> PointsDec;

/**
 * @brief Typedef for a vector of double precision floating-point weights.
 *
 * This typedef defines the alias 'Weights' for a vector of 'fp_type' values
 * representing weights.
 */
typedef std::vector<fp_type> Weights;

/**
 * @brief Typedef for a pair of vectors consisting of 2D points and their
 * corresponding double precision floating-point weights.
 *
 * This typedef defines the alias 'PointsWeights' for a pair of 'Points' and
 * 'Weights', representing a collection of points along with their associated
 * weights.
 */
typedef std::pair<Points, Weights> PointsWeights;

/**
 * @brief Typedef for a vector of arbitrary precision floating-point weights.
 *
 * This typedef defines the alias 'WeightsDec' for a vector of 'Real' values
 * representing weights with arbitrary precision.
 */
typedef std::vector<Real> WeightsDec;

/**
 * @brief Typedef for a pair of vectors consisting of 2D points and their
 * corresponding arbitrary precision floating-point weights.
 *
 * This typedef defines the alias 'PointsWeightsDec' for a pair of 'PointsDec'
 * and 'WeightsDec', representing a collection of points along with their
 * associated weights with arbitrary precision.
 */
typedef std::pair<PointsDec, WeightsDec> PointsWeightsDec;

/**
 * @brief Utility struct for conversion operations between different data types.
 */
struct Convert {
  /**
   * @brief Converts a vector of 2D points with double precision coordinates to
   * arbitrary precision floating-point coordinates.
   *
   * @param points Vector of 2D points with double precision coordinates.
   * @return Vector of 2D points with arbitrary precision floating-point
   * coordinates.
   */
  static PointsDec ToDec(const Points &points);

  /**
   * @brief Converts a pair of vectors containing 2D points and double precision
   * weights to arbitrary precision coordinates and weights.
   *
   * @param points Pair of vectors containing 2D points and double precision
   * weights.
   * @return Pair of vectors containing 2D points with arbitrary precision
   * coordinates and weights.
   */
  static PointsWeightsDec ToDec(const PointsWeights &points);

  /**
   * @brief Converts a vector of double precision weights to arbitrary precision
   * floating-point weights.
   *
   * @param weights Vector of double precision weights.
   * @return Vector of arbitrary precision floating-point weights.
   */
  static WeightsDec ToDec(const Weights &weights);

  /**
   * @brief Converts a vector of 2D points with arbitrary precision coordinates
   * to double precision coordinates.
   *
   * @param points Vector of 2D points with arbitrary precision coordinates.
   * @return Vector of 2D points with double precision coordinates.
   */
  static Points ToDouble(const PointsDec &points);

  /**
   * @brief Converts a pair of vectors containing 2D points with arbitrary
   * precision coordinates and weights to double precision coordinates and
   * weights.
   *
   * @param points Pair of vectors containing 2D points with arbitrary precision
   * coordinates and weights.
   * @return Pair of vectors containing 2D points with double precision
   * coordinates and weights.
   */
  static PointsWeights ToDouble(const PointsWeightsDec &points);

  /**
   * @brief Converts a vector of arbitrary precision floating-point weights to
   * double precision weights.
   *
   * @param weights Vector of arbitrary precision floating-point weights.
   * @return Vector of double precision weights.
   */
  static Weights ToDouble(const WeightsDec &weights);

  /**
   * @brief Converts days to seconds using double precision floating-point
   * arithmetic.
   *
   * @param days Number of days.
   * @return Equivalent number of seconds in double precision floating-point
   * format.
   */
  static fp_type ToSeconds(fp_type days);

  /**
   * @brief Converts seconds to days using double precision floating-point
   * arithmetic.
   *
   * @param seconds Number of seconds.
   * @return Equivalent number of days in double precision floating-point
   * format.
   */
  static fp_type ToDays(fp_type seconds);
};

/**
 * @brief Utility struct for parsing operations on CSV files containing 2D
 * points and weights.
 */
struct ParserCsv {
  /**
   * @brief Parses a CSV file containing 2D points with double precision
   * coordinates. If file contains weights, they are ignored.
   *
   * @param filename Path to the CSV file.
   * @return Vector of 2D points with double precision coordinates.
   */
  static Points Parse(const std::string &filename);

  /**
   * @brief Parses a CSV file containing 2D points with double precision
   * coordinates and corresponding weights. If file does not contain weights,
   * they are set to 1.0.
   *
   * @param filename Path to the CSV file.
   * @return Pair of vectors containing 2D points and double precision weights.
   */
  static PointsWeights ParseWeights(const std::string &filename);

 private:
  static void ParseDC(Points &points, std::ifstream &file);
  static void ParseDCW(PointsWeights &points, std::ifstream &file);
};

};  // namespace s21
