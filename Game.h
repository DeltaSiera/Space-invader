//
// Created by Deividas on 2017-05-05.
//
#ifndef SPACE_INVADER_GAME_H
#define SPACE_INVADER_GAME_H
#pragma once
#include <vector>
#include "Gamedata.h"
#include <memory>
#include "Elements.h"
#include "Enemies.h"
#include "Bullets.h"
class Gamedata;
class Bullet;
class Laser;
class Beam;
class Stage;
class Big_laser;
class Enemy;
class Ship;
class Life;
class Bonus;
/*
* Pagrindinė klasė, kurioje prasideda žaidimas
* Pagrindiniai atributai: kulkų rodyklių vektorius, priešų vektorius
* kintamasis _game_goes stebi, ar žaidimas veikia ar ne
* metodai, kurie skirti žaimo veikimui
*/
class Game {
    std::vector<std::unique_ptr<Bullet> > _ship_bullets;
    std::vector<std::unique_ptr<Bullet> > _enemies_bullets;
    std::vector<std::unique_ptr<Enemy> > _enemies;
    std::vector<std::unique_ptr<Stage> > _stages;
    std::unique_ptr<Big_laser> _big_lazer;
    Bonus *_bonus_item;
    Ship* _space_ship;
    bool _game_goes;
    Gamedata *_data;
    Life *ship_lifes;
    int _stage;
public:
    const int H, W;
    Game();																			//default contructor
    ~Game();
    void start();																	//žaidimo pradžios metodas, kuris paleidžia žaidimą
    void bonus_item();
    void render_all();
    void check_stage();																//metodas, kuris pagal lygį įkelia ateivius
    void move_enemies();															//priešai juda į abi puses priklausomai nuo laiko
    void check_impact();													        //tikrina, ar kulka susidūrė su priešu
    bool game_is_over();															//metodas, kuris patikrina,ar dar liko ateivių
    void update_bullets();															//meotdas, kuris išvalo kulkas, kurios patenka
    Gamedata* get_data() const;														//metodas, kuris grąžina paveiksliukų klasės objektą
    void check_input(Ship* space_ship);										        //tikrina, koks klavišas nuspaustas
    void add_big_laser(std::unique_ptr<Big_laser> b);
    void add_bullet(std::unique_ptr<Bullet> b);                                     //metodas, kuris užkrauna
    void add_enemy_bullet(std::unique_ptr<Beam> b);									//metodas, kuris prideda kulkas į žaidimą
    void include_enemies(std::unique_ptr<Enemy> enemy);
    template<typename T, typename U> bool find_collision(T& bullet, U &ship);
};

//void opostine_move(Enemy alien);

#endif //SPACE_INVADER_GAME_H