#include<game.h>

/*
    三个模块：
    方块 block.h / block.cpp
    游戏 game.h / game.cpp
    计分板 board.h / board.cpp
*/

int main()
{
    Game game;
    while(game.isOpen())
    {
        switch(game.currentState)
        {
            case gameState::Home:
                game.home();
                break;
            case gameState::Run:
                game.run();
                break;
            case gameState::Fail:
                game.fail();
                break;
            case gameState::History:
                
                break;
        }
    }
    return 0;
}
