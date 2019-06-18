//
// Created by Deividas on 2017-05-05.
//

#ifndef SPACE_INVADER_ELEMENTS_H
#define SPACE_INVADER_ELEMENTS_H
#pragma once
#include <vector>
#include "Enemies.h"
#include <memory>
//erdvëlaivio klasë
class Ship:public Entity {
    int ship_health;
public:
    void hit_me();
    void beam_laser();
    Ship(Game*game);
    void beam_bullet() const;
    void render_me()override;
    int& return_ship_health();
};

class Stage {
protected:
    Game* game;
public:
    virtual ~Stage() = default;
    Stage(Game* game);
    virtual void start_level() = 0;
};

class Stage1 : public Stage {
public:
    Stage1(Game* game);
    void start_level() override;
};

class Stage2 : public Stage {
public:
    Stage2(Game* game) :Stage(game) {}
    void start_level() override;
};

class Stage3 : public Stage {
public:
    Stage3(Game* game)
            : Stage(game)
    {}
    void start_level() override;
};

class Bonus:public Entity
{
    bool collision_made;
public:
    Bonus(Game* game);
    void stop_render();
    void render_me()override;
};
class Life:public Entity{
    Ship* space_ship;
public:
    void render_me()override ;
    Life(Game *game,Ship*ship);
};
#endif //SPACE_INVADER_ELEMENTS_H
