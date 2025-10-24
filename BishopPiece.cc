#include "BishopPiece.hh"
#include "ChessBoard.hh"

using Student::BishopPiece;
using Student::ChessBoard;
using Student::ChessPiece;

static int iabs(int x){ return (x<0)?-x:x; }

BishopPiece::BishopPiece(ChessBoard &board, Color color, int row, int column)
: ChessPiece(board, color, row, column),
  board_(&board), color_(color), row_(row), col_(column){}

bool BishopPiece::canMoveToLocation(int toRow, int toColumn)
{
  if (toRow == row_ && toColumn == col_) return false;

  int dRow = toRow - row_;
  int dCol = toColumn - col_;
  if (iabs(dRow) != iabs(dCol)) return false; // diagonal only

  int rStep = (dRow > 0) ? 1 : -1;
  int cStep = (dCol > 0) ? 1 : -1;
  int r = row_ + rStep, c = col_ + cStep;
  while (r != toRow && c != toColumn)
  {
    if (board_->getPiece(r, c) != nullptr) return false;
    r += rStep; c += cStep;
  }

  ChessPiece *dst = board_->getPiece(toRow, toColumn);
  return (dst == nullptr) || (dst->getColor() != color_);
}

const char *BishopPiece::toString()
{
  return (color_ == White) ? "\xE2\x99\x97" : "\xE2\x99\x9D";
}
