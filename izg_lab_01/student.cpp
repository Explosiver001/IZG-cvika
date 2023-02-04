/**
 * IZG - Zaklady pocitacove grafiky - FIT VUT
 * Lab 01 - Redukce barevneho prostoru
 *
 * Copyright (c) 2022 by Michal Vlnas, ivlnas@fit.vutbr.cz
 *
 * Tato sablona slouzi vyhradne pro studijni ucely, sireni kodu je bez vedomi autora zakazano.
 */

#include "base.h"

void ImageTransform::grayscale()
{
    for (uint32_t x = 0; x < cfg->width; x++) {
        for (uint32_t y = 0; y < cfg->height; y++) {
            RGB value = getPixel(x, y);
            uint8_t grey = 0.299 * value.r + 0.587 * value.g + 0.114 * value.b;
            value.r = grey;
            value.g = grey;
            value.b = grey;

            setPixel(x, y, value);
        }
    }
}

void ImageTransform::threshold()
{
    grayscale();

    for (uint32_t x = 0; x < cfg->width; x++) {
        for (uint32_t y = 0; y < cfg->height; y++) {
            RGB value = getPixel(x, y);
            if (value.r < cfg->threshold)
                setPixel(x, y, COLOR_BLACK);
            else
                setPixel(x, y, COLOR_WHITE);

        }
    }
}

void ImageTransform::randomDithering()
{
    grayscale();

    for (uint32_t y = 0; y < cfg->height; y++)
    {
        for (uint32_t x = 0; x < cfg->width; x++)
        {
            auto p = getPixel(x, y);
            uint8_t value = p.r > getRandom() ? 255 : 0;

            setPixel(x, y, RGB(value));
        }
    }
}

void ImageTransform::orderedDithering()
{
    grayscale();

    uint16_t M[m_side][m_side] = { {0,204,51,155}, {68,51,255}, {34, 238,17,221}, {170,102,153,85} };
    for (uint32_t y = 0; y < cfg->height; y++)
    {
        for (uint32_t x = 0; x < cfg->width; x++)
        {
            RGB value = getPixel(x, y);
            uint16_t i = x % m_side;
            uint16_t j = y % m_side;

            if (value.r < M[i][j])
                setPixel(x, y, COLOR_BLACK);
            else
                setPixel(x, y, COLOR_WHITE);
        }
    }

}

void ImageTransform::updatePixelWithError(uint32_t x, uint32_t y, float err)
{
    RGB value = getPixel(x, y);

    float error = std::round(err + value.r);

    uint8_t z = std::max(0.0f, std::min(255.0f, error));

    setPixel(x, y, RGB(z));
}

void ImageTransform::errorDistribution()
{
    grayscale();

    for (uint32_t x = 0; x < cfg->width; x++) {
        for (uint32_t y = 0; y < cfg->height; y++) {

            RGB value = getPixel(x, y);

            if (value.r > cfg->threshold)
            {
                float error = value.r - COLOR_WHITE.r;
                if (x + 1 < cfg->width)
                    updatePixelWithError(x + 1, y, error * 3.0 / 8.0);
                if (y + 1 < cfg->height)
                    updatePixelWithError(x, y + 1, error * 3.0 / 8.0);
                if (x + 1 < cfg->width && y + 1 < cfg->height)
                    updatePixelWithError(x + 1, y + 1, error * 2.0 / 8.0);

                setPixel(x, y, COLOR_WHITE);
            }


            else
            {
                float error = value.r;
                if (x + 1 < cfg->width)
                    updatePixelWithError(x + 1, y, error * 3.0 / 8.0);
                if (y + 1 < cfg->height)
                    updatePixelWithError(x, y + 1, error * 3.0 / 8.0);
                if (x + 1 < cfg->width && y + 1 < cfg->height)
                    updatePixelWithError(x + 1, y + 1, error * 2.0 / 8.0);

                setPixel(x, y, COLOR_BLACK);
            }

        }
    }

}
