#pragma once
#include <SFML/Graphics.hpp>
#include "Rigidbody.h"
#include "GameObject.h"
#include <list>

class Player : public GameObject
{
    private:

    public:
        MathUtil::Vector2 position;

        Player(){};
        Player(int xPos, int yPos, int circleRadius, float xSpeed, int screenWidth, int screenHeight, float mass, float elasticity)
        : GameObject(xPos, yPos, circleRadius, xSpeed, screenWidth, screenHeight, mass, elasticity)
        {
            //PLAYER SPECIFIC
            this->points = 0;
            this->player = true;
            this->shape.setFillColor(sf::Color::Blue);
            this->rbList.front().useGravity = false;
            //PLAYER SPEFICIC END
        }

        virtual void Draw();
        int points;
};