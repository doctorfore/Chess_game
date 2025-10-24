#ifndef CHESSPIECE_H
#define CHESSPIECE_H

#include <vector>

namespace Student
{
    enum Color {White, Black};
    
    class ChessBoard;
    
    class ChessPiece
    {
    protected:
        ChessBoard* _board;
        Color _color;
        int _row;
        int _col;
        
    public:
        ChessPiece(ChessBoard* board, Color color, int row, int col);
        virtual ~ChessPiece() = default;
        
        Color getColor();
        int getRow();
        int getCol();
        void setPosition(int row, int col);
        
        virtual char getLabel() = 0;
        virtual bool isValidMove(int toRow, int toCol) = 0;
        virtual bool canMoveToLocation(int toRow, int toCol);
    };
}


#endif