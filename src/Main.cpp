/**
 * Project Tangram
 */

#include "Model/Point.h"
//#include "Model/Triangle.h"
#include "Model/Piece.h"

#include <iostream>
#include <vector>
using namespace std;

/* Test function for points
*/
void testPoint() {
    cout << "---------Tests points---------" << endl;
    Point<int> p1;
    Point<int>  p2(3, 3);
    Point<double> p3(8.6, 3.4);
    cout << p1 << endl; // (0, 0)
    cout << p2 << endl; // (3, 3)
    cout << p3 << endl; // (8.6, 3.4)

}

void testTriangle() {
    cout << "---------Tests triangles--------" << endl;
    Point<int> p1;
    Point<int>  p2(3, 0);
    Point<int> p3(0, 2);
    Triangle<int> t(p1, p2, p3);
    cout << t << endl;
    /* Point A : (0, 0)
    * Point B : (3, 3)
    * Point C : (3, 0)
    */
    Point<int> p4(1, 1);
    Point<int> p5(9, 8);
    cout << p4 << " is in triangle ? " << t.isInTriangle(p4) << endl; // 1
    cout << p5 << " is in triangle ? " << t.isInTriangle(p5) << endl; // 0

}

void testPiece() {
    cout << "---------Tests pieces---------" << endl;
    Point<int> p1;
    Point<int>  p2(3, 0);
    Point<int> p3(0, 2);
    Triangle<int> t(p1, p2, p3);
    cout << t << endl;

    Point<int> p4(0, 8);
    Triangle<int> t2(p1, p2, p4);
    cout << t2 << endl;

    Piece<int> p;

    //Piece<int> p;
}

int main(int argc, char const *argv[]) {
    testPoint();
    testTriangle();
    testPiece();

	return 0;
}
