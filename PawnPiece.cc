#include "PawnPiece.hh"
#include "ChessBoard.hh"

using Student::PawnPiece;
using Student::ChessBoard;
using Student::ChessPiece;

PawnPiece::PawnPiece(ChessBoard &board, Color color, int row, int column)
: ChessPiece(board, color, row, column),
  board_(&board), color_(color), row_(row), col_(column){}

bool PawnPiece::canMoveToLocation(int toRow, int toColumn)
{
  if (toRow == row_ && toColumn == col_) return false;

  int dir  = (color_ == White) ? -1 : 1; // White up, Black down
  int dRow = toRow - row_;
  int dCol = toColumn - col_;

  ChessPiece *dst = board_->getPiece(toRow, toColumn);

  // Forward moves (no capture)
  if (dCol == 0)
  {
    // One step
    if (dRow == dir && dst == nullptr) return true;

    // Two steps from starting rank
    int startRow = (color_ == Black) ? 1 : (board_->getNumRows() - 2);
    if (row_ == startRow && dRow == 2*dir)
    {
      int midRow = row_ + dir;
      if (board_->getPiece(midRow, col_) == nullptr && dst == nullptr) return true;
    }
    return false;
  }

  // Diagonal capture
  if (dRow == dir && (dCol == 1 || dCol == -1))
  {
    return (dst != nullptr) && (dst->getColor() != color_);
  }

  return false;
}

const char *PawnPiece::toString()
{
  return (color_ == White) ? "\xE2\x99\x99" : "\xE2\x99\x9F";
}
