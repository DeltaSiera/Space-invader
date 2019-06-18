#include "Enemies.h"
#include <iostream>
#include <cstdlib>
#include "Elements.h"
#include "Bullets.h"
#include "Game.h"


Enemy::Enemy(SDL_Rect enemy_pos, MoveDirection enemy_dir, Game* game) :
        Entity(true, game, enemy_pos), enemy_dir(enemy_dir)
{
}

void Alien::render_me()
{
    auto alien_data = game->get_data();
    if (alive)
        alien_data->get_alien_image().draw(alien_data->get_render(), nullptr, &position);
}

void Alien::shoot_bullet()
{
    int current_time = SDL_GetTicks();
    if (current_time >= next_bullet_tick)
    {
        next_bullet_tick = current_time + 1000 + rand() % 2000;
        auto start_x = position.x,
                start_y = position.y;
        game->add_enemy_bullet(std::make_unique<Beam>(SDL_Rect{ start_x,start_y,8,8 }, Coord<int>(0, 7), game));
    }

}

void Alien::on_hit()
{
    alive = false;
}

Alien::Alien(const SDL_Rect& enemy_pos,
             const MoveDirection enemy_dir, Game* const game)
        : Enemy(enemy_pos, enemy_dir, game)
{
    next_bullet_tick = SDL_GetTicks() + std::rand() % 3000;
}

Alien::Alien(const Alien& obj) : Enemy(obj)
{
    std::cout << "Copy constructor\n";
    alive = obj.alive;
    game = obj.game;
    position = obj.position;
    enemy_dir = obj.enemy_dir;
}

void Alien::split_me(std::vector<std::unique_ptr<Enemy>> enemies)
{
    //auto start_x = 20;
    /*if (start_time % 100 == 0)
    for (int i = 0; i < 4; i++) {
    Enemy* alien2 = _enemies[i];
    _enemies.insert(_enemies.begin() + 2, alien2);
    start_x += 50;
    }*/
}

void Leader::render_me()
{
    Gamedata* boss_data = game->get_data();
    if (health >= 5 && alive)
        boss_data->get_boss_image().draw(boss_data->get_render(), nullptr, &position);

    else if (health <5 && alive)
        boss_data->get_boss2_image().draw(boss_data->get_render(), nullptr, &position);

}

void Leader::on_hit()
{
    health--;
    if (health <= 0)
    {
        alive = false;
    }
}

void Leader::shoot_bullet()
{
    int current_time = SDL_GetTicks();
    if (current_time >= next_bullet_tick)
    {
        next_bullet_tick = current_time + 1000 + rand() % 2000;
        auto start_x = position.x,
                start_y = position.y;
        game->add_enemy_bullet(std::make_unique<Beam>(SDL_Rect{ start_x,start_y,8,8 }, Coord<int>(0, 9), game));
    }
}

void Leader::split_me(std::vector<std::unique_ptr<Enemy>> enemies)
{
    std::cout << "afsfd";
}