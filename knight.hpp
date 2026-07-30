#pragma once

#include<SFML/Graphics.hpp>
#include "piece.hpp"

class knight : public piece
{
    public:
        knight(const sf::Texture &texture, bool is_White);
    public:
        int dirx[8] = {2, 2, -2, -2, -1, -1, 1, 1};
        int diry[8] = {1, -1, 1, -1, 2, -2, 2, -2};
        std::vector <sf::Vector2f> moves(board&) override;

};
