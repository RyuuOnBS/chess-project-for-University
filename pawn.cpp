#include "pawn.hpp"
#include "board.hpp"

        pawn::pawn(const sf::Texture &texture,bool is_White): piece::piece(texture, is_White)
        {
        }
        std::vector <sf::Vector2f> pawn::moves(board& b)
        {
            possible_moves.clear();
            is_pawn = true;
            is_En_Passant = false;
            int direction = is_White? -1 : 1;
            int newrow = row;
            int newcol = column + direction;
            int newCOL = column + 2* direction;
            int atkROW[] = {newrow - 1, newrow + 1};
            piece* front = b.getPieceLoc(newrow,newcol);
            piece* front1 = b.getPieceLoc(newrow,newCOL);
            piece* sides[2] = {b.getPieceLoc(newrow - 1, column), b.getPieceLoc(newrow + 1, column)};
            pawn* Capturable[2] = { dynamic_cast<pawn*>(sides[0]), dynamic_cast<pawn*>(sides[1])};

            if(front == nullptr)
            {
                if(newcol >= 0 and newcol <= 7)
                    possible_moves.push_back(b.get_Position(newrow, newcol));
                is_En_Passant = false;
            }
            
            if(is_First_Move)
            {
                if(front1 == nullptr)
                {
                    possible_moves.push_back(b.get_Position(newrow, newCOL));
                    is_En_Passant = true;
                }
            }
            
            for(int i = 0; i < 2; i++ )
            {
                if(b.is_Friendly(atkROW[i], newcol, !is_White))
                {
                    (i % 2 == 0)? atkROW[i] = newrow - 1 : newrow + 1;
                    if(newcol >= 0 or newcol <= 7)
                    {
                        possible_moves.push_back(b.get_Position(atkROW[i], newcol));
                    }
                }
            }
            if( column == 3 and is_White )
            {
                for(int i = 0; i < 2; i++)
                {
                    if( Capturable[i] != nullptr and Capturable[i]->is_White != is_White and Capturable[i]->is_En_Passant == true)
                    {
                        possible_moves.push_back(b.get_Position(Capturable[i]->row, 2));
                        Capturable[i]->is_Alive = false;
                    }
                }
            }
            else if( column == 4 and !is_White )
            {
                for(int i = 0; i < 2; i++)
                {
                    if( Capturable[i] != nullptr and Capturable[i]->is_White != is_White and Capturable[i]->is_En_Passant == true)
                    {
                        possible_moves.push_back(b.get_Position(Capturable[i]->row, 5));
                        Capturable[i]->is_Alive = false;
                    }
                }
            }                

            // Promotion
            sf::Vector2f pos = {row, column};
            if(pos.y == 7.f or pos.y == 0.f)
                can_Promote = true;

            return possible_moves;
        }