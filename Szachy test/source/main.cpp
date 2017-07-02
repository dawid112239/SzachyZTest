#include<Windows.h>
#include<stdio.h>
#include <cstdlib>
#include <ctime>
#include<math.h>
#include "res.h"
#include "plansza.h"
#include "pojedynczy_gracz.h"
#pragma comment(lib, "winmm.lib")


HWND hwndText2;
HWND hwndText1;
Plansza aktualna_plansza;
HINSTANCE hthisInstance;
bool GraczBialy = true;
bool GameOnn = true;
void OdswiezPlansze(HWND hwndMainWindow);
void WarunkiStartowe(HWND hwndMainWindow);
void RozstawFigury(HWND hwndMainWindow);
void Zamaluj(int x,int y);
HDC Okno;
HWND mojeOkno;
HWND pulpit;
HBITMAP bitmap_figury[12];
HBITMAP bitmap_Przyciski;
HBITMAP napis;
HBITMAP maskanapis;
HBITMAP maski[12];
HBITMAP litery[8];
HBITMAP maskilitery[8];
HBITMAP cyfry[8];
HBITMAP maskicyfry[8];
HBITMAP napisZmiany;
HBITMAP maskaNapisZmiany;
HBITMAP napisPro;
bool klikniecie = false;
int x, y;
int starex = 1;
int starey = 1;
void DeleteBitmaps();
void Obsluga_klikniec(WPARAM wParam, LPARAM lParam, HWND hwndDig);
void Zaznacz_figure(int x, int y);
int XZbiteBiale,YZbiteBiale,XZbiteCzarne,YZbiteCzarne;
void Zbicie(int x,int y,HWND hwndMainWindow);
bool RuszanaBialaLewaWieza,RuszanaBialaPrawaWieza,RuszanyBialyKrol;
bool RuszanaCzarnaLewaWieza, RuszanaCzarnaPrawaWieza, RuszanyCzarnyKrol;
void UstawWarunkiRoszady(int x, int y);
int tabZbitychBiale[15];
int tabZbitychCzarne[15];
int licznikZbicBialy,licznikZbicCzarny;
bool KrolSzachowany(int starex,int starey,int filedX, int fieldY);
HICON hIcon;
HBITMAP CreateBitmapMask(HBITMAP hbmColour, COLORREF crTransparent);
void ZrobTlo(HWND hwndMainWindow);
bool maksymalizowanie = false;
bool stanstartowy = true;
bool minimalizacja = false;
int minx, maxx, miny, maxy;
void SprawdzDojsciePionka(int fieldX, int fieldY);
int tablicaZmianBiale[4];
int tablicaZmianCzarne[4];
bool Zamianafigury = false;
int zmianamaxx, zmianamaxy, zmianaminx,zmianaminy;
int fieldX, fieldY;
void NarysujZmianeFigur(int zmianaminx, int zmianamaxx, int  zmianaminy, int zmianamaxy, int kolor);
void OczyscZmiany();
int szerokosc, wysokosc;
bool warunekMaksymalizacji = false;
bool SprawdzRoszade(int numer);
void SprawdzKoniec();
void DzwiekZbicia();
void DzwiekRuchu();
void DzwiekNiepoprawny();
void DzwiekZaznaczenia();
void DzwiekRoszady();
void DzwiekKoncaGry();
bool pierwszyRuchBialych = true;
bool pierwszyRuchCzarnych = true;
bool kliknieciePrawym = false;
void Obsluga_klikniec_prawym(WPARAM wParam, LPARAM lParam, HWND hwndDig);
bool pierwszypionek=false;
bool podpowiedzi = false;
void RysujRuch(int x, int y);
void RysujPolaZbic(int x1, int y1, int x2, int y2);
PojedynczyGracz tablicaSytuacji[10];
bool JedenGracz;
bool jedenGraczWykonalRuch = false;
bool JedenGraczWarianty[10];
bool SprawdzPoprawnoscTestowa();
int liczbaPoje = 0;
void WstawPrzyciski(HWND hwndMainWindow);
void RysujNapis(HWND hwndMainWindow);
void RysujGracza(HWND hwndMainWindow);
bool pro = false;
int czasBialych = 600;
int czasCzarnych = 600;
void WyswietlCzas(int min,int sek);
void WyswietlCzas();
char tabznakow[10];
BOOL usatwianietekstu = false;
INT starawysokosc,wysokoscobrazu;



int test[8][8] = {
  { 0,0,0,0,0,0,0,0 },
  { 0,0,0,0,0,0,0,0 },
  { 0,0,0,0,0,0,0,0 },
  { -6,0,0,0,0,0,0,6 },
  { 0,0,0,0,0,0,0,0 },
  { 0,0,0,0,0,0,0,0 },
  { 0,0,0,0,0,0,0,0 },
  { 0,0,0,0,0,0,0,0 }
};

int aa[8][8] = {
  { -2,-1,0,0,0,0,1,2 },
  { 0,-1,0,0,0,0,1,0 },
  { -4,0,-3,0,0,0,1,4 },
  { -5,-1,0,3,0,0,1,5 },
  { -6,0,0,0,3,0,0,6 },
  { -2,-1,0,0,0,0,1,4 },
  { 0,-4,-1,0,0,0,1,0 },
  { 0,-1,0,0,0,0,1,2 }
};
int bb[8][8] = {
  { -2,-1,0,0,0,0,1,2 },
  { -3,-1,0,0,0,0,1,3 },
  { -4,-1,0,0,0,0,1,4 },
  { -5,-1,0,0,0,0,1,5 },
  { -6,-1,0,0,0,1,0,6 },
  { -4,0,0,-1,0,0,1,4 },
  { -3,0,0,-1,0,0,1,3 },
  { -2,-1,0,0,0,0,1,2 }
};
int c[8][8] = {
  { 0,0,0,0,0,5,0,0 },
  { 0,0,0,0,0,0,0,0 },
  { -2,0,0,0,0,0,0,0 },
  { -6,0,0,0,0,0,0,6 },
  { -2,0,0,0,0,0,0,0 },
  { 0,0,0,0,0,0,0,0 },
  { 0,0,0,0,0,0,0,0 },
  { 0,0,0,0,0,0,0,0 }
};
int d[8][8] = {
  { 0,0,0,0,5,0,0,0 },
  { 0,0,0,0,0,0,0,0 },
  { 0,0,0,-1,0,0,0,0 },
  { 0,0,0,-6,-1,6,0,0 },
  { 0,0,0,-1,0,0,0,0 },
  { 0,0,0,0,0,0,0,0 },
  { 0,0,0,0,0,0,0,0 },
  { 0,0,0,0,0,0,0,0 }
};
int e[8][8] = {
  { -6,-1,5,0,0,0,0,0 },
  { 0,-1,0,0,0,0,0,6 },
  { -2,0,-2,0,0,0,0,0 },
  { 0,0,3,0,0,0,0,0 },
  { 0,0,0,0,0,0,0,0 },
  { 0,0,0,0,0,0,0,0 },
  { 0,0,0,0,0,0,0,0 },
  { 0,0,0,0,0,0,0,0 }
};
int f[8][8] = {
  { 0,-1,0,5,0,0,1,0 },
  { -6,-1,0,0,0,0,1,6 },
  { -2,-1,0,0,0,0,1,0 },
  { 0,0,0,0,4,0,0,0 },
  { 0,0,0,0,0,0,0,0 },
  { 0,0,0,0,0,0,0,0 },
  { 0,0,0,0,0,0,0,0 },
  { 0,0,0,0,0,0,0,0 }
};
int g[8][8] = {
  { 0,0,0,0,0,2,0,0 },
  { 0,0,0,0,0,0,0,-6 },
  { 0,0,0,0,0,5,0,0 },
  { 0,0,0,0,0,0,0,0 },
  { 0,0,0,0,0,0,0,0 },
  { 0,0,0,0,0,0,0,0 },
  { 0,0,0,-2,-5,0,0,0 },
  { 0,0,0,0,0,0,6,0 }
};
int h[8][8] = {
  { 0,0,-1,0,0,1,4,0 },
  { -2,-2,0,-5,0,5,1,6 },
  { 0,-1,0,0,0,0,1,0 },
  { 0,0,-1,0,0,0,0,0 },
  { 0,0,0,0,0,0,0,0 },
  { 0,-1,0,0,1,0,0,0 },
  { -6,0,-4,0,0,0,0,2 },
  { -4,-1,1,0,0,0,0,0 }
};
int k[8][8] = {
  { 0,2,0,0,0,1,0,0 },
  { 0,0,0,0,0,1,6,0 },
  { 0,5,0,0,-1,0,1,0 },
  { 0,0,0,0,0,0,0,0 },
  { 0,0,0,0,0,0,-5,0 },
  { -2,0,0,3,0,0,-2,0 },
  { -6,0,-1,0,0,0,4,0 },
  { 0,-1,-4,0,0,0,0,0 }
};
int l[8][8] = {
  { 0,0,2,2,0,0,0,0 },
  { 0,0,0,4,0,6,0,0 },
  { 0,0,0,0,0,4,0,0 },
  { 0,0,0,-6,0,0,0,0 },
  { 0,0,0,0,0,0,0,0 },
  { 0,0,0,0,0,0,0,0 },
  { 0,0,0,0,0,0,0,0 },
  { 0,0,0,0,0,0,0,0 }
};



INT_PTR CALLBACK DialogProc(HWND hwndDig, UINT uMsg, WPARAM wParam, LPARAM lParam)
{

  switch (uMsg)
  {

  case WM_SYSCOMMAND:
  {
    switch (wParam)
    {
    case SC_MINIMIZE:

      if (stanstartowy == true)
        maksymalizowanie = false;
      else
        maksymalizowanie = true;
      minimalizacja = true;

      return FALSE;
    case SC_MAXIMIZE:

      if (warunekMaksymalizacji)
      {
        maksymalizowanie = true;
        stanstartowy = false;
        minimalizacja = false;
      }
      else
      {
        maksymalizowanie = false;
        stanstartowy = true;
        minimalizacja = false;
      }
      if (Zamianafigury == true)
      {
        OdswiezPlansze(hwndDig);
      }
      return FALSE;
    case SC_RESTORE:

      if (minimalizacja == true)
      {
        minimalizacja = false;
        if (stanstartowy == true)
        {

          HBRUSH PendzelCzarny = CreateSolidBrush(0xFFFFCC);
          const RECT gorny = { 200,100,800,800 };
          FillRect(Okno, &gorny, PendzelCzarny);
          maksymalizowanie = false;
          OdswiezPlansze(hwndDig);
          DeleteObject(PendzelCzarny);
        }
        else
          maksymalizowanie = true;
      }
      else
      {
        HBRUSH PendzelCzarny = CreateSolidBrush(0xFFFFCC);
        const RECT gorny = { 200,100,800,800 };
        FillRect(Okno, &gorny, PendzelCzarny);
        maksymalizowanie = false;
        stanstartowy = true;
        OdswiezPlansze(hwndDig);
        DeleteObject(PendzelCzarny);
      }

      return FALSE;
    }
  
    return FALSE;
  }
  case WM_TIMER:
    switch (wParam)
    {
    case 0:
      WstawPrzyciski(hwndDig);
      if (warunekMaksymalizacji == true)
      {
        RECT rozmiarokna;
        GetWindowRect(hwndDig, &rozmiarokna);
        wysokoscobrazu = rozmiarokna.bottom - rozmiarokna.top;

        if (starawysokosc == 648 && wysokoscobrazu > starawysokosc)
        {
          maksymalizowanie = true;
          stanstartowy = false;
          OdswiezPlansze(hwndDig);
          starawysokosc = wysokoscobrazu;

        }
        if (starawysokosc > wysokoscobrazu && wysokoscobrazu == 648)
        {
          stanstartowy = true;
          maksymalizowanie = false;
          HBRUSH PendzelCzarny, Pudelko;
          PendzelCzarny = CreateSolidBrush(0xFFFFCC);
          Pudelko = (HBRUSH)SelectObject(Okno, PendzelCzarny);
          const RECT dolny = { 200,100,1000,1000 };
          FillRect(Okno, &dolny, PendzelCzarny);
          SelectObject(Okno, Pudelko);
          DeleteObject(PendzelCzarny);
          DeleteObject(Pudelko);
          OdswiezPlansze(hwndDig);
          starawysokosc = wysokoscobrazu;

        }
      }
      return TRUE;
    case 1:
      if (pro == true)
      {
        if (GraczBialy)
        {
          czasBialych--;
          int min = czasBialych / 60;
          int sek = czasBialych % 60;
          WyswietlCzas(min, sek);
          if (czasBialych == 0)
          {
            GameOnn = false;
            DzwiekNiepoprawny();
            MessageBox(mojeOkno, " BIA£YM SKOÑCZY£ SIÊ CZAS ", "PRZEGRANA", MB_OK);
            KillTimer(hwndDig,1);
          }
        }
        else
        {
          czasCzarnych--;
          int min = czasCzarnych/ 60;
          int sek = czasCzarnych % 60;
          WyswietlCzas(min, sek);
          if (czasCzarnych == 0)
          {
            GameOnn = false;
            DzwiekNiepoprawny();
            MessageBox(mojeOkno, " CZARNYM SKOÑCZY£ SIÊ CZAS ", "PRZEGRANA", MB_OK);
            KillTimer(hwndDig, 1);
          }
        }
      }
      return FALSE;
    }

    return TRUE;
  case WM_CTLCOLORSTATIC:
  {
    static HBRUSH hBrushColor;

    hBrushColor = CreateSolidBrush(0xFFFFCC); // White background is returned
    SetBkColor((HDC)wParam, 0xFFFFCC); // White background for text!! Ustawiamy t³o.
  // Background color that is used to repaint the control (doesn't affect text background)
    SetTextColor((HDC)wParam, RGB(180, 0, 0));
    return(LRESULT)hBrushColor;
  }
  case WM_INITDIALOG:
  {
    pulpit = GetDesktopWindow();
    RECT rozmiarokna;
    GetWindowRect(pulpit, &rozmiarokna);
    szerokosc = rozmiarokna.right - rozmiarokna.left;
    wysokosc = rozmiarokna.bottom - rozmiarokna.top;
    if (szerokosc >= 1150 && wysokosc >= 1000)
      warunekMaksymalizacji = true;
    else
      warunekMaksymalizacji = false;
    for (int i = 0; i < 12; i++)
    {
      bitmap_figury[i] = LoadBitmap(hthisInstance, MAKEINTRESOURCE(IDB_BITMAP1 + i));
      maski[i] = CreateBitmapMask(bitmap_figury[i], RGB(255, 0, 0));
    }
    for (int i = 0; i < 8; i++)
    {
      cyfry[i] = LoadBitmap(hthisInstance, MAKEINTRESOURCE(IDB_BITMAP15 + i));
      maskicyfry[i] = CreateBitmapMask(cyfry[i], RGB(255, 0, 0));
      litery[i] = LoadBitmap(hthisInstance, MAKEINTRESOURCE(IDB_BITMAP23 + i));
      maskilitery[i] = CreateBitmapMask(litery[i], RGB(255, 0, 0));
    }
    bitmap_Przyciski = LoadBitmap(hthisInstance, MAKEINTRESOURCE(IDB_BITMAP13));
    napis = LoadBitmap(hthisInstance, MAKEINTRESOURCE(IDB_BITMAP14));
    maskanapis = CreateBitmapMask(napis, RGB(255, 0, 0));
    napisZmiany = LoadBitmap(hthisInstance, MAKEINTRESOURCE(IDB_BITMAP31));
    maskaNapisZmiany = CreateBitmapMask(napisZmiany, RGB(255, 0, 0));
    napisPro = LoadBitmap(hthisInstance, MAKEINTRESOURCE(IDB_BITMAP32));

    hIcon = LoadIcon(hthisInstance, MAKEINTRESOURCE(IDI_ICON1));

    // Set the icon for this dialog.
    SendMessage(hwndDig, WM_SETICON, ICON_BIG, (LPARAM)hIcon);  // Set big icon
    SendMessage(hwndDig, WM_SETICON, ICON_SMALL, (LPARAM)hIcon);  // Set small icon
    return TRUE;
  }

  case WM_LBUTTONDOWN:
    Obsluga_klikniec(wParam,lParam,hwndDig);
    return TRUE;
  case WM_RBUTTONDOWN:
    Obsluga_klikniec_prawym(wParam, lParam, hwndDig);
    return TRUE;
  case WM_COMMAND:

    switch (HIWORD(wParam))
    {
    case BN_CLICKED:
      switch (LOWORD(wParam))
      {
      case IDC_BUTTON1:
      {
        //wcisnij Gracz vs Gracz
        WyswietlCzas();
        GraczBialy = true;
        JedenGracz = false;
        OczyscZmiany();
        aktualna_plansza.Zresetuj_(aktualna_plansza);
        WarunkiStartowe(hwndDig);
        klikniecie = false;
        GameOnn = true;
        pro = false;

        return TRUE;
      }
      case IDC_PRO:
      {
        //wcisnij Gracz vs Gracz
        czasBialych = czasCzarnych = 600;
        pro = true;
        GraczBialy = true;
        JedenGracz = false;
        OczyscZmiany();
        aktualna_plansza.Zresetuj_(aktualna_plansza);
        WarunkiStartowe(hwndDig);
        klikniecie = false;
        GameOnn = true;
        SetTimer(hwndDig,1,1000,NULL);
        usatwianietekstu = TRUE;
        sprintf_s(tabznakow, "10:00");
        SetWindowText(hwndText1, tabznakow);
        SetWindowText(hwndText2, tabznakow);
        usatwianietekstu = FALSE;
        return TRUE;
      }
      case IDC_POMOC:
      {
        if (pro == true)
        {
          KillTimer(hwndDig, 1);
        }
        MessageBox(mojeOkno, " Kliknij na przycisk ''GRACZ vs GRACZ'', aby rozegraæ pojedynek z innym u¿ytkownikiem. Kliknij na przycisk ''PRO'', aby rozegraæ pojedynek mieszcz¹c siê w 10 min dla jednego gracza. Kliknij na przycisk ''1 GRACZ'', aby rozpocz¹æ samodzieln¹ gre.   Do poruszania i wybierania figur, u¿yj lewego klawisza myszy. Aby wykonaæ roszade wybierz wie¿e, a nastêpnie kliknij na króla. Aby wykonaæ ruch dwoma pionkami, kliknij  na wybranych pionkach prawym klawiszem myszy. ", "POMOC", MB_OK);
        if(pro==true)
          SetTimer(hwndDig, 1, 1000, NULL);
        return TRUE;
      }
      case IDC_BUTTON2:   //pojedynczy gracz
      {
        WyswietlCzas();
        MessageBox(mojeOkno, " WYKONAJ SZACH MAT W JEDNYM RUCHU ", "POJEDYÑCZY GRACZ", MB_OK);
        jedenGraczWykonalRuch = false;
        pro = false;
        bool znaleziono = false;
        bool jestWolne = true;
        liczbaPoje = rand() % 10;
        if(JedenGraczWarianty[liczbaPoje]==false)
        JedenGraczWarianty[liczbaPoje] = true;
        else
        {
          int ilewolnych = 0;
          for (int i = 0; i < 10; i++)
          {
            if (JedenGraczWarianty[i] == false)
              ilewolnych++;
          }
          if (ilewolnych > 0)
          {
            while (!znaleziono)
            {
              liczbaPoje = rand() % 10;
              if (JedenGraczWarianty[liczbaPoje] == false)
              {
                JedenGraczWarianty[liczbaPoje] = true;
                znaleziono = true;
              }
               }
          }
          else
          {
            for (int i = 0; i < 10; i++)
              JedenGraczWarianty[i] = false;
          }
        }

        JedenGracz = true;
        for (int i = 0; i < 8; i++)
        {
          for (int j = 0; j < 8; j++)
          {
            aktualna_plansza.ustaw(tablicaSytuacji[liczbaPoje].Wczytaj(i,j),i,j);
          }
         }
        pierwszyRuchBialych = false;
        pierwszyRuchCzarnych = false;
        kliknieciePrawym = false;
        Zamianafigury = false;
        pierwszypionek = false;
        klikniecie = false;
        GameOnn = true;
        GraczBialy = true;
        licznikZbicBialy = licznikZbicCzarny = 0;
        for (int i = 0; i < 15; i++)
        {
          tabZbitychBiale[i] = 0;
          tabZbitychCzarne[i] = 0;
        }
        int licz1 = 2;
        int licz2 = -2;
        for (int i = 0; i < 4; i++)
        {
          tablicaZmianBiale[i] = licz1;
          tablicaZmianCzarne[i] = licz2;
          licz1++;
          licz2--;

        }
        RuszanaBialaLewaWieza = RuszanaBialaPrawaWieza = RuszanyBialyKrol = true;
        RuszanaCzarnaLewaWieza = RuszanaBialaPrawaWieza = RuszanyCzarnyKrol = true;
        XZbiteBiale = 0;
        YZbiteBiale = 150;
        XZbiteCzarne = 0;
        YZbiteCzarne = 420;
        RysujPolaZbic(XZbiteBiale, YZbiteBiale, XZbiteCzarne, YZbiteCzarne);
        Okno = GetDC(hwndDig);
        RysujGracza(hwndDig);
        OdswiezPlansze(hwndDig);
        WyswietlCzas();
        return TRUE;
      }
      case IDC_BUTTON3:     // podpowiedzi
      {
 
        podpowiedzi = !podpowiedzi;
        OdswiezPlansze(mojeOkno);
        return TRUE;
      }
      case IDC_BUTTONTEST:     // guzik testowy
      {
        GraczBialy = true;  //mozliwa zmiana
        WyswietlCzas();
        pro = false;
        JedenGracz = false;
        if (SprawdzPoprawnoscTestowa() == true)
        {
          for (int i = 0; i < 8; i++)
          {
            for (int j = 0; j < 8; j++)
            {
              aktualna_plansza.ustaw(test[i][j], i, j);
            }
          }
          if (GraczBialy == true && aktualna_plansza.ObliczSzachCzarnych() == true)
          {
            MessageBox(mojeOkno, " Niepoprawna kombinacja testowa w grze niemozliwa jest sytuacja bicia krola wiec nie moze byc szachowany gdy przeciwnik ma ruch ", "BLAD", MB_OK);
            WarunkiStartowe(hwndDig);
            return TRUE;
          }
          if (GraczBialy == false && aktualna_plansza.ObliczSzachBialych() == true)
          {
            MessageBox(mojeOkno, " Niepoprawna kombinacja testowa w grze niemozliwa jest sytuacja bicia krola wiec nie moze byc szachowany gdy przeciwnik ma ruch ", "BLAD", MB_OK);
            WarunkiStartowe(hwndDig);
            return TRUE;
          }
          pierwszyRuchBialych = false;
          pierwszyRuchCzarnych = false;
          kliknieciePrawym = false;
          Zamianafigury = false;
          pierwszypionek = false;
          klikniecie = false;
          GameOnn = true;
          licznikZbicBialy = licznikZbicCzarny = 0;
          for (int i = 0; i < 15; i++)
          {
            tabZbitychBiale[i] = 0;
            tabZbitychCzarne[i] = 0;
          }
          int licz1 = 2;
          int licz2 = -2;
          for (int i = 0; i < 4; i++)
          {
            tablicaZmianBiale[i] = licz1;
            tablicaZmianCzarne[i] = licz2;
            licz1++;
            licz2--;

          }
          RuszanaBialaLewaWieza = RuszanaBialaPrawaWieza = RuszanyBialyKrol = true;
          RuszanaCzarnaLewaWieza = RuszanaBialaPrawaWieza = RuszanyCzarnyKrol = true;
          XZbiteBiale = 0;
          YZbiteBiale = 150;
          XZbiteCzarne = 0;
          YZbiteCzarne = 420;
          RysujPolaZbic(XZbiteBiale, YZbiteBiale, XZbiteCzarne, YZbiteCzarne);
          Okno = GetDC(hwndDig);
          RysujGracza(hwndDig);
          OdswiezPlansze(hwndDig);
          SprawdzKoniec();
        }
        else
        {
          GameOnn = false;
          MessageBox(mojeOkno, " Niepoprawna kombinacja testowa musi byc po 1 krolu i nie wiecej niz 8 pionkow ", "BLAD", MB_OK);
        }
        return TRUE;
      }

      return FALSE;
      }
      return FALSE;
    }
  case WM_PAINT:
    if (usatwianietekstu == FALSE)
    {
      WstawPrzyciski(hwndDig);
      OdswiezPlansze(hwndDig);
      RysujGracza(hwndDig);
    }

  return TRUE;

  case WM_CLOSE:
    DestroyWindow(hwndDig);
    DeleteBitmaps();
    PostQuitMessage(0);
    return TRUE;

  }
  return FALSE;
}

bool KrolSzachowany(int starex, int starey, int filedX, int fieldY)    //funkcja sprawdzajaca czy wykonanie roszady jest mozliwe czy zadne pole przelotu krola nie jest szachowane
{
  bool warunek = false;

  if (GraczBialy == true)
  {
    warunek = aktualna_plansza.ObliczSzach(starex, starey, fieldX, fieldY, 0);
  }
  else
  {
    warunek = aktualna_plansza.ObliczSzach(starex, starey, fieldX, fieldY, 1);
  }

  return warunek;
}

void ZrobTlo(HWND hwndMainWindow)
{
  HDC hdc;
  HBRUSH hbrBkgnd;
  PAINTSTRUCT ps;
  RECT r;

  GetClientRect(hwndMainWindow, &r);
  hdc = BeginPaint(hwndMainWindow, &ps);
  hbrBkgnd = CreateSolidBrush(0xFFFFCC);
  FillRect(hdc, &r, hbrBkgnd);
  EndPaint(hwndMainWindow, &ps);

}

void Obsluga_klikniec(WPARAM wParam, LPARAM lParam, HWND hwndDig)
{
  x = LOWORD(lParam);
  y = HIWORD(lParam);
  if (GameOnn == true && kliknieciePrawym==false)
  {
    if (maksymalizowanie == false)
    {
      minx = 200;
      maxx = 600;
      miny = 100;
      maxy = 500;
    }
    else
    {
      minx = 200;
      maxx = 1000;
      miny = 100;
      maxy = 900;
    }

    if (x > minx && x < maxx && y>miny && y < maxy && Zamianafigury==false)
    {  
       fieldX = (x - 50) / 50;
       fieldY = (y - 100) / 50;
      if (maksymalizowanie == false)
      {
        fieldX = (x - 200) / 50;
        fieldY = (y - 100) / 50;
      }
      else
      {
        fieldX = (x - 200) / 100;
        fieldY = (y - 100) / 100;
      }
      int figura,krol;
      if (GraczBialy == true)
      {
        if (klikniecie == false)
        {
          if (aktualna_plansza.pobierz(fieldX, fieldY) > 0)
          {
            if (podpowiedzi)
              RysujRuch(fieldX, fieldY);
            Zaznacz_figure(fieldX,fieldY);
            starex = fieldX;
            starey = fieldY;
            klikniecie = true;
            DzwiekZaznaczenia();

          }
        }
        else
        {

          if (aktualna_plansza.pobierz(fieldX, fieldY) <= 0)
          {
            aktualna_plansza.Oblicz_ruch(starex, starey);
            if (aktualna_plansza.Sprawdz_ruch(fieldX, fieldY) == true && KrolSzachowany(starex,starey,fieldX,fieldY)==false)    
            {
              if (aktualna_plansza.pobierz(fieldX, fieldY) != 0)
              {
                Zbicie(fieldX, fieldY, hwndDig);
                SprawdzDojsciePionka(fieldX, fieldY);
                DzwiekZbicia();
              }

              if (aktualna_plansza.PobierzBicieWPrzelocieCzarne(fieldX, fieldY) == true)
              {

                Zbicie(fieldX, fieldY + 1, hwndDig);
                aktualna_plansza.ustaw(0, fieldX, fieldY + 1);
                DzwiekZbicia();
              }

              if(aktualna_plansza.pobierz(fieldX,fieldY)==0)
              DzwiekRuchu();
              UstawWarunkiRoszady(starex, starey);
              figura = aktualna_plansza.pobierz(starex, starey);
              if (figura == 1 && starey - fieldY == 2)
              {
                aktualna_plansza.UstawBicieWprzelicieBiale(fieldX, fieldY + 1);
              }
              krol = aktualna_plansza.pobierz(fieldX, fieldY);
              aktualna_plansza.ustaw(figura, fieldX, fieldY);
              aktualna_plansza.ustaw(0, starex, starey);
              
              OdswiezPlansze(hwndDig);
              Zamaluj(starex, starey);
              SprawdzDojsciePionka(fieldX, fieldY);
              klikniecie = false;
              GraczBialy = false;
              aktualna_plansza.ZresetujBiciePrzelocieCzarnym();
              RysujGracza(hwndDig);
              pierwszyRuchBialych = false;
              jedenGraczWykonalRuch = true;
            }
            else
            {
              DzwiekNiepoprawny();
            }

          }
          else
          {
            bool roszadabiala = false;
            if (RuszanyBialyKrol == false && RuszanaBialaPrawaWieza == false && starex==7 && starey==7 && aktualna_plansza.pobierz(fieldX,fieldY)==6)
            {
              aktualna_plansza.ObliczSzach(starex,starey,fieldX,fieldY,0);
              if (aktualna_plansza.pobierz(6, 7) == 0 && aktualna_plansza.pobierz(5, 7) == 0 && SprawdzRoszade(1)==true)
              {
               int id1= MessageBox(hwndDig, "Czy chcesz wykonaæ roszade ? ", "Roszada ?", MB_YESNO | MB_ICONQUESTION);
               if (id1 == IDYES)
               {
                 roszadabiala = true;
                 aktualna_plansza.ustaw(0, 7, 7);
                 aktualna_plansza.ustaw(0, 4, 7);
                 aktualna_plansza.ustaw(2, 5, 7);
                 aktualna_plansza.ustaw(6, 6, 7);
                 RozstawFigury(hwndDig);
                 Zamaluj(7, 7);
                 Zamaluj(4, 7);
                 RuszanyBialyKrol = true;      
                 GraczBialy = !GraczBialy;
                 klikniecie = false;
                 RysujGracza(hwndDig);


               }
              }
            }

            if (RuszanyBialyKrol == false && RuszanaBialaLewaWieza == false && starex==0 && starey==7 && aktualna_plansza.pobierz(fieldX, fieldY) == 6)
            {
              aktualna_plansza.ObliczSzach(starex, starey, fieldX, fieldY, 0);
              if (aktualna_plansza.pobierz(1, 7) == 0 && aktualna_plansza.pobierz(2, 7) == 0 && aktualna_plansza.pobierz(3, 7) == 0 && SprawdzRoszade(2) == true)
              {
                int id2 = MessageBox(hwndDig, "Czy chcesz wykonaæ roszade ? ", "Roszada ?", MB_YESNO | MB_ICONQUESTION);
                  if (id2 == IDYES)
                  {
                    roszadabiala = true;
                    aktualna_plansza.ustaw(0, 0, 7);
                    aktualna_plansza.ustaw(0, 4, 7);
                    aktualna_plansza.ustaw(2, 3, 7);
                    aktualna_plansza.ustaw(6, 2, 7);
                    RozstawFigury(hwndDig);                 
                    Zamaluj(0, 7);
                    Zamaluj(4, 7);
                    RuszanyBialyKrol = true;
                    GraczBialy = !GraczBialy;
                    klikniecie = false;
                    RysujGracza(hwndDig);

                  }
              }
            }

            Zamaluj(starex, starey);
            RozstawFigury(hwndDig);
            if (roszadabiala == false)
            {
              Zaznacz_figure(fieldX, fieldY);
              DzwiekZaznaczenia();
              if (podpowiedzi)
                RysujRuch(fieldX, fieldY);
            }
            else
              DzwiekRoszady();
            starex = fieldX;
            starey = fieldY;
            aktualna_plansza.ZresetujBiciePrzelocieCzarnym();
          }

        }
      }
      else
      {

        
          if (klikniecie == false)
          {
            if (aktualna_plansza.pobierz(fieldX, fieldY) < 0)
            {
              Zaznacz_figure(fieldX, fieldY);
              DzwiekZaznaczenia();
              starex = fieldX;
              starey = fieldY;
              klikniecie = true;
              if (podpowiedzi)
                RysujRuch(fieldX, fieldY);

            }
          }
          else
          {

              if (aktualna_plansza.pobierz(fieldX, fieldY) >= 0)
              {
                aktualna_plansza.Oblicz_ruch(starex, starey);
                if (aktualna_plansza.Sprawdz_ruch(fieldX, fieldY) == true && KrolSzachowany(starex, starey, fieldX, fieldY) == false)
                {


                  if (aktualna_plansza.pobierz(fieldX, fieldY) != 0)
                  {
                    Zbicie(fieldX, fieldY, hwndDig);
                    SprawdzDojsciePionka(fieldX, fieldY);
                    DzwiekZbicia();
                  }

                  if (aktualna_plansza.PobierzBicieWPrzelocieBiale(fieldX, fieldY) == true)
                  {

                    Zbicie(fieldX, fieldY -1, hwndDig);
                    aktualna_plansza.ustaw(0, fieldX, fieldY - 1);
                    DzwiekZbicia();
                  }
                  if (aktualna_plansza.pobierz(fieldX, fieldY) == 0)
                  DzwiekRuchu();
                  UstawWarunkiRoszady(starex, starey);
                  figura = aktualna_plansza.pobierz(starex, starey);
                  if (figura == -1 && fieldY-starey == 2)
                  {
                    aktualna_plansza.UstawBicieWprzelicieCzarne(fieldX, fieldY - 1);
                  }
                  krol = aktualna_plansza.pobierz(fieldX, fieldY);
                  aktualna_plansza.ustaw(figura, fieldX, fieldY);
                  aktualna_plansza.ustaw(0, starex, starey);
                 
                  OdswiezPlansze(hwndDig);
                  Zamaluj(starex, starey);
                  SprawdzDojsciePionka(fieldX, fieldY);
                  klikniecie = false;
                  GraczBialy = true;
                  aktualna_plansza.ZresetujBiciePrzelocieBialym();
                  RysujGracza(hwndDig);
                  pierwszyRuchCzarnych = false;
                }
                else
                {
                  DzwiekNiepoprawny();
                }

              }
            
            else
            {
              bool roszadaczarne = false;
              if (RuszanyCzarnyKrol == false && RuszanaCzarnaPrawaWieza == false && starex==7 && starey==0 && aktualna_plansza.pobierz(fieldX, fieldY) == -6)
              {
                aktualna_plansza.ObliczSzach(starex, starey, fieldX, fieldY, 1);
                if (aktualna_plansza.pobierz(6, 0) == 0 && aktualna_plansza.pobierz(5, 0) == 0 && SprawdzRoszade(3) == true)
                {
                  int id3 = MessageBox(hwndDig, "Czy chcesz wykonaæ roszade ? ", "Roszada ?", MB_YESNO | MB_ICONQUESTION);
                    if (id3 == IDYES)
                    {
                      roszadaczarne = true;
                      aktualna_plansza.ustaw(0, 7, 0);
                      aktualna_plansza.ustaw(0, 4, 0);
                      aktualna_plansza.ustaw(-2, 5, 0);
                      aktualna_plansza.ustaw(-6, 6, 0);
                      RozstawFigury(hwndDig);
                      Zamaluj(7, 0);
                      Zamaluj(4, 0);
                      RuszanyCzarnyKrol = true;             
                      GraczBialy = !GraczBialy;
                      klikniecie = false;
                      RysujGracza(hwndDig);

                    }
                }
              }

              if (RuszanyCzarnyKrol == false && RuszanaCzarnaLewaWieza == false && starex == 0 && starey == 0 && aktualna_plansza.pobierz(fieldX, fieldY) == -6)
              {
                aktualna_plansza.ObliczSzach(starex, starey, fieldX, fieldY, 1);
                if (aktualna_plansza.pobierz(1, 0) == 0 && aktualna_plansza.pobierz(2, 0) == 0 && aktualna_plansza.pobierz(3,0)==0 && SprawdzRoszade(4) == true)
                {
                  int id4 = MessageBox(hwndDig, "Czy chcesz wykonaæ roszade ? ", "Roszada ?", MB_YESNO | MB_ICONQUESTION);
                    if (id4 == IDYES)
                    {
                      roszadaczarne = true;
                      aktualna_plansza.ustaw(0, 0, 0);
                      aktualna_plansza.ustaw(0, 4, 0);
                      aktualna_plansza.ustaw(-2, 3, 0);
                      aktualna_plansza.ustaw(-6, 2, 0);
                      RozstawFigury(hwndDig);
                      Zamaluj(0, 0);                         
                      Zamaluj(4, 0);
                      RuszanyCzarnyKrol = true;
                      GraczBialy = !GraczBialy;
                      klikniecie = false;
                      RysujGracza(hwndDig);

                    }
                }
              }



              //sprawdzic czy kliknieto wieze potem krola i czy mozna zrobic roszade
              //OdswiezPlansze(hwndDig);
              Zamaluj(starex,starey);
              RozstawFigury(hwndDig);
              if (roszadaczarne == false)
              {
                Zaznacz_figure(fieldX, fieldY);
                DzwiekZaznaczenia();
                if (podpowiedzi)
                  RysujRuch(fieldX, fieldY);
              }
              else
                DzwiekRoszady();
              starex = fieldX;
              starey = fieldY;
              aktualna_plansza.ZresetujBiciePrzelocieBialym();

            }
          }
        

      }
      SprawdzKoniec();
    }
    if (Zamianafigury == true)
    {
      if (maksymalizowanie == true)
      {
        zmianaminx = 1050;
        zmianamaxx = 1150;
        zmianaminy = 300;
        zmianamaxy = 700;

      }
      else
      {
        zmianaminx = 620;
        zmianamaxx = 670;
        zmianaminy = 200;
        zmianamaxy = 400;
      }
      if (x > zmianaminx && x < zmianamaxx && y>zmianaminy && y < zmianamaxy)
      {
        SetTimer(hwndDig, 1, 1000, NULL);
        Zamianafigury = false;
        int zmy;
        int figurazmiana;
        if (maksymalizowanie == false)
        {
           zmy = (y - zmianaminy) / 50;
           if (GraczBialy == true) 
           {     //czarny dojechal
             figurazmiana = tablicaZmianCzarne[zmy];
             aktualna_plansza.ustaw(figurazmiana,fieldX,fieldY);
             Zamaluj(fieldX, fieldY);
             RozstawFigury(hwndDig);
             OczyscZmiany();
  
           }
           else             //bialy dojechal
           {
             figurazmiana = tablicaZmianBiale[zmy];
             aktualna_plansza.ustaw(figurazmiana, fieldX, fieldY);
             Zamaluj(fieldX, fieldY);
             RozstawFigury(hwndDig);
             OczyscZmiany();

           }
           
        }
        else
        {
          zmy = (y - zmianaminy) / 100;
          if (GraczBialy == true)
          {     //czarny dojechal

            figurazmiana = tablicaZmianCzarne[zmy];
            aktualna_plansza.ustaw(figurazmiana, fieldX, fieldY);
            Zamaluj(fieldX, fieldY);
            RozstawFigury(hwndDig);
            OczyscZmiany();

          }
          else             //bialy dojechal
          {

            figurazmiana = tablicaZmianBiale[zmy];
            aktualna_plansza.ustaw(figurazmiana, fieldX, fieldY);
            Zamaluj(fieldX, fieldY);
            RozstawFigury(hwndDig);
            OczyscZmiany();

          }
        }
      }
      SprawdzKoniec();
    }

  }

}


void Obsluga_klikniec_prawym(WPARAM wParam, LPARAM lParam, HWND hwndDig)
{
  int poleX;
  int poleY;
  int mix, mxx, miy, mxy;
  int klikx = LOWORD(lParam);
  int kliky = HIWORD(lParam);
  if (GameOnn == true && GraczBialy == true && pierwszyRuchBialych == true)   
  {
    if (maksymalizowanie == false)
    {
      mix = 200;
      mxx = 600;
      miy = 100;
      mxy = 500;
    }
    if(maksymalizowanie==true)
    {
      mix = 200;
      mxx = 1000;
      miy = 100;
      mxy = 900;
    }
     
    if (klikx > mix && klikx < mxx && kliky>miy && kliky < mxy)
    {
      if (maksymalizowanie == false)
      {
        poleX = (klikx - 200) / 50;
        poleY = (kliky - 100) / 50;
      }
      else
      {
        poleX = (klikx - 200) / 100;
        poleY = (kliky - 100) / 100;
      }

      //klikolem prawym gracz bialy na pole zczytalem pole 
      if (pierwszypionek == false && aktualna_plansza.pobierz(poleX, poleY) == 1)
      {
        kliknieciePrawym = true;
        aktualna_plansza.ustaw(1, poleX, poleY - 1);
        aktualna_plansza.ustaw(0, poleX, poleY);
        RozstawFigury(hwndDig);
        OdswiezPlansze(hwndDig);
        pierwszypionek = true;
        DzwiekRuchu();

      }
      if (pierwszypionek == true && aktualna_plansza.pobierz(poleX, poleY) == 1)
      {
        aktualna_plansza.ustaw(1, poleX, poleY - 1);
        aktualna_plansza.ustaw(0, poleX, poleY);
        RozstawFigury(hwndDig);
        OdswiezPlansze(hwndDig);
        pierwszypionek = false;
        DzwiekRuchu();

        klikniecie = false;
        GraczBialy = false;
        RysujGracza(hwndDig);
        kliknieciePrawym = false;
        pierwszyRuchBialych = false;
      }

    }
  }
  if (GameOnn == true && GraczBialy == false && pierwszyRuchCzarnych == true)
  {
    if (maksymalizowanie == false)
    {
      mix = 200;
      mxx = 600;
      miy = 100;
      mxy = 500;
    }
    if (maksymalizowanie == true)
    {
      mix = 200;
      mxx = 1000;
      miy = 100;
      mxy = 900;
    }
    if (klikx > mix && klikx < mxx && kliky>miy && kliky < mxy)
    {
      if (maksymalizowanie == false)
      {
        poleX = (klikx - 200) / 50;
        poleY = (kliky - 100) / 50;
      }
      else
      {
        poleX = (klikx - 200) / 100;
        poleY = (kliky - 100) / 100;
      }

      //klikolem prawym gracz czarny na pole zczytalem pole 
      if (pierwszypionek == false && aktualna_plansza.pobierz(poleX, poleY) == -1)
      {
        kliknieciePrawym = true;
        aktualna_plansza.ustaw(-1, poleX, poleY + 1);
        aktualna_plansza.ustaw(0, poleX, poleY);
        RozstawFigury(hwndDig);
        OdswiezPlansze(hwndDig);
        pierwszypionek = true;
        DzwiekRuchu();

      }
      if (pierwszypionek == true && aktualna_plansza.pobierz(poleX, poleY) == -1)
      {
        aktualna_plansza.ustaw(-1, poleX, poleY + 1);
        aktualna_plansza.ustaw(0, poleX, poleY);
        RozstawFigury(hwndDig);
        OdswiezPlansze(hwndDig);
        kliknieciePrawym = false;
        pierwszypionek = false;
        DzwiekRuchu();

        klikniecie = false;
        GraczBialy = true;
        RysujGracza(hwndDig);
        pierwszyRuchCzarnych = false;
      }
    }

  }

}        

bool SprawdzRoszade(int numer)
{
  bool warunek = false;
  switch (numer)
  {
  case 1:  //biale   prawa
    if (aktualna_plansza.ZwrocSzachPola(4,7)==false && aktualna_plansza.ZwrocSzachPola(5,7)==false && aktualna_plansza.ZwrocSzachPola(6, 7) == false)
      warunek = true;
    break;
  case 2:   //biale   lewa
    if (aktualna_plansza.ZwrocSzachPola(4, 7) == false && aktualna_plansza.ZwrocSzachPola(3, 7) == false && aktualna_plansza.ZwrocSzachPola(2, 7) == false)
      warunek = true;
    break;

  case 3:  //czarne     prawa
    if (aktualna_plansza.ZwrocSzachPola(4, 0) == false && aktualna_plansza.ZwrocSzachPola(5, 0) == false && aktualna_plansza.ZwrocSzachPola(6, 0) == false)
      warunek = true;
    break;

  case 4: //czarne   lewa
    if (aktualna_plansza.ZwrocSzachPola(4, 0) == false && aktualna_plansza.ZwrocSzachPola(3, 0) == false && aktualna_plansza.ZwrocSzachPola(2, 0) == false)
      warunek = true;
    break;
  }
 
  return warunek;
}


HBITMAP CreateBitmapMask(HBITMAP hbmColour, COLORREF crTransparent)
{
  HDC hdcMem, hdcMem2;
  HBITMAP hbmMask, hbmOld, hbmOld2;
  BITMAP bm;

  GetObject(hbmColour, sizeof(BITMAP), &bm);
  hbmMask = CreateBitmap(bm.bmWidth, bm.bmHeight, 1, 1, NULL);

  hdcMem = CreateCompatibleDC(NULL);
  hdcMem2 = CreateCompatibleDC(NULL);

  hbmOld = (HBITMAP)SelectObject(hdcMem, hbmColour);
  hbmOld2 = (HBITMAP)SelectObject(hdcMem2, hbmMask);

  SetBkColor(hdcMem, crTransparent);

  BitBlt(hdcMem2, 0, 0, bm.bmWidth, bm.bmHeight, hdcMem, 0, 0, SRCCOPY);
  BitBlt(hdcMem, 0, 0, bm.bmWidth, bm.bmHeight, hdcMem2, 0, 0, SRCINVERT);

  SelectObject(hdcMem, hbmOld);
  SelectObject(hdcMem2, hbmOld2);
  DeleteDC(hdcMem);
  DeleteDC(hdcMem2);

  return hbmMask;
}

void NarysujZmianeFigur(int zmianaminx, int zmianamaxx, int  zmianaminy, int zmianamaxy,int kolor)
{
  HDC hdc = GetDC(mojeOkno), hdcNowy = CreateCompatibleDC(hdc);
  BITMAP bmInfo;
  HBITMAP hbmOld;
  GetObject(napisZmiany, sizeof(bmInfo), &bmInfo);
  hbmOld = (HBITMAP)SelectObject(hdcNowy, maskaNapisZmiany);
  StretchBlt(hdc, 550, 10, 100, 50, hdcNowy, 0, 0, 100, 50, SRCAND);
  SelectObject(hdcNowy, napisZmiany);
  StretchBlt(hdc,550 , 10, 100, 50, hdcNowy, 0, 0, 100, 50, SRCPAINT);
  ReleaseDC(mojeOkno, hdc);
  SelectObject(hdcNowy, hbmOld);
  DeleteDC(hdcNowy);

  hdc = GetDC(mojeOkno), hdcNowy = CreateCompatibleDC(hdc);
  int bierka;
  for (int i = 0; i < 4; i++)
  {
    //dotarl bialy
    if (kolor == 0) {
      bierka = tablicaZmianBiale[i];
      GetObject(bitmap_figury[bierka - 1], sizeof(bmInfo), &bmInfo);
      hbmOld = (HBITMAP)SelectObject(hdcNowy, maski[bierka - 1]);
      if (maksymalizowanie == false)
      {
        StretchBlt(hdc, zmianaminx, zmianaminy, 50, 50, hdcNowy, 0, 0, 30, 30, SRCAND);
        SelectObject(hdcNowy, bitmap_figury[bierka - 1]);
        StretchBlt(hdc, zmianaminx, zmianaminy, 50, 50, hdcNowy, 0, 0, 30, 30, SRCPAINT);
        zmianaminy = zmianaminy + 50;
      }
      else
      {
        StretchBlt(hdc, zmianaminx, zmianaminy, 100, 100, hdcNowy, 0, 0, 30, 30, SRCAND);
        SelectObject(hdcNowy, bitmap_figury[bierka - 1]);
        StretchBlt(hdc, zmianaminx, zmianaminy, 100, 100, hdcNowy, 0, 0, 30, 30, SRCPAINT);
        zmianaminy = zmianaminy + 100;
      }
    }
    else  //dotarl czarny
    {
      bierka = tablicaZmianCzarne[i];
      GetObject(bitmap_figury[-bierka +5], sizeof(bmInfo), &bmInfo);
      hbmOld = (HBITMAP)SelectObject(hdcNowy, maski[-bierka+5]);
      if (maksymalizowanie == false)
      {
        StretchBlt(hdc, zmianaminx, zmianaminy, 50, 50, hdcNowy, 0, 0, 30, 30, SRCAND);
        SelectObject(hdcNowy, bitmap_figury[-bierka + 5]);
        StretchBlt(hdc, zmianaminx, zmianaminy, 50, 50, hdcNowy, 0, 0, 30, 30, SRCPAINT);
        zmianaminy = zmianaminy + 50;
      }
      else
      {
        StretchBlt(hdc, zmianaminx, zmianaminy, 100, 100, hdcNowy, 0, 0, 30, 30, SRCAND);
        SelectObject(hdcNowy, bitmap_figury[-bierka + 5]);
        StretchBlt(hdc, zmianaminx, zmianaminy, 100, 100, hdcNowy, 0, 0, 30, 30, SRCPAINT);
        zmianaminy = zmianaminy + 100;
      }
    }
  }

  ReleaseDC(mojeOkno, hdc);
  SelectObject(hdcNowy, hbmOld);
  DeleteDC(hdcNowy);

}

void SprawdzDojsciePionka(int fieldX, int fieldY)
{

  int xmin, xmax, ymin, ymax;
  if (aktualna_plansza.pobierz(fieldX, fieldY) == 1 && fieldY == 0)
  {

    Zamianafigury = true;
    KillTimer(mojeOkno, 1);
    if (maksymalizowanie == true)
    {
      xmin = 1050;
      xmax = 1150;
      ymin = 300;
      ymax = 700;
    }
    else
    {
      xmin = 620;
      xmax = 670;
      ymin = 200;
      ymax = 400;
    }
    NarysujZmianeFigur(xmin, xmax, ymin, ymax, 0);

  }

  if (aktualna_plansza.pobierz(fieldX, fieldY) == -1 && fieldY == 7)
  {

    Zamianafigury = true;
    KillTimer(mojeOkno,1);
    if (maksymalizowanie == true)
    {
      xmin = 1050;
      xmax = 1150;
      ymin = 300;
      ymax = 700;
    }
    else
    {
      xmin = 620;
      xmax = 670;
      ymin = 200;
      ymax = 400;
    }
    NarysujZmianeFigur(xmin, xmax, ymin, ymax, 1);
  }

}

void UstawWarunkiRoszady(int x, int y)
{
  int figura = aktualna_plansza.pobierz(x, y);
  switch (figura)
  {
  case 2:
    if (x == 0 && y == 7)
      RuszanaBialaLewaWieza = true;
    if (x == 7 && y == 7)
      RuszanaBialaPrawaWieza = true;
    break;
  case 6:
    RuszanyBialyKrol = true;
    break;

  case -2:
    if (x == 0 && y == 0)
      RuszanaCzarnaLewaWieza = true;
    if (x == 7 && y == 0)
      RuszanaCzarnaPrawaWieza = true;
    break;
  case -6:
    RuszanyCzarnyKrol = true;
    break;
  }


}

void Zbicie(int x,int y, HWND hwndMainWindow)
{
    int figuraa = aktualna_plansza.pobierz(x, y);
    Zamaluj(x,y);
    if (figuraa > 0)
    {

      HDC hdc = GetDC(hwndMainWindow), hdcNowy = CreateCompatibleDC(hdc);
      BITMAP bmInfo;
      HBITMAP hbmOld;
      GetObject(bitmap_figury[figuraa - 1], sizeof(bmInfo), &bmInfo);
      hbmOld = (HBITMAP)SelectObject(hdcNowy, maski[figuraa - 1]);

      StretchBlt(hdc, XZbiteBiale, YZbiteBiale, 30, 30, hdcNowy, 0, 0, 30, 30, SRCAND);
      SelectObject(hdcNowy, bitmap_figury[figuraa - 1]);
      StretchBlt(hdc, XZbiteBiale, YZbiteBiale, 30, 30, hdcNowy, 0, 0, 30, 30, SRCPAINT);

      ReleaseDC(hwndMainWindow, hdc);
      SelectObject(hdcNowy, hbmOld);
      DeleteDC(hdcNowy);

      tabZbitychBiale[licznikZbicBialy] = figuraa;
      licznikZbicBialy++;
      XZbiteBiale = XZbiteBiale + 30;
      if (XZbiteBiale == 150)
      {
        XZbiteBiale = 0;
        YZbiteBiale = YZbiteBiale + 30;
      }

    }

    if (figuraa < 0)
    {

      HDC hdc = GetDC(hwndMainWindow), hdcNowy = CreateCompatibleDC(hdc);
      BITMAP bmInfo;
      HBITMAP hbmOld;
      GetObject(bitmap_figury[-figuraa + 5], sizeof(bmInfo), &bmInfo);
      hbmOld = (HBITMAP)SelectObject(hdcNowy, maski[-figuraa +5]);

      StretchBlt(hdc, XZbiteCzarne, YZbiteCzarne, 30, 30, hdcNowy, 0, 0, 30, 30, SRCAND);
      SelectObject(hdcNowy, bitmap_figury[-figuraa +5]);
      StretchBlt(hdc, XZbiteCzarne, YZbiteCzarne, 30, 30, hdcNowy, 0, 0, 30, 30, SRCPAINT);

      ReleaseDC(hwndMainWindow, hdc);
      SelectObject(hdcNowy, hbmOld);
      DeleteDC(hdcNowy);

      tabZbitychCzarne[licznikZbicCzarny] = figuraa;
      licznikZbicCzarny++;
      XZbiteCzarne = XZbiteCzarne + 30;
      if (XZbiteCzarne == 150)
      {
        XZbiteCzarne = 0;
        YZbiteCzarne = YZbiteCzarne + 30;
      }

    }


  
}

void Rysuj_Obramowanie(int x, int y, HBRUSH Pendzel)
{
  if (maksymalizowanie == false)
  {
    x = 200 + (x * 50);
    y = 150 + (y * 50); //dolny  lewy naroznk pola
    const RECT pole1 = { x,y,x + 5,y - 50 };
    FillRect(Okno, &pole1, Pendzel);
    y = y - 50; //gorny lewy naroznik
    const RECT pole2 = { x,y,x + 50,y + 5 };
    FillRect(Okno, &pole2, Pendzel);
   // Rectangle(Okno, x, y, x + 50, y + 5);
    x = x + 50;    //gorny prawy
    const RECT pole3 = { x,y,x -5,y + 50 };
    FillRect(Okno, &pole3, Pendzel);
   // Rectangle(Okno, x, y, x - 5, y + 50);
    y = y + 50;                //dolny prawy
    const RECT pole4 = { x,y,x - 50,y - 5 };
    FillRect(Okno, &pole4, Pendzel);
   // Rectangle(Okno, x, y, x - 50, y - 5);
  }
  else
  {
    x = 200 + (x * 100);
    y = 200 + (y * 100); //dolny  lewy naroznk pola
    const RECT pole1 = { x,y,x +7,y -100 };
    FillRect(Okno, &pole1, Pendzel);
   // Rectangle(Okno, x, y, x + 7, y - 100);
    y = y - 100; //gorny lewy naroznik
    const RECT pole2 = { x,y,x +100,y + 7 };
    FillRect(Okno, &pole2, Pendzel);
   // Rectangle(Okno, x, y, x + 100, y + 7);
    x = x + 100;    //gorny prawy
    const RECT pole3 = { x,y,x - 7,y + 100 };
    FillRect(Okno, &pole3, Pendzel);
   // Rectangle(Okno, x, y, x - 7, y + 100);
    y = y + 100;                //dolny prawy
    const RECT pole4 = { x,y,x - 100,y -7 };
    FillRect(Okno, &pole4, Pendzel);
   // Rectangle(Okno, x, y, x - 100, y - 7);
  }
}

void RysujRuch(int x, int y)
{
  OdswiezPlansze(mojeOkno);
  Zaznacz_figure(x, y);
  aktualna_plansza.Oblicz_ruch(x, y);
  HBRUSH Pendzel, Pudelko;
  Pendzel = CreateSolidBrush(0x0000FF);  //kolor obramowania
  Pudelko = (HBRUSH)SelectObject(Okno, Pendzel);
  for (int i = 0; i < 8; i++)
  {
    for (int j = 0; j < 8; j++)
    {
      if (GraczBialy)
      {
        if (aktualna_plansza.Sprawdz_ruch(i, j) == true && aktualna_plansza.pobierz(i, j) <= 0 && aktualna_plansza.ObliczSzach(x,y,i,j,0)==false)
        {

          Rysuj_Obramowanie(i, j,Pendzel);

        }
        if (aktualna_plansza.ObliczSzachBialych() == true && aktualna_plansza.pobierz(i,j)==6)
        {
          Pendzel = CreateSolidBrush(0xCC00CC);
          Rysuj_Obramowanie(i, j, Pendzel);
          Pendzel = CreateSolidBrush(0x0000FF);
        }
      }
      else
      {
        if (aktualna_plansza.Sprawdz_ruch(i, j) == true && aktualna_plansza.pobierz(i, j) >= 0 && aktualna_plansza.ObliczSzach(x, y, i, j, 1) == false)
        {

          Rysuj_Obramowanie(i, j,Pendzel);

        }
        if (aktualna_plansza.ObliczSzachCzarnych() == true && aktualna_plansza.pobierz(i, j) == -6)
        {
          Pendzel = CreateSolidBrush(0xCC00CC);
          Rysuj_Obramowanie(i, j, Pendzel);
          Pendzel = CreateSolidBrush(0x0000FF);
        }
      }
    }
  }
  SelectObject(Okno, Pudelko);
  DeleteObject(Pendzel);
  DeleteObject(Pudelko);
}

void Zaznacz_figure(int x, int y)
{
  HBRUSH Pendzel, Pudelko;
  Pendzel = CreateSolidBrush(0x00FF00);  //kolor obramowania
  Pudelko = (HBRUSH)SelectObject(Okno, Pendzel);
  Rysuj_Obramowanie(x, y,Pendzel);
  SelectObject(Okno, Pudelko);
  DeleteObject(Pendzel);
  DeleteObject(Pudelko);

}


void RozstawFigury(HWND hwndMainWindow)
{

  int figura;
  int kolor;
  int x;
  int y;
  for (int i = 0; i < 8; i++)
  {
    for (int j = 0; j < 8; j++)
    {
      figura = aktualna_plansza.pobierz(i, j);
      kolor = aktualna_plansza.kolor_pola(i,j);
      if (maksymalizowanie == false)
      {
        x = 200 + (i * 50);
        y = 100 + (j * 50);
      }
      else
      {
        x = 200 + (i * 100);
        y = 100 + (j * 100);
      }
      if (figura != 0)
      {
        if (figura > 0)
        {

          HDC hdc = GetDC(hwndMainWindow), hdcNowy = CreateCompatibleDC(hdc);
          BITMAP bmInfo;
          HBITMAP hbmOld;
          GetObject(bitmap_figury[figura - 1], sizeof(bmInfo), &bmInfo);
          hbmOld = (HBITMAP)SelectObject(hdcNowy, maski[figura-1]);
          if (maksymalizowanie == false)
          {
            StretchBlt(hdc, x, y, 50, 50, hdcNowy, 0, 0, 30, 30, SRCAND);
            SelectObject(hdcNowy, bitmap_figury[figura - 1]);
            StretchBlt(hdc, x, y, 50, 50, hdcNowy, 0, 0, 30, 30, SRCPAINT);
          }
          else
          {
            StretchBlt(hdc, x, y, 100, 100, hdcNowy, 0, 0, 30, 30, SRCAND);
            SelectObject(hdcNowy, bitmap_figury[figura - 1]);
            StretchBlt(hdc, x, y, 100, 100, hdcNowy, 0, 0, 30, 30, SRCPAINT);
          }
         
          ReleaseDC(hwndMainWindow, hdc);
          SelectObject(hdcNowy, hbmOld);
          DeleteDC(hdcNowy);
        }
        else
        {
          HDC hdc = GetDC(hwndMainWindow), hdcNowy = CreateCompatibleDC(hdc);
          BITMAP bmInfo;
          HBITMAP hbmOld;
          GetObject(bitmap_figury[-figura +5], sizeof(bmInfo), &bmInfo);
          hbmOld = (HBITMAP)SelectObject(hdcNowy, maski[-figura + 5]);
          if (maksymalizowanie == false)
          {
            StretchBlt(hdc, x, y, 50, 50, hdcNowy, 0, 0, 30, 30, SRCAND);
            SelectObject(hdcNowy, bitmap_figury[-figura + 5]);
            StretchBlt(hdc, x, y, 50, 50, hdcNowy, 0, 0, 30, 30, SRCPAINT);
          }
          else
          {
            StretchBlt(hdc, x, y, 100, 100, hdcNowy, 0, 0, 30, 30, SRCAND);
            SelectObject(hdcNowy, bitmap_figury[-figura + 5]);
            StretchBlt(hdc, x, y, 100, 100, hdcNowy, 0, 0, 30, 30, SRCPAINT);
          }

          ReleaseDC(hwndMainWindow, hdc);
          SelectObject(hdcNowy, hbmOld);
          DeleteDC(hdcNowy);

        }
      }
    }
  }
 
}

void Zamaluj(int x, int y)
{
  int kolor = aktualna_plansza.kolor_pola(x, y);
  if (kolor == 1)
  {
    HBRUSH PendzelCzarny, Pudelko;
    PendzelCzarny = CreateSolidBrush(0x193367);
    Pudelko = (HBRUSH)SelectObject(Okno, PendzelCzarny);
    int xx,yy;
    if (maksymalizowanie == false)
    {
       xx = (x * 50) + 200;
       yy = (y * 50) + 100;

   //   Rectangle(Okno, xx, yy, xx + 50, yy + 50);
      const RECT pole = { xx,yy,xx +50,yy + 50 };
      FillRect(Okno, &pole, PendzelCzarny);
     }
    else
    {
      xx = (x * 100) + 200;
      yy = (y * 100) + 100;
    //  Rectangle(Okno, xx, yy, xx + 100, yy + 100);
      const RECT pole = { xx,yy,xx + 100,yy + 100 };
      FillRect(Okno, &pole, PendzelCzarny);
    }
    SelectObject(Okno, Pudelko);
    DeleteObject(PendzelCzarny);
    DeleteObject(Pudelko);
  }
  else
  {
    HBRUSH PedzelBialy, Pudelko;
    PedzelBialy = CreateSolidBrush(0xC0C0C0);
    Pudelko = (HBRUSH)SelectObject(Okno, PedzelBialy);
    int xx, yy;
    if (maksymalizowanie == false)
    {
      xx = (x * 50) + 200;
      yy = (y * 50) + 100;
      const RECT pole = { xx,yy,xx + 50,yy + 50 };
      FillRect(Okno, &pole, PedzelBialy);
    }
    else
    {
      xx = (x * 100) + 200;
      yy = (y * 100) + 100;
      const RECT pole = { xx,yy,xx + 100,yy + 100 };
      FillRect(Okno, &pole, PedzelBialy);
    }

    SelectObject(Okno, Pudelko);
    DeleteObject(PedzelBialy);
    DeleteObject(Pudelko);
  }
}

void CzyscPlansze()
{
  HBRUSH PedzelBialy, Pudelko;
  PedzelBialy = CreateSolidBrush(0xC0C0C0);
  Pudelko = (HBRUSH)SelectObject(Okno, PedzelBialy);
  if(maksymalizowanie==false)
  Rectangle(Okno, 200, 100, 600, 500);
  else
  Rectangle(Okno, 200, 100, 1000, 900);
  SelectObject(Okno, Pudelko);
  DeleteObject(PedzelBialy);
  DeleteObject(Pudelko);

}


void RysujPlansze()
{


  HBRUSH PendzelCzarny, Pudelko;
  PendzelCzarny = CreateSolidBrush(0x193367);
  Pudelko = (HBRUSH)SelectObject(Okno, PendzelCzarny);
  if (maksymalizowanie == false)
  {
    int x = 250;
    int y = 100;
    int licznik = 0;
    for (int i = 1; i < 9; i++)
    {
      for (int j = 1; j < 5; j++)
      {
        Rectangle(Okno, x, y, x + 50, y + 50);
        x = x + 100;
      }
      if (licznik % 2 == 0)
      {
        licznik++;
        y = y + 50;
        x = 200;
      }
      else
      {
        licznik++;
        y = y + 50;
        x = 250;
      }
    }

  }
  else
  {
    int x = 300;
    int y = 100;
    int licznik = 0;
    for (int i = 1; i < 9; i++)
    {
      for (int j = 1; j < 5; j++)
      {
        Rectangle(Okno, x, y, x + 100, y + 100);
        x = x + 200;
      }
      if (licznik % 2 == 0)
      {
        licznik++;
        y = y + 100;
        x = 200;
      }
      else
      {
        licznik++;
        y = y + 100;
        x = 300;
      }
    }
  }
  SelectObject(Okno, Pudelko);
  DeleteObject(PendzelCzarny);
  DeleteObject(Pudelko);
}


void RysujPolaZbic(int x1, int y1, int x2, int y2)
{
  HBRUSH PendzelCzarny, Pudelko;
  PendzelCzarny = CreateSolidBrush(0xFFFFCC);
  Pudelko = (HBRUSH)SelectObject(Okno, PendzelCzarny);
  const RECT dolny = {x1,y1,x1+150,y1+120};
  const RECT gorny = {x2,y2,x2+150,y2+120};
  FillRect(Okno, &dolny, PendzelCzarny);
  FillRect(Okno, &gorny, PendzelCzarny);
  SelectObject(Okno, Pudelko);
  DeleteObject(PendzelCzarny);
  DeleteObject(Pudelko);
}


void WarunkiStartowe(HWND hwndMainWindow)
{
  aktualna_plansza.Zresetuj_(aktualna_plansza);
  pierwszyRuchBialych = true;
  pierwszyRuchCzarnych = true;
  kliknieciePrawym = false;
  Zamianafigury = false;
  pierwszypionek = false;
  klikniecie = false;
  JedenGracz = false;
  licznikZbicBialy = licznikZbicCzarny = 0;
  for (int i = 0; i < 15; i++)
  {
    tabZbitychBiale[i] = 0;
    tabZbitychCzarne[i] = 0;
  }
  int licz1 = 2;
  int licz2 = -2;
  for (int i = 0; i < 4; i++)
  {
    tablicaZmianBiale[i] = licz1 ;
    tablicaZmianCzarne[i] = licz2;
    licz1 ++ ;
    licz2 --;

  }
  RuszanaBialaLewaWieza = RuszanaBialaPrawaWieza = RuszanyBialyKrol = false;
  RuszanaCzarnaLewaWieza = RuszanaBialaPrawaWieza = RuszanyCzarnyKrol = false;
  XZbiteBiale = 0;
  YZbiteBiale = 150;
  XZbiteCzarne = 0;
  YZbiteCzarne = 420;
  RysujPolaZbic(XZbiteBiale,YZbiteBiale,XZbiteCzarne,YZbiteCzarne);
  Okno = GetDC(hwndMainWindow);
  RysujGracza(hwndMainWindow);
  OdswiezPlansze(hwndMainWindow);
}

void RozstawZbicia(HWND hwndMainWindow)
{
  int x1 = 0;
  int y1 = 150;
  int x2 = 0;
  int y2 = 420;
  int figura;
  for (int i = 0; i < 15; i++)
  {
    figura = tabZbitychBiale[i];
    if (figura > 0)
    {

      HDC hdc = GetDC(hwndMainWindow), hdcNowy = CreateCompatibleDC(hdc);
      BITMAP bmInfo;
      HBITMAP hbmOld;
      GetObject(bitmap_figury[figura - 1], sizeof(bmInfo), &bmInfo);
      hbmOld = (HBITMAP)SelectObject(hdcNowy, maski[figura - 1]);

      StretchBlt(hdc, x1, y1, 30, 30, hdcNowy, 0, 0, 30, 30, SRCAND);
      SelectObject(hdcNowy, bitmap_figury[figura - 1]);
      StretchBlt(hdc, x1, y1, 30, 30, hdcNowy, 0, 0, 30, 30, SRCPAINT);

      ReleaseDC(hwndMainWindow, hdc);
      SelectObject(hdcNowy, hbmOld);
      DeleteDC(hdcNowy);

      x1 = x1 + 30;
      if (x1 == 150)
      {
        x1 = 0;
        y1 = y1 + 30;
      }
    }
  }

  for (int i = 0; i < 15; i++)
  {
    figura = tabZbitychCzarne[i];
    if (figura < 0)
    {
      HDC hdc = GetDC(hwndMainWindow), hdcNowy = CreateCompatibleDC(hdc);
      BITMAP bmInfo;
      HBITMAP hbmOld;
      GetObject(bitmap_figury[-figura + 5], sizeof(bmInfo), &bmInfo);
      hbmOld = (HBITMAP)SelectObject(hdcNowy, maski[-figura + 5]);

      StretchBlt(hdc, x2, y2, 30, 30, hdcNowy, 0, 0, 30, 30, SRCAND);
      SelectObject(hdcNowy, bitmap_figury[-figura + 5]);
      StretchBlt(hdc, x2, y2, 30, 30, hdcNowy, 0, 0, 30, 30, SRCPAINT);

      ReleaseDC(hwndMainWindow, hdc);
      SelectObject(hdcNowy, hbmOld);
      DeleteDC(hdcNowy);
      x2 = x2 + 30;
      if (x2 == 150)
      {
        x2 = 0;
        y2 = y2 + 30;
      }
    }
  }

}

void RysujNapis(HWND hwndMainWindow)
{
  HBRUSH PendzelCzarny, Pudelko;
  PendzelCzarny = CreateSolidBrush(0xFFFFCC);
  Pudelko = (HBRUSH)SelectObject(Okno, PendzelCzarny);
  const RECT pole = { 170,100,200,900 };
  FillRect(Okno, &pole, PendzelCzarny);
  SelectObject(Okno, Pudelko);
  DeleteObject(PendzelCzarny);
  DeleteObject(Pudelko);
  HDC hdc = GetDC(hwndMainWindow), hdcNowy = CreateCompatibleDC(hdc);
  BITMAP bmInfo;
  HBITMAP hbmOld;
  GetObject(napis, sizeof(bmInfo), &bmInfo);
  hbmOld = (HBITMAP)SelectObject(hdcNowy, maskanapis);
 
  StretchBlt(hdc, 200, 40, 190, 25, hdcNowy, 0, 0, 286, 35, SRCAND);
  SelectObject(hdcNowy, napis);
  StretchBlt(hdc, 200, 40, 190, 25, hdcNowy, 0, 0, 286, 35, SRCPAINT);

  ReleaseDC(hwndMainWindow, hdc);
  SelectObject(hdcNowy, hbmOld);
  DeleteDC(hdcNowy);
  int xcyfry;
  int ycyfry;
  int ycyfryprzyrost;
  int xlitery;
  int ylitery;
  int xliteryprzyrost;

  if (maksymalizowanie==false)
  {
    ycyfry = 460;
    ycyfryprzyrost = 50;
    xcyfry = 170;
    ylitery = 505;
    xlitery = 210;
    xliteryprzyrost = 50;
  }
  else
  {
    ycyfry = 840;
    ycyfryprzyrost = 100;
    xcyfry = 170;
    ylitery = 910;
    xlitery = 235;
    xliteryprzyrost = 100;
  }

    for (int i = 0; i < 8;i++)
    {
      HDC hdc = GetDC(hwndMainWindow), hdcNowy = CreateCompatibleDC(hdc);
      BITMAP bmInfo;
      HBITMAP hbmOld;
      GetObject(cyfry[i], sizeof(bmInfo), &bmInfo);
      hbmOld = (HBITMAP)SelectObject(hdcNowy, maskicyfry[i]);

      StretchBlt(hdc, xcyfry, ycyfry,30,30, hdcNowy, 0, 0, 30, 30, SRCAND);
      SelectObject(hdcNowy, cyfry[i]);
      StretchBlt(hdc, xcyfry, ycyfry,30, 30, hdcNowy, 0, 0, 30, 30, SRCPAINT);

      ReleaseDC(hwndMainWindow, hdc);
      SelectObject(hdcNowy, hbmOld);
      DeleteDC(hdcNowy);
      ycyfry = ycyfry - ycyfryprzyrost;

      hdc = GetDC(hwndMainWindow), hdcNowy = CreateCompatibleDC(hdc);
      bmInfo;
      hbmOld;
      GetObject(litery[i], sizeof(bmInfo), &bmInfo);
      hbmOld = (HBITMAP)SelectObject(hdcNowy, maskilitery[i]);

      StretchBlt(hdc, xlitery, ylitery, 30, 30, hdcNowy, 0, 0, 30, 30, SRCAND);
      SelectObject(hdcNowy, litery[i]);
      StretchBlt(hdc, xlitery, ylitery, 30, 30, hdcNowy, 0, 0, 30, 30, SRCPAINT);

      ReleaseDC(hwndMainWindow, hdc);
      SelectObject(hdcNowy, hbmOld);
      DeleteDC(hdcNowy);
      xlitery = xlitery + xliteryprzyrost;
    }


}

void OdswiezPlansze(HWND hwndMainWindow)
{

  ZrobTlo(hwndMainWindow);
  RysujPolaZbic(0, 150, 0, 420);
  RozstawZbicia(hwndMainWindow);
  CzyscPlansze();
  RysujPlansze();
  RozstawFigury(hwndMainWindow);
  WstawPrzyciski(hwndMainWindow);
  RysujNapis(hwndMainWindow);
  if (Zamianafigury == true)
  {
    if (GraczBialy == true)
    {
      if (maksymalizowanie == true)
        NarysujZmianeFigur(1050, 1150, 300, 700, 1);
      else
        NarysujZmianeFigur(620, 670, 200, 400, 1);
    }
    else
    {
      if (maksymalizowanie == true)
        NarysujZmianeFigur(1050, 1150, 300, 700, 0);
      else
        NarysujZmianeFigur(620, 670, 200, 400, 0);
    }
  }
}

void OczyscZmiany()
{
  if (maksymalizowanie == true)
  {
    HBRUSH PendzelCzarny, Pudelko;
    PendzelCzarny = CreateSolidBrush(0xFFFFCC);
    Pudelko = (HBRUSH)SelectObject(Okno, PendzelCzarny);
    const RECT dolny = { 1050,300,1150,700 };
    FillRect(Okno, &dolny, PendzelCzarny);
    SelectObject(Okno, Pudelko);
    DeleteObject(PendzelCzarny);
    DeleteObject(Pudelko);
  }
  else
  {
    HBRUSH PendzelCzarny, Pudelko;
    PendzelCzarny = CreateSolidBrush(0xFFFFCC);
    Pudelko = (HBRUSH)SelectObject(Okno, PendzelCzarny);
    const RECT dolny = { 620,200,670,400 };
    FillRect(Okno, &dolny, PendzelCzarny);
    SelectObject(Okno, Pudelko);
    DeleteObject(PendzelCzarny);
    DeleteObject(Pudelko);
  }
  HBRUSH PendzelCzarny, Pudelko;
  PendzelCzarny = CreateSolidBrush(0xFFFFCC);
  Pudelko = (HBRUSH)SelectObject(Okno, PendzelCzarny);
  const RECT dolny = { 550,10,650,60 };
  FillRect(Okno, &dolny, PendzelCzarny);
  SelectObject(Okno, Pudelko);
  DeleteObject(PendzelCzarny);
  DeleteObject(Pudelko);
}

void DzwiekZbicia()
{
  sndPlaySound("..//res//zbicie.wav", SND_ASYNC);
}

void DzwiekRuchu()
{

  sndPlaySound("..//res//ruch.wav", SND_ASYNC);
}

void DzwiekNiepoprawny()
{

  sndPlaySound("..//res//niepoprawny.wav", SND_ASYNC);
}

void DzwiekZaznaczenia()
{
  sndPlaySound("..//res//zaznaczenie.wav", SND_ASYNC);
}

void DzwiekRoszady()
{
  sndPlaySound("..//res//roszada.wav", SND_ASYNC);
}

void DzwiekKoncaGry()
{
  sndPlaySound("..//res//wygrana.wav", SND_ASYNC);
}

void SprawdzKoniec()
{
  if (JedenGracz==true && jedenGraczWykonalRuch==true)
  {
    if (jedenGraczWykonalRuch == true && aktualna_plansza.SzachMatCzarnych() == true)
    {
      DzwiekKoncaGry();
      GameOnn = false;
      MessageBox(mojeOkno, " BRAWO !", "WYGRANA!!!!", MB_OK);
      }
    else
    {
      DzwiekNiepoprawny();
      GameOnn = false;
      int id=MessageBox(mojeOkno, "NIE DA£EŒ RADY ! CZY CHCESZ SPRÓBOWA JESZCZE RAZ ?", "Przegrana!!!!", MB_YESNO | MB_ICONQUESTION);
      if (id == IDYES)
      {
        JedenGracz = true;
        GameOnn = true;
        jedenGraczWykonalRuch = false;
        for (int i = 0; i < 8; i++)
        {
          for (int j = 0; j < 8; j++)
          {
            aktualna_plansza.ustaw(tablicaSytuacji[liczbaPoje].Wczytaj(i, j), i, j);
          }
        }
        pierwszyRuchBialych = false;
        pierwszyRuchCzarnych = false;
        kliknieciePrawym = false;
        Zamianafigury = false;
        pierwszypionek = false;
        klikniecie = false;
        GameOnn = true;
        GraczBialy = true;
        licznikZbicBialy = licznikZbicCzarny = 0;
        for (int i = 0; i < 15; i++)
        {
          tabZbitychBiale[i] = 0;
          tabZbitychCzarne[i] = 0;
        }
        int licz1 = 2;
        int licz2 = -2;
        for (int i = 0; i < 4; i++)
        {
          tablicaZmianBiale[i] = licz1;
          tablicaZmianCzarne[i] = licz2;
          licz1++;
          licz2--;

        }
        RuszanaBialaLewaWieza = RuszanaBialaPrawaWieza = RuszanyBialyKrol = true;
        RuszanaCzarnaLewaWieza = RuszanaBialaPrawaWieza = RuszanyCzarnyKrol = true;
        XZbiteBiale = 0;
        YZbiteBiale = 150;
        XZbiteCzarne = 0;
        YZbiteCzarne = 420;
        RysujPolaZbic(XZbiteBiale, YZbiteBiale, XZbiteCzarne, YZbiteCzarne);
        Okno = GetDC(mojeOkno);
        RysujGracza(mojeOkno);
        OdswiezPlansze(mojeOkno);
      }
    }
  }
  else
  {

    if (GraczBialy == true)
    {
      if (aktualna_plansza.SzachMatBialych() == true)
      {
        DzwiekKoncaGry();
        GameOnn = false;
        MessageBox(mojeOkno, "SZACH MAT CZARNE WYGRA£Y !", "WYGRANA!!!!", MB_OK);

      }
      if (aktualna_plansza.PatBialych() == true)
      {
        DzwiekKoncaGry();
        GameOnn = false;
        MessageBox(mojeOkno, "SYTUACJA PATOWA !", "PAT!!!!", MB_OK);

      }
    }
    else
    {
      if (aktualna_plansza.SzachMatCzarnych() == true)
      {
        DzwiekKoncaGry();
        GameOnn = false;
        MessageBox(mojeOkno, "SZACH MAT BIA£E WYGRA£Y !", "WYGRANA!!!!", MB_OK);

      }
      if (aktualna_plansza.PatCzarnych() == true)
      {
        DzwiekKoncaGry();
        GameOnn = false;
        MessageBox(mojeOkno, "SYTUACJA PATOWA !", "PAT!!!!", MB_OK);

      }
    }
  }
}

void UstawPojedynczegoGracza()
{
  int tablica[8][8] = { 0 };
  for (int i = 0; i < 10; i++)
  {
    switch (i)
    {
    case 0:
      for (int x = 0; x < 8; x++)
      {
        for (int y = 0; y < 8; y++)
        {
          tablica[x][y] = aa[x][y];
        }
      }
      break;
    case 1:
      for (int x = 0; x < 8; x++)
      {
        for (int y = 0; y < 8; y++)
        {
          tablica[x][y] = bb[x][y];
        }
      }
      break;
    case 2:
      for (int x = 0; x < 8; x++)
      {
        for (int y = 0; y < 8; y++)
        {
          tablica[x][y] = c[x][y];
        }
      }
      break;
    case 3:
      for (int x = 0; x < 8; x++)
      {
        for (int y = 0; y < 8; y++)
        {
          tablica[x][y] = d[x][y];
        }
      }
      break;
    case 4:
      for (int x = 0; x < 8; x++)
      {
        for (int y = 0; y < 8; y++)
        {
          tablica[x][y] = e[x][y];
        }
      }
      break;
    case 5:
      for (int x = 0; x < 8; x++)
      {
        for (int y = 0; y < 8; y++)
        {
          tablica[x][y] = f[x][y];
        }
      }
      break;
    case 6:
      for (int x = 0; x < 8; x++)
      {
        for (int y = 0; y < 8; y++)
        {
          tablica[x][y] = g[x][y];
        }
      }
      break;
    case 7:
      for (int x = 0; x < 8; x++)
      {
        for (int y = 0; y < 8; y++)
        {
          tablica[x][y] = h[x][y];
        }
      }
      break;
    case 8:
      for (int x = 0; x < 8; x++)
      {
        for (int y = 0; y < 8; y++)
        {
          tablica[x][y] = k[x][y];
        }
      }
      break;
    case 9:
      for (int x = 0; x < 8; x++)
      {
        for (int y = 0; y < 8; y++)
        {
          tablica[x][y] = l[x][y];
        }
      }
      break;
     }
    tablicaSytuacji[i].ustawWrtosci(tablica);
  }


}

bool SprawdzPoprawnoscTestowa()
{
  int liczPionkiCzarne = 0;
  int liczPionkiBiale = 0;
  int liczKrolCzarne = 0;
  int liczKrolBiale = 0;
  for (int i = 0; i < 8; i++)
  {
    for (int j = 0; j < 8; j++)
    {
      switch (test[i][j])
      {
      case 1:
        liczPionkiBiale++;
        break;
      case -1:
        liczPionkiCzarne++;
        break;
      case 6:
        liczKrolBiale++;
        break;
      case -6:
        liczKrolCzarne++;
        break;

      }
    }
  }
  if (liczPionkiBiale > 8 || liczPionkiCzarne > 8)
    return false;
  if (liczKrolBiale != 1 || liczKrolCzarne != 1)
    return false;

  return true;
}

void RysujGracza(HWND hwndMainWindow)
{

  HBRUSH PendzelCzarny, Pudelko;
  PendzelCzarny = CreateSolidBrush(0xFFFFCC);
  Pudelko = (HBRUSH)SelectObject(Okno, PendzelCzarny);
  const RECT pole = { 400,30,450,80 };
  FillRect(Okno, &pole, PendzelCzarny);
  SelectObject(Okno, Pudelko);
  DeleteObject(PendzelCzarny);
  DeleteObject(Pudelko);
  if (GraczBialy)
  {
    HDC hdc = GetDC(hwndMainWindow), hdcNowy = CreateCompatibleDC(hdc);
    BITMAP bmInfo;
    HBITMAP hbmOld;
    GetObject(bitmap_figury[5], sizeof(bmInfo), &bmInfo);
    hbmOld = (HBITMAP)SelectObject(hdcNowy, maski[5]);
    StretchBlt(hdc, 400, 30, 40, 40, hdcNowy, 0, 0, 30, 30, SRCAND);
    SelectObject(hdcNowy, bitmap_figury[5]);
    StretchBlt(hdc, 400, 30, 40, 40, hdcNowy, 0, 0, 30, 30, SRCPAINT);
    ReleaseDC(hwndMainWindow, hdc);
    SelectObject(hdcNowy, hbmOld);
    DeleteDC(hdcNowy);
  }
  else
  {
    HDC hdc = GetDC(hwndMainWindow), hdcNowy = CreateCompatibleDC(hdc);
    BITMAP bmInfo;
    HBITMAP hbmOld;
    GetObject(bitmap_figury[11], sizeof(bmInfo), &bmInfo);
    hbmOld = (HBITMAP)SelectObject(hdcNowy, maski[11]);
    StretchBlt(hdc, 400, 30, 40, 40, hdcNowy, 0, 0, 30, 30, SRCAND);
    SelectObject(hdcNowy, bitmap_figury[11]);
    StretchBlt(hdc, 400, 30, 40, 40, hdcNowy, 0, 0, 30, 30, SRCPAINT);
    ReleaseDC(hwndMainWindow, hdc);
    SelectObject(hdcNowy, hbmOld);
    DeleteDC(hdcNowy);
  }
}

void WstawPrzyciski(HWND hwndMainWindow)
{
  HDC hdcNowy = CreateCompatibleDC(Okno);
  HDC hdc=GetDC(hwndMainWindow);
  SelectObject(hdcNowy, bitmap_Przyciski);
  HBITMAP hbmOld = (HBITMAP)SelectObject(hdcNowy, bitmap_Przyciski);
  BITMAP bmInfo;
  GetObject(bitmap_Przyciski, sizeof(bmInfo), &bmInfo);
  StretchBlt(hdc, 10, 12, 147, 122, hdcNowy, 0, 0, 274, 220, SRCCOPY);
  ReleaseDC(hwndMainWindow, hdc);
  SelectObject(hdcNowy, hbmOld);
  DeleteDC(hdcNowy);
  hdcNowy = CreateCompatibleDC(Okno);
  hdc = GetDC(hwndMainWindow);
  SelectObject(hdcNowy, napisPro);
  hbmOld = (HBITMAP)SelectObject(hdcNowy, napisPro);
  GetObject(napisPro, sizeof(bmInfo), &bmInfo);
  StretchBlt(hdc, 157, 12, 95, 67, hdcNowy, 0, 0, 120, 150, SRCCOPY);
  ReleaseDC(hwndMainWindow, hdc);
  SelectObject(hdcNowy, hbmOld);
  DeleteDC(hdcNowy);
}

void WyswietlCzas(int min,int sek)
{
  usatwianietekstu = TRUE;
  wsprintf(tabznakow, "%d:%d", min, sek);
  if(GraczBialy)
  SetWindowText(hwndText1, tabznakow);
  else
    SetWindowText(hwndText2, tabznakow);
  usatwianietekstu = FALSE;
}

void WyswietlCzas()
{
  usatwianietekstu = TRUE;
  sprintf_s(tabznakow, "--:--");
  SetWindowText(hwndText1, tabznakow);
  SetWindowText(hwndText2, tabznakow);
  usatwianietekstu = FALSE;

}

int WINAPI WinMain(HINSTANCE hinstance, HINSTANCE hPrevinstance, PSTR szCmdLIne, int iCmdShow)
{
  hthisInstance = hinstance;
  HWND hwndMainWindow = CreateDialog(hinstance, MAKEINTRESOURCE(IDD_MAINVIEW), NULL, DialogProc);
  ShowWindow(hwndMainWindow, iCmdShow);
  mojeOkno = hwndMainWindow;
  hwndText1 = GetDlgItem(mojeOkno, IDC_EDIT1);
  hwndText2 = GetDlgItem(mojeOkno, IDC_EDIT2);
  MSG msg = {};
  Okno = GetDC(hwndMainWindow);
  WarunkiStartowe(hwndMainWindow);
  UstawPojedynczegoGracza();
  for (int i = 0; i < 10; i++)
    JedenGraczWarianty[i] = false;
  srand(unsigned int(time(NULL)));
  WstawPrzyciski(hwndMainWindow);
  WyswietlCzas();

  RECT rozmiarokna;
  GetWindowRect(hwndMainWindow, &rozmiarokna);
  starawysokosc = rozmiarokna.bottom - rozmiarokna.top;

  SetTimer(hwndMainWindow,0,200,NULL);
  while (GetMessage(&msg, NULL, 0, 0))
  {

    TranslateMessage(&msg);
    DispatchMessage(&msg);

  }
  return 0;
}


void DeleteBitmaps()
{
  for (int i = 0; i < 12; i++)
  {
    DeleteObject(bitmap_figury[i]);
    DeleteObject(maski[i]);
  }
  for (int i = 0; i < 8; i++)
  {
    DeleteObject(litery[i]);
    DeleteObject(cyfry[i]);
    DeleteObject(maskicyfry[i]);
    DeleteObject(maskicyfry[i]);
  }
  DeleteObject(napis);
  DeleteObject(maskanapis);
  DeleteObject(bitmap_Przyciski);
  DeleteObject(napisZmiany);
  DeleteObject(maskaNapisZmiany);
  DeleteObject(napisPro);
}
