#include "rook.hpp"
#include "board.hpp"

        rook::rook(const sf::Texture &texture, bool is_White) : piece(texture, is_White)
        {
        }    
        std::vector <sf::Vector2f> rook::moves(board& b)
        {
            possible_moves.clear();
            for(int d = 0; d < 4; d++)
            {
                for(int i = 1; i <= 8; i++)
                {
                    int newrow = row + (dirx[d]*i);
                    int newcol = column + (diry[d]*i);

                    if(newrow <= 7 and newcol <= 7 and newrow >= 0 and newcol >= 0)
                    {
                        if(!b.is_Friendly(newrow, newcol, is_White))
                        {
                            possible_moves.push_back(b.get_Position( newrow, newcol));
                        }
                        else
                        {
                            break;
                        }
                        if(b.is_Friendly(newrow, newcol, !is_White))
                        {
                            possible_moves.push_back(b.get_Position(newrow, newcol));
                            break;
                        }
                    }
                    else
                    {    
                        break;
                    }
                }
            }
            return possible_moves;
        }
