#pragma once

#include "data_struct.h"
#include "cubic_spline/cubic_spline.h"
#include "newton_polynomial/newton_polynomial.h"
#include "least_squares/least_squares.h"

namespace s21 {


class Facade {
    public:
        ~Facade();
        std::pair<bool, Points> InterpolationFile(const std::string &filename);
        // Points &InterpolationRawData();
        Points CubicSplineData(int points);
        Points NewtonPolynomialData(int points, unsigned degree);
        void InterpolationClear();
        std::pair<double, double> InterpolationClac(double time, unsigned degree);

        std::pair<bool, Points> ApproximationFile(const std::string &filename);
        // Points &ApproximationRawData();
        Points LeastSquaresData(unsigned points, unsigned degree);
        void ApproximationClear();
    
    private:
        PointsDec interpolation_data_;
        PointsWeightsDec approximation_data_;

        void RemoveInterpolation();
        void RemoveApproximation();

        NewtonPolynomial *newton_polynomial_{nullptr};
        CubicSpline *cubic_spline_{nullptr};
        LeastSquares *least_squares_{nullptr};
};





} // namespace s21
