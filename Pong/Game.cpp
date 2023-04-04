#include "Game.h"
#include <iostream>

Game::Game() : mWindow(nullptr),
               mRenderer(nullptr),
               mIsRunning(true)
{
    WidthWindow = 1024;
    HeightWindow = 768;
    Window_x = 100.0f;
    Window_y = 100.0f;
    mTickCount = Uint32(0);
    ZeroVector = Vector2(0, 0);
}

bool Game::Initialize()
{
    // Initialize SDL
    int sdlResult = SDL_Init(SDL_INIT_VIDEO);
    if (sdlResult != 0)
    {
        SDL_Log("Unable to initialize SDL: %s\n", SDL_GetError());
        return false;
    }

    // Create an SDL Window
    mWindow = SDL_CreateWindow(
        "Pong Programming int C++",
        Window_x,     // Top left x-coordinate of window
        Window_y,     // Top left y-coordinate of window
        WidthWindow,  // Width of window
        HeightWindow, // Height of window
        0             // Flags
    );
    if (!mWindow)
    {
        SDL_Log("Failed to create window: %s", SDL_GetError());
        return false;
    }

    // Create SDL renderer
    mRenderer = SDL_CreateRenderer(
        mWindow, // Window to create renderer for
        -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!mRenderer)
    {
        SDL_Log("Failed to create renderer: %s", SDL_GetError());
        return false;
    }

    //
    Thinckness_Walls = 15;
    paddle.height = 120;
    paddle.width = 15;
    paddle2.height = 120;
    paddle2.width = 15;
    paddle.x_coordinate = 0.0f;
    paddle.y_coordinate = HeightWindow / 2 - paddle.height / 2;
    paddle2.x_coordinate = WidthWindow - paddle2.width;
    paddle2.y_coordinate = HeightWindow / 2 - paddle2.height / 2;
    ball.height = 15;
    ball.width = 15;
    ball.x_coordinate = WidthWindow / 2 - ball.width / 2;
    ball.y_coordinate = HeightWindow / 2 - ball.height / 2;
    ballMoveDirection = Vector2(-200.0f, 235.0f);
    return true;
}
void Game::RunLoop()
{
    while (mIsRunning)
    {
        ProcessInput();
        UpdateGame();
        GenerateOutput();
    }
    return;
}
void Game::ProcessInput()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
            // If we get an SDL_QUIT event, end loop
        case SDL_QUIT:
            mIsRunning = false;
            break;
        }
    }

    // Get state of keyboard
    const Uint8 *state = SDL_GetKeyboardState(NULL);
    // If escape is pressed, also end loop
    if (state[SDL_SCANCODE_ESCAPE])
    {
        mIsRunning = false;
    }

    // Update paddle direction based on W/S keys
    paddleMoveDirection = ZeroVector;
    paddleMoveDirection2 = ZeroVector;
    if (state[SDL_SCANCODE_W])
    {
        paddleMoveDirection.y = -1;
    }
    if (state[SDL_SCANCODE_S])
    {
        paddleMoveDirection.y = 1;
    }
    if (state[SDL_SCANCODE_UP])
    {
        paddleMoveDirection2.y = -1;
    }
    if (state[SDL_SCANCODE_DOWN])
    {
        paddleMoveDirection2.y = 1;
    }
    return;
}
void Game::GenerateOutput()
{
    // Set Draw Color to blue
    SDL_SetRenderDrawColor(
        mRenderer,
        0,   // R
        0,   // G
        255, // B
        255  // A
    );

    // Clear back buffer
    SDL_RenderClear(mRenderer);
    // Change the Color
    SDL_SetRenderDrawColor(mRenderer, 255, 255, 255, 255);
    // Draw top wall
    SDL_Rect wall{
        0,               // top left-x
        0,               // top left-y
        WidthWindow,     // width of wall
        Thinckness_Walls // height of wall
    };
    SDL_RenderFillRect(mRenderer, &wall);

    // Draw bottom wall
    wall.y = HeightWindow - Thinckness_Walls;
    SDL_RenderFillRect(mRenderer, &wall);

    // Draw Paddle
    SDL_Rect padll2Draw{
        paddle.x_coordinate, // top left-x
        paddle.y_coordinate, // top left-y
        paddle.width,        // width of Paddle
        paddle.height        // height of Paddle
    };
    SDL_RenderFillRect(mRenderer, &padll2Draw);

    // Draw Paddle2
    SDL_Rect paddl2Draw2{
        paddle2.x_coordinate, // top left-x
        paddle2.y_coordinate, // top left-y
        paddle2.width,        // width of Paddle
        paddle2.height        // height of Paddle
    };
    SDL_RenderFillRect(mRenderer, &paddl2Draw2);

    // Draw Ball
    SDL_Rect ball2Draw{
        ball.x_coordinate, // top left-x
        ball.y_coordinate, // top left-y
        ball.width,        // width of ball
        ball.height        // height of ball
    };
    SDL_RenderFillRect(mRenderer, &ball2Draw);

    // Swape front buffer and back buffer
    SDL_RenderPresent(mRenderer);
    return;
}
void Game::UpdateGame()
{
    // Wait until 16ms has elapsed since last frame
    while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTickCount + 16))
        ;
    // Delta time is the difference in ticks from last frame
    //(converted to seconds
    float deltaTime = (SDL_GetTicks() - mTickCount) / 1000.0f;

    // Clamp maximum delta time value
    if (deltaTime > 0.05f)
    {
        deltaTime = 0.05f;
    }
    // Update tick counts (for next frame)
    mTickCount = SDL_GetTicks();

    // Update paddle position based on direction
    if (paddleMoveDirection != ZeroVector)
    {
        // Update paddle position based on direction
        paddle += paddleMoveDirection * 300.0f * deltaTime;
        // Make Sure paddle doesn't move off screen!
        if (paddle.y_coordinate + paddle.height > HeightWindow - Thinckness_Walls)
        {
            paddle.y_coordinate = HeightWindow - Thinckness_Walls - paddle.height;
        }
        else if (paddle.y_coordinate < Thinckness_Walls)
        {
            paddle.y_coordinate = Thinckness_Walls;
        }
    }
    // Upate paddle2 postion based on direction
    if (paddleMoveDirection2 != ZeroVector)
    {
        // Update paddle position based on direction
        paddle2 += paddleMoveDirection2 * 300.0f * deltaTime;
        // Make Sure paddle doesn't move off screen!
        if (paddle2.y_coordinate + paddle2.height > HeightWindow - Thinckness_Walls)
        {
            paddle2.y_coordinate = HeightWindow - Thinckness_Walls - paddle2.height;
        }
        else if (paddle2.y_coordinate < Thinckness_Walls)
        {
            paddle2.y_coordinate = Thinckness_Walls;
        }
    }
    // Update ball position base on direction
    ball += ballMoveDirection * deltaTime;

    // Bounce if need
    // Did we intersect with the paddle
    if (ball.y_coordinate + ball.height >= paddle.y_coordinate &&
        ball.y_coordinate <= paddle.y_coordinate + paddle.height &&
        ball.x_coordinate <= paddle.x_coordinate + paddle.width &&
        ballMoveDirection.x < 0.0f)
    {
        ballMoveDirection.x *= -1.0f;
    }
    // Did the ball strike top wall
    else if (ball.y_coordinate <= Thinckness_Walls && ballMoveDirection.y < 0.0f)
    {
        ballMoveDirection.y *= -1.0f;
    }
    // Did the ball strike right paddle
    else if (ball.y_coordinate + ball.height >= paddle2.y_coordinate &&
             ball.y_coordinate <= paddle2.y_coordinate + paddle2.height &&
             ball.x_coordinate + ball.width >= paddle2.x_coordinate &&
             ballMoveDirection.x > 0.0f)
    {
        ballMoveDirection.x *= -1.0f;
    }
    // Did the ball strike bottom wall
    else if (ball.y_coordinate + ball.height >= HeightWindow - Thinckness_Walls && ballMoveDirection.y > 0.0f)
    {
        ballMoveDirection.y *= -1.0f;
    }
    // Did the ball go off the screen from left side?
    else if (ball.x_coordinate <= 0.0f && ballMoveDirection.x < 0.0f)
    {
        mIsRunning = false;
    }
    // Did the ball go off the screen from right side?
    else if (ball.x_coordinate + ball.width >= WidthWindow && ballMoveDirection.x > 0.0f)
    {
        mIsRunning = false;
    }
    return;
}
void Game::Shutdown()
{
    SDL_DestroyRenderer(mRenderer);
    SDL_DestroyWindow(mWindow);
    SDL_Quit();
}

Block::Block()
{
    x_coordinate = 0;
    y_coordinate = 0;
    width = 0;
    height = 0;
}
Block::Block(const Block &block)
{
    x_coordinate = block.x_coordinate;
    y_coordinate = block.y_coordinate;
    width = block.width;
    height = block.height;
}
Block::Block(const int &x_, const int &y_, const int &width_, const int &height_)
{
    x_coordinate = x_;
    y_coordinate = y_;
    width = width_;
    height = height_;
}
void Block::operator+=(const Vector2 &v)
{
    x_coordinate = x_coordinate + v.x;
    y_coordinate = y_coordinate + v.y;
    return;
}
void Block::operator-=(const Vector2 &v)
{
    x_coordinate = x_coordinate - v.x;
    y_coordinate = y_coordinate - v.y;
    return;
}
Block Block::operator+(const Vector2 &v)
{
    Block tempBlock;
    tempBlock.x_coordinate = x_coordinate + v.x;
    tempBlock.y_coordinate = y_coordinate + v.y;
    return tempBlock;
}
Block Block::operator-(const Vector2 &v)
{
    Block tempBlock;
    tempBlock.x_coordinate = x_coordinate + v.x;
    tempBlock.y_coordinate = y_coordinate + v.y;
    return tempBlock;
}

void Vector2::operator=(const Vector2 &v)
{
    x = v.x;
    y = v.y;
    return;
}
void Vector2::operator+=(const Vector2 &v)
{
    x = x + v.x;
    y = y + v.y;
    return;
}
void Vector2::operator-=(const Vector2 &v)
{
    x = x - v.x;
    y = y - v.y;
    return;
}
Vector2::Vector2()
{
    x = 0;
    y = 0;
}
Vector2::Vector2(const Vector2 &v)
{
    x = v.x;
    y = v.y;
}
Vector2::Vector2(const int &x_, const int &y_)
{
    x = x_;
    y = y_;
}
Vector2 Vector2::operator+(const Vector2 &v)
{
    Vector2 tempV;
    tempV.x = x + v.x;
    tempV.y = y + v.y;
    return tempV;
}
Vector2 Vector2::operator-(const Vector2 &v)
{
    Vector2 tempV;
    tempV.x = x - v.x;
    tempV.y = y - v.y;
    return tempV;
}
float Vector2::operator*(const Vector2 &v)
{
    float val_result = x * v.x + y * v.y;
    return val_result;
}
Vector2 Vector2::operator*(const float &val)
{
    Vector2 tempVec;
    tempVec.x = x * val;
    tempVec.y = y * val;
    return tempVec;
}
Vector2 operator*(const float &val, const Vector2 &v)
{
    Vector2 tempVec;
    tempVec.x = v.x * val;
    tempVec.y = v.y * val;
    return tempVec;
}
void Vector2::operator*=(const float &val)
{
    x = x * val;
    y = y * val;
    return;
}
Vector2 Vector2::operator/(const float &val)
{
    Vector2 tempVec;
    tempVec.x = x / val;
    tempVec.y = y / val;
    return tempVec;
}
void Vector2::operator/=(const float &val)
{
    x = x / val;
    y = y / val;
    return;
}
bool Vector2::operator==(const Vector2 &v)
{
    if (x == v.x && y == v.y)
        return true;
    else
        return false;
}
bool Vector2::operator!=(const Vector2 &v)
{
    if (x == v.x && y == v.y)
        return false;
    else
        return true;
}