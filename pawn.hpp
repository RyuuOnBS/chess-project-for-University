#pragma once

#include<SFML/Graphics.hpp>
#include "piece.hpp"

class pawn : public piece
{
    public:
        bool can_Promote = false;
        bool is_En_Passant = false;

    public:
        pawn(const sf::Texture &texture,bool is_White);

        std::vector <sf::Vector2f> moves(board& b) override;
};