#include<game.h>

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
