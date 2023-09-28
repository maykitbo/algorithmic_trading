#include "../algorithms/interpolation/newton_polynomial.h"
#include "../algorithms/interpolation/cubic_spline.h"

#include <gtest/gtest.h>
#include <math.h>

using namespace s21;

#define __EXPECT_SORTED(points) \
    for (unsigned i = 0; i < points.size() - 1; ++i) \
    { \
        EXPECT_LE(points[i].x, points[i + 1].x); \
    }

#define __EXPECT_NUMBER(x) \
    EXPECT_FALSE(std::isnan(x)); \
    EXPECT_FALSE(std::isinf(x));

#define __NAN_INF_NOT_EXIST(points) \
    for (unsigned i = 0; i < points.size(); ++i) \
    { \
        __EXPECT_NUMBER(points[i].x); \
        __EXPECT_NUMBER(points[i].y); \
    }

void CubicSplineSolve(const Points &points)
{
    for (int g = 0; g < points.size() * 4; ++g)
    {
        Points result = CubicSpline::Solve(points, g);
        EXPECT_EQ(result.size(), g < points.size() ? points.size() : g);
        __EXPECT_SORTED(result);
        EXPECT_EQ(result.front().x, points.front().x);
        __NAN_INF_NOT_EXIST(result);
    }
}

void CubicSplineCalc(const Points &points)
{
    fp_type step = (points.back().x - points.front().x) / 87.0;
    fp_type time = points.front().x;
    for (int k = 0; k < 87; ++k, time += step)
    {
        __EXPECT_NUMBER(CubicSpline::Calc(points, time));
    }
}

void NewtonPolynomialSolve(const Points &points)
{
    for (int g = 0; g < points.size() * 4; ++g)
    {
        for (int k = 2; k <= 16; ++k)
        {
            Points result = NewtonPolynomial::Solve(points, k, g);
            EXPECT_EQ(result.size(), g < points.size() ? points.size() : g);
            __EXPECT_SORTED(result);
            EXPECT_EQ(result.front().x, points.front().x);
            __NAN_INF_NOT_EXIST(result);
        }
    }
}

void NewtonPolynomialCalc(const Points &points)
{
    for (int g = 2; g <= 16; ++g)
    {
        fp_type step = (points.back().x - points.front().x) / 87.0;
        fp_type time = points.front().x;
        for (int l = 0; l < 87; ++l, time += step)
        {
            __EXPECT_NUMBER(NewtonPolynomial::Calc(points, g, time));
        }
    }
}

std::vector<Points> __data__{{{0.0, 0.0}, {1.0, 1.0}, {2.0, 0.0}},
                            ParserCsv::Parse("materials/AAPL.csv"),
                            ParserCsv::Parse("materials/ADBE.csv"),
                            ParserCsv::Parse("materials/CVX.csv"),
                            ParserCsv::Parse("materials/DPZ.csv"),};


#define __ONE_TEST_PACK(n) \
    TEST(Interpolation, cubic_spline_solve_##n) \
    { \
        CubicSplineSolve(__data__[n]); \
    } \
    TEST(Interpolation, cubic_spline_calc_##n) \
    { \
        CubicSplineCalc(__data__[n]); \
    } \
    TEST(Interpolation, newton_polynomial_solve_##n) \
    { \
        NewtonPolynomialSolve(__data__[n]); \
    } \
    TEST(Interpolation, newton_polynomial_calc_##n) \
    { \
        NewtonPolynomialCalc(__data__[n]); \
    }

__ONE_TEST_PACK(0)
__ONE_TEST_PACK(1)
__ONE_TEST_PACK(2)
__ONE_TEST_PACK(3)
__ONE_TEST_PACK(4)
