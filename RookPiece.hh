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

    int  getRowImpl() const { return row_; }
    int  getColImpl() const { return col_; }
    void setPosImpl(int r, int c) { row_ = r; col_ = c; }

  private:
    ChessBoard *board_;
    Color color_;
    int row_;
    int col_;
  };
}

#endif
