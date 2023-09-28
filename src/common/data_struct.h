#pragma once

#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <ctime>
#include <iostream>
#include <algorithm>

#include <boost/multiprecision/cpp_dec_float.hpp>


namespace s21 {

typedef double fp_type;
typedef boost::multiprecision::cpp_dec_float_50 Real;
// typedef boost::multiprecision::cpp_dec_float_50 fp_type; // 50 decimal digits

struct PointDec;


/**
 * @brief The Point struct
*/
struct Point
{
    fp_type x;
    // time_t x;
    fp_type y;
    bool operator==(const Point &p) const;
    bool operator!=(const Point &p) const;
    static double ToSeconds(double days);
    static double ToDays(double seconds);

    Point() = default;
    Point(fp_type x, fp_type y) : x(x), y(y) {}
    Point(const PointDec &p);
};

struct PointDec
{
    
    Real x;
    Real y;
    PointDec() = default;
    PointDec(Real x, Real y) : x(x), y(y) {}
    PointDec(const Point &p);
};

typedef std::vector<Point> Points;
typedef std::vector<PointDec> PointsDec;

struct Convert
{
    static PointsDec ToDec(const Points &points);
    static Points ToDouble(const PointsDec &points);
};

/**
 * @brief The ParserCsv struct
*/
struct ParserCsv {
    static Points Parse(const std::string &filename);
};

};
