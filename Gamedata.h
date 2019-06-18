//
// Created by Deividas on 2017-05-05.
//

#ifndef SPACE_INVADER_GAMEDATA_H
#define SPACE_INVADER_GAMEDATA_H

#pragma once
#include "SDL.h"
#include "Elements.h"
#include "Game.h"
/*
* Klasë Image uþkrauna paveiksliukus á objektus
* Turi metodus ákrauti paveikliukui ir já prieðti
* -----------------------------------------------
* Klasë Gamedata apdoroja paveikliukus ir perpieðia juos
* Turi meotudus gràþinti "pieðëjà" atnaujinti turiná ekrane
*/
class Image {
    SDL_Texture* texture;
public:
    Image();
    ~Image();
    void draw(SDL_Renderer* ren, SDL_Rect* srect, SDL_Rect* drect) const;
    void loadBMP(SDL_Renderer* ren, const std::string& filename);
};
/*----------------------------*/
class Gamedata {
    Game* game;
    SDL_Renderer *ren;
    SDL_Window *win;
    Image ship, bullet, _blast_image,
            life1, life2, life3, life4, life5,
            enemy, enemy_bullet,
            leader_image, leader_image2, leader_bullet,
            _bonus_item;
public:
    Gamedata(Game* game);
    ~Gamedata();
    //ship
    const Image& get_ship_image() { return ship; }
    const Image& get_ship_bullet_image() { return bullet; }
    const Image& get_ship_blast_image() { return _blast_image; }
    //first level enemy
    const Image& get_alien_image() { return enemy; }
    const Image& get_laser2_image() { return enemy_bullet; }
    //second level enemy
    const Image& get_boss_image() { return leader_image; }
    const Image& get_boss2_image() { return leader_image2; }
    const Image& get_boss_bullet() { return  leader_bullet; }
    //bonus item
    const Image& get_bonus_item() { return  _bonus_item; }
    //gyvybių paveiksliukai-------------------
    const Image& get_life5() { return  life5; }
    const Image& get_life4() { return  life4; }
    const Image& get_life3() { return  life3; }
    const Image& get_life2() { return  life2; }
    const Image& get_life1() { return  life1; }
    //renderer
    SDL_Renderer *get_render() { return ren; }
};





#endif //SPACE_INVADER_GAMEDATA_H
