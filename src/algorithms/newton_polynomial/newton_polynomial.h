#pragma once

#include "../../common/data_struct.h"


namespace s21 {

/**
 * @brief Class for performing interpolation using Newton's Polynomial method.
 * 
 * This class provides methods to create a Newton polynomial interpolation from a set of 2D points.
 */
class NewtonPolynomial {
    public:
        /**
         * @brief Constructs a NewtonPolynomial object from a set of 2D points.
         * 
         * @param points A vector of 2D points. For more information, see the documentation for the PointsDec type.
         */
        NewtonPolynomial(const PointsDec &points);

        /**
         * @brief Solves the interpolation problem and returns a vector of interpolated points using Newton's Polynomial method.
         * 
         * @param N Number of interpolated points to generate. If N is less than the size of input data, returns input data.
         * @param degree Degree of the polynomial used for interpolation.
         * @return Vector of interpolated points. For more information, see the documentation for the PointsDec type.
         */
        PointsDec Solve(unsigned N, unsigned degree);

        /**
         * @brief Calculates the Y value corresponding to the given X value using the Newton polynomial interpolation.
         * 
         * @param time X value for which the Y value needs to be calculated.
         * @param degree Degree of the polynomial used for interpolation.
         * @return Y value calculated using the Newton polynomial interpolation.
         */
        Real Calc(Real time, unsigned degree);

        /**
         * @brief Static method to solve the interpolation problem and return a vector of interpolated points using Newton's Polynomial method.
         * 
         * See the documentation for the Solve method for more information.
         */
        static PointsDec Solve(const PointsDec &points, unsigned degree, unsigned N);

        /**
         * @brief Static method to calculate the Y value corresponding to the given X value using the Newton polynomial interpolation.
         * 
         * See the documentation for the Calc method for more information.
         */
        static Real Calc(const PointsDec &points, unsigned degree, Real time);

    private:

        const PointsDec &points_;
        std::vector<std::vector<Real>> coef_;
        unsigned size_;
        unsigned degree_;

        Real Interpolate(Real x_interpolated, unsigned k);
        bool CreatePolynomial(unsigned degree);
};



} // namespace s21