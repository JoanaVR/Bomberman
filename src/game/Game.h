#pragma once

#include "Board.h"
#include "Player.h"

#include <vector>

class Game
{
public:
    enum Keys
    {
        K_UNDEFINED,
        K_UP,
        K_DOWN,
        K_RIGHT,
        K_LEFT,
        K_ENTER,
        K_a,
        K_s,
        K_d,
        K_w,
        K_SPACE
    };

    enum KeyAction
    {
        UNDEFINED,
        PRESSED,
        RELEASED
        
    };

    Game(const std::string &level, std::function<void ()> onGameOver = nullptr);
    void addObject(GameObject *object);
    Board *getBoard();
    void keyboardEvent(int key, int scancode, int action, int modifiers);
    void move();

private:
    Board *mBoard;
    std::vector<Player *> mPlayers;
    std::function<void ()> mOnGameOver;
};