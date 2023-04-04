#ifndef GAME_HEAD
#define GAME_HEAD
#pragma once

#include <SDL.h>
struct Vector2;
struct Block;

struct Block
{
    float x_coordinate; // top left x
    float y_coordinate; // top left y
    int width;
    int height;
    Block();
    Block(const Block &block);
    Block(const int &x_coord, const int &y_coord, const int &iWidth, const int &iHeight);
    ~Block(){};
    void operator+=(const Vector2 &v);
    void operator-=(const Vector2 &v);
    Block operator+(const Vector2 &v);
    Block operator-(const Vector2 &v);
};

struct Vector2
{
    float x;
    float y;
    Vector2();
    Vector2(const Vector2 &v);
    Vector2(const int &x, const int &y);
    ~Vector2(){};
    void operator=(const Vector2 &v);
    void operator+=(const Vector2 &v);
    void operator-=(const Vector2 &v);
    Vector2 operator+(const Vector2 &v);
    Vector2 operator-(const Vector2 &v);
    float operator*(const Vector2 &v);
    Vector2 operator*(const float &val);
    friend Vector2 operator*(const float &val, const Vector2 &v);
    void operator*=(const float &val);
    Vector2 operator/(const float &val);
    void operator/=(const float &val);
    bool operator==(const Vector2 &v);
    bool operator!=(const Vector2 &v);
};

class Game
{
public:
    Game();
    // Initializes the game
    bool Initialize();
    // Runs the game
    void RunLoop();
    // Shutdown the game
    void Shutdown();

private:
    // Helper functions for the game loop
    void ProcessInput();
    void UpdateGame();
    void GenerateOutput();

    // the width and height of the window
    int WidthWindow;
    int HeightWindow;
    // the top-left x and top-left y
    float Window_x;
    float Window_y;
    // the thickness of wall
    int Thinckness_Walls;
    // Window created by SDL
    SDL_Window *mWindow;

    // Renderer for 2D drawing
    SDL_Renderer *mRenderer;

    // Number of ticks since start of game
    Uint32 mTickCount;

    // Game should continue to run
    bool mIsRunning;

    // Pong specific
    // paddle
    Block paddle;
    Block paddle2;
    // ball
    Block ball;

    // Vector the direction of the Objects to move
    // vector of paddle
    Vector2 paddleMoveDirection;
    // Vector of paddle2
    Vector2 paddleMoveDirection2;
    // vector of ball
    Vector2 ballMoveDirection;
    // zero vector
    Vector2 ZeroVector;
};
#endif
