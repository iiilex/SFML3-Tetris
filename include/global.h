#pragma once

// 窗口的长宽(像素)
inline constexpr int window_x = 1000;
inline constexpr int window_y = 1200;

// 方块的长宽（像素）
inline constexpr float block_x = 60;
inline constexpr float block_y = 60;

// 游戏区域的大小（单位长度）
inline constexpr int gameSet_x = 10;
inline constexpr int gameSet_y = 20;

// 每个方块的点阵的大小
inline constexpr int blockSet_x = 4;
inline constexpr int blockSet_y = 4;

// 速度模块
inline constexpr float distance = 0.8;
inline float velocity = 1;
inline float interval = distance / velocity;

// 各种自己调配的颜色
inline constexpr sf::Color MyYellow = sf::Color({238,220,91});
inline constexpr sf::Color MyPurple = sf::Color({157,123,176});
inline constexpr sf::Color MyGreen = sf::Color({119,162,118});
inline constexpr sf::Color MyPink = sf::Color({249,163,170});
inline constexpr sf::Color MyBrown = sf::Color({187,167,72});
inline constexpr sf::Color MyOrange = sf::Color({255,169,23});
inline constexpr sf::Color MyBlue = sf::Color({127,151,181});

// 游戏网格
//大小10*20. 以左上角为原点建系，即左上角的点为(0,0) 
inline bool gameSet[gameSet_x][gameSet_y];

inline constexpr int levelUpCnt = 20;
inline constexpr float degreeOfDifficulty = 0.08f;