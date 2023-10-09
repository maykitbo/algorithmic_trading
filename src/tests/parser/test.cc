#include "../../common/data_struct.h"

#include <gtest/gtest.h>

using namespace s21;

void OneFileTest(const std::string &file_name, unsigned expected_size)
{
    Points points = ParserCsv::Parse(file_name);
    unsigned size = points.size();
    EXPECT_EQ(size, expected_size);
    for (unsigned i = 0; i < size - 1; ++i)
    {
        EXPECT_TRUE(points[i].first > 0.0);
        EXPECT_TRUE(points[i].first < points[i + 1].first);
    }
    EXPECT_TRUE(points[size - 1].first > 0.0);
    std::sort(points.begin(), points.end(),
        [](const Point &a, const Point &b) { return a.first < b.first; });
    points.erase(std::unique(points.begin(), points.end(),
        [](const Point &a, const Point &b) { return a.first == b.first; }), points.end());
    EXPECT_EQ(size, expected_size);
}

void BadFileTest(const std::string &file_name)
{
    EXPECT_THROW(ParserCsv::Parse(file_name), std::runtime_error);
}

void WeightTest(const std::string &file, const std::function<void(fp_type)> &func)
{
    PointsWeights pw = ParserCsv::ParseWeights(file);
    EXPECT_EQ(pw.first.size(), 9);
    EXPECT_EQ(pw.second.size(), 9);
    for (unsigned i = 0; i < pw.first.size(); ++i)
    {
        func(pw.second[i]);
    }
}

#define __PARSER_TEST(name, size) TEST(Parser, name) \
    { OneFileTest("materials/" #name ".csv", size); }

#define __BAD_PARSER_TEST(name) TEST(Parser, bad_##name) \
    { BadFileTest("materials/bad_csv/" #name ".csv"); }

#define __WEIGHT_TEST(name, func) TEST(Parser, weight_##name) \
    { WeightTest("materials/" #name ".csv", func); }

__PARSER_TEST(AAPL, 254)
__PARSER_TEST(ADBE, 254)
__PARSER_TEST(CVX_original, 254)
__PARSER_TEST(CVX, 9)
__PARSER_TEST(CVX2, 9)
__PARSER_TEST(DPZ, 254)
__PARSER_TEST(F, 254)

__BAD_PARSER_TEST(AAPL)
__BAD_PARSER_TEST(CVX)
__BAD_PARSER_TEST(qwerty)

__WEIGHT_TEST(CVX, [](fp_type x) { EXPECT_EQ(x, 1.0); })
__WEIGHT_TEST(CVX_w1, [](fp_type x) { EXPECT_EQ(x, 1.0); })
__WEIGHT_TEST(CVX_wr, [](fp_type x) { EXPECT_TRUE(x != 1.0); })
