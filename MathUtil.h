#pragma once

namespace MathUtil
{
    struct Vector2
    {
        float x;
        float y;
    };
    float GetSquareRoot(int number);
    float AddAndSquareNumbers(int num1, int num2);
    float Add(float num1, float num2);
    Vector2 Add(Vector2 vec1, Vector2 vec2);
    float Subtract(float num1, float num2);
    Vector2 Subtract(Vector2 vec1, Vector2 vec2);
    float Multiply(float num1, float num2);
    float Divide(float num1, float num2);
    int CalcDistance(int x1, int x2, int y1, int y2);
    float Pow(float num, float exponent);
    float Abs(float num);
    float CalcDeltaTime(float fps);
}
