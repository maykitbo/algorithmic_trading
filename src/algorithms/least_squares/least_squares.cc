#include "least_squares.h"

using namespace s21;

LeastSquares::LeastSquares(const PointsDec &points)
    : points_(points)
    , degree_(0)
    , weights_(points_.size())
    {}

void LeastSquares::MulXTW2X(const matrix &X, matrix &A)
{
    const Real *x = X.Data();
    Real *a = A.Data();
    unsigned K = X.GetRows();
    for (unsigned i = 0; i < degree_; ++i)
    {
        for (unsigned j = 0; j < degree_; ++j)
        {
            Real sum = 0.0;
            for (unsigned k = 0; k < K; ++k)
            {
                sum += x[k * degree_ + i] * x[k * degree_ + j] * weights_[k];
            }
            a[i * degree_ + j] = sum;
        }
    }
}

void LeastSquares::MulCW2Y(const matrix &C)
{
    const Real *c = C.Data();
    Real *coef = coef_.data();
    auto y = points_.data();
    unsigned K = C.GetCols();
    for (unsigned i = 0; i < degree_; ++i)
    {
        Real sum = 0.0;
        for (unsigned k = 0; k < K; ++k)
        {
            sum += c[i * K + k] * y[k].second * weights_[k];
        }
        coef[i] = sum;
    }
}

bool LeastSquares::CreatePolynomial(unsigned degree, const WeightsDec &weights)
{
    if (degree_ == degree + 1 && weights_ == weights) {
        return true;
    }
    degree_ = degree + 1;
    if (degree_ >= points_.size() - 1 || degree_ < 2) {
        std::cerr << "Invalid degree: " << degree_ << '\n';
        return false;
    }

    unsigned n = points_.size();

    std::transform(weights.begin(), weights.end(), weights_.begin(),
        [](Real x) { return x * x; });

    coef_.resize(degree_, 0.0);
    matrix X(n, degree_, [&] (auto i, auto j)
        { return boost::multiprecision::pow(points_[i].first, j); });

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

PointsDec LeastSquares::Solve(unsigned points_count, unsigned degree, const WeightsDec &weights)
{
    if (points_count < 0 || !CreatePolynomial(degree, weights)) {
        return points_;
    }

    unsigned n = (int)points_.back().first - (int)points_.front().first + points_count;

    PointsDec interpolated(n);

    Real x = points_.front().first;

    for (int i = 0; i < n; ++i, x += 1.0) {
        Real y = coef_[0];

        for (int j = 1; j < degree_; ++j) {
            y += coef_[j] * boost::multiprecision::pow(x, j);
        }

        interpolated[i] = {x, y};
    }
    return interpolated;
}

PointsDec LeastSquares::Solve(const PointsDec &points, unsigned degree,
                unsigned points_count, const WeightsDec &weights)
{
    LeastSquares a(points);
    return a.Solve(points_count, degree, weights);
}
