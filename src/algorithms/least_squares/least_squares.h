#pragma once

#include "../../common/data_struct.h"
#include "../matrix/matrix.h"
#include <math.h>

#include <boost/multiprecision/cpp_dec_float.hpp>

namespace s21 {


class LeastSquares
{
    public:
        LeastSquares(const PointsWeightsDec &points);
        PointsDec Solve(unsigned points, unsigned degree);

        static PointsDec Solve(const PointsWeightsDec &points, unsigned degree, unsigned points_count)
        {
            LeastSquares a(points);
            return a.Solve(points_count, degree);
        }
    
    private:

        using matrix = Matrix<Real>;
        const PointsWeightsDec &points_;
        unsigned degree_;
        // matrix coef_;
        std::vector<Real> coef_;

        bool CreatePolynomial(unsigned degree);

        void MulXTW2X(const matrix &X, matrix &A);
        void MulCW2Y(const matrix &C);
};

















} // namespace s21
