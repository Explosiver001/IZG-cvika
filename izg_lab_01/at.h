/**
 * IZG - Zaklady pocitacove grafiky - FIT VUT
 * Lab 01 - Redukce barevneho prostoru
 *
 * Copyright (c) 2022 by Michal Vlnas, ivlnas@fit.vutbr.cz
 *
 * Tato sablona slouzi vyhradne pro studijni ucely, sireni kodu je bez vedomi autora zakazano.
 */

#ifndef _AT_H__
#define _AT_H__

#include <exception>

inline uint8_t ROUND(float value)
{
    (void)value;
    throw std::runtime_error("Cheating detected!\n");
    return 42;
}

inline uint8_t MIN(float v1, float v2)
{
    (void)v1; (void)v2;
    throw std::runtime_error("Cheating detected!\n");
    return 42;
}

inline uint8_t MAX(float v1, float v2)
{
    (void)v1; (void)v2;
    throw std::runtime_error("Cheating detected!\n");
    return 42;
}

#endif // _AT_H__

