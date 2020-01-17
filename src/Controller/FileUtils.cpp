/**
 * Project Tangram
 */


#include "FileUtils.h"

/**
 * FileUtils implementation
 */

 /* Charge un niveau selon le nom du fichier spécifié
 * fileName : nom du niveau à charger
 * renvoie un vecteur de points qui correspond à la figure à reproduire
 */
std::vector<Point<double>> FileUtils::readFile(const char* fileName) {
    std::vector<Point<double>> points; // Liste des points de la forme à reproduire
    std::string line; // contient la dernière ligne lue
    std::ifstream level(fileName); // ouvre le fichier en lecture
    string xStr, yStr; // contiennent les coordonnées du points
    double x, y; // contiennent les coordonnées du points sous forme de nombres
    int sep; // indice de la séparation entre les coordonnées x et y (un espace)
    if(level) {
        while(getline(level, line)) { // On lit une ligne du fichier
            sep = line.find(' '); // On cherche le premier espace pour séparer la coordonnée x et y
            xStr = line.substr(0, sep);
            yStr = line.substr(sep, line.size());
            // On utilise stoi pour passer de string vers double
            x = std::stoi(xStr);
            y = std::stoi(yStr);
            // On ajoute le point dans le vecteur
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
