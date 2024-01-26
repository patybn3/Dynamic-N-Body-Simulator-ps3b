/*
    Copyright 2023 Patricia Antlitz
*/
#pragma once
#include <iostream>
#include <vector>
#include <string>

#include <SFML/Graphics.hpp>
#include "CelestialBody.hpp"  // Include CelestialBody.h here

class CelestialBody;  // Forward declaration of CelestialBody

class Universe {
 public:
    Universe();

    void step(double seconds);

    std::vector<CelestialBody>& getBodies() { return bodies; }

    // Overload the >> operator to read the number of planets and universe radius
    friend std::istream &operator>>(std::istream &is, Universe &universe);
    // Overload the << operator to print the information back
    friend std::ostream &operator<<(std::ostream &os, const Universe &universe);

 private:
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;

    int numPlanets;
    double radius;
    // Container to store CelestialBody objects
    std::vector<CelestialBody> bodies;
};
