#include "plansza.h"



int a[8][8] = {
  {-2,-1,0,0,0,0,1,2 },
  {-3,-1,0,0,0,0,1,3 },
  {-4,-1,0,0,0,0,1,4 },
  {-5,-1,0,0,0,0,1,5 },
  {-6,-1,0,0,0,0,1,6 },
  {-4,-1,0,0,0,0,1,4 },
  {-3,-1,0,0,0,0,1,3 },
  {-2,-1,0,0,0,0,1,2 }
};

int b[8][8] = {
  {0,1,0,1,0,1,0,1},
  {1,0,1,0,1,0,1,0},
  {0,1,0,1,0,1,0,1},
  {1,0,1,0,1,0,1,0},
  {0,1,0,1,0,1,0,1},
  {1,0,1,0,1,0,1,0},
  {0,1,0,1,0,1,0,1},
  {1,0,1,0,1,0,1,0}
};



Plansza::Plansza()
{
  for (int i = 0; i < 8; i++)
  {
    for (int j = 0; j < 8; j++)
    {
      polozenie_[i][j] = a[i][j];
      kolor_pola_[i][j] = b[i][j];
      ruch_figury_[i][j] = false;
      bicie_w_przelocie_biale[i][j] = false;
      bicie_w_przelocie_czarne[i][j] = false;
      tablicaSzacha[i][j] = false;
    }
  }


}

Plansza::~Plansza()
{
}

void Plansza::Zresetuj_(Plansza &aktualna)     // tworzy nowy obiekt zeby ustawic przez konstruktor domyslne ustawienia i podstawia pod aktualny stan gry
{
  Plansza a;
  aktualna = a;
}

bool Plansza::ustaw(int figura, int x, int y)         //ustawia wartosc na planszy i zwraca czy sie udalo
{
  polozenie_[x][y] = figura;
  return true;
}

int Plansza::pobierz(int x, int y)          //umozliwia pobranie kto jest w tym miejsciu
{
  return polozenie_[x][y];
}

int Plansza::kolor_pola(int x, int y)
{
  return kolor_pola_[x][y];
}

void Plansza::Oblicz_ruch(int x, int y)
{
  for (int i = 0; i < 8; i++)
  {
    for (int j = 0; j < 8; j++)
    {
      ruch_figury_[i][j] = false;
    }
  }
    switch (polozenie_[x][y])
    {
    case 2:
    case -2:
      RuchWieza(x,y);

      break;
    case 3:
    case -3:
      RuchKonik(x, y);   

      break;
    case 4:
    case -4:
      RuchGoniec(x, y);

      break;
    case 5:
    case -5:
      RuchWieza(x, y);
      RuchGoniec(x, y);

      break;
    case 6:
    case -6:
      RuchKrol(x, y);    

      break;
    }

    if (polozenie_[x][y] == 1)
    {
      if (y == 6)
      {
        if(polozenie_[x][y-1]==0)
        ruch_figury_[x][y - 1] = true;
        if(polozenie_[x][y-2]==0 && polozenie_[x][y - 1] == 0)
        ruch_figury_[x][y - 2] = true;
        if (x - 1 >= 0 && polozenie_[x - 1][y - 1] < 0)
          ruch_figury_[x - 1][y - 1] = true;
        if (x + 1 <8 && polozenie_[x +1][y - 1] < 0)
          ruch_figury_[x + 1][y - 1] = true;
      }
      else
      {
        if (polozenie_[x][y - 1] == 0)
          ruch_figury_[x][y - 1] = true;
        if (x - 1 >= 0 && polozenie_[x - 1][y - 1] < 0)
          ruch_figury_[x - 1][y - 1] = true;
        if (x + 1 <8 && polozenie_[x + 1][y - 1] < 0)
          ruch_figury_[x + 1][y - 1] = true;
        if (x - 1 >= 0 && bicie_w_przelocie_czarne[x-1][y-1]==true && polozenie_[x - 1][y - 1] == 0)
          ruch_figury_[x - 1][y - 1] = true;
        if (x + 1 <8 && bicie_w_przelocie_czarne[x + 1][y - 1] == true && polozenie_[x -+1][y - 1] == 0)
          ruch_figury_[x + 1][y - 1] = true;
      }
    }
    if (polozenie_[x][y] == -1)
    {
      if (y == 1)
      {
        if (polozenie_[x][y + 1] == 0)
          ruch_figury_[x][y + 1] = true;
        if (polozenie_[x][y + 2] == 0 && polozenie_[x][y + 1] == 0)
          ruch_figury_[x][y + 2] = true;
        if (x - 1 >= 0 && polozenie_[x - 1][y + 1] > 0)
          ruch_figury_[x - 1][y + 1] = true;
        if (x + 1 <8 && polozenie_[x + 1][y + 1] >0)
          ruch_figury_[x + 1][y + 1] = true;
      }
      else
      {
        if (polozenie_[x][y + 1] == 0)
          ruch_figury_[x][y + 1] = true;
        if (x - 1 >= 0 && polozenie_[x - 1][y + 1] > 0)
          ruch_figury_[x - 1][y + 1] = true;
        if (x + 1 <8 && polozenie_[x + 1][y + 1] >0)
          ruch_figury_[x + 1][y + 1] = true;
        if (x - 1 >= 0 && bicie_w_przelocie_biale[x -1][y + 1] == true && polozenie_[x - 1][y + 1] == 0)
          ruch_figury_[x -1][y + 1] = true;
        if (x + 1 <8 && bicie_w_przelocie_biale[x + 1][y + 1] == true && polozenie_[x + 1][y + 1] ==0)
          ruch_figury_[x + 1][y +1] = true;
      }
    }

    

}

bool Plansza::Sprawdz_ruch(int x, int y)
{
  return ruch_figury_[x][y];
}

void Plansza::RuchWieza(int x, int y)
{
  int pomocx = x;
  int pomocy = y;
  Prawo(pomocx, pomocy);
  Lewo(pomocx, pomocy);
  Gora(pomocx, pomocy);
  Dol(pomocx, pomocy);

}

void Plansza::Prawo(int x, int y)
{
  bool blokada = false;
  while (x < 8 && blokada==false)
  {
    x++;
    if (x < 8)
    {
      if (polozenie_[x][y] == 0)
        ruch_figury_[x][y] = true;
      else
      {
        ruch_figury_[x][y] = true;
        blokada = true;
      }
    }

  }
}

void Plansza::Lewo(int x, int y)
{
  bool blokada = false;
  while (x >=0 && blokada == false)
  {
    x--;
    if (x >=0)
    {
      if (polozenie_[x][y] == 0)
        ruch_figury_[x][y] = true;
      else
      {
        ruch_figury_[x][y] = true;
        blokada = true;
      }
    }

  }
}

void Plansza::Gora(int x, int y)
{
  bool blokada = false;
  while (y >= 0 && blokada == false)
  {
    y--;
    if (y>= 0)
    {
      if (polozenie_[x][y] == 0)
        ruch_figury_[x][y] = true;
      else
      {
        ruch_figury_[x][y] = true;
        blokada = true;
      }
    }

  }
}

void Plansza::Dol(int x, int y)
{
  bool blokada = false;
  while (y <8 && blokada == false)
  {
    y++;
    if (y<8)
    {
      if (polozenie_[x][y] == 0)
        ruch_figury_[x][y] = true;
      else
      {
        ruch_figury_[x][y] = true;
        blokada = true;
      }
    }

  }
}

void Plansza::RuchKrol(int x, int y)
{
  if (x - 1 >= 0)
    ruch_figury_[x - 1][y] = true;
  if (x + 1<8)
    ruch_figury_[x + 1][y] = true;
  if (y + 1 < 8)
    ruch_figury_[x][y + 1] = true;
  if (y - 1 >= 0)
    ruch_figury_[x][y - 1] = true;
  if (y - 1 >= 0 && x + 1<8)
    ruch_figury_[x + 1][y - 1] = true;
  if (y - 1 >= 0 && x - 1 >= 0)
    ruch_figury_[x - 1][y - 1] = true;
  if (y + 1 < 8 && x - 1 >= 0)
    ruch_figury_[x - 1][y + 1] = true;
  if (y + 1 < 8 && x + 1 < 8)
    ruch_figury_[x + 1][y + 1] = true;
}

void Plansza::RuchKonik(int x, int y)
{
  if (y - 1 >= 0 && x - 2 >= 0)
    ruch_figury_[x - 2][y - 1] = true;
  if (y - 1 >= 0 && x +2 <8)
    ruch_figury_[x + 2][y - 1] = true;
  if (y +1 <8 && x - 2 >= 0)
    ruch_figury_[x - 2][y + 1] = true;
  if (y + 1 <8 && x + 2 <8)
    ruch_figury_[x + 2][y + 1] = true;

  if (y - 2 >= 0 && x - 1 >= 0)
    ruch_figury_[x - 1][y - 2] = true;
  if (y - 2 >= 0 && x + 1 <8)
    ruch_figury_[x + 1][y - 2] = true;
  if (y + 2 <8 && x - 1 >= 0)
    ruch_figury_[x - 1][y + 2] = true;
  if (y + 2 <8 && x + 1 <8)
    ruch_figury_[x + 1][y + 2] = true;

 

}

void Plansza::RuchGoniec(int x, int y)
{
  int pomx = x;
  int pomy = y;
  bool blokada = false;
  while (x >=0 && y>=0  && blokada == false)
  {
    x--;
    y--;
    if (x >=0 && y >= 0)
    {
      if (polozenie_[x][y] == 0)
        ruch_figury_[x][y] = true;
      else
      {
        ruch_figury_[x][y] = true;
        blokada = true;
      }
    }

  }

  x=pomx;
  y=pomy;
  blokada = false;
  while (x < 8 && y<8 && blokada == false)
  {
    x++;
    y++;
    if (x < 8 && y<8)
    {
      if (polozenie_[x][y] == 0)
        ruch_figury_[x][y] = true;
      else
      {
        ruch_figury_[x][y] = true;
        blokada = true;
      }
    }

  }

  x = pomx;
  y = pomy;
  blokada = false;
  while (x < 8 && y>=0 &&  blokada == false)
  {
    x++;
    y--;
    if (x < 8 && y>=0)
    {
      if (polozenie_[x][y] == 0)
        ruch_figury_[x][y] = true;
      else
      {
        ruch_figury_[x][y] = true;
        blokada = true;
      }
    }

  }

  x = pomx;
  y = pomy;
  blokada = false;
  while (x >=0 && y<8 && blokada == false)
  {
    x--;
    y++;
    if (x >=0 && y<8)
    {
      if (polozenie_[x][y] == 0)
        ruch_figury_[x][y] = true;
      else
      {
        ruch_figury_[x][y] = true;
        blokada = true;
      }
    }

  }



}

void Plansza::ZresetujBiciePrzelocieBialym()
{
  for (int i = 0; i < 8; i++)
  {
    for (int j = 0; j < 8; j++)
    {
      bicie_w_przelocie_biale[i][j] = false;
    }
  }
}

void Plansza::ZresetujBiciePrzelocieCzarnym()
{
  for (int i = 0; i < 8; i++)
  {
    for (int j = 0; j < 8; j++)
    {
      bicie_w_przelocie_czarne[i][j] = false;
    }
  }
}

void Plansza::UstawBicieWprzelicieBiale(int x, int y)
{
  bicie_w_przelocie_biale[x][y] = true;
}

void Plansza::UstawBicieWprzelicieCzarne(int x, int y)
{
  bicie_w_przelocie_czarne[x][y] = true;
}

bool Plansza::PobierzBicieWPrzelocieBiale(int x, int y)
{
  return bicie_w_przelocie_biale[x][y];
}

bool Plansza::PobierzBicieWPrzelocieCzarne(int x, int y)
{
  return bicie_w_przelocie_czarne[x][y];
}

void Plansza::WyliczeniaSzacha(int x, int y)
{

  switch (polozenie_[x][y])
  {
  case 2:
  case -2:
    WiezaSzach(x, y);
    break;
  case 3:
  case -3:
    if (y - 1 >= 0 && x - 2 >= 0)
      tablicaSzacha[x - 2][y - 1] = true;
    if (y - 1 >= 0 && x + 2 <8)
      tablicaSzacha[x + 2][y - 1] = true;
    if (y + 1 <8 && x - 2 >= 0)
      tablicaSzacha[x - 2][y + 1] = true;
    if (y + 1 <8 && x + 2 <8)
      tablicaSzacha[x + 2][y + 1] = true;

    if (y - 2 >= 0 && x - 1 >= 0)
      tablicaSzacha[x - 1][y - 2] = true;
    if (y - 2 >= 0 && x + 1 <8)
      tablicaSzacha[x + 1][y - 2] = true;
    if (y + 2 <8 && x - 1 >= 0)
      tablicaSzacha[x - 1][y + 2] = true;
    if (y + 2 <8 && x + 1 <8)
      tablicaSzacha[x + 1][y + 2] = true;

    break;
  case 4:
  case -4:
    GoniecSzach(x, y);
    break;
  case 5:
  case -5:
    GoniecSzach(x, y);
    WiezaSzach(x, y);
    break;
  case 6:
  case -6:
    if (x - 1 >= 0)
      tablicaSzacha[x - 1][y] = true;
    if (x + 1<8)
      tablicaSzacha[x + 1][y] = true;
    if (y + 1 < 8)
      tablicaSzacha[x][y + 1] = true;
    if (y - 1 >= 0)
      tablicaSzacha[x][y - 1] = true;
    if (y - 1 >= 0 && x + 1<8)
      tablicaSzacha[x + 1][y - 1] = true;
    if (y - 1 >= 0 && x - 1 >= 0)
      tablicaSzacha[x - 1][y - 1] = true;
    if (y + 1 < 8 && x - 1 >= 0)
      tablicaSzacha[x - 1][y + 1] = true;
    if (y + 1 < 8 && x + 1 < 8)
      tablicaSzacha[x + 1][y + 1] = true;
    int zmienna = 0;
    break;
  }
  if (polozenie_[x][y] == 1)
  {
    if (x + 1 <8 && y - 1 >=0)
      tablicaSzacha[x + 1][y - 1] = true;
    if (x - 1 >= 0 && y - 1 >= 0)
      tablicaSzacha[x - 1][y - 1] = true;
  }
  if (polozenie_[x][y] == -1)                                   
  {
     if (x +1<8 && y + 1 < 8)
      tablicaSzacha[x +1][y + 1] = true;
     if (x - 1>=0 && y + 1 <8)
       tablicaSzacha[x - 1][y + 1] = true;

  }

}

void Plansza::WiezaSzach(int x, int y)
{
  int pomx = x;
  int pomy = y;
  bool blokada = false;
  while (x < 8 && blokada == false)
  {
    x++;
    if (x < 8)
    {
      if (polozenie_[x][y] == 0)
        tablicaSzacha[x][y] = true;
      else
      {
        tablicaSzacha[x][y] = true;
        blokada = true;
      }
    }

  }

  x = pomx;
  y = pomy;
  blokada = false;
  while (x >= 0 && blokada == false)
  {
    x--;
    if (x >= 0)
    {
      if (polozenie_[x][y] == 0)
        tablicaSzacha[x][y] = true;
      else
      {
        tablicaSzacha[x][y] = true;
        blokada = true;
      }
    }

  }
  x = pomx;
  y = pomy;
  blokada = false;
  while (y >= 0 && blokada == false)
  {
    y--;
    if (y >= 0)
    {
      if (polozenie_[x][y] == 0)
        tablicaSzacha[x][y] = true;
      else
      {
        tablicaSzacha[x][y] = true;
        blokada = true;
      }
    }

  }

  x = pomx;
  y = pomy;
  blokada = false;
  while (y <8 && blokada == false)
  {
    y++;
    if (y<8)
    {
      if (polozenie_[x][y] == 0)
        tablicaSzacha[x][y] = true;
      else
      {
        tablicaSzacha[x][y] = true;
        blokada = true;
      }
    }

  }
}

void Plansza::GoniecSzach(int x, int y)
{
    int pomx = x;
    int pomy = y;
    bool blokada = false;
    while (x >= 0 && y >= 0 && blokada == false)
    {
      x--;
      y--;
      if (x >= 0 && y >= 0)
      {
        if (polozenie_[x][y] == 0)
          tablicaSzacha[x][y] = true;
        else
        {
          tablicaSzacha[x][y] = true;
          blokada = true;
        }
      }

    }

    x = pomx;
    y = pomy;
    blokada = false;
    while (x < 8 && y < 8 && blokada == false)
    {
      x++;
      y++;
      if (x < 8 && y < 8)
      {
        if (polozenie_[x][y] == 0)
          tablicaSzacha[x][y] = true;
        else
        {
          tablicaSzacha[x][y] = true;
          blokada = true;
        }
      }

    }

    x = pomx;
    y = pomy;
    blokada = false;
    while (x < 8 && y >= 0 && blokada == false)
    {
      x++;
      y--;
      if (x < 8 && y >= 0)
      {
        if (polozenie_[x][y] == 0)
          tablicaSzacha[x][y] = true;
        else
        {
          tablicaSzacha[x][y] = true;
          blokada = true;
        }
      }

    }

    x = pomx;
    y = pomy;
    blokada = false;
    while (x >= 0 && y < 8 && blokada == false)
    {
      x--;
      y++;
      if (x >= 0 && y < 8)
      {
        if (polozenie_[x][y] == 0)
          tablicaSzacha[x][y] = true;
        else
        {
          tablicaSzacha[x][y] = true;
          blokada = true;
        }
      }

    }


}

bool Plansza::ObliczSzach(int starex, int starey, int fieldX, int fieldY, int kolor)
{
  bool szach = false;
  
  int figura1 = polozenie_[starex][starey];
  int figura2 = polozenie_[fieldX][fieldY];
    polozenie_[starex][starey] = 0;
    polozenie_[fieldX][fieldY] = figura1;
  
  for (int i = 0; i < 8; i++)
  {
    for (int j = 0; j < 8; j++)
    {
      tablicaSzacha[i][j] = false;
    }
  }


  switch (kolor)
  {
  case 0:
    szach = ObliczSzachBialych();
    break;
  case 1:
    szach = ObliczSzachCzarnych();
    break;
  }
  if (figura2 == 0)
  {
    polozenie_[starex][starey] = figura1;
    polozenie_[fieldX][fieldY] = 0;
  }
  else
  {
    polozenie_[starex][starey] = figura1;
    polozenie_[fieldX][fieldY] = figura2;
  }

  return szach;

}

bool Plansza::ObliczSzachBialych()
{
  bool warunek = false;

  for (int i = 0; i < 8; i++)
  {
    for (int j = 0; j < 8; j++)
    {
      if (polozenie_[i][j] < 0)
      {
        WyliczeniaSzacha(i, j);
      }
    }
  }

  for (int i = 0; i < 8; i++)
  {
    for (int j = 0; j < 8; j++)
    {
      if (polozenie_[i][j] == 6)
      {
        warunek = ZwrocSzachPola(i,j);
      }
    }
  }


  return warunek;

}

bool Plansza::ObliczSzachCzarnych()
{
  bool warunek = false;

  for (int i = 0; i < 8; i++)
  {
    for (int j = 0; j < 8; j++)
    {
      if (polozenie_[i][j] > 0)
      {
        WyliczeniaSzacha(i, j);
      }
    }
  }

  for (int i = 0; i < 8; i++)
  {
    for (int j = 0; j < 8; j++)
    {
      if (polozenie_[i][j] == -6)
      {
        warunek = ZwrocSzachPola(i, j);
      }
    }
  }


  return warunek;
  
}

bool Plansza::ZwrocSzachPola(int x, int y)
{
  return tablicaSzacha[x][y];
}

bool Plansza::SzachMatBialych()
{
  for (int i = 0; i < 8; i++)
  {
    for (int j = 0; j < 8; j++)
    {
      tablicaSzacha[i][j] = false;
    }
  }

  if (ObliczSzachBialych() == true)
  {
    if (WyliczSzachMatBalych() == true)
      return true;
    else
      return false;
  }
  else
  return false;
}

bool Plansza::SzachMatCzarnych()
{
  for (int i = 0; i < 8; i++)
  {
    for (int j = 0; j < 8; j++)
    {
      tablicaSzacha[i][j] = false;
    }
  }

  if (ObliczSzachCzarnych() == true)
  {
    if (WyliczSzachMatCzarnych() == true)
      return true;
    else
      return false;
  }
  else
    return false;
}

bool Plansza::PatBialych()
{
  if (ObliczSzachBialych() == false)
  {
    return WyliczPatBialych();
  }
  return false;
}

bool Plansza::PatCzarnych()
{
  if (ObliczSzachCzarnych() == false)
  {
    return WyliczPatCzarnych();
  }
  return false;
}

bool Plansza::WyliczPatBialych()
{

  int polKrolaX;
  int polKrolaY;
  for (int i = 0; i < 8; i++)
  {
    for (int j = 0; j < 8; j++)
    {

      if (polozenie_[i][j] == 6)
      {
        polKrolaX = i;
        polKrolaY = j;
      }
    }
  }
  //wylicza czy krol moze sie ruszyc 
  if (polKrolaX - 1 >= 0 && tablicaSzacha[polKrolaX - 1][polKrolaY] == false && polozenie_[polKrolaX - 1][polKrolaY] == 0)
    return false;
  if (polKrolaX + 1 < 8 && tablicaSzacha[polKrolaX + 1][polKrolaY] == false && polozenie_[polKrolaX + 1][polKrolaY] == 0)
    return false;
  if (polKrolaY + 1 < 8 && tablicaSzacha[polKrolaX][polKrolaY + 1] == false && polozenie_[polKrolaX][polKrolaY + 1] == 0)
    return false;
  if (polKrolaY - 1 >= 0 && tablicaSzacha[polKrolaX][polKrolaY - 1] == false && polozenie_[polKrolaX][polKrolaY - 1] == 0)
    return false;
  if (polKrolaY - 1 >= 0 && polKrolaX + 1 < 8 && tablicaSzacha[polKrolaX + 1][polKrolaY - 1] == false && polozenie_[polKrolaX + 1][polKrolaY - 1] == 0)
    return false;
  if (polKrolaY - 1 >= 0 && polKrolaX - 1 >= 0 && tablicaSzacha[polKrolaX - 1][polKrolaY - 1] == false && polozenie_[polKrolaX - 1][polKrolaY - 1] == 0)
    return false;
  if (polKrolaY + 1 < 8 && polKrolaX - 1 >= 0 && tablicaSzacha[polKrolaX - 1][polKrolaY + 1] == false && polozenie_[polKrolaX - 1][polKrolaY + 1] == 0)
    return false;
  if (polKrolaY + 1 < 8 && polKrolaX + 1 < 8 && tablicaSzacha[polKrolaX + 1][polKrolaY + 1] == false && polozenie_[polKrolaX + 1][polKrolaY + 1] == 0)
    return false;
  //wyliczenie czy jaka kolwiek inna figura moze sie ruszyc 

  for (int i = 0; i < 8; i++)
  {
    for (int j = 0; j < 8; j++)
    {
      if (polozenie_[i][j] > 0 && polozenie_[i][j] != 6)
      {
        Oblicz_ruch(i,j);
        for (int k = 0; k < 8; k++)
        {
          for (int z = 0; z < 8; z++)
          {
            if (ruch_figury_[k][z] == true && polozenie_[k][z] <= 0)
              return false;
          }
        }

      }
    }
  }

  return true;
}

bool Plansza::WyliczPatCzarnych()
{
  int polKrolaX;
  int polKrolaY;
  for (int i = 0; i < 8; i++)
  {
    for (int j = 0; j < 8; j++)
    {
      if (polozenie_[i][j] == -6)
      {
        polKrolaX = i;
        polKrolaY = j;
      }
    }
  }

  if (polKrolaX - 1 >= 0 && tablicaSzacha[polKrolaX - 1][polKrolaY] == false && polozenie_[polKrolaX - 1][polKrolaY] == 0)
    return false;
  if (polKrolaX + 1 < 8 && tablicaSzacha[polKrolaX + 1][polKrolaY] == false && polozenie_[polKrolaX + 1][polKrolaY] == 0)
    return false;
  if (polKrolaY + 1 < 8 && tablicaSzacha[polKrolaX][polKrolaY + 1] == false && polozenie_[polKrolaX][polKrolaY + 1] == 0)
    return false;
  if (polKrolaY - 1 >= 0 && tablicaSzacha[polKrolaX][polKrolaY - 1] == false && polozenie_[polKrolaX][polKrolaY - 1] == 0)
    return false;
  if (polKrolaY - 1 >= 0 && polKrolaX + 1 < 8 && tablicaSzacha[polKrolaX + 1][polKrolaY - 1] == false && polozenie_[polKrolaX + 1][polKrolaY - 1] == 0)
    return false;
  if (polKrolaY - 1 >= 0 && polKrolaX - 1 >= 0 && tablicaSzacha[polKrolaX - 1][polKrolaY - 1] == false && polozenie_[polKrolaX - 1][polKrolaY - 1] == 0)
    return false;
  if (polKrolaY + 1 < 8 && polKrolaX - 1 >= 0 && tablicaSzacha[polKrolaX - 1][polKrolaY + 1] == false && polozenie_[polKrolaX - 1][polKrolaY + 1] == 0)
    return false;
  if (polKrolaY + 1 < 8 && polKrolaX + 1 < 8 && tablicaSzacha[polKrolaX + 1][polKrolaY + 1] == false && polozenie_[polKrolaX + 1][polKrolaY + 1] == 0)
    return false;
  //wyliczenie czy jaka kolwiek inna figura moze sie ruszyc 

  for (int i = 0; i < 8; i++)
  {
    for (int j = 0; j < 8; j++)
    {
      if (polozenie_[i][j] < 0 && polozenie_[i][j] !=- 6)
      {
        Oblicz_ruch(i, j);
        for (int k = 0; k < 8; k++)
        {
          for (int z = 0; z < 8; z++)
          {
            if (ruch_figury_[k][z] == true && polozenie_[k][z]>=0)
              return false;
          }
        }

      }
    }
  }
  return true;
}

bool Plansza::WyliczSzachMatBalych()
{
  for (int i = 0; i < 8; i++)
  {
    for (int j = 0; j < 8; j++)
    {
      if (polozenie_[i][j] > 0 )
      {
        Oblicz_ruch(i, j);
        for (int k = 0; k < 8; k++)
        {
          for (int z = 0; z < 8; z++)
          {
            if (ruch_figury_[k][z] == true && polozenie_[k][z] <= 0)
            {
              for (int u = 0; u < 8; u++)
              {
                for (int r = 0; r < 8; r++)
                  tablicaSzacha[u][r] = false;
              }
              int figura1 = polozenie_[i][j];
              int figura2 = polozenie_[k][z];
              polozenie_[i][j] = 0;
              polozenie_[k][z] = figura1;
              if (ObliczSzachBialych() == false)
              {
                polozenie_[i][j] = figura1;
                polozenie_[k][z] = figura2;
                return false;
              }
              else
              {
                polozenie_[i][j] = figura1;
                polozenie_[k][z] = figura2;
              }

            }
          }
        }

      }
    }
  }

  return true;

}

bool Plansza::WyliczSzachMatCzarnych()
{
  for (int i = 0; i < 8; i++)
  {
    for (int j = 0; j < 8; j++)
    {
      if (polozenie_[i][j] < 0)
      {
        Oblicz_ruch(i, j);
        for (int k = 0; k < 8; k++)
        {
          for (int z = 0; z < 8; z++)
          {
            if (ruch_figury_[k][z] == true && polozenie_[k][z] >= 0)
            {
              for (int u = 0; u < 8; u++)
              {
                for (int r = 0; r < 8; r++)
                  tablicaSzacha[u][r] = false;
              }
              int figura1 = polozenie_[i][j];
              int figura2 = polozenie_[k][z];
              polozenie_[i][j] = 0;
              polozenie_[k][z] = figura1;
              if (ObliczSzachCzarnych() == false)
              {
                polozenie_[i][j] = figura1;
                polozenie_[k][z] = figura2;
                return false;
              }
              else
              {
                polozenie_[i][j] = figura1;
                polozenie_[k][z] = figura2;
              }

            }
          }
        }

      }
    }
  }

  return true;    
}

