#ifndef __BISHOPPIECE_H__
#define __BISHOPPIECE_H__

#include "ChessPiece.hh"

namespace Student
{
  class BishopPiece : public ChessPiece
  {
  public:
    BishopPiece(ChessBoard &board, Color color, int row, int column);
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
