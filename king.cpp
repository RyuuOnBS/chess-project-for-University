#include "king.hpp"
#include "board.hpp"
#include "rook.hpp"

        king::king(const sf::Texture &texture, bool is_White): piece(texture, is_White)
        {
        }

        std::vector <sf::Vector2f> king::moves(board& b)
        {
            piece* sides[2];
            is_king = true;
            is_castling = false;
            sides[0] = b.getPieceLoc(row - 4, column);
            sides[1] = b.getPieceLoc(row + 3,column);
            piece* leftside[4] ={b.getPieceLoc(row - 1, column),b.getPieceLoc(row - 2, column),b.getPieceLoc(row - 3, column),b.getPieceLoc(row - 4, column)};
            piece* rightside[3] ={b.getPieceLoc(row + 1, column),b.getPieceLoc(row + 2, column),b.getPieceLoc(row + 3, column)};
            rook* castling_check[2] = {dynamic_cast<rook*>(sides[0]),dynamic_cast<rook*>(sides[1])};
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
                    if(b.is_Friendly(newrow, newcol, !is_White))
                    {
                        possible_moves.push_back(b.get_Position(newrow,newcol));
                    }
                }
            }
            for(int i = 0; i < 2 ; i++)
            {
                if(castling_check[i] != nullptr and (column == 0 or column == 7) and is_First_Move and castling_check[i]->is_First_Move)
                {
                    if(leftside[0] == nullptr and leftside[1] == nullptr and leftside[2] == nullptr and leftside[3] == castling_check[i])
                    {
                        is_castling = true;
                        possible_moves.push_back(b.get_Position(row - 2, column));
                    }
                    if(rightside[0] == nullptr and rightside[1] == nullptr and rightside[2] == castling_check[i])
                    {
                        is_castling = true;
                        possible_moves.push_back(b.get_Position(row + 2, column));
                    }
                }
            }
            return possible_moves;
        }
