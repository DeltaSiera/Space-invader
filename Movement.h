//
// Created by Deividas on 2017-05-05.
//

#ifndef SPACE_INVADER_MOVEMENT_H
#define SPACE_INVADER_MOVEMENT_H
#pragma once

#include <map>
#include "SDL.h"

/*class sdl_rect{
public:
    sdl_rect(int x, int y, int w, int h) : x(x), y(y), w(w), h(h) {}

private:
    int x,y,
        w,h;
};
*/
/*std::map<char,int> dirs;
        dirs['d'] = 0;
        dirs['a'] = 1;
        dirs['w'] = 2;
        dirs['s'] = 3;*/
enum MoveDirection {
    D = 0,
    A = 1,
    W = 2,
    S = 3
};
//klasė Coord, kuri sugeneruoja judėjimo koordinates, default reikšmės (0,0)
template<typename T>class Coord {
public:
    T x, y;												//pradinës koordinatës
    Coord(T x = 0, T y = 0) {
        this->x = x;										//priskiriamos pradinës reikðmës
        this->y = y;
    }
};
/*statiniai judėjimai----------------------------------------*/
static const Coord<int> UP = { 0,-4 };							//objekto paėjimas į viršų
static const Coord<int> DOWN = { 0,4 };							//objekto paėjimas į apačią
static const Coord<int> LEFT = { -4,0 };							//objekto paėjimas į kairę
static const Coord<int> RIGHT = { 4,0 };							//objekto paėjimas į dešinę
static const Coord<int> dirs[4] = { RIGHT,LEFT,UP,DOWN };		//masyvas, kuris saugo judėjimo kryptis
/*-------------------------------------------------------------*/
//operatoriaus += perkroivmas, detaliau sudedamos koordinatės

inline void operator +=(SDL_Rect &rect, const Coord<int>& vec) {
    rect.x += vec.x;
    rect.y += vec.y;
}


//padaryt, kad būtų galima valdyt su pele
//daugiau priešų, daugiau rūšių
//daugiau lygių
//pasidaryt, kad ateiviai pagal lygius skirtingas kulkas šaudyt, gal ne spindulius
//padary foną, kuris judėtų, taip apt laivo ir ateivių animacijas
//
#endif //SPACE_INVADER_MOVEMENT_H
