#pragma once

#include "../../common/data_struct.h"

#include <limits>



namespace s21 {

class CubicSpline
{
    public:
        CubicSpline(const PointsDec &points);
        PointsDec Solve(unsigned int N);
        Real Calc(Real time);

        static PointsDec Solve(const PointsDec &points, unsigned int N)
        {
            CubicSpline cs(points);
            return cs.Solve(N);
        }
        static Real Calc(const PointsDec &points, Real time)
        {
            CubicSpline cs(points);
            return cs.Calc(time);
        }
    
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





} // namespace s21
