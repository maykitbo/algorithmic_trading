#include "least_squares.h"

using namespace s21;

LeastSquares::LeastSquares(const PointsDec &points)
    : points_(points)
    , degree_(0)
    {}

bool LeastSquares::CreatePolynomial(unsigned degree)
{
    if (degree_ == degree + 1) {
        return true;
    }
    degree_ = degree + 1;
    if (degree_ >= points_.size() - 1 || degree_ < 2) {
        // throw std::runtime_error("Invalid degree");
        std::cerr << "Invalid degree\n";
        return false;
    }

    // Calculate the coefficients of the polynomial using the least squares method
    unsigned n = points_.size();

    coef_ = matrix(degree_, 1, 0.0);
    matrix X(n, degree_, [&] (auto i, auto j) { return boost::multiprecision::pow(points_[i].first, j); });
    matrix Y(n, 1, [&] (auto i, auto j) { return points_[i].second; });
    // coef_ = (X^t * X)^-1 * X^t * Y
    // A = X^t * X
    matrix A(degree_, degree_);
    matrix::MulATB(X, X, A);
    // B = A^-1
    matrix B(degree_, degree_);
    matrix::Inverse(A, B);
    // C = B * X^t
    matrix C(degree_, n);
    matrix::MulABT(B, X, C);
    // coef_ = C * Y
    matrix::Mul(C, Y, coef_);

    // std::cout << coef_ << '\n';

    // std::cout << "M:\n" << M << '\n';
    // std::cout << "Y:\n" << Y << '\n';
    return true;
}

PointsDec LeastSquares::Solve(unsigned points_count, unsigned degree)
{
    if (points_count == 0 || !CreatePolynomial(degree)) {
        return points_;
    }

    unsigned n = (int)points_.back().first - (int)points_.front().first + points_count;

    // Points interpolated_points(n);
    PointsDec interpolated(n);
    // interpolated_points.reserve(n);

    Real x = points_.front().first;
    // PointDec p;

    for (int i = 0; i < n; ++i, x += 1.0) {
        Real y = coef_(0, 0);

        for (int j = 1; j < degree_; ++j) {
            // y += coef_(j, 0) * std::pow(x, j);
            y += coef_(j, 0) * boost::multiprecision::pow(x, j);
        }

        interpolated[i] = {x, y};
        // interpolated_points.emplace_back(x, y);
    }

    // return interpolated;
    return interpolated;
}
