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
        std::uniform_int_distribution<> distrib; // 随机数

        sf::RenderWindow window; //窗口

        sf::Music bgm;
        sf::SoundBuffer fx;
        sf::Sound remove_fx;
        // bgm 和 音效

        sf::Color colorSet[gameSet_x][gameSet_y];
        int layerCount[gameSet_y]; // 每一层的方块个数
        //大小10*20.以左上角为原点建系，即左上角的点为(0,0)

        ScoreBoard scoreboard;
        SpeedBoard speedboard;
        // 两种计分板
        
        sf::Font EngFont;
        sf::Font CnFont;
        sf::Text endText;
        //字体和文字

        std::optional<Block> MyBlock;
        std::optional<Block> Shadow;
        // 俄罗斯方块，和对应的阴影

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

        //按钮和背景

    public:
        gameState currentState;

        Game();
        void home();
        void run();
        void fail();

        void fix(Block &block); // 方块固定
        void draw(sf::RenderWindow &window); //绘图
        BlockType getType(); 
        void layerClear(int layerId);
        void drawAll();

        bool isOpen();
};