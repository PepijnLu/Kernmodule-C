g++ -c main.cpp -I"C:\Users\User1\Documents\libraries\SFML-2.6.1\include"
g++ -c GameObject.cpp Rigidbody.cpp Circle.cpp Player.cpp MathUtil.cpp -I"C:\Users\User1\Documents\libraries\SFML-2.6.1\include"
g++ main.o GameObject.o Rigidbody.o Circle.o Player.o MathUtil.o -o main -L"C:\Users\User1\Documents\libraries\SFML-2.6.1\lib" -lsfml-graphics -lsfml-window -lsfml-system
