#include "compare.h"

using namespace s21;

void InterpolationTime::Compare(
        const PointsDec &points,
        bool cubic_spline,
        const std::vector<unsigned> &newtons_degree,
        unsigned points_count,
        unsigned partitions,
        const result_proc &func)
{

    unsigned size = points.size() + 1;
    unsigned subj = newtons_degree.size() + (cubic_spline ? 1 : 0);
    unsigned step = (points_count - size) / (partitions - 1);
    if (step < 1) {
        std::cerr << "Error: step < 1\n";
        return;
    }
    for (int k = size; k <= points_count; k += step)
    {
        result_data result(subj);
        unsigned i = 0;
        unsigned N = OptimalIterations(size, k);

        if (cubic_spline)
        {
            result[i].second = k;
            result[i++].first = Time::Test<Time::mcs>([&] {
                CubicSpline::Solve(points, k);
            }, N);
        }
        for (auto degree : newtons_degree)
        {
            result[i].second = k;
            result[i++].first = Time::Test<Time::mcs>([&] {
                NewtonPolynomial::Solve(points, degree, k);
            }, N);
        }
        func(result);
    }
}

unsigned InterpolationTime::OptimalIterations(unsigned size, unsigned k)
{
    using namespace boost::icl;
    static interval_map<unsigned, unsigned> iterations = []() {
        interval_map<unsigned, unsigned> itarations;
        itarations.insert(make_pair(interval<unsigned>::right_open(0, 1000), 10));
        itarations.insert(make_pair(interval<unsigned>::right_open(1000, 10000), 5));
        itarations.insert(make_pair(interval<unsigned>::right_open(10000, 100000), 3));
        itarations.insert(make_pair(interval<unsigned>::right_open(100000, std::numeric_limits<unsigned>::max()), 1));
        return itarations;
    }();

    unsigned f = size * k / 200;
    auto it = iterations.find(f);
    if (it != iterations.end()) {
        return it->second;
    }
    return 1;
}


