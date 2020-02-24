/*!
 * \file FileUtils.h
 * \brief Utils functions to read and write files.
 * \author Biguenet Denis & Gosset Severin
 * \date 22/02/2020
 */

#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "../../include/Model/Point.h"

/*! \class FileUtils
 * \brief Utils fonctions to read and write files.
 *
 * Static class without fields
 * Used to save and create levels
 */
class FileUtils {
    public :
        /*!
         * \brief Read file function to load level
         * \param fileName : the level's name
         * \return a vector of points that represents the shape to reproduce
         *
         */
        static std::vector<Point<double>> readFile(const char* fileName);

        /*!
         * \brief Write file function to save created level
         * \param points : the points from the shape created by the user
         * \param fileName : the level's name
         *
         * The points are written in the specified file.
         */
    	static void writeFile(std::vector<Point<double>> points, const char * fileName);
    private :

};

