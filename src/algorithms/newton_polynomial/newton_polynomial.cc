#include "newton_polynomial.h"

#include "../../utility/utility.h"

#include <math.h>

using namespace s21;

NewtonPolynomial::NewtonPolynomial(const PointsDec &points)
    : points_(points)
    , size_(points_.size())
    , degree_(0)
{
    if (size_ < 2)
    {
        std::cerr << "NewtonPolynomial: size of points must be greater than 1\n";
    }
}

bool NewtonPolynomial::CreatePolynomial(unsigned degree)
{
    if (degree_ == degree)
    {
        return true;
    }
    degree_ = degree;
    if (degree_ >= size_ - 1 || degree_ < 2)
    {
        std::cerr << "Invalid degree\n";
        return false;
    }
    coef_.resize(size_ - degree_ + 1, std::vector<Real>(degree_, 0.0));
    for (int k = 1; k < degree_; ++k)
    {
        coef_.push_back(std::vector<Real>(degree_ - k));
    }
    std::vector<std::vector<Real>> divided_differences_(degree_, std::vector<Real>(degree_));
    for (int k = 0; k < size_; ++k)
    {
        unsigned m = coef_[k].size();
        for (unsigned i = 0; i < m; ++i)
        {
            divided_differences_[i][0] = points_[i + k].second;
        }
        coef_[k][0] = divided_differences_[0][0];
        for (unsigned j = 1; j < m; ++j)
        {
            for (unsigned i = 0; i < m - j; ++i)
            {
                divided_differences_[i][j] = (divided_differences_[i + 1][j - 1] -
                    divided_differences_[i][j - 1]) / (points_[i + j + k].first - points_[i + k].first);

            }
            coef_[k][j] = divided_differences_[0][j];
        }
    }
    return true;
}

Real NewtonPolynomial::Interpolate(Real x_interpolated, unsigned k)
{
    unsigned n = coef_[k].size() - 1;
    auto &coef = coef_[k];
    Real result = coef[n];
    for (unsigned i = 1; i <= n; ++i)
    {
        result = (result * (x_interpolated - points_[n - i + k].first)) + coef[n - i];
    }
    return result;
}


PointsDec NewtonPolynomial::Solve(unsigned N, unsigned degree)
{
    if (N <= size_ || size_ < 2 || !CreatePolynomial(degree))
    {
        return points_;
    }
    PointsDec result;
    result.reserve(N);

    Real x_interpolated = points_[0].first;
    Real step = (points_.back().first - points_.front().first) / (Real)(N - 1);

    unsigned d = 0;

    for (unsigned k = 0; k < N; ++k, x_interpolated += step) {
        Real y_interpolated = Interpolate(x_interpolated, d);
        result.push_back({x_interpolated, y_interpolated});

        if (x_interpolated > points_[d + degree_ / 2].first)
        {
            ++d;
        }
    }
    return result;
}

Real NewtonPolynomial::Calc(Real time, unsigned degree)
{
    if (time < points_.front().first || time > points_.back().first || !CreatePolynomial(degree))
    {
        return std::numeric_limits<Real>::quiet_NaN();
    }
    unsigned d = 0;
    for (unsigned i = 0; i < size_ - 1; ++i)
    {
        if (time >= points_[i].first)
        {
            return Interpolate(time, d);
        }
        if (i > d + degree_ / 2)
        {
            ++d;
        }
    }
    return std::numeric_limits<Real>::quiet_NaN();
}
