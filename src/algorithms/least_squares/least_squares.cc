#include "least_squares.h"

using namespace s21;

LeastSquares::LeastSquares(const PointsWeightsDec &points)
    : points_(points)
    , degree_(0)
    {}

void LeastSquares::MulXTW2X(const matrix &X, matrix &A)
{
    const Real *x = X.Data();
    Real *a = A.Data();
    const Real *w = points_.second.data();
    unsigned I = X.GetCols();
    unsigned J = X.GetCols();
    unsigned K = X.GetRows();
    for (unsigned i = 0; i < I; ++i)
    {
        for (unsigned j = 0; j < J; ++j)
        {
            Real sum = 0.0;
            for (unsigned k = 0; k < K; ++k)
            {
                sum += x[k * I + i] * x[k * J + j] * w[k] * w[k];
                // sum += x[i * K + k] * x[k * K + j] * w[k] * w[k];
            }
            a[i * J + j] = sum;
        }
    }
}

void LeastSquares::MulCW2Y(const matrix &C)
{
    const Real *c = C.Data();
    Real *coef = coef_.data();
    const Real *w = points_.second.data();
    auto y = points_.first.data();
    unsigned I = C.GetRows();
    unsigned K = C.GetCols();
    for (unsigned i = 0; i < I; ++i)
    {
        Real sum = 0.0;
        for (unsigned k = 0; k < K; ++k)
        {
            sum += c[i * K + k] * y[k].second * w[k] * w[k];
        }
        coef[i] = sum;
    }
}

bool LeastSquares::CreatePolynomial(unsigned degree)
{
    if (degree_ == degree + 1) {
        return true;
    }
    degree_ = degree + 1;
    if (degree_ >= points_.first.size() - 1 || degree_ < 2) {
        std::cerr << "Invalid degree: " << degree_ << '\n';
        return false;
    }
    unsigned n = points_.first.size();

    coef_.resize(degree_, 0.0);
    matrix X(n, degree_, [&] (auto i, auto j)
        { return boost::multiprecision::pow(points_.first[i].first, j); });

    // coef_ = (X^t * W^2 * X)^-1 * X^t * W^2 * Y
    // A = X^t * W^2 * X
    matrix A(degree_, degree_);
    MulXTW2X(X, A);
    // B = A^-1
    matrix B(degree_, degree_, 0.0);
    matrix::Inverse(A, B);
    // C = B * X^t
    matrix C(degree_, n, 0.0);
    matrix::MulABT(B, X, C);
    // coef_ = C * W^2 * Y
    MulCW2Y(C);

    return true;
}

PointsDec LeastSquares::Solve(unsigned points_count, unsigned degree)
{
    if (points_count < 0 || !CreatePolynomial(degree)) {
        return points_.first;
    }

    unsigned n = (int)points_.first.back().first - (int)points_.first.front().first + points_count;

    PointsDec interpolated(n);

    Real x = points_.first.front().first;

    for (int i = 0; i < n; ++i, x += 1.0) {
        Real y = coef_[0];

        for (int j = 1; j < degree_; ++j) {
            y += coef_[j] * boost::multiprecision::pow(x, j);
        }

        interpolated[i] = {x, y};
    }
    return interpolated;
}
