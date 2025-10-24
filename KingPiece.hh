#ifndef __KINGPIECE_H__
#define __KINGPIECE_H__

#include "ChessPiece.hh"

namespace Student
{
  class KingPiece : public ChessPiece
  {
  public:
    KingPiece(ChessBoard &board, Color color, int row, int column);
    bool canMoveToLocation(int toRow, int toColumn) override; // Part 1: always false
    const char *toString() override;

  private:
    ChessBoard *m_board;
    Color m_color;
    int m_row;
    int m_col;
  };
}

#endif
