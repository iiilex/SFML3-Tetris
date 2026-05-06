#pragma once

#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include<random>
#include<optional>

#include<global.h>
#include<block.h>
#include<board.h>
class Game
{
    protected:
        std::mt19937 gen;
        std::uniform_int_distribution<> distrib;

        sf::RenderWindow window;

        sf::Music bgm;
        sf::SoundBuffer fx;
        sf::Sound remove_fx;

        sf::Color colorSet[gameSet_x][gameSet_y];
        int layerCount[gameSet_y]; // 每一层的方块个数
        //大小10*20.以左上角为原点建系，即左上角的点为(0,0)

        ScoreBoard scoreboard;
        SpeedBoard speedboard;

        std::optional<Block> MyBlock;
        std::optional<Block> Shadow;

        sf::VertexArray line;
    public:
        Game();
        void run();
        void fix(Block &block);
        void draw(sf::RenderWindow &window);
        BlockType getType();
        void layerClear(int layerId);
        void drawAll();
};