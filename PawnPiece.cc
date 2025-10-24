#include "PawnPiece.hh"
#include "ChessBoard.hh"

using Student::PawnPiece;
using Student::ChessBoard;
using Student::ChessPiece;

PawnPiece::PawnPiece(ChessBoard &board, Color color, int row, int column)
: ChessPiece(board, color, row, column),
  m_board(&board), m_color(color), m_row(row), m_col(column)
{}

bool PawnPiece::canMoveToLocation(int toRow, int toColumn)
{
  if (toRow == m_row && toColumn == m_col) return false;

  int dir  = (m_color == White) ? -1 : 1; // White up, Black down
  int dRow = toRow - m_row;
  int dCol = toColumn - m_col;

  ChessPiece *dst = m_board->getPiece(toRow, toColumn);

  // Forward moves (no capture)
  if (dCol == 0)
  {
    // One step
    if (dRow == dir && dst == nullptr) return true;

    // Two steps from starting rank
    int startRow = (m_color == Black) ? 1 : (m_board->getNumRows() - 2);
    if (m_row == startRow && dRow == 2*dir)
    {
      int midRow = m_row + dir;
      if (m_board->getPiece(midRow, m_col) == nullptr && dst == nullptr) return true;
    }
    return false;
  }

  // Diagonal capture
  if (dRow == dir && (dCol == 1 || dCol == -1))
  {
    return (dst != nullptr) && (dst->getColor() != m_color);
  }

  return false;
}

const char *PawnPiece::toString()
{
  return (m_color == White) ? "\xE2\x99\x99" : "\xE2\x99\x9F";
}
