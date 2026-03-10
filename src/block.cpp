#include<SFML/Graphics.hpp>
#include<global.h>
#include<block.h>
#include<iostream>
using std::cout;
using std::endl;

Block::Block()
{
    is_shadow = false;
    for(int x=0; x<blockSet_x; x++)
        for(int y=0; y<blockSet_y; y++)
            blockSet[x][y] = 0;
    position.x = gameSet_x / 2 - 1;
    position.y = -4;
}

Block::Block(const BlockType &type, bool flag)
{
    is_shadow = flag;
    for(int x=0; x<blockSet_x; x++)
        for(int y=0; y<blockSet_y; y++)
            blockSet[x][y] = 0;
    position.x = 4;
    position.y = -3;
    myType = type;
    switch(type)
    {
        case(BlockType::L):
        {
            position.y = -3;
            blockSet[1][1] = blockSet[1][2] = blockSet[1][3] = blockSet[2][3] = 1;
            color = MyYellow;
            break;
        }
        case(BlockType::J):
        {
            blockSet[2][1] = blockSet[2][2] = blockSet[2][3] = blockSet[1][3] = 1;
            color = MyPurple;
            break;
        }
        case(BlockType::O):
        {
            blockSet[1][1] = blockSet[1][2] = blockSet[2][1] = blockSet[2][2] = 1;
            color = MyGreen;
            break;
        }
        case(BlockType::T):
        {
            blockSet[2][1] = blockSet[1][2] = blockSet[2][2] = blockSet[3][2] = 1;
            color = MyPink;
            break;
        }
        case(BlockType::S):
        {
            blockSet[1][2] = blockSet[2][1] = blockSet[2][2] = blockSet[3][1] = 1;
            color = MyBrown;
            break;
        }
        case(BlockType::Z):
        {
            blockSet[1][2] = blockSet[2][2] = blockSet[2][3] = blockSet[3][3] = 1;
            color = MyOrange;
            break;
        }
        case(BlockType::I):
        {
            blockSet[1][0] = blockSet[1][1] = blockSet[1][2] = blockSet[1][3] = 1;
            color = MyBlue;
            break;
        }
    }
}

bool Block::move(int stride)
{
    for(int x=0; x<blockSet_x; x++)
        for(int y=0; y<blockSet_y; y++)
        {
            if(blockSet[x][y]==0)  continue;
            int now_x = x + position.x + stride;
            int now_y = y + position.y;
            if(now_x < 0 || now_x >= gameSet_x || now_y >=0 && gameSet[now_x][now_y])
                return false;
        }
    position.x += stride;
    return true;
}

bool Block::fall()
{
    for(int x=0; x<blockSet_x; x++)
        for(int y=0; y<blockSet_y; y++)
        {
            if(blockSet[x][y]==0)  continue;
            int now_x = x + position.x;
            int now_y = y + position.y + 1;
            if(now_y < 0)  continue;
            if(now_y >= gameSet_y || gameSet[now_x][now_y])
                return false;
        }
    position.y += 1;
    return true;
}

void Block::draw(sf::RenderWindow &window)
{
    for(int x=0; x<blockSet_x; x++)
        for(int y=0; y<blockSet_y; y++)
        {
            if(blockSet[x][y] == 0)  continue;
            sf::Vector2f draw_position;
            draw_position.x = (x + position.x) * block_x;
            draw_position.y = (y + position.y) * block_y;
            sf::RectangleShape shape;
            shape.setSize({block_x, block_y});
            shape.setFillColor(color);
            shape.setOutlineThickness(-1.5f);
            shape.setOutlineColor(sf::Color::Black);
            shape.setPosition(draw_position);
            window.draw(shape);
        }
}

void swap(bool a[][4], bool t[][4])
{
    for(int x=0; x<blockSet_x; x++)
        for(int y=0; y<blockSet_y; y++)
        {
            bool tt = a[x][y];
            a[x][y] = t[x][y];
            t[x][y] = tt;
        }
}

bool Block::rotate()
{
    bool blockSet_temp[blockSet_x][blockSet_y];
    for(int x=0; x<blockSet_x; x++)
        for(int y=0; y<blockSet_y; y++)
            blockSet_temp[y][blockSet_x-1-x] = blockSet[x][y];
    
    swap(blockSet_temp, blockSet);

    for(int x=0; x<blockSet_x; x++)
        for(int y=0; y<blockSet_y; y++)
        {
            if(blockSet[x][y] == 0)  continue;
            int now_x = x + position.x;
            int now_y = y + position.y;
            if(now_x < 0 && !move(1) || now_x >= gameSet_x && !move(-1))
            {
                swap(blockSet_temp, blockSet);
                return false;
            }
            if(now_y >= gameSet_y)  position.y--;
            if(now_y < 0)  continue;
            if(gameSet[now_x][now_y] == 1)
            {
                if(move(1))
                {
                    now_x = x + position.x;
                    now_y = y + position.y;
                    if(gameSet[now_x][now_y] == 0)  continue;
                }
                else if(move(-1))
                {
                    now_x = x + position.x;
                    now_y = y + position.y;
                    if(gameSet[now_x][now_y] == 0)  continue;
                }
                else
                {
                    swap(blockSet_temp, blockSet);
                    return false;
                }
            }
        }
    return true;
}

sf::Vector2i Block::getPosition() const
{
    return position;
}

sf::Color Block::getColor() const
{
    return color;
}

bool Block::isExist(int x, int y) const
{
    return blockSet[x][y];
}

BlockType Block::getType()
{
    return myType;
}

void Block::setColor(sf::Color newColor)
{
    color = newColor;
}

bool Block::getIsShadow()
{
    return is_shadow;
}

void Block::updateShadow(Block &block)
{
    if(!is_shadow)  return ;
    position = block.position;
    for(int x=0; x<blockSet_x; x++)
        for(int y=0; y<blockSet_y; y++)
            this->blockSet[x][y] = block.blockSet[x][y];
    while(fall());
}