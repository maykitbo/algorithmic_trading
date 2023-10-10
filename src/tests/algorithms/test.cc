#include "test.h"

using namespace s21;

////////// SUB

void FileTest::ExpectedNumber(Real x) {
  EXPECT_FALSE(std::isnan(static_cast<fp_type>(x)));
  EXPECT_FALSE(std::isinf(static_cast<fp_type>(x)));
}

void FileTest::ValidatePoints(const PointsDec &result, unsigned g) {
  EXPECT_EQ(result.size(), std::max<size_t>(g, points_.size()));
  EXPECT_EQ(result.front().first, points_.front().first);
  for (unsigned i = 0; i < result.size() - 1; ++i) {
    EXPECT_LE(result[i].first, result[i + 1].first);
    ExpectedNumber(result[i].second);
  }
  ExpectedNumber(result.back().second);
}

////////// CUBIC SPLINE

void FileTest::CubicSplineSolve() {
  for (int g = 0; g < points_.size(); ++g) {
    unsigned N = Random::Int<unsigned>(0, points_.size() * 4);
    PointsDec result = CubicSpline::Solve(points_, N);
    ValidatePoints(result, N);
  }
}

void FileTest::CubicSplineCalc() {
  int max = Random::Int(70, 130);
  Real step =
      (points_.back().first - points_.front().first) / static_cast<Real>(max);
  Real time = points_.front().first;
  for (int k = 0; k < max; ++k, time += step) {
    ExpectedNumber(CubicSpline::Calc(points_, time));
  }
  EXPECT_TRUE(std::isnan(static_cast<fp_type>(
      CubicSpline::Calc(points_, points_.back().first + 1.0))));
  EXPECT_TRUE(std::isnan(static_cast<fp_type>(
      CubicSpline::Calc(points_, points_.front().first - 1.0))));
}

////////// NEWTON POLYNOMIAL

void FileTest::NewtonPolynomialSolve() {
  for (int g = 0; g < points_.size() / 2; ++g) {
    unsigned N = Random::Int<unsigned>(0, points_.size() * 4);
    for (int k = 0; k < 3; ++k) {
      unsigned degree =
          Random::Int<unsigned>(2, std::min<unsigned>(points_.size() - 2, 16));
      PointsDec result = NewtonPolynomial::Solve(points_, degree, N);
      ValidatePoints(result, N);
    }
  }
}

void FileTest::NewtonPolynomialCalc() {
  int max = Random::Int(70, 130);
  Real step =
      (points_.back().first - points_.front().first) / static_cast<Real>(max);
  Real time = points_.front().first;
  for (int k = 0; k < max; ++k, time += step) {
    for (int g = 0; g < 3; ++g) {
      unsigned degree =
          Random::Int<unsigned>(2, std::min<unsigned>(points_.size() - 2, 16));
      ExpectedNumber(NewtonPolynomial::Calc(points_, degree, time));
    }
  }
  EXPECT_TRUE(std::isnan(static_cast<fp_type>(
      NewtonPolynomial::Calc(points_, 2, points_.back().first + 1.0))));
  EXPECT_TRUE(std::isnan(static_cast<fp_type>(
      NewtonPolynomial::Calc(points_, 2, points_.front().first - 1.0))));
}

////////// LEAST SQUARES

void FileTest::LeastSquares() {
  for (int N = 0; N < points_.size(); ++N) {
    for (int degree = 1; degree < 6; ++degree) {
      PointsDec result =
          LeastSquares::Solve(points_, degree, N, points_w_.second);
      for (unsigned i = 0; i < result.size() - 1; ++i) {
        ExpectedNumber(result[i].second);
        EXPECT_EQ(result[i + 1].first - result[i].first, 1);
      }
      ExpectedNumber(result.back().second);
      EXPECT_EQ(result.front().first, points_.front().first);
    }
  }
}
