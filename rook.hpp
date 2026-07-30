#pragma once

#include <SFML/Graphics.hpp>
#include "piece.hpp"

class rook : public piece
{
    public:
        rook(const sf::Texture &texture, bool is_White);

    public:
        int dirx[4] = {1, 0, -1, 0};
        int diry[4] = {0, 1, 0, -1};
        std::vector <sf::Vector2f> moves(board&) override;

};
