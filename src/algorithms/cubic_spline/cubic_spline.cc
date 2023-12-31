#include "cubic_spline.h"

using namespace s21;

CubicSpline::CubicSpline(const PointsDec &points)
        : points_(points)
        , size_(points.size())
        , b_(size_, 0.0)
        , c_(size_, 0.0)
        , d_(size_, 0.0)
{
    if (size_ < 3) {
        std::cerr << "Invalid points count\n";
        return;
    }
    int N = size_ - 1;

    std::vector<Real> h(N, 0.0);
    std::vector<Real> alpha(N, 0.0);
    std::vector<Real> lambda(size_, 0.0);
    std::vector<Real> mu(size_, 0.0);
    std::vector<Real> z(size_, 0.0);

    for (int i = 0; i < N; ++i) {
        h[i] = points_[i + 1].first - points_[i].first;
    }
    for (int i = 1; i < N; ++i) {
        alpha[i] = 3.0 * (points_[i + 1].second - points_[i].second) / h[i] -
               3.0 * (points_[i].second - points_[i - 1].second) / h[i - 1];
    }
    lambda[0] = 1.0;
    for (int i = 1; i < N; ++i) {
        lambda[i] = 2.0 * (points_[i + 1].first - points_[i - 1].first) - h[i - 1] * mu[i - 1];
        mu[i] = h[i] / lambda[i];
        z[i] = (alpha[i] - h[i - 1] * z[i - 1]) / lambda[i];
    }
    lambda[N] = 1.0;
    for (int i = N - 1; i >= 0; --i) {
        c_[i] = z[i] - mu[i] * c_[i + 1];
        b_[i] = (points_[i + 1].second - points_[i].second) / h[i] -
               h[i] * (c_[i + 1] + 2.0 * c_[i]) / 3.0;
        d_[i] = (c_[i + 1] - c_[i]) / (3.0 * h[i]);
    }
}

PointsDec CubicSpline::Solve(unsigned N)
{
    if (N <= size_ || size_ < 2)
    {
        return points_;
    }
    PointsDec spline_points(N);

    Real x = points_[0].first;
    Real k = (Real)(size_ - 1) / (Real)(N - 1);
    Real step = (points_.back().first - points_.front().first) / (Real)(N - 1);
    for (unsigned i = 0; i < N; ++i, x += step)
    {
        Real x_i = (Real)i * k;
        int j = (int)x_i;
        Real dx = x_i - j;
        
        Real y_i = points_[j].second + b_[j] * dx + c_[j] * dx * dx + d_[j] * dx * dx * dx;
        spline_points[i] = {x, y_i};
    }

    return spline_points;
}

Real CubicSpline::Calc(Real time)
{
    if (time < points_.front().first || time > points_.back().first)
    {
        return std::numeric_limits<Real>::quiet_NaN();
    }

    Real x_i = (time - points_.front().first) * (Real)(size_ - 1) / (points_.back().first - points_.front().first);
    int j = (int)x_i;
    Real dx = x_i - j;
    Real y_i = points_[j].second + b_[j] * dx + c_[j] * dx * dx + d_[j] * dx * dx * dx;
    return y_i;

}

PointsDec CubicSpline::Solve(const PointsDec &points, unsigned int N)
{
    CubicSpline cs(points);
    return cs.Solve(N);
}

Real CubicSpline::Calc(const PointsDec &points, Real time)
{
    CubicSpline cs(points);
    return cs.Calc(time);
}
