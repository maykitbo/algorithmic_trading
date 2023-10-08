#include "data_struct.h"

using namespace s21;


// Point::Point(const PointDec &p)
//     : x(p.x.convert_to<fp_type>())
//     , y(p.y.convert_to<fp_type>())
//     {}

// PointDec::PointDec(const Point &p)
//     : x(p.x)
//     , y(p.y)
//     {}

Points ParserCsv::Parse(const std::string &filename)
{
    Points points;
    std::ifstream file(filename);

    if (!file.is_open())
    {
        throw std::runtime_error("Error: Unable to open file " + filename);
    }
    std::string line;
    std::string sscanf_format;
    std::getline(file, line);
    
    if (line == "Date,Close")
    {
        sscanf_format = "%4d-%2d-%2d,%lf";
    }
    else
    {
        throw std::runtime_error("Error: Unable to parse header " + line);
    }
    while (std::getline(file, line))
    {
        Point point;
        std::tm tm{};
        int ser = sscanf(line.c_str(), sscanf_format.c_str(), &tm.tm_year, &tm.tm_mon, &tm.tm_mday, &point.second);
        if (ser != 4)
        {
            throw std::runtime_error("Error: Unable to parse date string " + line);
            continue;
        }
        tm.tm_year -= 1900;
        tm.tm_mon -= 1;
        time_t time = mktime(&tm);
        // point.x = (double)time / (60.0 * 60.0 * 24.0); // Seconds to days
        point.first = Convert::ToDays(time);
        points.push_back(point);
        
    }
    file.close();
    return points;
}

fp_type Convert::ToSeconds(fp_type days)
{
    return days * 60.0 * 60.0 * 24.0;
}

fp_type Convert::ToDays(fp_type seconds)
{
    return seconds / 60.0 / 60.0 / 24.0;
}

PointsDec Convert::ToDec(const Points &points)
{
    return PointsDec(points.begin(), points.end());
}

Points Convert::ToDouble(const PointsDec &points)
{
    return Points(points.begin(), points.end());
}


// bool Point::operator==(const Point &p) const {
//     return x == p.x && y == p.y;
// }

// bool Point::operator!=(const Point &p) const {
//     return !(*this == p);
// }

