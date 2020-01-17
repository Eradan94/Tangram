/**
 * Project Tangram
 */

#include "../Model/Point.h"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#pragma once
class FileUtils {
    public :
        static std::vector<Point<int>> readFile(const char* fileName);
    	static void writeFile(std::vector<Point<int>> points, const char * filename);
    private :

};

