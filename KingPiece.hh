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
