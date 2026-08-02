#pragma once

#include <SFML/Graphics.hpp>
#include "piece.hpp"

class king : public piece
{
    public:
        king(const sf::Texture &texture, bool is_White);

    public:
        int dirx[8] = {1, 1, -1, -1, 0, 0, 1, -1};
        int diry[8] = {1, -1, 1, -1, 1, -1, 0, 0};
        
        std::vector <sf::Vector2f> moves(board&) override;
};