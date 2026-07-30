    
#include "board.hpp"
#include "piece.hpp"

    std::vector <piece*> blackpiece;
    std::vector <piece*> whitepiece;

    sf::Vector2f board::get_Position(int row, int column)
    {
        return {17.f+static_cast<float>(row)*95.f,17.f+static_cast<float>(column)*95.f};
    }
    sf::Vector2f board::get_Position1(int row, int column)
    {
        return {23.f+static_cast<float>(row)*95.f,22.f+static_cast<float>(column)*95.f};
    }
    sf::Vector2f board::get_Position2(int row, int column)
    {
        return {26.f+static_cast<float>(row)*95.f,27.f+static_cast<float>(column)*95.f};
    }
    sf::Vector2f board::get_Index(float row, float column)
    {
        return { (row - 17.f)/95.f, (column - 17.f)/95.f };
    }
    sf::Vector2f board::set_text_position(int row){
        return {static_cast<float>(20+(row*95)),static_cast<float>(8*94)};
    }
    sf::Vector2f board::set_num_position(int column){
        return {static_cast<float>(20),static_cast<float>(18+((7-column)*95))};
    }
    


    bool board::is_Friendly(float row, float col, bool is_white)
    {
    piece* piss = getPieceLoc(row,col);
    
    if(piss == nullptr)
        return false;
    
    return piss->is_White == is_white;
    }

    void board::capturePiece(piece* captured)
    {
        std::vector <piece*>& pieces = captured->is_White ? whitepiece : blackpiece;
        auto it = find(pieces.begin(), pieces.end(), captured);

        if(it != pieces.end())
        {
            pieces.erase(it);
        }
    }

piece* board::getPieceLoc(int row,int col)
{
    for(piece* p : whitepiece)
    {
        if(p != nullptr and p->row == row and p->column == col and p->is_Alive)
        {
            return p;
        }
    }
    for(piece* p : blackpiece)
    {
        if(p != nullptr and p->row == row and p->column == col and p->is_Alive)
        {
            return p;
        }
    }
    return nullptr;
}
