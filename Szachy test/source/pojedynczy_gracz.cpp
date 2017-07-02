#include "pojedynczy_gracz.h"



PojedynczyGracz::PojedynczyGracz()
{
  sytuacja[8][8] = { 0 };
}


PojedynczyGracz::~PojedynczyGracz()
{
}

void PojedynczyGracz::ustawWrtosci(int tablica[8][8])
{
  for (int i = 0; i < 8; i++)
  {
    for (int j = 0; j < 8; j++)
    {
      sytuacja[i][j] = tablica[i][j];
     }
  }
}

int  PojedynczyGracz::Wczytaj(int x, int y)
{
  return sytuacja[x][y];
}