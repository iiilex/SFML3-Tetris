/*
    game.cpp : 负责游戏相关的流程进行

    1. 游戏流程相关的变量
        游戏棋盘（bool, 1表示当前格有方块）
        渲染棋盘(sf::Color, 存储当前格子的颜色)
        背景音乐
        音效

    2. 游戏的主循环 game.run()
        处理输入
            按下 Down : 当前方块顺时针旋转90度（如果可以）
            按下 Left : 向左移动一格（如果可以）
            按下 Right : 向右移动一格（如果可以）
            按下 Space : 加速下落
            按下 P : 暂停游戏
            按下 ESC : 退出游戏
        状态的更新
            方块的自由下落
            游戏棋盘的更新（有方块固定）
            如果能消除就消除
        渲染内容
            绘制下落的方块
            绘制棋盘
            绘制当前分数

    3.还要注意音乐、音效相关的内容

*/

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <optional>
#include <string>
#include <random>

#include <global.h>
#include <game.h>
#include <block.h>
#include <board.h>

using std::cout;
using std::endl;
using std::optional;

BlockType Game::getType()
{
    std::uniform_int_distribution<> distrib(1, 7);
    int num = distrib(gen);
    switch (num)
    {
    case 1:
        return BlockType::L;
    case 2:
        return BlockType::J;
    case 3:
        return BlockType::O;
    case 4:
        return BlockType::S;
    case 5:
        return BlockType::Z;
    case 6:
        return BlockType::T;
    case 7:
        return BlockType::I;
    }
}

Game::Game() : gen(std::random_device{}()), distrib(1, 7), window(sf::VideoMode({window_x, window_y}), "Tetris", sf::Style::Titlebar | sf::Style::Close), bgm("./music/bgm.wav"), fx("./music/remove_fx.wav"), remove_fx(fx), is_paused(false), scoreboard(), speedboard(), line(sf::PrimitiveType::Lines, 2)
{
    remove_fx.setVolume(100.f);
    for (int x = 0; x < gameSet_x; x++)
        for (int y = 0; y < gameSet_y; y++)
            gameSet[x][y] = 0;
    for (int y = 0; y < gameSet_y; y++)
        layerCount[y] = 0;
}

void Game::fix(Block &block)
{
    sf::Vector2i position = block.getPosition();
    sf::Color color = block.getColor();
    for (int x = 0; x < blockSet_x; x++)
        for (int y = 0; y < blockSet_y; y++)
        {
            if (!block.isExist(x, y))
                continue;
            int now_x = position.x + x;
            int now_y = position.y + y;
            if (now_y < 0)
                continue;
            gameSet[now_x][now_y] = 1;
            colorSet[now_x][now_y] = color;
            layerCount[now_y]++;
        }

    bool cleared;
    int layerClearCount = 0;
    do
    {
        cleared = false;
        for (int y = gameSet_y - 1; y >= 0; y--)
        {
            if (cleared && layerCount[y] != gameSet_x)
                break;
            if (layerCount[y] == gameSet_x)
            {
                cleared = true;
                layerClearCount++;
                remove_fx.play();
                layerClear(y);
                y++;
            }
        }
    } while (cleared);
    scoreboard.addScore(layerClearCount);
}

void Game::layerClear(int layerId)
{
    Shadow->setColor({0, 0, 0, 0});
    MyBlock->setColor({0, 0, 0, 0});
    sf::Clock clock;
    for (int i = 1; i <= 3; i++)
    {
        for (int x = 0; x < gameSet_x; x++)
            colorSet[x][layerId].a = 0;
        drawAll();

        while (clock.getElapsedTime().asSeconds() < 0.05f)
            ;
        clock.restart();

        for (int x = 0; x < gameSet_x; x++)
            colorSet[x][layerId].a = 255;
        drawAll();

        while (clock.getElapsedTime().asSeconds() < 0.05f)
            ;
        clock.restart();
    }

    for (int y = layerId - 1; y >= 0; y--)
        for (int x = 0; x < gameSet_x; x++)
        {
            gameSet[x][y + 1] = gameSet[x][y];
            colorSet[x][y + 1] = colorSet[x][y];
            layerCount[y + 1] = layerCount[y];
        }
}

void Game::draw(sf::RenderWindow &window)
{
    for (int x = 0; x < gameSet_x; x++)
        for (int y = 0; y < gameSet_y; y++)
        {
            if (gameSet[x][y] == 0)
                continue;
            sf::Vector2f draw_position;
            draw_position.x = x * block_x;
            draw_position.y = y * block_y;
            sf::RectangleShape shape;
            shape.setSize({block_x, block_y});
            shape.setFillColor(colorSet[x][y]);
            shape.setOutlineThickness(-1.5f);
            shape.setOutlineColor(sf::Color::Black);
            shape.setPosition(draw_position);
            window.draw(shape);
        }
}

void Game::run()
{

    window.setFramerateLimit(80);

    sf::Clock clock;
    float timer = 0.f;

    int blockCnt = 0;

    line[0].position = {gameSet_x * block_x + 1, 0.f};
    line[1].position = {gameSet_x * block_x + 1, window_y};

    sf::Font MyFont("fonts/arial.ttf");
    sf::Text endText(MyFont);
    endText.setString("YOU ARE DIED!");
    endText.setFillColor(sf::Color::Red);
    endText.setCharacterSize(70);
    auto endTextBound = endText.getLocalBounds();
    endText.setPosition({window_x / 2 - endTextBound.size.x / 2, window_y / 2 - endTextBound.size.y / 2});

    bgm.setVolume(70.f);
    bgm.setLooping(true);
    bgm.play();

    bool is_mute = false;
    bool is_end = false;

    while (window.isOpen())
    {
        if (is_end)
        {
            while (const std::optional event = window.pollEvent())
            {
                if (event->is<sf::Event::Closed>())
                    window.close();
                if (const auto *keyPressed = event->getIf<sf::Event::KeyPressed>())
                    if (keyPressed->scancode == sf::Keyboard::Scancode::Escape)
                        window.close();
            }
            window.clear();
            window.draw(endText);
            scoreboard.draw(window);
            speedboard.draw(window);
            window.display();
            continue;
        }

        if (!MyBlock.has_value())
        {
            auto type = getType();
            MyBlock.emplace(type);
            Shadow.emplace(type, true);
            Shadow->setColor({255, 255, 255, 100});
            while (Shadow->fall())
                ;
            blockCnt++;
            if (blockCnt == levelUpCnt)
            {
                speedboard.addSpeed();
                blockCnt = 0;
            }
        }

        bool is_quick_fall = false;

        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
            if (const auto *keyPressed = event->getIf<sf::Event::KeyPressed>())
            {
                if (keyPressed->scancode == sf::Keyboard::Scancode::P)
                {
                    is_paused = !is_paused;
                    if (is_paused)
                        bgm.pause();
                    else
                        bgm.play();
                }
                if (is_paused)
                    break;

                if (keyPressed->scancode == sf::Keyboard::Scancode::Escape)
                    window.close();
                if (keyPressed->scancode == sf::Keyboard::Scancode::Left)
                {
                    if (MyBlock.has_value())
                        MyBlock->move(-1);
                    if (Shadow.has_value())
                        Shadow->updateShadow(MyBlock.value());
                }
                if (keyPressed->scancode == sf::Keyboard::Scancode::Right)
                {
                    if (MyBlock.has_value())
                        MyBlock->move(1);
                    if (Shadow.has_value())
                        Shadow->updateShadow(MyBlock.value());
                }
                if (keyPressed->scancode == sf::Keyboard::Scancode::Space)
                {
                    if (MyBlock.has_value())
                        while (MyBlock->fall());
                    fix(MyBlock.value());
                    MyBlock.reset();
                    Shadow.reset();
                    is_quick_fall = true;
                }
                if (keyPressed->scancode == sf::Keyboard::Scancode::Up)
                {
                    if(MyBlock.has_value())
                        MyBlock->rotate();
                    if (Shadow.has_value())
                        Shadow->updateShadow(MyBlock.value());
                }
                if (keyPressed->scancode == sf::Keyboard::Scancode::Down)
                    if(MyBlock.has_value())
                        MyBlock->fall();

                if (keyPressed->scancode == sf::Keyboard::Scancode::M)
                {
                    if (is_mute == false)
                    {
                        bgm.setVolume(0);
                        remove_fx.setVolume(0);
                    }
                    else
                    {
                        bgm.setVolume(70);
                        remove_fx.setVolume(100);
                    }
                    is_mute = !is_mute;
                }
            }
        }

        sf::Time deltatime = clock.restart();
        timer += deltatime.asSeconds();
        while (timer >= interval)
        {
            if (is_paused || is_quick_fall)
            {
                timer = 0;
                break;
            }
            if (!MyBlock->fall())
            {
                fix(MyBlock.value());
                MyBlock.reset();
                Shadow.reset();
                timer = 0.f;
                if (layerCount[0] != 0)
                {
                    is_end = true;
                    bgm.stop();
                }
                break;
            }
            timer -= interval;
        }

        if (is_paused)
            continue;

        drawAll();
    }
}

void Game::drawAll()
{
    window.clear();
    window.draw(line);
    scoreboard.draw(window);
    speedboard.draw(window);
    if (MyBlock.has_value())
        MyBlock->draw(window);
    if (Shadow.has_value())
        Shadow->draw(window);
    this->draw(window);
    window.display();
}