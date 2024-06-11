#include <iostream>
#include <stdlib.h>
#include <SFML/Graphics.hpp>
#include <list>
#include <random>
#include <string>
#include <memory>

#include "Enemy.h"
#include "Player.h"
#include "MathUtil.h"
#include "GameObject.h"

using namespace std;

string gameName = "Asteroids";
int totalEnemiesToSpawn = 100;
int totalPointsNeeded = 80;
int maxFrameRate = 60;
int screenWidth = 800;
int screenHeight = 800;
int maxEnemiesAtOnce = 10;

//In N/s
float playerSpeed = 700.f;
//In kgs
float playerMass = 75.f;
//1 = conserve all energy, 0 = conserve no energy
float playerElasticity = 0.2;
//Enemy radius
int playerSize = 50;
//In m/s
int maxPlayerSpeedX = 10;
//Doesn't move in Y
int maxPlayerSpeedY = 0;

//In N/s
int minEnemySpeed = 200, maxEnemySpeed = 800;
//In m/s, currently based on average human sprinting speed
int maxEnemySpeedX = 8;
int maxEnemySpeedY = 10;
//In kgs
int minEnemyMass = 20, maxEnemyMass = 150;
//10 = conserve all energy, 0 = conserve no energy
int minEnemyElasticity = 0, maxEnemyElasticity = 10;

//Circle radius
int enemySize = 25;

int enemyStartYpos = -500;
int standardFontSize = 50;

//Enemy spawn cooldown in frames
int minFramesBetweenEnemies = 20;

int playerStartXpos = MathUtil::Subtract(MathUtil::Divide(screenWidth, 2), playerSize);
int playerStartYpos = MathUtil::Subtract(screenHeight, MathUtil::Multiply(playerSize, 2));
int enemyStartXpos = MathUtil::Subtract(MathUtil::Divide(screenWidth, 2), enemySize);
MathUtil::Vector2 inputValue;
int frameCount;
int enemyCount;
int totalEnemiesSpawned;
int totalEnemiesPassed;
std::vector<std::unique_ptr<Enemy>> enemyList;
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

    //Create the player
    Player *player = new Player(playerStartXpos, playerStartYpos, playerSize, playerSpeed, screenWidth, screenHeight, playerMass, playerElasticity, maxPlayerSpeedX, maxPlayerSpeedY);

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

        int arrowKeysPressed = 0;

        if (event.type == sf::Event::KeyPressed) 
        {
            // Handle left arrow key press
            if ( (event.key.code == sf::Keyboard::Left)) 
            {
                inputValue.x = -1;
                arrowKeysPressed++;
            }
            // Handle right arrow key press
            if (event.key.code == sf::Keyboard::Right) 
            {
                inputValue.x = 1;
                arrowKeysPressed++;
            }
        }
        //Handle both arrows being pressed
        if (arrowKeysPressed == 2)
        {
            inputValue.x = 0;
        }

        //Feed the inputvalue to the player
        player->inputValue = inputValue;
        player->Draw();
        window.draw(player->shape);

        //Reset the inputvalue
        inputValue.x = 0;

        //Check if a new enemy is needed
        if (totalEnemiesSpawned < totalEnemiesToSpawn)
        {
            //Cooldown count down
            frameCount--;

            if (frameCount <= 0)
            {
                // Generate some random numbers
                float enemySpeedX = disSpeed(gen);
                float enemyMass = disMass(gen);
                float enemyElasticity = MathUtil::Divide(disElasticity(gen), 10);

                //Create an enemy
                enemyList.push_back(std::make_unique<Enemy>(enemyStartXpos, enemyStartYpos, enemySize, enemySpeedX, screenWidth, screenHeight, enemyMass, enemyElasticity, maxEnemySpeedX, maxEnemySpeedY));
                totalEnemiesSpawned++;
                enemyCount++;

                //Reset the spawn cooldown
                frameCount = minFramesBetweenEnemies;
            }
        }

        //Loop through all the existing enemies
        for (auto& obj : enemyList)
        {
            obj->Draw();
            window.draw(obj->shape);
            //Check collision between enemy and player
            if (MathUtil::Add(obj->centerPointY, obj->circleRadius) >= MathUtil::Subtract(screenHeight, (MathUtil::Multiply(playerSize, 2))))
            {
                int distanceEnemyToPlayer = MathUtil::CalcDistance(obj->centerPointX, player->centerPointX, obj->centerPointY, player->centerPointY);

                //Hit
                if ((MathUtil::Subtract(distanceEnemyToPlayer, obj->circleRadius) <= player->circleRadius) && (!obj->hitThePlayer))
                {
                    obj->awardPoint = false;
                    obj->hitThePlayer = true;
                    obj->needsRemoving = true;
                }
            }

            //Logic for if an object reached the bottom
            if (obj->needsRemoving)
            {
                if (obj->awardPoint)
                {
                    player->points++;
                    text.setString("Points: " + std::to_string(player->points) + "/" + std::to_string(totalPointsNeeded));
                    window.draw(text);
                }
                enemyCount--;
                totalEnemiesPassed++;
            }
        }

        //Erase and destroy all enemies that need to be removed (reached the bottom)
        enemyList.erase(std::remove_if(enemyList.begin(), enemyList.end(),
                                   [](const std::unique_ptr<Enemy>& obj) { return obj->needsRemoving; }),
                    enemyList.end());

        //Trigger the end screen
        if ((totalEnemiesPassed >= totalEnemiesToSpawn))
        {
            sf::RectangleShape square(sf::Vector2f(screenWidth, screenHeight));
            text.setCharacterSize(MathUtil::Multiply(standardFontSize, 2));
            //Win case
            if (player->points >= totalPointsNeeded)
            {
                text.setString("You win");
                square.setFillColor(sf::Color::Green);
            }
            //Lose case
            else
            {
                text.setString("You lose");
                square.setFillColor(sf::Color::Red);
            }
            window.draw(square);
        }
        window.draw(text);
        window.display();
    }

    //Clean up memory when closing
    delete player;
    enemyList.clear();

    return 0;
}




