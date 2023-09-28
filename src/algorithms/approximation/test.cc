#include "least_squares.h"
#include "../../common/data_struct.h"

using namespace s21;

int main() {
    Points points = {
        {1, 1},
        {2, 2},
        {3, -3},
        {4, 4},
        {5, -5}
    };

    LeastSquares ls(points, 3);

    return 0;
}
