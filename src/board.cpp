#include<SFML/Graphics.hpp>
#include<global.h>
#include<board.h>

ScoreBoard::ScoreBoard() : score(0), font("./fonts/arial.ttf"), explains(font), scores(font)
{
    explains.setString("Score:");
    explains.setCharacterSize(70);
    auto explainsBounds = explains.getLocalBounds();
    explains.setPosition({900 - explainsBounds.size.x,100});

    scores.setString("0");
    scores.setCharacterSize(70);
    auto scoresBounds = scores.getLocalBounds();
    scores.setPosition({900 - scoresBounds.size.x, 200});
}

void ScoreBoard::draw(sf::RenderWindow &window)
{
    window.draw(explains);
    window.draw(scores);
}

void ScoreBoard::addScore(int layerClearCount)
{
    int t = 0;
    for(int i = layerClearCount; i>=1; i--)
        t += i;
    t *= 10 * velocity;
    score += t;
    scores.setString(std::to_string(score));
    auto scoresBounds = scores.getLocalBounds();
    scores.setPosition({900 - scoresBounds.size.x, 200});
}

SpeedBoard::SpeedBoard() : font("./fonts/arial.ttf"), explains(font), speed(font)
{
    explains.setString("Speed:");
    explains.setCharacterSize(70);
    auto explainsBounds = explains.getLocalBounds();
    explains.setPosition({900 - explainsBounds.size.x,500});
    
    speed.setString("1");
    speed.setCharacterSize(70);
    auto speedBounds = speed.getLocalBounds();
    speed.setPosition({900 - speedBounds.size.x,600});

}

void SpeedBoard::addSpeed()
{
    velocity += 1 ;
    interval = distance / (1 + degreeOfDifficulty*velocity);
    speed.setString(std::to_string(int(velocity)));
    auto speedBounds = speed.getLocalBounds();
    speed.setPosition({900 - speedBounds.size.x,600});
}

void SpeedBoard::draw(sf::RenderWindow &window)
{
    window.draw(explains);
    window.draw(speed);
}
