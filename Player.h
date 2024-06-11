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
        virtual ~Player(){};
        Player(int xPos, int yPos, int circleRadius, float xSpeed, int screenWidth, int screenHeight, float mass, float elasticity, float maxSpeedX, float maxSpeedY)
        : GameObject(xPos, yPos, circleRadius, xSpeed, screenWidth, screenHeight, mass, elasticity, maxSpeedX, maxSpeedY)
        {
            this->points = 0;

            //Tell the game that this is the player
            this->player = true;

            this->shape.setFillColor(sf::Color::Blue);
            this->rb->useGravity = false;
        }

        virtual void Draw();
        int points;
};