#ifndef PLANSZA_H_
#define PLANSZA_H_

class Plansza
{
public:
  static const int rozmiar_planszy_ = 8;
  Plansza();
  ~Plansza();
  void Zresetuj_(Plansza &aktualna);
  bool ustaw(int figura, int x, int y);
  int pobierz(int x, int y);
  int kolor_pola(int x, int y);
  void Oblicz_ruch(int x, int y);
  bool Sprawdz_ruch(int x, int y);
  void RuchWieza(int x,int y);              
  void RuchKrol(int x, int y);               
  void RuchKonik(int x, int y);
  void RuchGoniec(int x, int y);   
  void ZresetujBiciePrzelocieBialym();
  void ZresetujBiciePrzelocieCzarnym();
  void UstawBicieWprzelicieBiale(int x,int y);
  void UstawBicieWprzelicieCzarne(int x, int y);
  bool PobierzBicieWPrzelocieBiale(int x, int y);
  bool PobierzBicieWPrzelocieCzarne(int x, int y);
  bool ObliczSzach(int starex, int starey, int fieldX, int fieldY, int kolor);
  bool ZwrocSzachPola(int x, int y);
  bool ObliczSzachBialych();
  bool ObliczSzachCzarnych();
  void WyliczeniaSzacha(int x, int y);
  void Prawo(int x, int y);
  void Lewo(int x, int y);
  void Gora(int x, int y);
  void Dol(int x, int y);
  void WiezaSzach(int x, int y);
  void GoniecSzach(int x, int y);
  bool SzachMatBialych();
  bool SzachMatCzarnych();
  bool PatBialych();
  bool PatCzarnych();
  bool WyliczSzachMatBalych();
  bool WyliczSzachMatCzarnych();
  bool WyliczPatBialych();
  bool WyliczPatCzarnych();


private:
  int polozenie_[rozmiar_planszy_][rozmiar_planszy_];       //roztawienie figur -czarne +biale
  int kolor_pola_[rozmiar_planszy_][rozmiar_planszy_];       //kolory pol 0 biale 1 brazowe
  bool ruch_figury_[rozmiar_planszy_][rozmiar_planszy_];   //tablica mozliwych ruchow figur
  bool bicie_w_przelocie_biale[rozmiar_planszy_][rozmiar_planszy_];
  bool bicie_w_przelocie_czarne[rozmiar_planszy_][rozmiar_planszy_];
  bool tablicaSzacha[rozmiar_planszy_][rozmiar_planszy_];


};

#endif  //PLANSZA_H_