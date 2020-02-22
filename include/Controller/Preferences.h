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
        void setGameButtonHeight(double buttonHeight);

        double getMagnetism();
        double getRotationPerSpinning();
        double getTolerance();
        double getGameButtonHeight();
    private :
        static Preferences& instance;
        std::map<std::string, double> options;

        Preferences() {
            options["magnetism"] = 20;
            options["rotation"] = 0.19634954084936;
            options["tolerance"] = 4;
            options["gameButtonHeight"] = 100;
        }
};

