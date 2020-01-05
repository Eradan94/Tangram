/**
 * Project Tangram
 */

#include <SFML/Graphics.hpp>

#include "Model/Point.h"
#include "Model/Piece.h"

#include <iostream>
#include <vector>
#include <Game.h>

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
    Point<int>  p4(2, 0);
    Point<int>  p5(1, 0);
    p4.rotate(p5, 1.57); // 90 degrees
    cout << p4 << endl;
}

void testTriangle() {
    cout << "---------Tests triangles--------" << endl;
    Point<int> p1;
    Point<int>  p2(30, 0);
    Point<int> p3(0, 30);
    Triangle<int> t(p1, p2, p3, sf::Color(255, 0, 0));
    cout << t << endl;
    /* Point A : (0, 0) Point B : (30, 0) Point C : (0, 30)*/
    Point<int> p4(1, 1);
    Point<int> p5(-9, 8);
    cout << p4 << " is in triangle ? " << t.isInTriangle(p4) << endl; // 1
    cout << p5 << " is in triangle ? " << t.isInTriangle(p5) << endl; // 0
    cout << "Center of t : " << t.center() << endl; //Center : (10, 10)
    Point<int> p6(10, 0);
    t.rotate(p6, 1.57); // 90 degrees
    cout << "rotated triangle : " << t << endl;
    Point<int> translation(3, 3);
    t.translate(translation);
    cout << "translation (3, 3) triangle" << t << endl;
}

void testPiece() {
    cout << "---------Tests pieces---------" << endl;
    Point<int> p1;
    Point<int>  p2(30, 0);
    Point<int> p3(0, 30);
    Triangle<int> t(p1, p2, p3, sf::Color(255, 0, 0));
    cout << t << endl;

    Point<int> p4(0, -30);
    Triangle<int> t2(p1, p2, p4, sf::Color(255, 0, 0));
    cout << t2 << endl;
    /* Point A : (0, 0) Point B : (30, 0) Point C : (0, -30)*/

    Piece<int> p;
    p.addTriangle(t);
    p.addTriangle(t2);
    cout << p << endl;
    cout << "Center of p : " << p.center() << endl; //Center : (10, 10)

    double theta = 6.283; // 360 degrees
    Point<int> c = p.center();
    p.rotate(c, theta);
    cout << "Rotated piece : " << p << endl;
    Point<int> clickPos(0, 0);
    p.centralize(clickPos);
    cout << "Centralized piece : " << p << endl;
}

void testShape() {
    Point<int> p1;
    Point<int> p2(30, 0);
    Point<int> p3(0, 30);
    Triangle<int> t(p1, p2, p3, sf::Color(255, 0, 0));
    Piece<int> p;
    p.addTriangle(t);
    vector<Shape<int>*> shapes;
    shapes.push_back(&t);
    shapes.push_back(&p);
}

void testSFML() {
    sf::RenderWindow window(sf::VideoMode(1600, 1000), "SFML works!");

    Point<int> p1(30, 30);
    Point<int> p2(30, 60);
    Point<int> p3(60, 30);
    Triangle<int> t(p1, p2, p3, sf::Color(255, 0, 0));
    Point<int> p4(30, 0);
    Triangle<int> t2(p4, p1, p3, sf::Color(255, 0, 0));
    Piece<int> p;
    p.addTriangle(t);
    p.addTriangle(t2);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear();
        p.draw(window);
        window.display();
    }
}

int main(int argc, char const *argv[]) {
    //testPoint();
    //testTriangle();
    //testPiece();
    //testShape();
//    testSFML();
	Game * game = Game::init();

	sf::RenderWindow window(sf::VideoMode(1600, 1000), "SFML works!");

	while (window.isOpen())
	{
		sf::Event event{};
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		window.clear();
		game->draw(window);
		window.display();
	}

	return 0;
}
