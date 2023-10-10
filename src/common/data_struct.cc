#include "data_struct.h"

using namespace s21;

Points ParserCsv::Parse(const std::string &filename) {
  Points points;
  std::ifstream file(filename);

  if (!file.is_open())
    throw std::runtime_error("Error: Unable to open file " + filename);

  std::string line;
  std::getline(file, line);

  if (strncmp(line.c_str(), "Date,Close", 10) == 0) {
    ParseDC(points, file);
  } else {
    throw std::runtime_error("Error: Unable to parse header " + line);
  }
  file.close();
  return points;
}

PointsWeights ParserCsv::ParseWeights(const std::string &filename) {
  PointsWeights pw;
  std::ifstream file(filename);

  if (!file.is_open()) {
    throw std::runtime_error("Error: Unable to open file " + filename);
  }

  std::string line;
  std::getline(file, line);

  if (strncmp(line.c_str(), "Date,Close,Weight", 16) == 0) {
    ParseDCW(pw, file);
  } else if (strncmp(line.c_str(), "Date,Close", 10) == 0) {
    ParseDC(pw.first, file);
    pw.second.resize(pw.first.size(), 1.0);
  } else {
    throw std::runtime_error("Error: Unable to parse header " + line);
  }
  file.close();
  return pw;
}

void ParserCsv::ParseDC(Points &points, std::ifstream &file) {
  std::string line;
  while (std::getline(file, line)) {
    Point point;
    std::tm tm{};
    if (sscanf(line.c_str(), "%4d-%2d-%2d,%lf", &tm.tm_year, &tm.tm_mon,
               &tm.tm_mday, &point.second) != 4) {
      std::cerr << "ParserCsv Warning. Incorrect line will be skipped: " << line
                << '\n';
      continue;
    }
    tm.tm_year -= 1900;
    tm.tm_mon -= 1;
    time_t time = mktime(&tm);
    point.first = Convert::ToDays(time);
    points.push_back(point);
  }
}

void ParserCsv::ParseDCW(PointsWeights &points, std::ifstream &file) {
  std::string line;
  while (std::getline(file, line)) {
    Point point;
    fp_type weight;
    std::tm tm{};
    int res = sscanf(line.c_str(), "%4d-%2d-%2d,%lf,%lf", &tm.tm_year,
                     &tm.tm_mon, &tm.tm_mday, &point.second, &weight);
    if (res != 5 || weight <= 0.0) {
      std::cerr << "ParserCsv Warning. Incorrect line will be skipped: " << line
                << '\n';
      continue;
    }
    tm.tm_year -= 1900;
    tm.tm_mon -= 1;
    time_t time = mktime(&tm);
    point.first = Convert::ToDays(time);
    points.first.push_back(point);
    points.second.push_back(weight);
  }
}

fp_type Convert::ToSeconds(fp_type days) { return days * 60.0 * 60.0 * 24.0; }

fp_type Convert::ToDays(fp_type seconds) {
  return seconds / 60.0 / 60.0 / 24.0;
}

PointsDec Convert::ToDec(const Points &points) {
  return PointsDec(points.begin(), points.end());
}

Points Convert::ToDouble(const PointsDec &points) {
  return Points(points.begin(), points.end());
}

WeightsDec Convert::ToDec(const Weights &weights) {
  return WeightsDec(weights.begin(), weights.end());
}

Weights Convert::ToDouble(const WeightsDec &weights) {
  return Weights(weights.begin(), weights.end());
}

PointsWeightsDec Convert::ToDec(const PointsWeights &points) {
  return PointsWeightsDec{ToDec(points.first), ToDec(points.second)};
}

PointsWeights Convert::ToDouble(const PointsWeightsDec &points) {
  return PointsWeights{ToDouble(points.first), ToDouble(points.second)};
}