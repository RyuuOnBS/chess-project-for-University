#include "king.hpp"
#include "board.hpp"


        bool is_king = true;
        king::king(const sf::Texture &texture, bool is_White): piece(texture, is_White)
        {
        }
        
        std::vector <sf::Vector2f> king::moves(board& b)
        {
            // piece* sides[2];
            // if(is_White)
            // {
            //     piece* sides[2] = {b.getPieceLoc(row - 3, column), b.getPieceLoc(row + 4,column)};
            // }
            // else
            // {
            //     piece* sides[2] = {b.getPieceLoc(row - 4, column), b.getPieceLoc(row + 3,column)};            
            // }
            
            // rook* castling_check[2] = {dynamic_cast<rook*>(sides[0]),dynamic_cast<rook*>(sides[1])};
            // possible_moves.clear();

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
                    if(b.is_Friendly(newrow, newcol, !is_White))
                    {
                        possible_moves.push_back(b.get_Position(newrow,newcol));
                    }
                }
            }
            // for(int i = 0; i < 2 ; i++)
            // {
            //     int dir = ( i % 2 == 0)? 1 : -1;
            //     if(castling_check[i] != nullptr and (column == 0 or column == 7) and is_First_Move and castling_check[i]->is_First_Move)
            //     {
            //         possible_moves.push_back(b.get_Position1( row + 2 * dir, column ));
            //     }
            // }
            return possible_moves;
        }
