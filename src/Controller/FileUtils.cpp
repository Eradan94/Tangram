/**
 * Project Tangram
 */


#include "../../include/Controller/FileUtils.h"

/**
 * FileUtils implementation
 */

std::vector<Point<double>> FileUtils::readFile(const char* fileName) {
    std::vector<Point<double>> points;
    std::string line;
    std::ifstream level(fileName);
    std::string xStr, yStr;
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

void FileUtils::writeFile(std::vector<Point<double>> points, std::string fileName) {
	std::string line;
	std::ofstream level(fileName);
	std::string xStr, yStr;
	if(level) {
        for_each(points.cbegin(), points.cend(), [&level](Point<double> p) {
            level << p.getX() << " " << p.getY() << std::endl;
        });
	}
	else {
        std::cerr << "Unable to open file" << std::endl;
	}
}
