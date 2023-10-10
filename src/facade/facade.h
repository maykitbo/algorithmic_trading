#pragma once

#include "data_struct.h"
#include "cubic_spline/cubic_spline.h"
#include "newton_polynomial/newton_polynomial.h"
#include "least_squares/least_squares.h"
#include "interpolation_time/compare.h"

namespace s21 {


class Facade {
    public:
        ~Facade();
        std::pair<bool, Points> InterpolationFile(const std::string &filename);
        Points CubicSplineData(int points);
        Points NewtonPolynomialData(int points, unsigned degree);
        void InterpolationClear();
        std::pair<double, double> InterpolationClac(double time, unsigned degree);

        std::pair<bool, PointsWeights> ApproximationFile(const std::string &filename);
        Points LeastSquaresData(unsigned points, unsigned degree, const Weights &weights);
        Points LeastSquaresData(unsigned points, unsigned degree);
        void ApproximationClear();

        int TimeTestFile(const std::string &filename);
        void TimeCompare(
                bool cubic_spline,
                const std::vector<unsigned> &newtons_degree,
                unsigned points_count,
                unsigned partitions,
                const InterpolationTime::result_proc &func);

        void TimeTestClear();
    
    private:
        PointsDec interpolation_data_;
        PointsWeightsDec approximation_data_;
        PointsDec time_test_data_;

        void RemoveInterpolation();
        void RemoveApproximation();

        NewtonPolynomial *newton_polynomial_{nullptr};
        CubicSpline *cubic_spline_{nullptr};
        LeastSquares *least_squares_{nullptr};
};





} // namespace s21
