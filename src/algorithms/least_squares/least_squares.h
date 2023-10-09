#pragma once

#include "../../common/data_struct.h"
#include "../matrix/matrix.h"
#include <math.h>
#include <algorithm>

#include <boost/multiprecision/cpp_dec_float.hpp>

namespace s21 {


class LeastSquares
{
    public:
        LeastSquares(const PointsDec &points);
        PointsDec Solve(unsigned points, unsigned degree, const WeightsDec &weights);

        static PointsDec Solve(const PointsDec &points, unsigned degree,
                unsigned points_count, const WeightsDec &weights)
        {
            LeastSquares a(points);
            return a.Solve(points_count, degree, weights);
        }
    
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

















} // namespace s21
