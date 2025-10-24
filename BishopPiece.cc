#include "BishopPiece.hh"
#include "ChessBoard.hh"

using Student::BishopPiece;
using Student::ChessBoard;
using Student::ChessPiece;

static int iabs(int x){ return (x<0)?-x:x; }

BishopPiece::BishopPiece(ChessBoard &board, Color color, int row, int column)
: ChessPiece(board, color, row, column),
  m_board(&board), m_color(color), m_row(row), m_col(column)
{}

bool BishopPiece::canMoveToLocation(int toRow, int toColumn)
{
  if (toRow == m_row && toColumn == m_col) return false;

  int dRow = toRow - m_row;
  int dCol = toColumn - m_col;
  if (iabs(dRow) != iabs(dCol)) return false; // diagonal only

  int rStep = (dRow > 0) ? 1 : -1;
  int cStep = (dCol > 0) ? 1 : -1;
  int r = m_row + rStep, c = m_col + cStep;
  while (r != toRow && c != toColumn)
  {
    if (m_board->getPiece(r, c) != nullptr) return false;
    r += rStep; c += cStep;
  }

  ChessPiece *dst = m_board->getPiece(toRow, toColumn);
  return (dst == nullptr) || (dst->getColor() != m_color);
}

const char *BishopPiece::toString()
{
  return (m_color == White) ? "♗" : "♝";
}
