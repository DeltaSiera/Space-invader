//
// Created by Deividas on 2017-05-20.
//

#ifndef SPACE_INVADER_BULLETS_H
#define SPACE_INVADER_BULLETS_H
#pragma once
#include "Movement.h"
#include "Game.h"

class Bullet:public Entity {
protected:
    Coord<int> vec;																//judëjimo vektoriaus objektas
public:
    void update();															//atnaujina kulkos judëjimo kryptá
    bool is_visible() const;													//meotadas, kuris patikrina, ar kulkas dar yra matoma ekrane
    virtual ~Bullet() = default;

    virtual void render_me() override =0;
    Bullet(SDL_Rect bullet_pos, Coord<int> vec, Game* game);						//default konstruktorius, kuris priskiria pozicijas pradines, judëjimà ir rodyklæ á game tipo objektà
};

class Laser :public Bullet
{
public:

    Laser(const SDL_Rect& bullet_pos, const Coord<int>& vec, Game* game)
            : Bullet(bullet_pos, vec, game)
    {}
    //const SDL_Rect& get_pos() override; //metodas, skirtas gràþinti pozicijai
    //Coord& get_vec() override; //metodas, kuris gràþina judëjimo kryptis
    void render_me() override;
};
class Beam : public Bullet {
public:

    Beam(const SDL_Rect &bullet_pos, const Coord<int> &vec, Game *game);
    //const SDL_Rect& get_pos() override; //metodas, skirtas gràþinti pozicijai
    //Coord& get_vec() override; //metodas, kuris gràþina judëjimo kryptis
    void render_me() override;
};
class Big_laser :public Bullet
{
    int cool_down;
public:
    const int& check_timer();
    void make_laser_shoot();
    Big_laser(const SDL_Rect &bullet_pos, const Coord<int> &vec, Game *game);
    void render_me() override;

};
#endif //SPACE_INVADER_BULLETS_H
