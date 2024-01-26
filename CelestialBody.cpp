/*
    Copyright 2023 Patricia Antlitz
*/
#include <algorithm>
#include <cmath>
#include "CelestialBody.hpp"

const double G = 6.67e-11;

CelestialBody::CelestialBody() : xPos(0.0), yPos(0.0), xVel(0.0), yVel(0.0), mass(0.0), image("") {}

void CelestialBody::update(double seconds, const std::vector<CelestialBody>& bodies) {
    double fx = 0.0;
    double fy = 0.0;

    for (const CelestialBody& other : bodies) {
        if (this != &other) {
            double dx = other.getXPos() - xPos;
            double dy = other.getYPos() - yPos;
            double r = std::sqrt(dx * dx + dy * dy);
            r = std::max(r, 1.0);

            double force = G * mass * other.getMass() / (r * r);
            double forceX = force * (dx /r);
            double forceY = force * (dy / r);

            fx += forceX;
            fy += forceY;
        }
    }

    double ax = fx / mass;
    double ay = fy / mass;

    xVel += ax * seconds;
    yVel += ay * seconds;

    xPos += xVel * seconds;
    yPos += yVel * seconds;
}

void CelestialBody::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    // Create and draw an SFML sprite for this CelestialBody
    sf::Sprite sprite;
    sf::Texture texture;

    if (!texture.loadFromFile("assets/" + image))
        return;

    sprite.setTexture(texture);
    // Set sprite position based on body's data
    sprite.setPosition(static_cast<float>(xPos) / 1e9 + 400, static_cast<float>(yPos) / 1e9 + 300);
    // Draw the sprite
    target.draw(sprite, states);
}

// Overload the >> operator to read the planet data
std::istream& operator>>(std::istream& is, CelestialBody& body) {
    is >> body.xPos >> body.yPos >> body.xVel >> body.yVel >> body.mass >> body.image;
    return is;
}

// Overload the << operator to print the information back
std::ostream& operator<<(std::ostream& os, const CelestialBody& body) {
    os << body.xPos << " " << body.yPos << " " << body.xVel << " " << body.yVel
        << " " << body.mass << " " << body.image;
    return os;
}
