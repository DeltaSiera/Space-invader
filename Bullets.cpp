//
// Created by Deividas on 2017-05-20.
//
#include "Bullets.h"
/*Coord& Laser::get_vec() {
return vec;
}*/

void Laser::render_me()
{
    auto data = game->get_data();
    data->get_ship_bullet_image().draw(data->get_render(), nullptr, &position);
}


Bullet::Bullet(SDL_Rect bullet_pos, Coord<int> vec, Game* game):
        Entity(true, game, bullet_pos),vec(vec)
{}

bool Bullet::is_visible() const
{										//const - kad nebūtų galima keisti laukų

    return !(position.x < -20 || position.y < -20 ||
             position.x >= game->W + 20 || position.y >= game->H + 20);
}

void Bullet::update() {													//metodas, kurio pagalba kulka juda į viršų

    this->position += vec;
}
Beam::Beam(const SDL_Rect &bullet_pos, const Coord <int>&vec, Game *game) : Bullet(bullet_pos, vec, game) {}

void Beam::render_me() {
    auto enemy_data = game->get_data();
    enemy_data->get_laser2_image().draw(enemy_data->get_render(), nullptr, &position);
}

void Big_laser::make_laser_shoot()
{

}

Big_laser::Big_laser(const SDL_Rect & bullet_pos, const Coord<int>& vec, Game * game) : Bullet(bullet_pos, vec, game),cool_down(1)
{
}

void Big_laser::render_me()
{
    auto timer = SDL_GetTicks();
    auto _blast_data = game->get_data();
    if(timer % 15 == 0)
        cool_down--;
    if(cool_down>0 && alive){
        _blast_data->get_ship_blast_image().draw(_blast_data->get_render(), nullptr, &position);
    }
    if(cool_down <=0)
        alive = false;

}

const int &Big_laser::check_timer() {
    return cool_down;
}

