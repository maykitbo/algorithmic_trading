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

typedef std::pair<fp_type, fp_type> Point;
typedef std::pair<Real, Real> PointDec;

typedef std::vector<std::pair<fp_type, fp_type>> Points;
typedef std::vector<std::pair<Real, Real>> PointsDec;

struct Convert
{
    static PointsDec ToDec(const Points &points);
    static Points ToDouble(const PointsDec &points);
    static fp_type ToSeconds(fp_type days);
    static fp_type ToDays(fp_type seconds);
};

struct ParserCsv {
    static Points Parse(const std::string &filename);
};

};
