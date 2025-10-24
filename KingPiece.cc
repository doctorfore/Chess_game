#include "KingPiece.hh"
#include "ChessBoard.hh"

using Student::KingPiece;
using Student::ChessBoard;
using Student::ChessPiece;

KingPiece::KingPiece(ChessBoard &board, Color color, int row, int column)
: ChessPiece(board, color, row, column),
  m_board(&board), m_color(color), m_row(row), m_col(column)
{}

bool KingPiece::canMoveToLocation(int, int)
{
  // Part 1: ignore king movement logic
  return false;
}

const char *KingPiece::toString()
{
  return (m_color == White) ? "\xE2\x99\x94" : "\xE2\x99\x9A";
}
