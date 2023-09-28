#include "facade.h"

using namespace s21;

Facade::~Facade()
{
    RemoveInterpolation();
    RemoveApproximation();
}

void Facade::RemoveInterpolation()
{
    if (cubic_spline_ != nullptr)
        delete cubic_spline_;
    if (newton_polynomial_ != nullptr)
        delete newton_polynomial_;
}

void Facade::RemoveApproximation()
{
    if (least_squares_ != nullptr)
        delete least_squares_;
}

std::pair<bool, Points> Facade::InterpolationFile(const std::string &filename)
{
    try {
        Points data = ParserCsv::Parse(filename);
        RemoveInterpolation();
        interpolation_data_ = Convert::ToDec(data);
        cubic_spline_ = new CubicSpline(interpolation_data_);
        newton_polynomial_ = new NewtonPolynomial(interpolation_data_);
        return {true, std::move(data)};
    } catch (const std::exception &e) {
        std::cerr << e.what() << '\n';
        return {false, Points()};
    }
    return {false, Points()};
}

std::pair<double, double> Facade::InterpolationClac(double time, unsigned degree)
{
    return std::make_pair((double)cubic_spline_->Calc(time),
                        (double)newton_polynomial_->Calc(time, degree));
    
}

Points Facade::CubicSplineData(int points)
{
    return Convert::ToDouble(cubic_spline_->Solve(points));
    
}

Points Facade::NewtonPolynomialData(int points, unsigned degree)
{
    return Convert::ToDouble(newton_polynomial_->Solve(points, degree));
}

void Facade::InterpolationClear()
{
    interpolation_data_.clear();
}


std::pair<bool, Points> Facade::ApproximationFile(const std::string &filename)
{
    try {
        Points data = ParserCsv::Parse(filename);
        RemoveApproximation();
        approximation_data_ = Convert::ToDec(data);
        least_squares_ = new LeastSquares(approximation_data_);
        return {true, std::move(data)};
    } catch (const std::exception &e) {
        std::cout << e.what() << '\n';
        return {false, Points()};
    }
    return {false, Points()};
}

Points Facade::LeastSquaresData(unsigned points, unsigned degree)
{
    return Convert::ToDouble(least_squares_->Solve(points, degree));
}

void Facade::ApproximationClear()
{
    approximation_data_.clear();
}
