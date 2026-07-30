#pragma once

#include<SFML/Graphics.hpp>

class piece;

class board
{
    public:
    std::vector <piece*> blackpiece;
    std::vector <piece*> whitepiece;

    static sf::Vector2f get_Position(int row, int column);

    static sf::Vector2f get_Position1(int row, int column);

    static sf::Vector2f get_Position2(int row, int column);

    static sf::Vector2f get_Index(float row, float column);

    static sf::Vector2f set_text_position(int row);

    static sf::Vector2f set_num_position(int column);

    piece* getPieceLoc(int row,int col);

    bool is_Friendly(float row, float col, bool is_white);

    void capturePiece(piece* captured);
};