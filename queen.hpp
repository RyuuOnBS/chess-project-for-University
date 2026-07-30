#pragma once

#include<SFML/Graphics.hpp>
#include "piece.hpp"

class queen : public piece
{
   public:
       queen(const sf::Texture &texture, bool is_White);

    public:
        int dirx[8] = {1, 1, -1, -1, 1, 0, -1, 0};
        int diry[8] = {1, -1, 1, -1, 0, 1, 0, -1};
        
        std::vector <sf::Vector2f> moves(board&) override;

};