/**
 * Project Tangram
 */


#include "../../include/Controller/Preferences.h"

/**
 * Preferences implementation
 */

void Preferences::setMagnetism(double magnetism) {
    options["magnetism"] = magnetism;
}

void Preferences::setRotationPerSpinning(double rotationPerSpinning) {
    options["rotation"] = rotationPerSpinning;
}

void Preferences::setTolerance(double tolerance) {
    options["tolerance"] = tolerance;
}

void Preferences::setGameButtonHeight(double buttonHeight) {
    options["gameButtonHeight"] = buttonHeight;
}



double Preferences::getMagnetism() {
    return options["magnetism"];
}

double Preferences::getRotationPerSpinning() {
    return options["rotation"];
}

double Preferences::getTolerance() {
    return options["tolerance"];
}

double Preferences::getGameButtonHeight() {
    return options["gameButtonHeight"];
}
