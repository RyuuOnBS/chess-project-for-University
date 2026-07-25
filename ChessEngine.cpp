#include<Sfml/Graphics.hpp>
#include<optional>

using namespace std;
// Includes all functions of sfml library
using namespace sf; 


// 1 means the value of the index is positive and the piece moves in positive direction of the same axis
// -1 means the value of the index becomes negative and the piece moves in negative direction of the same axis
// 0 indicates no change in the value
class piece;
class board
{
    public:
    vector <piece*> blackpiece;
    vector <piece*> whitepiece;

    static Vector2f get_Position(int row, int column)
    {
        return {17.f+static_cast<float>(row)*95.f,17.f+static_cast<float>(column)*95.f};
    }
    static Vector2f get_Index(float row, float column)
    {
        return { (row - 17.f)/95.f, (column - 17.f)/95.f };
    }
    static Vector2f set_text_position(int row){
        return {static_cast<float>(20+(row*95)),static_cast<float>(8*94)};
    }
    static Vector2f set_num_position(int column){
        return {static_cast<float>(20),static_cast<float>(18+((7-column)*95))};
    }
    
    piece* getPieceLoc(int row,int col);

    bool is_not_Friendly(float row, float col, bool is_white);
};
class piece
{
    public:
        Sprite sprite;
        int pos_x, pos_y;
        float row,column;
        bool is_First_Move = true;
        bool is_White;
        bool can_capture = false;
        bool is_Alive = true;
        bool is_Selected  = false;
        vector <Vector2f> possible_moves;

        piece(const Texture &texture, bool is_White) : sprite(texture), is_White(is_White)
        {
        }
    public:
        virtual vector <Vector2f> moves(board& BOARD) = 0;
};
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

bool board::is_not_Friendly(float row, float col, bool is_white)
    {
        piece* piss = getPieceLoc(row,col);
        
        if(piss == nullptr)
        return false;
        
        return piss->is_White == is_white;
    }
class pawn : public piece
{
    private:
        bool can_Promote;
        bool is_En_Passant;

    public:
        pawn(const Texture &texture,bool is_White): piece(texture, is_White)
        {
        }
        vector <Vector2f> moves(board& b) override
        {
            possible_moves.clear();
            int direction = is_White? -1 : 1;
            int newrow = row;
            int newcol = column + direction;
            int newCOL = column + 2* direction;
            int atkROW[] = {newrow - 1, newrow + 1};
            if(!b.is_not_Friendly(newrow, newcol, is_White))
            {
                if(newcol >= 0 or newcol <= 7)
                    possible_moves.push_back(b.get_Position(newrow, newcol));
            }

            if(is_First_Move)
                if(!b.is_not_Friendly(row,column + 2 * direction, is_White))
                    possible_moves.push_back(b.get_Position(newrow, newCOL));

            for(int i = 0; i < 2; i++ )
            {
                if(b.is_not_Friendly(atkROW[i], newcol, !is_White))
                {
                    (i % 2 == 0)? atkROW[i] = newrow - 1 : newrow + 1;
                    if(newcol >= 0 or newcol <= 7)
                    {
                        possible_moves.push_back(b.get_Position(atkROW[i], newcol));
                    }
                }
            }

            Vector2f pos = {row, column};
            // Promotion
            if(pos.x == 7.f or pos.y == 0.f)
                can_Promote = true;

            return possible_moves;
        }
};
class rook : public piece
{
    public:
        rook(const Texture &texture, bool is_White): piece(texture, is_White)
        {
        }    
    public:
        int dirx[4] = {1, 0, -1, 0};
        int diry[4] = {0, 1, 0, -1};
        vector <Vector2f> moves(board& b) override
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
                        if(!b.is_not_Friendly(newrow, newcol, is_White))
                        {
                            possible_moves.push_back(b.get_Position( newrow, newcol));
                        }
                        else
                        {
                            break;
                        }
                        if(b.is_not_Friendly(newrow, newcol, !is_White))
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
};
class knight : public piece
{
    public:
        knight(const Texture &texture, bool is_White): piece(texture, is_White)
        {
        }
    public:
        int dirx[8] = {2, 2, -2, -2, -1, -1, 1, 1};
        int diry[8] = {1, -1, 1, -1, 2, -2, 2, -2};
        vector <Vector2f> moves(board& b) override
        {
            possible_moves.clear();
            for(int i = 0; i < 8; i++)
            {
                int newrow = row + dirx[i];
                int newcol = column + diry[i];

                if(newrow <= 7 and newcol <= 7 and newrow >= 0 and newcol >= 0)
                {
                    if(!b.is_not_Friendly(newrow, newcol, is_White))
                    {
                        possible_moves.push_back(b.get_Position( newrow, newcol));
                    }
                }
            }
        return possible_moves;
        }
    
};
class bishop : public piece
{
    public:
        bishop(const Texture &texture, bool is_White): piece(texture, is_White)
        {
        }
    public:
        int dirx[4] = {1, 1, -1, -1};
        int diry[4] = {1, -1, 1, -1};

        vector <Vector2f> moves(board& b) override
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
                        if(!b.is_not_Friendly(newrow, newcol, is_White))
                        {
                            possible_moves.push_back(b.get_Position(newrow, newcol));
                        }
                        else
                        {
                            break;
                        }
                        if(b.is_not_Friendly(newrow, newcol, !is_White))
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
};
class queen : public piece
{
   public:
       queen(const Texture &texture, bool is_White): piece(texture, is_White)
        {
        }
    public:
        int dirx[8] = {1, 1, -1, -1, 1, 0, -1, 0};
        int diry[8] = {1, -1, 1, -1, 0, 1, 0, -1};
        
        vector <Vector2f> moves(board& b) override
        {
            possible_moves.clear();
            for(int d = 0; d < 8; d++)
            {
                for(int i = 1; i <= 8; i++)
                {
                    int newrow = row + (dirx[d]*i);
                    int newcol = column + (diry[d]*i);

                    if(newrow <= 7 and newcol <= 7 and newrow >= 0 and newcol >= 0)
                    {
                        if(!b.is_not_Friendly(newrow, newcol, is_White))
                        {
                            possible_moves.push_back(b.get_Position( newrow, newcol));
                        }
                        else
                        {
                            break;
                        }
                        if(b.is_not_Friendly(newrow, newcol, !is_White))
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
};
class king : public piece
{
    public:
        king(const Texture &texture, bool is_White): piece(texture, is_White)
        {
        }
    public:
        int dirx[8] = {1, 1, -1, -1, 0, 0, 1, -1};
        int diry[8] = {1, -1, 1, -1, 1, -1, 0, 0};

        vector <Vector2f> moves(board& b) override
        {
            possible_moves.clear();
            for(int i = 0; i < 8; i++)
            {
                int newrow = row + dirx[i];
                int newcol = column + diry[i];

                if(newrow <= 7 and newcol <= 7 and newrow >= 0 and newcol >= 0)
                {
                    if(!b.is_not_Friendly(newrow, newcol, is_White))
                    {
                        possible_moves.push_back(b.get_Position( newrow, newcol));
                    }
                }

            }
            return possible_moves;
        }
};
int main()
{
// render window for the chess board
    RenderWindow window(VideoMode({ 1280 , 800 }), "Chess Game");
    board b;

// Initiazing a white side texture object
    Texture whitepawntexture("piece_images/white_pawn.png");
    Texture whiterooktexture("piece_images/white_rook.png");
    Texture whiteknighttexture("piece_images/white_knight.png");
    Texture whitebishoptexture("piece_images/white_bishop.png");
    Texture whitequeentexture("piece_images/white_queen.png");
    Texture whitekingtexture("piece_images/white_king.png");

// Initiazing a black side texture object
    Texture blackpawntexture("piece_images/black_pawn.png");
    Texture blackrooktexture("piece_images/black_rook.png");
    Texture blackknighttexture("piece_images/black_knight.png");
    Texture blackbishoptexture("piece_images/black_bishop.png");
    Texture blackqueentexture("piece_images/black_queen.png");
    Texture blackkingtexture("piece_images/black_king.png");

    Texture move_highlight("piece_images/Move_highlight.png");
    Sprite Highlight(move_highlight);
// Importing white piece sprite
    vector<pawn> whitepawn;
    for(int i = 0; i < 8; i++)
    {
        whitepawn.emplace_back(whitepawntexture, true);
    }
    for(int i = 0; i < 8; i++)
    {   
        whitepawn[i].row = i;
        whitepawn[i].column = 6;
        whitepawn[i].sprite.setPosition(b.get_Position(i, 6));
        whitepawn[i].sprite.setScale({0.1855f, 0.1855f});
    }
    vector<rook> whiterook;
    for(int i = 0; i < 2; i++)
    {
        whiterook.emplace_back(whiterooktexture, true);
    }
    for(int i = 0; i < 2; i++)
    {
        whiterook[i].row = i * 7;
        whiterook[i].column = 7;
        whiterook[i].sprite.setPosition(board::get_Position(i*7,7));
        whiterook[i].sprite.setScale({0.1855f, 0.1855f});
    }
    vector<knight> whiteknight;
    for(int i = 0; i < 2; i++)
    {
        whiteknight.emplace_back(whiteknighttexture, true);
    }
    for(int i = 0; i < 2; i++)
    {   if(i == 0)
        {
            whiteknight[i].row = 1;
            whiteknight[i].column = 7;
            whiteknight[i].sprite.setPosition(board::get_Position(1, 7));}
        else
        {
            whiteknight[i].row = i * 6;
            whiteknight[i].column = 7;
            whiteknight[i].sprite.setPosition(board::get_Position(i*6, 7));
        }
        whiteknight[i].sprite.setScale({0.1855f, 0.1855f});
    }
    vector<bishop> whitebishop;
    for(int i = 0; i < 2; i++)
    {
        whitebishop.emplace_back(whitebishoptexture, true);
    }
    for(int i = 0; i < 2; i++)
    {   
        if(i == 0)
        {
            whitebishop[i].row = 2;
            whitebishop[i].column = 7;
            whitebishop[i].sprite.setPosition(board::get_Position(2, 7));
        }
       
        else
        {
            whitebishop[i].row = i * 5;
            whitebishop[i].column = 7;
            whitebishop[i].sprite.setPosition(board::get_Position(i * 5, 7));
        }
        whitebishop[i].sprite.setScale({0.1855f, 0.1855f});
    }
    vector<queen> whitequeen;
    for(int i = 0; i < 1; i++)
    {
        whitequeen.emplace_back(whitequeentexture, true);
    }
    whitequeen[0].row = 4;
    whitequeen[0].column = 7;
    whitequeen[0].sprite.setPosition(board::get_Position(4, 7));
    whitequeen[0].sprite.setScale({0.1855f, 0.1855f});

    vector<king> whiteking;
    for(int i = 0; i < 1; i++)
    {
        whiteking.emplace_back(whitekingtexture, true);
    }
    whiteking[0].row = 3;
    whiteking[0].column = 7;
    whiteking[0].sprite.setPosition(board::get_Position(3, 7));
    whiteking[0].sprite.setScale({0.1855f, 0.1855f});
    
// Importing black piece sprite
    vector<pawn> blackpawn;
    for(int i = 0; i < 8; i++)
    {
        blackpawn.emplace_back(blackpawntexture, false);
    }
    for(int i = 0; i < 8; i++)
    {
        blackpawn[i].row = i;
        blackpawn[i].column = 1;
        blackpawn[i].sprite.setPosition(board::get_Position(i, 1));
        blackpawn[i].sprite.setScale({0.1855f, 0.1855f});
    }
    vector<rook> blackrook;
    for(int i = 0; i < 2; i++)
    {
        blackrook.emplace_back(blackrooktexture, false);
    }
    for(int i = 0; i < 2; i++)
    {
        blackrook[i].row = i * 7;
        blackrook[i].column = 0;
        blackrook[i].sprite.setPosition(board::get_Position(i * 7, 0));
        blackrook[i].sprite.setScale({0.1855f, 0.1855f});
    }
    vector<knight> blackknight;
    for(int i = 0; i < 2; i++)
    {
        blackknight.emplace_back(blackknighttexture, false);
    }
    for(int i = 0; i < 2; i++)
    {   if(i == 0)
        {
            blackknight[i].row = 1;
            blackknight[i].column = 0;
            blackknight[i].sprite.setPosition(board::get_Position(1, 0));
        }
        else
        {
            blackknight[i].row = i * 6;
            blackknight[i].column = 0;
            blackknight[i].sprite.setPosition(board::get_Position(i * 6, 0));
        }
        blackknight[i].sprite.setScale({0.1855f, 0.1855f});
    }
    vector<bishop> blackbishop;
    for(int i = 0; i < 2; i++)
    {
        blackbishop.emplace_back(blackbishoptexture, false);
    }
    for(int i = 0; i < 2; i++)
    {   if(i == 0)
        {
            blackbishop[i].row = 2;
            blackbishop[i].column = 0;
            blackbishop[i].sprite.setPosition(board::get_Position(2, 0));
        }
        else
        {
            blackbishop[i].row = i * 5;
            blackbishop[i].column = 0;
            blackbishop[i].sprite.setPosition(board::get_Position(i * 5, 0));
        }
        blackbishop[i].sprite.setScale({0.1855f, 0.1855f});
    }
    vector<queen> blackqueen;
    for(int i = 0; i < 1; i++)
    {
        blackqueen.emplace_back(blackqueentexture, false);
    }
    blackqueen[0].row = 4;
    blackqueen[0].column = 0;
    blackqueen[0].sprite.setPosition(board::get_Position(4, 0));
    blackqueen[0].sprite.setScale({0.1855f, 0.1855f});

    vector<king> blackking;
    for(int i = 0; i < 1; i++)
    {
        blackking.emplace_back(blackkingtexture, false);
    }
    blackking[0].row = 3;
    blackking[0].column = 0;
    blackking[0].sprite.setPosition(board::get_Position(3,0));
    blackking[0].sprite.setScale({0.1855f, 0.1855f});

// Storing white pieces in a vector array
    for(auto& pawn : whitepawn)
    {
        b.whitepiece.push_back(&pawn);
    }
    for(auto& knight : whiteknight)
    {
        b.whitepiece.push_back(&knight);
    }
    for(auto& bishop : whitebishop)
    {
        b.whitepiece.push_back(&bishop);
    }
    for(auto& rook : whiterook)
    {
        b.whitepiece.push_back(&rook);
    }
    for(auto& queen : whitequeen)
    {
        b.whitepiece.push_back(&queen);
    }
    for(auto& king : whiteking)
    {
        b.whitepiece.push_back(&king);
    }
// Storing black pieces in a vector array
    for(auto& pawn : blackpawn)
    {
        b.blackpiece.push_back(&pawn);
    }
    for(auto& knight : blackknight)
    {
        b.blackpiece.push_back(&knight);
    }
    for(auto& bishop : blackbishop)
    {
        b.blackpiece.push_back(&bishop);
    }
    for(auto& rook : blackrook)
    {
        b.blackpiece.push_back(&rook);
    }
    for(auto& queen : blackqueen)
    {
        b.blackpiece.push_back(&queen);
    }
    for(auto& king : blackking)
    {
        b.blackpiece.push_back(&king);
    }


// Declare a font object to load font style
    Font font;

// File error handling
    if(!font.openFromFile("times.ttf"))
    {
        return -1;
    }
    Text text(font, string(1,'A'));
    text.setCharacterSize(20);
// creates a square shape for chess board
    RectangleShape Square({95,95});

// creates a rectangle for the inner frame of the chess board
    RectangleShape Inner_Frame({774 , 776});

// creates a square for the outer frame of the chess board
    RectangleShape Outer_Frame({ 795 , 800 });

    RectangleShape Board_Border({ 764 , 765 });
    piece* selectedpiece = nullptr;
    vector <Vector2f> highlightmoves;
    bool SELECTED;
    int turn = 0;
// Event handling...
    while(window.isOpen())
    {
        while(optional event = window.pollEvent())
        {
            if(event->is<Event::Closed>())
            {
                window.close();
            }
            if(event->is<Event::MouseButtonPressed>())
            {
                auto * mb = event->getIf<Event::MouseButtonPressed>();
                if(mb->button == Mouse::Button::Left)
                {
                    Vector2i mousepixel = Mouse::getPosition(window);
                    Vector2f mousepos = window.mapPixelToCoords(mousepixel);
                    vector <piece*>& active = (turn % 2 == 0)?b.whitepiece : b.blackpiece;
                    bool moved = false;

                    if(selectedpiece != nullptr)
                    {
                        for(auto& k : highlightmoves)
                        {
                            Highlight.setPosition(k);
                            if(Highlight.getGlobalBounds().contains(mousepos))
                            {
                                Vector2f idx = b.get_Index(k.x,k.y);
                                selectedpiece->row = idx.x;
                                selectedpiece->column = idx.y;
                                selectedpiece->is_First_Move = false;
                                selectedpiece->sprite.setPosition(b.get_Position(static_cast<int>(idx.x),static_cast<int>(idx.y)));
                                selectedpiece->is_Selected = false;
                                selectedpiece->sprite.setColor(Color::White);
                                selectedpiece = nullptr;
                                highlightmoves.clear();
                                turn++;
                                moved = true;
                                break;
                            }
                        }
                    }
                    if(!moved)
                    {
                        for(piece* p : active)
                        {
                            p->is_Selected = false;
                            p->sprite.setColor(Color::White);
                        }
                        selectedpiece = nullptr;
                        highlightmoves.clear();

                        for(piece* p : active)
                        {
                            if(p->sprite.getGlobalBounds().contains(mousepos))
                            {
                                p->is_Selected = true;
                                selectedpiece = p;
                                highlightmoves = p->moves(b);
                                break;
                            }
                        }
                    }
                    SELECTED = (selectedpiece != nullptr);
                }
            } 
        }

// Outermost frame of the board, no need to change the position as it is already at (0,0)
        Outer_Frame.setFillColor(Color (63, 11, 9));
        window.draw(Outer_Frame); 
        
        // Innermost frame of the board, position is set to (10,10) to create a border effect
        Inner_Frame.setPosition({10,10});
        Inner_Frame.setFillColor(Color(93, 43, 43));
        window.draw(Inner_Frame);
        
// It is made so that the there is a black border separating the chess board and the frame
        Board_Border.setPosition({15,15});
        Board_Border.setFillColor(Color(63, 31, 31));
        window.draw(Board_Border);


/* Loop to render the chess board squares, I set the first square at an unusual 
position so to design a basic fram around the chess board */
        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                Square.setPosition(board::get_Position(i, j));
                Square.setFillColor(((i + j) % 2 == 0) ? Color(223, 215, 200) : Color(168, 66, 45));
                window.draw(Square);
            }
        }

        for(const auto& i : highlightmoves)
        {   
            if(SELECTED)
            {
                Highlight.setPosition(i);
                Sprite highlightshadow = Highlight;
                highlightshadow.setColor(Color(0,0,0,100));
                highlightshadow.move({2.f,2.f});
                window.draw(highlightshadow);
                Highlight.setColor(Color(255,255,255,200));
                window.draw(Highlight);
            }
        }

// To render the sprites
        for(piece* p: b.whitepiece)
        {   
            if(p->is_Selected == true)
            {
                Sprite shadow = p->sprite;
                shadow.setColor(Color(0,0,0,100));
                shadow.move({4.f,4.f});
                window.draw(shadow);
                p->sprite.setColor(Color(255,50,50));
                window.draw(p->sprite);
            }
            else
            {
                Sprite shadow = p->sprite;
                shadow.setColor(Color(0,0,0,100));
                shadow.move({4.f,4.f});
                window.draw(shadow);
                window.draw(p->sprite);
            }
        }
        for(piece* p: b.blackpiece)
        {
            if(p->is_Selected == true)
            {
                Sprite shadow = p->sprite;
                shadow.setColor(Color(0,0,0,100));
                shadow.move({4.f,4.f});
                window.draw(shadow);
                p->sprite.setColor(Color(255,50,50));
                window.draw(p->sprite);
            }
            else
            {
                Sprite shadow = p->sprite;
                shadow.setColor(Color(0,0,0,100));
                shadow.move({4.f,4.f});
                window.draw(shadow);
                window.draw(p->sprite);               
            }
        }

// Drawing chess indexes
for(int j = 0; j <= 1 ; j ++)
{
// Conditional statement to run the loop of numerical indexes only
    if(j == 0)
    {
// Logic to display numerical indexes in the first column and rows 1 to 8
        for(int m = 7; m >= 0; m--)
        {   
// The conditional statement to make the color of the index to alternately switch
            if(m % 2 == 0)
            {   
                text.setFillColor(Color(223, 215, 200));
                text.setPosition(board::set_num_position(m));
                text.setString(to_string(m + 1));
                window.draw(text);
            }
            else
            {
                text.setFillColor(Color(168, 66, 45));
                text.setPosition(board::set_num_position(m));
                text.setString(to_string(m + 1));
                window.draw(text);
            }

        }
    }
// Conditional statement to run the loop of alphabetical indexes only           
    else
    {
// Logic to display alphabetical indexes in the last row and columns A to H
        for(int i = 0; i < 8; i++)
        { 
// The conditional statement to make the color of the index to alternately switch
            if(i % 2 == 0)
            {
                text.setFillColor(Color(223, 215, 200));
                text.setPosition(board::set_text_position(i));
                text.setString(string(1, 'A' + i));
                window.draw(text);
            }
            else
            {
                text.setFillColor(Color(168, 66, 45));
                text.setPosition(board::set_text_position(i));
                text.setString(string(1, 'A' + i));
                window.draw(text);
            }
        }
    }
}
// function in sfml to display the rendered graphics
window.display();
window.clear(Color(232, 212, 190));
}
}