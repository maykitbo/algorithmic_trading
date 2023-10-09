#include "test.h"

INSTANTIATE_TEST_SUITE_P(
    InterpolationTest, FileTest,
    testing::Combine(testing::Values(
        // "AAPL.csv",
        // "ADBE.csv",
        // "CVX_original.csv",
        "CVX.csv"
        // "CVX2.csv",
        // "DPZ.csv",
        // "F.csv",
        // "a45.csv",
        // "a98.csv"
    )));


// TEST_P(FileTest, CubicSplineSolve)
// {
//     std::cout << ':' << std::get<0>(GetParam()) << ' '; 
//     CubicSplineSolve();
// }

// TEST_P(FileTest, CubicSplineCalc)
// {
//     std::cout << ':' << std::get<0>(GetParam()) << ' '; 
//     CubicSplineCalc();
// }

// TEST_P(FileTest, NewtonPolynomialSolve)
// {
//     std::cout << ':' << std::get<0>(GetParam()) << ' '; 
//     NewtonPolynomialSolve();
// }

// TEST_P(FileTest, NewtonPolynomialCalc)
// {
//     std::cout << ':' << std::get<0>(GetParam()) << ' '; 
//     NewtonPolynomialCalc();
// }

TEST_P(FileTest, LeastSquares)
{
    std::cout << ':' << std::get<0>(GetParam()) << ' '; 
    LeastSquares();
}
