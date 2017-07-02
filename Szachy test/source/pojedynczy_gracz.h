#ifndef POJEDYNCZY_GRACZ_H_
#define POJEDYNCZY_GRACZ_H_

class PojedynczyGracz
{
public:
  PojedynczyGracz();
  ~PojedynczyGracz();
  void ustawWrtosci(int tablica[8][8]);
  int  Wczytaj(int x,int y);
private:
  int sytuacja[8][8];



};

    #endif //POJEDYNCZY_GRACZ_H_