/*!
 * \file Preferences.h
 * \brief Singleton class to represents preferences
 * \author Biguenet Denis & Gosset Severin
 * \date 22/02/2020
 */

#pragma once

#define _USE_MATH_DEFINES
#include <cmath>
#include <string>
#include <iostream>
#include <map>

/*! \class Preferences
 * \brief Singleton class to represents preferences
 *
 */
class Preferences {
    public :
        /*!
        * \brief Gets the instance
        * \return the instance
        */
        static Preferences& getInstance(){
            static Preferences instance;
            return instance;
        }

        /*!
        * \brief Sets the magnetism
        * \param : the new magnetism
        *
        */
        void setMagnetism(double magnetism);

        /*!
        * \brief Sets the rotation per mouse spinning
        * \param : the new rotation angle by spinning
        *
        */
        void setRotationPerSpinning(double rotationPerSpinning);

        /*!
        * \brief Sets the tolerance of error
        * \param : the new tolerance
        *
        */
        void setTolerance(double tolerance);

        /*!
        * \brief Sets the height of buttons
        * \param : the new height
        *
        */
        void setGameButtonHeight(double buttonHeight);

        /*!
        * \brief Gets the magnetism
        * \return the magnetism
        */
        double getMagnetism();

        /*!
        * \brief Gets the rotation angle per mouse spinning
        * \return the rotation angle per mouse spinning
        */
        double getRotationPerSpinning();

        /*!
        * \brief Gets the tolerance of error
        * \return the tolerance
        */
        double getTolerance();

        /*!
        * \brief Gets the button's height
        * \return the height
        */
        double getGameButtonHeight();
    private :
        static Preferences& instance; /*!Instance*/
        std::map<std::string, double> options; /*!map to associate a string to a preference*/

        /*!
        * \brief Default constructor
        *
        */
        Preferences() {
            options["magnetism"] = 20;
            options["rotation"] = 0.19634954084936;
            options["tolerance"] = 4;
            options["gameButtonHeight"] = 100;
        }
};

