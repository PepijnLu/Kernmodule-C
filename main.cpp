#include <iostream>
#include <stdlib.h>
#include <SFML/Graphics.hpp>
#include <list>
#include <random>
#include <string>

#include "Circle.h"
#include "Player.h"
#include "MathUtil.h"
#include "GameObject.h"

using namespace std;

/*
TO DO:
-clean up code

Things to ask teacher:
-Do I need more math / memory management?
-Why broken on other pc's? 
*/
string gameName = "Asteroids";
int totalEnemiesToSpawn = 50;
int totalPointsNeeded = 35;
int maxFrameRate = 60;
int screenWidth = 800;
int screenHeight = 800;
int maxEnemiesAtOnce = 7;

//In N/s
float playerSpeed = 700.f;
//In kgs
float playerMass = 75.f;
//1 = conserve all energy, 0 = conserve no energy
float playerElasticity = 0.2;
int playerSize = 50;
int playerStartXpos = MathUtil::Subtract(MathUtil::Divide(screenWidth, 2), playerSize);
int playerStartYpos = MathUtil::Subtract(screenHeight, MathUtil::Multiply(playerSize, 2));

//In N/s
int minEnemySpeed = 200, maxEnemySpeed = 800;
//In kgs
int minEnemyMass = 20, maxEnemyMass = 150;
//10 = conserve all energy, 0 = conserve no energy
int minEnemyElasticity = 0, maxEnemyElasticity = 10;
int enemySize = 25;
int enemyStartXpos = MathUtil::Subtract(MathUtil::Divide(screenWidth, 2), enemySize);
int enemyStartYpos = -500;
int standardFontSize = 50;
int minFramesBetweenEnemies = 20;

MathUtil::Vector2 inputValue;
int frameCount;
int enemyCount;
int totalEnemiesSpawned;
int totalEnemiesPassed;
std::list<Circle*> enemyList;
sf::Time previousTime;

int main()
{
    sf::RenderWindow window(sf::VideoMode(screenWidth, screenHeight), gameName);
    window.setFramerateLimit(maxFrameRate);

    sf::Font font;
    if (!font.loadFromFile("arial.ttf"))
    {
        // Handle error
        return -1;
    }

    // Create a random number engine
    std::random_device rd;  // Obtain a random number from hardware
    std::mt19937 gen(rd()); // Seed the generator

    // Define a distribution
    std::uniform_int_distribution<> disSpeed(minEnemySpeed, maxEnemySpeed); // Define the range
    std::uniform_int_distribution<> disMass(minEnemyMass, maxEnemyMass); // Define the range
    std::uniform_int_distribution<> disElasticity(minEnemyElasticity, maxEnemyElasticity); // Define the range

    Player *player = new Player(playerStartXpos, playerStartYpos, playerSize, playerSpeed, screenWidth, screenHeight, playerMass, playerElasticity);

    // Create a text object
    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(standardFontSize);
    text.setFillColor(sf::Color::White);
    text.setPosition(0, 0);
    text.setString("Points: " + std::to_string(player->points) + "/" + std::to_string(totalPointsNeeded));

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();

        int arrowKeysPressed;
        if (event.type == sf::Event::KeyPressed) 
        {
            if ( (event.key.code == sf::Keyboard::Left)) 
            {
                // Handle left arrow key press
                inputValue.x = -1;
                arrowKeysPressed++;
            }
            if (event.key.code == sf::Keyboard::Right) 
            {
                // Handle right arrow key press
                inputValue.x = 1;
                arrowKeysPressed++;
            }
        }
        if (arrowKeysPressed == 2)
        {
            inputValue.x = 0;
        }

        player->inputValue = inputValue;
        player->Draw();
        window.draw(player->shape);

        inputValue.x = 0;
        if (totalEnemiesSpawned < totalEnemiesToSpawn)
        {
            frameCount--;
            if (frameCount <= 0)
            {
                // Generate a random number
                float circleSpeedX = disSpeed(gen);
                float circleMass = disMass(gen);
                float circleElasticity = MathUtil::Divide(disElasticity(gen), 10);

                Circle* tempCircle = new Circle(enemyStartXpos, enemyStartYpos, enemySize, circleSpeedX, screenWidth, screenHeight, circleMass, circleElasticity);
                totalEnemiesSpawned++;
                enemyList.insert(std::next(enemyList.begin()), tempCircle);
                enemyCount++;
                frameCount = minFramesBetweenEnemies;
            }
        }

        for (auto it = enemyList.begin(); it != enemyList.end();)
        {
            auto& obj = *it;
            obj->Draw();
            window.draw(obj->shape);

            if (MathUtil::Add(obj->centerPointY, obj->circleRadius) >= MathUtil::Subtract(screenHeight, (MathUtil::Multiply(playerSize, 2))))
            {
                int distanceEnemyToPlayer = MathUtil::CalcDistance(obj->centerPointX, player->centerPointX, obj->centerPointY, player->centerPointY);

                if ((MathUtil::Subtract(distanceEnemyToPlayer, obj->circleRadius) <= player->circleRadius) && (!obj->hitThePlayer))
                {
                    obj->awardPoint = false;
                    obj->hitThePlayer = true;
                    obj->needsRemoving = true;
                }
            }

            if (obj->needsRemoving)
            {
                if (obj->awardPoint)
                {
                    player->points++;
                    text.setString("Points: " + std::to_string(player->points) + "/" + std::to_string(totalPointsNeeded));
                    window.draw(text);
                }
                it = enemyList.erase(it);
                enemyCount--;
                totalEnemiesPassed++;
                delete obj;
            }

            else
            {
                ++it; // Move to the next element
            }
        }

        if ((totalEnemiesPassed >= totalEnemiesToSpawn))
        {
            sf::RectangleShape square(sf::Vector2f(screenWidth, screenHeight));
            text.setCharacterSize(MathUtil::Multiply(standardFontSize, 2));
            if (player->points >= totalPointsNeeded)
            {
                text.setString("GG");
                square.setFillColor(sf::Color::Green);
            }
            else
            {
                text.setString("Womp Womp");
                square.setFillColor(sf::Color::Red);
            }
            delete player;
            window.draw(square);
        }
        window.draw(text);
        window.display();
    }

    return 0;
}




