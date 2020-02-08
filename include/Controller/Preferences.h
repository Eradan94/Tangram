/**
 * Project Tangram
 */

#define _USE_MATH_DEFINES
#include <cmath>
#include <string>
#include <iostream>
#include <map>

#pragma once
class Preferences {
    public :
        static Preferences& getInstance(){
            static Preferences instance;
            return instance;
        }
        void setMagnetism(double magnetism);
        void setRotationPerSpinning(double rotationPerSpinning);
        void setTolerance(double tolerance);

        double getMagnetism();
        double getRotationPerSpinning();
        double getTolerance();
    private :
        static Preferences& instance;
        std::map<std::string, double> options;

        Preferences() {
            //Temporaire
            options["magnetism"] = 20;
            options["rotation"] = 0,19634954084936;
            options["tolerance"] = 4;
            //TODO : faire une fonction pour parser le fichier .ini, en créer un par défaut s'il n'existe pas
        }
};

