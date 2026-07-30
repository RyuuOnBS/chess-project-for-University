#pragma once

#include <SFML/Graphics.hpp>
#include "piece.hpp"

class bishop : public piece
{
    public:
        bishop(const sf::Texture &texture, bool is_White);

    public:
        int dirx[4] = {1, 1, -1, -1};
        int diry[4] = {1, -1, 1, -1};

        std::vector <sf::Vector2f> moves(board&) override;
};