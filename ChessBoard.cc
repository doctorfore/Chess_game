#include "ChessBoard.hh"
#include "PawnPiece.hh"
#include "RookPiece.hh"
#include "BishopPiece.hh"
#include "KingPiece.hh"
#include <algorithm>



using Student::ChessBoard;
using Student::ChessPiece;

std::ostringstream ChessBoard::displayBoard() {
    std::ostringstream outputString;
    // ... keep previous displayBoard
    return outputString;
}



// check boundry functions 
bool ChessBoard::inBounds(int r, int c) const {
    return (r >= 0 && r < numRows && c >= 0 && c < numCols);
}

ChessBoard::ChessBoard(int numRow, int numCol)
: numRows(numRow), numCols(numCol), turn(White),
  board(std::vector<std::vector<ChessPiece *>>(numRow, std::vector<ChessPiece *>(numCol, nullptr)))
{}

void ChessBoard::createChessPiece(Color col, Type ty, int startRow, int startColumn) {
    ChessPiece *&slot = board.at(startRow).at(startColumn);
    if (slot) { delete slot; slot = nullptr; }

    switch (ty) {
        case Pawn:   slot = new PawnPiece(*this, col, startRow, startColumn); break;
        case Rook:   slot = new RookPiece(*this, col, startRow, startColumn); break;
        case Bishop: slot = new BishopPiece(*this, col, startRow, startColumn); break;
        case King:   slot = new KingPiece(*this, col, startRow, startColumn); break;
    }
}

// path check 
bool ChessBoard::isPathClear(int fromRow, int fromCol, int toRow, int toCol) {
    int dRow = toRow - fromRow;
    int dCol = toCol - fromCol;
    
    // confirm moving directions 
    int rowStep = (dRow == 0) ? 0 : (dRow > 0 ? 1 : -1);
    int colStep = (dCol == 0) ? 0 : (dCol > 0 ? 1 : -1);
    
    int currentRow = fromRow + rowStep;
    int currentCol = fromCol + colStep;
    
    // check all blocks in the path 
    while (currentRow != toRow || currentCol != toCol) {
        if (!inBounds(currentRow, currentCol) || board.at(currentRow).at(currentCol) != nullptr) {
            return false; // path being bloced
        }
        currentRow += rowStep;
        currentCol += colStep;
    }
    
    return true;
}

// remove chess
void ChessBoard::removePiece(int row, int col) {
    ChessPiece*& piece = board.at(row).at(col);
    if (piece != nullptr) {
        delete piece;
        piece = nullptr;
    }
}

bool ChessBoard::isValidMove(int fromRow, int fromColumn, int toRow, int toColumn) {
    if (!inBounds(fromRow, fromColumn)) return false;
    if (!inBounds(toRow, toColumn))     return false;
    if (fromRow == toRow && fromColumn == toColumn) return false;

    ChessPiece *src = board.at(fromRow).at(fromColumn);
    if (src == nullptr) return false;

    ChessPiece *dst = board.at(toRow).at(toColumn);
    if (dst != nullptr && dst->getColor() == src->getColor()) return false;

    // check path for chess moving on same line 
    Type pieceType = src->getType();
    if (pieceType == Rook || pieceType == Bishop) {
        if (!isPathClear(fromRow, fromColumn, toRow, toColumn)) {
            return false;
        }
    }

    return src->canMoveToLocation(toRow, toColumn);
}

//  movePiece
bool ChessBoard::movePiece(int fromRow, int fromColumn, int toRow, int toColumn) {
    // 1. basic check
    if (!isValidMove(fromRow, fromColumn, toRow, toColumn)) {
        return false;
    }
    
    ChessPiece* movingPiece = board.at(fromRow).at(fromColumn);
    
    // 2. check round 
    if (movingPiece->getColor() != turn) {
        return false;
    }
    
    // 3. perform moving 
    ChessPiece* targetPiece = board.at(toRow).at(toColumn);
    
    if (targetPiece != nullptr) {
        removePiece(toRow, toColumn);
    }
    
    board.at(toRow).at(toColumn) = movingPiece;
    board.at(fromRow).at(fromColumn) = nullptr;
    
    movingPiece->setPosition(toRow, toColumn);
    
    turn = (turn == White) ? Black : White;
    
    return true;
}

// isPieceUnderThreat
bool ChessBoard::isPieceUnderThreat(int row, int column) {
    ChessPiece* targetPiece = board.at(row).at(column);
    if (targetPiece == nullptr) {
        return false;
    }
    
    Color targetColor = targetPiece->getColor();
    Color opponentColor = (targetColor == White) ? Black : White;
    
    for (int r = 0; r < numRows; r++) {
        for (int c = 0; c < numCols; c++) {
            ChessPiece* attacker = board.at(r).at(c);
            
            if (attacker != nullptr && attacker->getColor() == opponentColor) {
                if (isValidMove(r, c, row, column)) {
                    return true;
                }
            }
        }
    }
    
    return false;
}

// classifier functions 
ChessBoard::~ChessBoard() {
    for (int r = 0; r < numRows; ++r) {
        for (int c = 0; c < numCols; ++c) {
            ChessPiece* p = board.at(r).at(c);
            if (p) {
                delete p;
                board.at(r).at(c) = nullptr;
            }
        }
    }
}
