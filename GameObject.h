#ifndef GameObject_H
#define GameObject_H

#pragma once
#include <SFML/Graphics.hpp>
#include <list>
#include <iostream>
#include "Rigidbody.h"
#include "GameObject.h"

using namespace std;


class GameObject
{
    private:
        float maxSpeed;
        int circleDiameter;
        bool inCollision;

    public:
        MathUtil::Vector2 position;
        MathUtil::Vector2 stdVec;

        GameObject()
        {
            cout << "Base constructor!" << endl;
        }
        ~GameObject()
        {
            cout << "Base constructor!" << endl;
        }
        GameObject(int xPos, int yPos, int circleRadius, float xSpeed, int screenWidth, int screenHeight, float mass, float elasticity);

        int circleRadius;
        float xSpeed;
        virtual void Draw();
        void BounceAgainstWalls();
        void ApplyVector(MathUtil::Vector2 vec);
        void NormalMovement(MathUtil::Vector2 inputValue);
        sf::CircleShape shape;
        int centerPointX;
        int centerPointY;
        bool player;
        bool needsRemoving, awardPoint;
        int screenWidth, screenHeight;

        MathUtil::Vector2 inputValue;
        bool hitThePlayer;

        //std::list<Rigidbody> rbList;
        std::vector<std::unique_ptr<Rigidbody>> rbList;
};

#endif