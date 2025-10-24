#include "ChessBoard.hh"
#include "PawnPiece.hh"
#include "RookPiece.hh"
#include "BishopPiece.hh"
#include "KingPiece.hh"

using Student::ChessBoard;
using Student::ChessPiece;
using Student::PawnPiece;
using Student::RookPiece;
using Student::BishopPiece;
using Student::KingPiece;

std::ostringstream ChessBoard::displayBoard()
{
    std::ostringstream outputString;
    // top scale
    outputString << "  ";
    for (int i = 0; i < numCols; i++){
        outputString << i << " ";
    }
    outputString << std::endl << "  ";
    // top border
    for (int i = 0; i < numCols; i++){
        outputString << "– ";
    }
    outputString << std::endl;

    for (int row = 0; row < numRows; row++){
        outputString << row << "|";
        for (int column = 0; column < numCols; column++){
            ChessPiece *piece = board.at(row).at(column);
            outputString << (piece == nullptr ? " " : piece->toString()) << " ";
        }
        outputString << "|" << std::endl;
    }

    // bottom border
    outputString << "  ";
    for (int i = 0; i < numCols; i++){
        outputString << "– ";
    }
    outputString << std::endl << std::endl;

    return outputString;
}

//Local helper
static bool inBounds(ChessBoard &b, int r, int c)
{
    return (0 <= r && r < b.getNumRows() && 0 <= c && c < b.getNumCols());
}

ChessBoard::ChessBoard(int numRow, int numCol)
: numRows(numRow), numCols(numCol), turn(White),
  board(std::vector<std::vector<ChessPiece *>>(numRow, std::vector<ChessPiece *>(numCol, nullptr)))
{}

void ChessBoard::createChessPiece(Color col, Type ty, int startRow, int startColumn)
{
    ChessPiece *&slot = board.at(startRow).at(startColumn);
    if (slot) { delete slot; slot = nullptr; }

    switch (ty)
    {
        case Pawn:   slot = new PawnPiece(*this, col, startRow, startColumn); break;
        case Rook:   slot = new RookPiece(*this, col, startRow, startColumn); break;
        case Bishop: slot = new BishopPiece(*this, col, startRow, startColumn); break;
        case King:   slot = new KingPiece(*this, col, startRow, startColumn); break;
    }
}

bool ChessBoard::isValidMove(int fromRow, int fromColumn, int toRow, int toColumn)
{
    if (!inBounds(*this, fromRow, fromColumn)) return false;
    if (!inBounds(*this, toRow, toColumn))     return false;
    if (fromRow == toRow && fromColumn == toColumn) return false;

    ChessPiece *src = board.at(fromRow).at(fromColumn);
    if (src == nullptr) return false;

    ChessPiece *dst = board.at(toRow).at(toColumn);
    if (dst != nullptr && dst->getColor() == src->getColor()) return false;

    return src->canMoveToLocation(toRow, toColumn);
}

// destructor
namespace Student {
ChessBoard::~ChessBoard()
{
    // delete every allocated piece
    for (int r = 0; r < numRows; ++r) {
        for (int c = 0; c < numCols; ++c) {
            ChessPiece* p = board.at(r).at(c);
            if (p) { delete p; board.at(r).at(c) = nullptr; }
        }
    }
}
}

// for local tester
bool ChessBoard::movePiece(int, int, int, int) { return false; }
bool ChessBoard::isPieceUnderThreat(int, int)  { return false; }
