#pragma once

#include "data_struct.h"
#include "cubic_spline/cubic_spline.h"
#include "newton_polynomial/newton_polynomial.h"
#include "least_squares/least_squares.h"
#include "interpolation_time/compare.h"

namespace s21 {

/**
 * @brief Facade class providing a simplified interface for interpolation, approximation, and performance testing operations.
 * 
 * The Facade class encapsulates the functionality of interpolation, approximation, and performance time testing operations.
 */
class Facade {
public:
    /**
     * @brief Destructor for the Facade class.
     */
    ~Facade();

    /**
     * @brief Load data to be used for interpolation from a file.
     * 
     * @param filename Path to the file containing 2D points for interpolation.
     * @return A pair indicating the success status and the loaded Points.
     * See the documentation for ParserCsv for more information.
     */
    std::pair<bool, Points> InterpolationFile(const std::string &filename);

    /**
     * @brief Generates interpolated points using Cubic Spline interpolation.
     * 
     * @param points Number of interpolated points to generate.
     * @return Interpolated Points using Cubic Spline method.
     * See the documentation for CubicSpline for more information.
     */
    Points CubicSplineData(int points);

    /**
     * @brief Generates interpolated points using Newton's Polynomial interpolation.
     * 
     * @param points Number of interpolated points to generate.
     * @param degree Degree of the polynomial used for interpolation.
     * @return Interpolated Points using Newton's Polynomial method.
     * See the documentation for NewtonPolynomial for more information.
     */
    Points NewtonPolynomialData(int points, unsigned degree);

    /**
     * @brief Clears the internal data used for interpolation.
     */
    void InterpolationClear();

    /**
     * @brief Calculates interpolated Y value for the given X value using the specified interpolation degree.
     * 
     * @param time X value for which the Y value needs to be calculated.
     * @param degree Degree of the interpolation method used.
     * @return A pair representing the interpolated X and Y values.
     */
    std::pair<double, double> InterpolationClac(double time, unsigned degree);

    /**
     * @brief Load data to be used for approximation from a file.
     * 
     * @param filename Path to the file containing 2D points and weights for approximation.
     * @return A pair indicating the success status and the loaded PointsWeights.
     * See the documentation for ParserCsv for more information.
     */
    std::pair<bool, PointsWeights> ApproximationFile(const std::string &filename);

    /**
     * @brief Generates approximated points using Least Squares method with specified points and degree and weights.
     * 
     * @param points Number of points to be approximated.
     * @param degree Degree of the polynomial used for approximation.
     * @param weights Vector of double precision weights corresponding to input points.
     * @return Approximated Points using Least Squares method.
     * See the documentation for LeastSquares for more information.
     */
    Points LeastSquaresData(unsigned points, unsigned degree, const Weights &weights);

    /**
     * @brief Generates approximated points using Least Squares method with specified points and degree.
     * 
     * @param points Number of points to be approximated.
     * @param degree Degree of the polynomial used for approximation.
     * @return Approximated Points using Least Squares method.
     * See the documentation for LeastSquares for more information.
     */
    Points LeastSquaresData(unsigned points, unsigned degree);

    /**
     * @brief Clears the internal data used for approximation.
     */
    void ApproximationClear();

    /**
     * @brief Performs performance testing for interpolation methods and compares their execution times.
     * 
     * @param cubic_spline Flag indicating whether to include Cubic Spline interpolation in the comparison.
     * @param newtons_degree Vector of unsigned integers representing the degrees of Newton's Polynomial for comparison.
     * @param points_count Total number of points in the output sequence (including input points and interpolated points).
     * @param partitions Number of times the comparison is performed.
     * @param func Callback function that receives the comparison results.
     * See the documentation for InterpolationTime for more information.
     */
    void TimeCompare(
        bool cubic_spline,
        const std::vector<unsigned> &newtons_degree,
        unsigned points_count,
        unsigned partitions,
        const InterpolationTime::result_proc &func);

    /**
     * @brief Loads data to be used for performance testing from a file.
     * 
     * @param filename Path to the file containing 2D points for performance testing.
     * @return Size of the loaded data.
     */
    int TimeTestFile(const std::string &filename);

    /**
     * @brief Clears the internal data used for performance testing.
     */
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
