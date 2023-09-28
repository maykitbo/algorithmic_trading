#pragma once

#include "../../common/data_struct.h"
#include "../matrix/matrix.h"
#include <math.h>

#include <boost/multiprecision/cpp_dec_float.hpp>

namespace s21 {


class LeastSquares
{
    public:
        LeastSquares(const PointsDec &points);
        PointsDec Solve(unsigned points, unsigned degree);

        static PointsDec Solve(const PointsDec &points, unsigned degree, unsigned points_count)
        {
            LeastSquares a(points);
            return a.Solve(points_count, degree);
        }
    
    private:

        using matrix = Matrix<Real>;
        const PointsDec &points_;
        unsigned degree_;
        matrix coef_;

        bool CreatePolynomial(unsigned degree);
};

















} // namespace s21
