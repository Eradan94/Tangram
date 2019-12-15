/**
 * Project Tangram
 */

#include "Model/Point.h"
#include "Model/Triangle.h"

#include <iostream>
#include <vector>
using namespace std;

int main(int argc, char const *argv[]) {
    Point<int> p1;
    Point<int>  p2(3, 3);
    Point<double> p3(8.6, 3.4);
    Point<int> p4(3, 0);
    cout << p1 << p2 << p3 << endl;

    Triangle<int> t(p1, p2, p4);
    cout << t << endl;

    Point<int> p5(2, 1);
    Point<int> p6(9, 1);
    cout << t.isInTriangle(p5) << endl;
    cout << t.isInTriangle(p6) << endl;

	return 0;
}
