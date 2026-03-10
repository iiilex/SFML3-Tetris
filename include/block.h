/*
    一个方块类
    方块们需要做什么事情呢？

    0. 初始化
        Block block(type);

    1. 下落
        bool block.fall()
        如果成功下落，返回true

    2. 水平移动
        bool block.move(int stride)
        如果成功移动，返回true

    3. 旋转
        bool block.rotate()
        顺时针旋转90度，如果成功移动，返回true

    4. 渲染到窗口
        block.draw(sf::RenderWindow &window)
    
    5. 一些对外接口
        block.getPosition()
        block.getColor()
        block.isExist(int x, int y) // 返回blockSet[x][y]

*/

#pragma once

#include<SFML/Graphics.hpp>

enum class BlockType
{
    L, J, O, S, Z, I, T
}; // 不同方块的种类有不同的初始化策略

class Block
{
    protected:
        bool blockSet[blockSet_x][blockSet_y];
        bool is_shadow;
        sf::Color color;
        sf::Vector2i position; // 虚拟格子左上角在棋盘中的坐标
        BlockType myType;
    public:
        Block();
        Block(const BlockType &type, bool flag = false);
        bool fall();
        bool move(int stride);
        bool rotate();
        void draw(sf::RenderWindow &window);
        sf::Vector2i getPosition() const;
        sf::Color  getColor() const;
        BlockType getType();
        void setColor(sf::Color newColor);
        bool isExist(int x, int y) const;
        bool getIsShadow();
        void updateShadow(Block &block);
};
