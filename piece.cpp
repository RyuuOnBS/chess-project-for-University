#include "piece.hpp"
#include "board.hpp"

        piece::piece(const sf::Texture &texture, bool is_White) : sprite(texture), is_White(is_White)
        {
        };

        piece::~piece() = default;

