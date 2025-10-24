#include "ChessPiece.hh"
#include "ChessBoard.hh"

using Student::ChessPiece;
using Student::ChessBoard;

ChessPiece::ChessPiece(ChessBoard &/*board*/, Color /*color*/, int /*row*/, int /*column*/)
{
  // No storage here (we're not allowed to edit ChessPiece.hh to add fields).
  // Derived classes keep their own state.
}

// Infer color from the Unicode symbol returned by toString()
Color ChessPiece::getColor()
{
  const char* s = this->toString();
  // White: ♙(E2 99 99), ♖(E2 99 96), ♗(E2 99 97), ♔(E2 99 94)
  // Black: ♟(E2 99 9F), ♜(E2 99 9C), ♝(E2 99 9D), ♚(E2 99 9A)
  unsigned char b2 = (unsigned char)s[2];
  return (b2 == 0x99 || b2 == 0x96 || b2 == 0x97 || b2 == 0x94) ? White : Black;
}

Type ChessPiece::getType()
{
  const char* s = this->toString();
  unsigned char b2 = (unsigned char)s[2];
  if (b2 == 0x99 || b2 == 0x9F) return Pawn;
  if (b2 == 0x96 || b2 == 0x9C) return Rook;
  if (b2 == 0x97 || b2 == 0x9D) return Bishop;
  return King;
}

// Part 1 doesn't require positional getters to be meaningful.
// Safe sentinels + no-op setter.
int  ChessPiece::getRow()                { return -1; }
int  ChessPiece::getColumn()             { return -1; }
void ChessPiece::setPosition(int, int)   { /* no-op in Part 1 */ }
