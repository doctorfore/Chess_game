#include "RookPiece.hh"
#include "ChessBoard.hh"

using Student::RookPiece;
using Student::ChessBoard;
using Student::ChessPiece;

static int stepDir(int d){ return (d>0)?1:((d<0)?-1:0); }

RookPiece::RookPiece(ChessBoard &board, Color color, int row, int column)
: ChessPiece(board, color, row, column),
  board_(&board), color_(color), row_(row), col_(column){}

bool RookPiece::canMoveToLocation(int toRow, int toColumn)
{
  if (toRow == row_ && toColumn == col_) return false;

  int dRow = toRow - row_;
  int dCol = toColumn - col_;
  if (!(dRow == 0 || dCol == 0)) return false; // straight only

  int rStep = stepDir(dRow), cStep = stepDir(dCol);
  int r = row_ + rStep, c = col_ + cStep;
  while (r != toRow || c != toColumn)
  {
    if (board_->getPiece(r, c) != nullptr) return false;
    r += rStep; c += cStep;
  }

  ChessPiece *dst = board_->getPiece(toRow, toColumn);
  return (dst == nullptr) || (dst->getColor() != color_);
}

const char *RookPiece::toString()
{
  return (color_ == White) ? "\xE2\x99\x96" : "\xE2\x99\x9C";
}
