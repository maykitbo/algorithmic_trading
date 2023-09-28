#include "matrix.h"
// #include "blas.h"
#include <gtest/gtest.h>
// #include "../utility/m_random.h"

using namespace s21;

// TEST(Matrix, Constructor) {
//   Matrix<int> m(2, 3);
//   EXPECT_EQ(2, m.GetRows());
//   EXPECT_EQ(3, m.GetCols());
// }

// TEST(Matrix, Geters) {
//     Matrix<int> m(300, 100, [] { return Random::Int(0, 100); });
//     EXPECT_EQ(300, m.GetRows());
//     EXPECT_EQ(100, m.GetCols());
//     for (int k = 0; k < 100; ++k) {
//         int r = Random::Int(0, 300);
//         int c = Random::Int(0, 100);
//         EXPECT_EQ(m(r, c), m[r][c]);
//     }
// }

TEST(Matrix, Inverse) {
    Matrix<float> m({{1.0, -2.0, 3.0}, {4.0, 5.0, 6.0}, {7.0, 8.0, 9.0}});
    Matrix<float> expected({{0.125, -1.75, 1.125}, {-0.25, 0.5, -0.25}, {0.125, 11.0 / 12.0, -13.0 / 24.0}});
    Matrix<float> inv(3, 3);
    Matrix<float>::Inverse(m, inv);
    EXPECT_EQ(expected, inv);
}

// TEST(Matrix, mul) {
//     Matrix<int> a(10, 10, [] { return Random::Int(0, 100); });
//     Matrix<int> b(10, 10, [] { return Random::Int(0, 100); });
//     auto c1 = a * b;
//     Matrix<int> c2(10, 10);
//     Matrix<int>::MulParallel(a, b, c2, 4);
//     EXPECT_EQ(c1, c2);
// }

// TEST(Matrix, mul_blas) {
//     Matrix<float> a(10, 10, [] { return Random::Int(0, 100); });
//     Matrix<float> b(10, 10, [] { return Random::Int(0, 100); });
//     auto c1 = a * b;
//     Matrix<float> c2(10, 10);
//     BLAS<float>::Mul(a, b, c2);
//     EXPECT_EQ(c1, c2);
// }

// TEST(Matrix, mul_bt) {
//     Matrix<int> a(10, 10, [] { return Random::Int(0, 100); });
//     Matrix<int> b(10, 10, [] { return Random::Int(0, 100); });
//     auto c1 = a * b.Transpose();
//     Matrix<int> c2(10, 10);
//     Matrix<int> c3(10, 10);
//     Matrix<int> c4(10, 10);
//     Matrix<int>::MulBTParallel(a, b, c2, 4);
//     Matrix<int>::MulBT(a, b, c3);
//     BLAS<int>::MulBT(a, b, c4);
//     EXPECT_EQ(c1, c2);
//     EXPECT_EQ(c1, c3);
//     EXPECT_EQ(c1, c4);
// }

