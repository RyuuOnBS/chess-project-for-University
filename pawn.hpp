#pragma once

#include<SFML/Graphics.hpp>
#include "piece.hpp"

class pawn : public piece
{
    private:
        bool can_Promote;
        bool is_En_Passant = false;

    public:
        pawn(const sf::Texture &texture,bool is_White);

        std::vector <sf::Vector2f> moves(board& b) override;
};