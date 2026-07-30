#include "knight.hpp"
#include "board.hpp"

        knight::knight(const sf::Texture &texture, bool is_White): piece(texture, is_White)
        {
        }
        std::vector <sf::Vector2f> knight::moves(board& b)
        {
            possible_moves.clear();
            for(int i = 0; i < 8; i++)
            {
                int newrow = row + dirx[i];
                int newcol = column + diry[i];

                if(newrow <= 7 and newcol <= 7 and newrow >= 0 and newcol >= 0)
                {
                    if(!b.is_Friendly(newrow, newcol, is_White))
                    {
                        possible_moves.push_back(b.get_Position( newrow, newcol));
                    }
                }
            }
        return possible_moves;
        }