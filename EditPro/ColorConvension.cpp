
/*
#include "ColorConvension.h"
#include <iostream>
#include <cmath>

void colorConvension::RGB2HSV(float p_r, float p_g, float p_b, float& p_H_ptr, float& p_S_ptr, float& p_V_ptr) {
    float fCMax = std::max(std::max(p_r, p_g), p_b);
    float fCMin = std::min(std::min(p_r, p_g), p_b);
    float fDelta = fCMax - fCMin;

    if (fDelta > 0) {
        if (fCMax == p_r) {
            p_H_ptr = 60 * (fmod(((p_g- p_b) / fDelta), 6));
        }
        else if (fCMax == p_g) {
            p_H_ptr = 60 * (((p_b - p_r) / fDelta) + 2);
        }
        else if (fCMax == p_b) {
            p_H_ptr = 60 * (((p_r - p_g) / fDelta) + 4);
        }

        if (fCMax > 0) {
            p_S_ptr = fDelta / fCMax;
        }
        else {
            p_S_ptr = 0;
        }

        p_V_ptr = fCMax;
    }
    else {
        p_H_ptr = 0;
        p_S_ptr = 0;
        p_V_ptr = fCMax;
    }

    if (p_H_ptr < 0) {
        p_H_ptr = 360 + p_H_ptr;
    }
}



void colorConvension::HSV2RGB(float& p_r_ptr, float& p_g_ptr, float& p_b_ptr, float p_h, float p_s, float p_v) {
    float fC = p_v * p_s; // Chroma
    float fHPrime = fmod(p_h / 60.0, 6);
    float fX = fC * (1 - fabs(fmod(fHPrime, 2) - 1));
    float fM = p_v - fC;

    if (0 <= fHPrime && fHPrime < 1) {
        p_r_ptr = fC;
        p_g_ptr = fX;
        p_b_ptr = 0;
    }
    else if (1 <= fHPrime && fHPrime < 2) {
        p_r_ptr = fX;
        p_g_ptr = fC;
        p_b_ptr = 0;
    }
    else if (2 <= fHPrime && fHPrime < 3) {
        p_r_ptr = 0;
        p_g_ptr = fC;
        p_b_ptr = fX;
    }
    else if (3 <= fHPrime && fHPrime < 4) {
        p_r_ptr = 0;
        p_g_ptr = fX;
        p_b_ptr = fC;
    }
    else if (4 <= fHPrime && fHPrime < 5) {
        p_r_ptr = fX;
        p_g_ptr = 0;
        p_b_ptr = fC;
    }
    else if (5 <= fHPrime && fHPrime < 6) {
        p_r_ptr = fC;
        p_g_ptr = 0;
        p_b_ptr = fX;
    }
    else {
        p_r_ptr = 0;
        p_g_ptr = 0;
        p_b_ptr = 0;
    }

    p_r_ptr += fM;
    p_g_ptr += fM;
    p_b_ptr += fM;
}

*/
