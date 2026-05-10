#pragma once

#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include<random>
#include<optional>

#include<global.h>
#include<block.h>
#include<board.h>

enum class gameState
{
    Home,
    Run,
    Fail,
    History
};

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
        
        sf::Font EngFont;
        sf::Font CnFont;
        sf::Text endText;

        std::optional<Block> MyBlock;
        std::optional<Block> Shadow;

        sf::VertexArray line;

        sf::Texture startBgTexture;
        sf::Texture BgTexture;

        sf::Sprite startBg;
        sf::Sprite Bg;

        sf::Texture startTexture;
        sf::Texture historyTexture;
        sf::Texture resetTexture;
        sf::Texture menuTexture;

        sf::Sprite start;
        sf::Sprite history;
        sf::Sprite reset;
        sf::Sprite menu;

    public:
        gameState currentState;

        Game();
        void home();
        void run();
        void fail();

        void fix(Block &block);
        void draw(sf::RenderWindow &window);
        BlockType getType();
        void layerClear(int layerId);
        void drawAll();

        bool isOpen();
};