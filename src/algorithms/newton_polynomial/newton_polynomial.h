#pragma once

#include "../../common/data_struct.h"


namespace s21 {

class NewtonPolynomial {
    public:
        NewtonPolynomial(const PointsDec &points);
        PointsDec Solve(unsigned N, unsigned degree);
        Real Calc(Real time, unsigned degree);


        static PointsDec Solve(const PointsDec &points, unsigned degree, unsigned N)
        {
            NewtonPolynomial np(points);
            return np.Solve(N, degree);
        }
        static Real Calc(const PointsDec &points, unsigned degree, Real time)
        {
            NewtonPolynomial np(points);
            return np.Calc(time, degree);
        }

    private:

        const PointsDec &points_;
        std::vector<std::vector<Real>> coef_;
        unsigned size_;
        unsigned degree_;

        Real Interpolate(Real x_interpolated, unsigned k);
        bool CreatePolynomial(unsigned degree);
};



} // namespace s21