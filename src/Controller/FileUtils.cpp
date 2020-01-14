/**
 * Project Tangram
 */


#include "FileUtils.h"

/**
 * FileUtils implementation
 */

std::vector<Point<double>> FileUtils::readFile(const char* fileName) {
    std::vector<Point<double>> points;
    std::string line;
    std::ifstream level(fileName);
    string xStr, yStr;
    double x, y;
    int sep;
    if(level) {
        while(getline(level, line)) {
            sep = line.find(' ');
            xStr = line.substr(0, sep);
            yStr = line.substr(sep, line.size());
            x = std::stoi(xStr);
            y = std::stoi(yStr);
            points.push_back(Point(x, y));
        }
    }
    else {
        std::cerr << "file does not exist" << std::endl;
    }
    return points;
}

void FileUtils::writeFile(std::vector<Point<double>> points, const char *filename) {
	std::string line;
	std::ofstream level(filename);
	string xStr, yStr;
	double x, y;
	int sep;
	for_each(points.cbegin(), points.cend(), [&level](Point<double> p) {
		level << p.getX() << " " << p.getY() << endl;
	});
}
