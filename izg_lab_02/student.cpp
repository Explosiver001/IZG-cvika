/******************************************************************************
 * Laborator 02 - Zaklady pocitacove grafiky - IZG
 * isolony@fit.vutbr.cz
 *
 * $Id: $
 * 
 * Popis: Hlavicky funkci pro funkce studentu
 *
 * Opravy a modifikace:
 * ipolasek@fit.vutbr.cz
 * ivelas@fit.vutbr.cz
 * itomesek@fit.vutbr.cz
 */

#include "student.h"
#include "globals.h"

// Header standardni knihovny obsahujici funci mySwap.
#include <memory>
// Zjednoduseni zapisu, napr. std::mySwap -> mySwap.
using namespace std;

/**
 * Provede vykresleni pixelu na dane pozici ve vystupnim rasteru. Pokud je
 * souradnice mimo hranice rasteru, potom tato funkce neprovede zadnou zmenu.
 */
S_RGBA getPixel(int x, int y)
{
    if (x >= 0 && y >= 0 && x < gWidth && y < gHeight)
    { return gFrameBuffer[y * gWidth + x]; }
    else
    { return makeBlackColor(); }
}



/** 
 * Vycte barvu pixelu na dane pozici ve vystupnim rasteru. Pokud je souradnice
 * mimo hranice rasteru, potom funkce vraci barvu (0, 0, 0, 0).
 */
void setPixel(int x, int y, S_RGBA color)
{
    if (x >= 0 && y >= 0 && x < gWidth && y < gHeight)
    { 
            gFrameBuffer[y * gWidth + x] = color;
    }
}

void swap(int& x, int& y)
{
    int temp = x;
    x = y;
    y = temp;
}

int myAbs(int x) {
    if (x >= 0)
        return x;
    else
        return -x;
}

////////////////////////////////////////////////////////////////////////////////
// Ukol za 2b
////////////////////////////////////////////////////////////////////////////////
#define FRAC_BITS 8
/* Vykresli usecku od [x1, y1] po [x2, y2] vcetne koncovych bodu */
void drawLine(int x1, int y1, int x2, int y2, S_RGBA color)
{
    /*
     * Doplnte do funkce na oznacena mista (#) kod tak, aby po stisku klavesy
     * T aplikace spravne vykreslila cely testovaci vzor se vsemi kvadranty:
     *
     *   ╲  ┃  ╱
     *    ╲ ┃ ╱
     *  ━━━━╋━━━━
     *    ╱ ┃ ╲
     *   ╱  ┃  ╲
     */

     // Namisto "int dx = x2 - x1", lze v modernim c++ pouzit: 

    bool axisSwap = false;

    auto dx{ x2 - x1 };
    auto dy{ y2 - y1 };
    
    if (myAbs(dy) > myAbs(dx)) {
        axisSwap = true;
        swap(dx, dy);
        swap(x1, y1);
        swap(x2, y2);
    }
    
    // #1 : Doplnte kod pro kontrolu vstupu a upravu koordinatu pro ruzne kvadranty.
    
    if (x1 > x2) {
        swap(x1, x2);
        swap(y1, y2);
    }
    
    auto y{ y1 << FRAC_BITS };
    auto k{ dx == 0 ? 0 : (dy << FRAC_BITS) / dx };



    for (int x = x1; x <= x2; ++x)
    {
        // #2 : Doplnte kod pro upravu koordinatu pro ruzne kvadranty, pripadne upravte i putPixel(...).

        if(!axisSwap)
            setPixel(x, y >> FRAC_BITS, color);
        else
            setPixel(y >> FRAC_BITS, x, color);


        y += k;
    } 
}

////////////////////////////////////////////////////////////////////////////////
// Ukol za 1b
////////////////////////////////////////////////////////////////////////////////
void put8PixelsOfCircle(int x, int y, int s1, int s2, S_RGBA color)
{
    /*
     * Doplnte do funkce kod tak, aby po stisku klavesy T aplikace spravne
     * vykreslila testovaci vzor s kruznici ve vsech kvadrantech: 
     *
     * ╭────┳────╮
     * │    ┃    │
     * │    ┃    │
     * ┣━━━━╋━━━━┫
     * │    ┃    │
     * │    ┃    │
     * ╰────┻────╯
     */
    setPixel(x + s1, y + s2, color);
}

/* Vykresli kruznici se stredem v [s1, s2] o polomeru radius */
void drawCircle(int s1, int s2, float radius, S_RGBA color)
{
    const auto r{ static_cast<int>(radius) };

    /* Zaciname na pozici [r, 0] a iterujeme pres nejmensi zmenu, tedy y! */
    auto x{ r };
    auto y{ 0 };

    auto P{ 1 - r };
    auto X2{ 2 - 2 * r };
    auto Y2{ 3 };

    while (x >= y) 
    {
        
        put8PixelsOfCircle(x, y, s1, s2, color);
        put8PixelsOfCircle(-x, y, s1, s2, color);
        put8PixelsOfCircle(x, -y, s1, s2, color);
        put8PixelsOfCircle(-x, -y, s1, s2, color);
        put8PixelsOfCircle(y, x, s1, s2, color);
        put8PixelsOfCircle(-y, x, s1, s2, color);
        put8PixelsOfCircle(y, -x, s1, s2, color);
        put8PixelsOfCircle(-y, -x, s1, s2, color);
        

        if (P >= 0) 
        {
            P += X2;
            X2 += 2;
            --x;
        }

        P += Y2;
        Y2 += 2;
        ++y;
    }
}

/*****************************************************************************/
/*****************************************************************************/