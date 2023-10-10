#pragma once

#include "cubic_spline/cubic_spline.h"
#include "newton_polynomial/newton_polynomial.h"
#include "data_struct.h"
#include "utility/m_time.h"

#include <boost/icl/interval_map.hpp>
#include <limits>

namespace s21 {

class InterpolationTime
{
    public:
        using result_data = std::vector<std::pair<int64_t, unsigned>>;
        using result_proc =
            std::function<void(const result_data&)>;
        static void Compare(
                const PointsDec &points,
                bool cubic_spline,
                const std::vector<unsigned> &newtons_degree,
                unsigned points_count,
                unsigned partitions,
                const result_proc &func);
    private:
        static unsigned OptimalIterations(unsigned size, unsigned k);
};

} // namespace s21
