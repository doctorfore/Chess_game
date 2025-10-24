#ifndef _ROOKPIECE_H__
#define _ROOKPIECE_H__

#include "ChessPiece.hh"

namespace Student
{
  class RookPiece : public ChessPiece
  {
  public:
    RookPiece(ChessBoard &board, Color color, int row, int column);
    bool canMoveToLocation(int toRow, int toColumn) override;
    const char *toString() override;

  private:
    ChessBoard *m_board;
    Color m_color;
    int m_row;
    int m_col;
  };
}

#endif
