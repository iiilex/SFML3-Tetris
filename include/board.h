/*
    各种记录-控制板块。

    1. 计分板 ScoreBoard

    2. 速度板 SpeedBoard

    3. 介绍板 GuideBoard

*/

#pragma once

#include<SFML/Graphics.hpp>
#include<global.h>

class ScoreBoard
{
    protected:
        int score;
        sf::Font font;
        sf::Text explains;
        sf::Text scores;

    public:
        ScoreBoard();
        void addScore(int layerClearCount);
        void draw(sf::RenderWindow &window);

};

class SpeedBoard
{
    protected:
        sf::Font font;
        sf::Text explains;
        sf::Text speed;
    
    public:
        SpeedBoard();
        void addSpeed();
        void draw(sf::RenderWindow &window);
};
