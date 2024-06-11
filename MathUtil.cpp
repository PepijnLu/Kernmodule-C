#include "MathUtil.h"

#include <iostream>
#include <stdlib.h>
#include <SFML/Graphics.hpp>

using namespace std;

namespace MathUtil
{
    //Amount of 0's = amount of decimals the square root is accurate to
    float squareRootAccuracy = 100000;

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

        //Handle negative exponents
        if (exponent < 0)
        {
            exponent = Abs(exponent);
            float denominator = 0;
            for(int i = 1; i < exponent; i++)
            {
                numSquared = MathUtil::Multiply(numSquared, num);
                denominator = numSquared;
            }
            numSquared = Divide(1, denominator);
        }

        //Anything to the power of 0 is 1
        else if (exponent == 0)
        {
            return 1;
        }
        //Handle positive exponents
        else if (exponent > 0)
        {
            for(int i = 1; i < exponent; i++)
            {
                numSquared = MathUtil::Multiply(numSquared, num);
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
        //Babylonian method for finding square roots
        else
        {
            //Any positive number works
            int intialNumber = 10;
            
            float prevNumber = intialNumber;
            while (!found)
            {
                float newNumber = Divide(Add(prevNumber, (Divide(number, prevNumber))), 2);

                if (int(MathUtil::Multiply(newNumber, squareRootAccuracy)) == int(MathUtil::Multiply(prevNumber, squareRootAccuracy)))
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

    //Pyhtagoream theorem
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
}









