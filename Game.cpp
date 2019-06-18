#include "Game.h"
#include <iostream>
#include <algorithm>

Game::Game() :
        _big_lazer(nullptr), _game_goes(true), _data(nullptr),
        _stage(0),
        H(640), W(1000) {
    _stages.push_back(std::make_unique<Stage1>(this));
    _stages.push_back(std::make_unique<Stage2>(this));
    _stages.push_back(std::make_unique<Stage3>(this));
}

void Game::start() {
    _data = new Gamedata(this),
    _space_ship = new Ship(this),
    ship_lifes = new Life(this, _space_ship),
    _bonus_item = new Bonus(this);
    while (_game_goes) {
        bonus_item();
        check_input(_space_ship);
        check_impact();
        update_bullets();
        move_enemies();
        game_is_over();
        check_stage();
        render_all();
        SDL_Delay(1000 / 60);
    }
}

void Game::check_input(
        Ship *space_ship)        //metodas, kuris tikrina, koks klavišas paspaustas ir atitinkamai judina kulkas arba laivą
{
    SDL_PumpEvents();                                //atnaujinams state masyvas
    SDL_Event e;
    auto &ship_pos = space_ship->get_pos();
    const auto state = SDL_GetKeyboardState(nullptr);
    while (SDL_PollEvent(&e) != 0)
        if (e.type == SDL_MOUSEBUTTONDOWN)
            space_ship->beam_bullet();
    if (state[SDL_SCANCODE_A]) {
        if (_big_lazer) {
            _big_lazer->get_pos() += LEFT;
            if (_big_lazer->get_pos().x <= 0)
                _big_lazer->get_pos().x = 1000;
        }
        ship_pos += (LEFT);
        if (ship_pos.x <= 0) ship_pos.x = 1000;
    }
    if (state[SDL_SCANCODE_D]) {
        if (_big_lazer) {
            _big_lazer->get_pos() += RIGHT;
            if (_big_lazer->get_pos().x >= 1000)
                _big_lazer->get_pos().x = 0;
        }
        //laivo pozicijos keitimas
        ship_pos += RIGHT;
        if (ship_pos.x >= 1000) ship_pos.x = 0;
    }
    if (state[SDL_SCANCODE_W]) {
        if (_big_lazer)
            _big_lazer->get_pos() += UP;
        ship_pos += UP;
        if (ship_pos.y <= 0)
            ship_pos.y = 0;
    }
    if (state[SDL_SCANCODE_S]) {
        if (_big_lazer)
            _big_lazer->get_pos() += DOWN;
        ship_pos += DOWN;
        if (ship_pos.y >= 580)
            ship_pos.y = 580;
    }
    if (state[SDL_SCANCODE_Q]) {
        _game_goes = false;          //kai paspaudžias q klavišas, tai baigiamas žaidimo seansas
    }

}

Gamedata *Game::get_data() const {
    return _data;
}

void Game::move_enemies() {
    for (auto &alien : _enemies) {
        if (alien->get_dir() == A || alien->get_pos().x < 0) {                            //Move Left
            alien->get_pos() += dirs[alien->get_dir()];
            if (alien->get_pos().x <
                0)                                                    //If an enemy has exceeded allowed bounds, change direction
                for (auto &i : _enemies) {
                    i->get_dir() = D;
                    i->get_pos() += DOWN;//metodas opsite, kryptis iš alien dir
                }
        }
        if (alien->get_dir() == D) {                                                    //Move Right
            alien->get_pos() += dirs[alien->get_dir()];
            if (alien->get_pos().x >
                900)                                                //If an enemy has exceeded allowed bounds, change direction
                for (auto &i : _enemies) {
                    i->get_dir() = A;                                                    //Pakeièiama kryptis
                    i->get_pos().y += 10;
                }
        }
        if (alien->get_pos().y >=
            550) {                                                //jei nors vienas prieðas priarrtëja prie nustatytos ribos, tada - þaidimo pabaiga
            _game_goes = false;
        }
    }
}

/*void Game::opostine_move() const
{

}*/

void Game::check_impact() {
    for (unsigned int ship = 0; ship < _ship_bullets.size(); ship++) {
        for (unsigned int alien = 0; alien < _enemies.size(); alien++) {
            if (find_collision(_ship_bullets[ship], _enemies[alien])) {
                _enemies[alien]->on_hit();
                if (!_enemies[alien]->is_alive()) { //padaryt bool kintam ir jį tikrint
                    _enemies[alien].reset();
                    _enemies.erase(_enemies.begin() + alien); //paðalinamas ateivis ið prieðø vektoriaus

                }
                alien--;
                //padaryt delete iš vektoriaus abiejuose variantuose
                _ship_bullets[ship].reset();
                _ship_bullets.erase(_ship_bullets.begin() + ship); //paðalinamas lazeris ið ShipLasers vektoriaus
                //std::cout << "Impact!\n"; //iðvedama, kad ávyko susidûriams
                break; //jei ávyko susidûrimas, tada ciklas nutraukiamas
            }

        }
    }
    //patikrina laivo ir ateivių kulkų susidūrimą
    for (unsigned int enemy = 0; enemy < _enemies_bullets.size(); enemy++) {
        if (find_collision(_enemies_bullets[enemy], _space_ship)) {
            _space_ship->hit_me();
            _enemies_bullets[enemy].reset();
            _enemies_bullets.erase(_enemies_bullets.begin() + enemy);
            enemy--;
        }
    }
    for (unsigned int j = 0; j < _enemies.size(); j++) {
        if (_big_lazer) {
            if (find_collision(_big_lazer, _enemies[j])) {
                _enemies[j]->on_hit();
                if (!_enemies[j]->is_alive()) { //padaryt bool kintam ir jį tikrint
                    _enemies[j].reset();
                    _enemies.erase(_enemies.begin() + j); //paðalinamas ateivis ið prieðø vektoriaus
                }           //
            }
        }
    }

    for (int i = 0; i < _enemies.size(); ++i) {
        if (find_collision(_enemies[i], _space_ship))
            _game_goes = false;
    }
}


template<typename T, typename U>
bool Game::find_collision(T &bullet, U &thing) {
    auto bullet_pos = bullet->get_pos(),
            enemy_pos = thing->get_pos();
    auto s_laserleft = bullet_pos.x,
            s_laserright = bullet_pos.x + bullet_pos.w,
            s_lasertop = bullet_pos.y,
            s_laserbot = bullet_pos.y + bullet_pos.h;
    //------------------------------------
    auto enemyLeft = enemy_pos.x,                                                    //Enemy collisions
            enemyRight = enemy_pos.x + enemy_pos.w,
            enemyTop = enemy_pos.y,
            enemyBot = enemy_pos.y + enemy_pos.h;

    return s_laserright >= enemyLeft && s_laserleft <= enemyRight && s_lasertop <= enemyBot && s_laserbot >= enemyTop;
    //jei yra susidûrimas, tada gràþinama trued
}

//Funkcija, kuri patikrina, ar liko dar ateiviø, jei ne, þaidimas baigiasi, graþina true, kitu atveju - false
bool Game::game_is_over()//patikrina,ar yra dar priešų, kitu atveju baigia žaidimą
{
    if (_enemies.size() == 0 && _stage == 3 ||
        !_space_ship->is_alive()) { //sàlyga, kuri tikrina,ar dar liko bent vienas ateivis
        _game_goes = false; //sëkmës atveju gràþina true
        std::cout << std::endl << "Game over! \n";
    } else if (!_game_goes) { //tikrinama, ar _game_goes yra tiesa
        std::cout << "Aliens came too close. Game is over!\n";
        return false;
    }
    return false;
}

void Game::check_stage()                    //metodas, kuris pagal priešų dydį ir lygių skaičių įkelia kitus priešus
{
    if (_enemies.size() == 0) {
        _stage++;
        if ((_stage) > _stages.size())
            exit(1);
        _stages[_stage - 1]->start_level();
    }
}

void Game::add_enemy_bullet(std::unique_ptr <Beam> b) {
    _enemies_bullets.push_back(move(b));
}

void Game::update_bullets() {
    for (auto &laser : _ship_bullets)
        laser->update();

    auto ship_bullets_end = std::remove_if(_ship_bullets.begin(), _ship_bullets.end(),
                                           [](std::unique_ptr <Bullet> &bullet) {
                                               return !bullet->is_visible();
                                           });
    _ship_bullets.erase(ship_bullets_end, _ship_bullets.end());

    for (auto &b : _enemies_bullets)
        b->update();

    auto enemy_bullets_end = std::remove_if(_enemies_bullets.begin(), _enemies_bullets.end(),
                                            [](std::unique_ptr <Bullet> &Bullet) {
                                                return !Bullet->is_visible();
                                            });
    _enemies_bullets.erase(enemy_bullets_end, _enemies_bullets.end());
}

void Game::include_enemies(std::unique_ptr <Enemy> enemy) {
    _enemies.push_back(std::move(enemy));
}

Game::~Game() {
    delete _space_ship;
    delete _data;
    delete _bonus_item;
    delete ship_lifes;
}

void Game::add_bullet(std::unique_ptr <Bullet> b) {
    _ship_bullets.push_back(move(b));
}

void Game::render_all() {
    SDL_RenderClear(_data->get_render()); //atnaujimas priešėjas
    SDL_SetRenderDrawColor(_data->get_render(), 255, 255, 255, 0);

    for (auto &bullet : _enemies_bullets)    //piešia priešų kulkas
        bullet->render_me();

    for (auto &k : _ship_bullets)        //piešia laivo kulkas
        k->render_me();

    for (auto &alien : _enemies) {       //piešia priešus
        alien->render_me();
        alien->shoot_bullet();
    }

    _space_ship->render_me();            //piešia laivą
    _bonus_item->render_me();           //piešia bonusą

    if (!_bonus_item->is_alive()) {
        _big_lazer->render_me();
    }


    ship_lifes->render_me();

    SDL_RenderPresent(_data->get_render());
}

void Game::bonus_item() {
    if (find_collision(_space_ship, _bonus_item)) {
        _bonus_item->stop_render();
        _space_ship->beam_laser();
        //_big_lazer->make_laser_shoot();
    }
}

void Game::add_big_laser(std::unique_ptr <Big_laser> b) {
    _big_lazer = move(b);
}


