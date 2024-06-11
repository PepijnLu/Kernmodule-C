#include "MathUtil.h"

#include <iostream>
#include <stdlib.h>
#include <SFML/Graphics.hpp>

using namespace std;

namespace MathUtil
{
    float Add(float num1, float num2)
    {
        return (num1 + num2);
    }
    float Subtract(float num1, float num2)
    {
        return (num1 - num2);
    }
    float Multiply(float num1, float num2)
    {
        return (num1 * num2);
    }
    float Divide(float num1, float num2)
    {
        return (num1 / num2);
    }
    float Pow(float num, float exponent)
    {
        float numSquared = num;

        if (exponent < 0)
        {
            exponent = Abs(exponent);
            float denominator = 0;
            for(int i = 1; i < exponent; i++)
            {
                denominator = numSquared *= num;
            }
            numSquared = 1/denominator;
        }
        else if (exponent == 0)
        {
            return 1;
        }
        else if (exponent > 0)
        {
            for(int i = 1; i < exponent; i++)
            {
                numSquared *= num;
            }
        }
        return numSquared;
    }

    float Abs(float num)
    {
        if (num < 0)
        {
            num = -num;
        }
        return num;
    }

    float GetSquareRoot(int number)
    {
        bool found = false;

        if (number < 0)
        {
            cout << "sorry im not smart enough to get the square root of negative numbers" << endl; 
            return -1;
        }
        else if (number == 0 || number == 1)
        {
            return number;
        }
        else
        {
            int intialNumber = 10;
            float prevNumber = intialNumber;
            while (!found)
            {
                float newNumber = ((prevNumber + (number / prevNumber))/2);

                if (int(newNumber * 100000) == (int(prevNumber * 100000)))
                {
                    found = true;
                    return newNumber;
                }
                else
                {
                    prevNumber = newNumber;
                } 
            }
        }

        return 0;
    }

    Vector2 Add(Vector2 vec1, Vector2 vec2)
    {
        Vector2 newVec;
        newVec.x = Add(vec1.x, vec2.x);
        newVec.y = Add(vec1.y, vec2.y);
        return newVec;
    }

    Vector2 Subtract(Vector2 vec1, Vector2 vec2)
    {
        Vector2 newVec;
        newVec.x = Subtract(vec1.x, vec2.x);
        newVec.y = Subtract(vec1.y, vec2.y);
        return newVec;
    }

    int CalcDistance(int x1, int x2, int y1, int y2)
    {
        int distanceX = Subtract(x1, x2);
        int distanceY = Subtract(y1, y2);

        int distanceXSquared = Pow(distanceX, 2);
        int distanceYSquared = Pow(distanceY, 2);

        int distancesSquared = Add(distanceXSquared, distanceYSquared);
        int distance = GetSquareRoot(distancesSquared);

        return distance;
    }

    float CalcDeltaTime(float fps)
    {
        float a = Divide(1, fps);
        float deltaTime = Multiply(a, 60);;

        return deltaTime;
    }
}









