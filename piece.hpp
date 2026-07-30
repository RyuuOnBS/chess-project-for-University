#pragma once

#include<SFML/Graphics.hpp>

class board;

class piece
{
    public:
        sf::Sprite sprite;
        int pos_x, pos_y;
        float row,column;
        bool is_First_Move = true;
        bool is_White;
        bool can_capture = false;
        bool is_Alive = true;
        bool is_Selected  = false;
        std::vector <sf::Vector2f> possible_moves;

        piece(const sf::Texture &texture, bool is_White);

    public:
        virtual std::vector <sf::Vector2f> moves(board& BOARD) = 0;

        virtual ~piece();
};
