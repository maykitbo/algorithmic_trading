#include <gtest/gtest.h>
#include <math.h>

#include "../../algorithms/cubic_spline/cubic_spline.h"
#include "../../algorithms/least_squares/least_squares.h"
#include "../../algorithms/newton_polynomial/newton_polynomial.h"
#include "../../common/data_struct.h"
#include "../../utility/m_random.h"

class FileTest : public testing::TestWithParam<std::tuple<std::string>> {
 protected:
  s21::PointsWeightsDec points_w_;
  const s21::PointsDec &points_;

 public:
  FileTest()
      : points_w_(s21::Convert::ToDec(s21::ParserCsv::ParseWeights(
            std::string("materials/") + std::get<0>(GetParam())))),
        points_(points_w_.first) {}

 protected:
  void ExpectedNumber(s21::Real x);
  void ValidatePoints(const s21::PointsDec &result, unsigned g);

  void CubicSplineSolve();
  void CubicSplineCalc();

  void NewtonPolynomialSolve();
  void NewtonPolynomialCalc();

  void LeastSquares();
};
