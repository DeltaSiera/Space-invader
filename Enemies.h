//
// Created by Deividas on 2017-05-05.
//

#ifndef SPACE_INVADER_ENEMIES_H
#define SPACE_INVADER_ENEMIES_H
#pragma once
#include <vector>
#include "SDL.h"
#include "Movement.h"
#include <memory>

class Game;
/*
*Prieðo klasë, kuri turi atributus: pradines pozicija
*judëjimo kryptis
*/
class Entity
{
protected:
    bool alive;
    Game * game;
    SDL_Rect position;
public:
    Entity(bool alive, Game* game, const SDL_Rect pos)
            : alive(alive),
              game(game),
              position(pos){}

    virtual SDL_Rect &get_pos() { return position; }
    ////virtual void on_hit() = 0;
    virtual ~Entity() = default;
    virtual bool is_alive() { return alive; };
    virtual void render_me() = 0;

};
class Enemy:public Entity {
protected:
    //Uint32 start_time;
    MoveDirection enemy_dir;
public:
    virtual void on_hit() = 0;
    MoveDirection &get_dir() { return enemy_dir; }	                    //metodas, kuris gràþina nuorodà á judëjimo kryptá
    virtual void split_me(std::vector<std::unique_ptr<Enemy>> enemies) = 0;
    virtual void shoot_bullet() = 0;
    Enemy(SDL_Rect enemy_pos, MoveDirection enemy_dir, Game* game);
};

//-----------------------------------------------
class Alien : public Enemy {
protected:
    int next_bullet_tick = 0;
public:
    void on_hit() override;
    Alien(const Alien &obj);
    void render_me() override;
    void split_me(std::vector<std::unique_ptr<Enemy>> enemies) override;
    void shoot_bullet() override;
    Alien(const SDL_Rect& enemy_pos, const MoveDirection enemy_dir, Game* const game);
};

/*Boso klasë, kuri turi savo vektoriø, kuris ðaudo kulkas*/
class Leader : public Alien {
    int health;
public:
    void render_me() override;
    void on_hit() override;
    Leader(const SDL_Rect& enemy_pos, const MoveDirection enemy_dir,
           Game* const game, int boss_health)
            : Alien(enemy_pos, enemy_dir, game), health(boss_health) {}

    void shoot_bullet() override;
    void split_me(std::vector<std::unique_ptr<Enemy>> enemies)override;

};
//padaryt prieðà, kuris iðauna krûvà bullet
#endif //SPACE_INVADER_ENEMIES_H
