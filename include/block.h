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
        bool blockSet[blockSet_x][blockSet_y]; //用来构造方块的形状
        bool is_shadow; // 是否为阴影
        sf::Color color; // 方块的颜色
        sf::Vector2i position; // 虚拟格子左上角在棋盘中的坐标
        BlockType myType; //  当前方块的种类
    public:
        Block(); // 无参构造函数，防御性，常规情况不调用
        Block(const BlockType &type, bool flag = false); // 有参构造函数，flag为true代表是阴影
        bool fall(); // 下落1步
        bool move(int stride); // 移动向右 stride 步，通过stride的符号控制正负
        bool rotate(); // 顺时针旋转 90度
        void draw(sf::RenderWindow &window); // 绘制
        sf::Vector2i getPosition() const; // 当前位置
        sf::Color  getColor() const; // 当前颜色
        BlockType getType(); // 当前方块种类
        void setColor(sf::Color newColor); // 设置颜色
        bool isExist(int x, int y) const; // 辅助位置判断
        bool getIsShadow(); // 是否为阴影
        void updateShadow(Block &block); // 对于阴影的更新位置方法
};
