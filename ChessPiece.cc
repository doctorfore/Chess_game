#include "ChessPiece.hh"
#include "ChessBoard.hh"
#include "PawnPiece.hh"
#include "RookPiece.hh"
#include "BishopPiece.hh"
#include "KingPiece.hh"

using Student::ChessPiece;
using Student::ChessBoard;
using Student::PawnPiece;
using Student::RookPiece;
using Student::BishopPiece;
using Student::KingPiece;

ChessPiece::ChessPiece(ChessBoard &/*board*/, Color /*color*/, int /*row*/, int /*column*/) {}

Color ChessPiece::getColor()
{
  const char* s = this->toString();
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

int ChessPiece::getRow()
{
  if (auto p = dynamic_cast<PawnPiece*>(this))   return p->getRowImpl();
  if (auto p = dynamic_cast<RookPiece*>(this))   return p->getRowImpl();
  if (auto p = dynamic_cast<BishopPiece*>(this)) return p->getRowImpl();
  if (auto p = dynamic_cast<KingPiece*>(this))   return p->getRowImpl();
  return -1;
}

int ChessPiece::getColumn()
{
  if (auto p = dynamic_cast<PawnPiece*>(this))   return p->getColImpl();
  if (auto p = dynamic_cast<RookPiece*>(this))   return p->getColImpl();
  if (auto p = dynamic_cast<BishopPiece*>(this)) return p->getColImpl();
  if (auto p = dynamic_cast<KingPiece*>(this))   return p->getColImpl();
  return -1;
}

void ChessPiece::setPosition(int row, int column)
{
  if (auto p = dynamic_cast<PawnPiece*>(this))   { p->setPosImpl(row, column); return; }
  if (auto p = dynamic_cast<RookPiece*>(this))   { p->setPosImpl(row, column); return; }
  if (auto p = dynamic_cast<BishopPiece*>(this)) { p->setPosImpl(row, column); return; }
  if (auto p = dynamic_cast<KingPiece*>(this))   { p->setPosImpl(row, column); return; }
}
