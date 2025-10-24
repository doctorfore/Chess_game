#include "RookPiece.hh"
#include "ChessBoard.hh"

using Student::RookPiece;
using Student::ChessBoard;
using Student::ChessPiece;

static int stepDir(int d){ return (d>0)?1:((d<0)?-1:0); }

RookPiece::RookPiece(ChessBoard &board, Color color, int row, int column)
: ChessPiece(board, color, row, column),
  m_board(&board), m_color(color), m_row(row), m_col(column)
{}

bool RookPiece::canMoveToLocation(int toRow, int toColumn)
{
  if (toRow == m_row && toColumn == m_col) return false;

  int dRow = toRow - m_row;
  int dCol = toColumn - m_col;
  if (!(dRow == 0 || dCol == 0)) return false; // straight only

  int rStep = stepDir(dRow), cStep = stepDir(dCol);
  int r = m_row + rStep, c = m_col + cStep;
  while (r != toRow || c != toColumn)
  {
    if (m_board->getPiece(r, c) != nullptr) return false;
    r += rStep; c += cStep;
  }

  ChessPiece *dst = m_board->getPiece(toRow, toColumn);
  return (dst == nullptr) || (dst->getColor() != m_color);
}

const char *RookPiece::toString()
{
    return (m_color == White) ? "\xE2\x99\x96" : "\xE2\x99\x9C";
}
