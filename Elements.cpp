#include <cstdlib>
#include <iostream>
#include  "Game.h"


void Ship::render_me()
{
    std::cout << ship_health << "\n";
    auto data = game->get_data();			//renderis
    if (alive)
        data->get_ship_image().draw(data->get_render(), nullptr, &position);
}

void Ship::beam_laser()
{
    game->add_big_laser(
            std::make_unique<Big_laser>(SDL_Rect{position.x + 25, position.y - 505, 1, 500}, Coord<int>(0, 0), game));
}

//Ship klasės kontruktorius, kuris inizializuoja pradines laivo objekto koordinates
Ship::Ship(Game*game) :
        Entity(true,game,{500,580,50,50}),
        ship_health(5)
{}

void Ship::beam_bullet() const {											//metodas, skirtas šaudyti kulkoms, const tam, kad nebūtų galima viduje keisti laukų{

    game->add_bullet(std::make_unique<Laser>(SDL_Rect{ position.x + 20 ,position.y - 10,10,10 }, Coord<int>(0, -10), game));			//kreipiamasi į game klasės atributą pridėti kulkas į vektorių
}

void Ship::hit_me() {       //kai pataiko į laivą, sumažina gyvibių skaičių vienetu
    ship_health--;
    if (ship_health <1)
        alive = false;
}



int& Ship::return_ship_health()     //grąžina laivo gyvybių skaičių, pagal kuriuos bus piešiami skaičiai
{
    return ship_health;
}

Stage::Stage(Game* game) : game(game)
{
}

Stage1::Stage1(Game* game) : Stage(game) {}

void Stage1::start_level()
{
    int start_x = 100;
    for (auto i = 0; i < 12; i++)
    {
        game->include_enemies(std::make_unique<Alien>(SDL_Rect{ start_x += 50 , 10,15,15 }, A, game));
    }
}

void Stage2::start_level()
{
    auto start_x = 250;
    for (auto i = 0; i < 5; i++)
        game->include_enemies(std::make_unique<Leader>(SDL_Rect{ start_x += 100, 25,100,50 }, D, game, 10));

}

void Stage3::start_level()
{
    auto start_x = 250;
    auto start_x_other = 200;
    for (auto i = 0; i < 6; i++)
    {
        game->include_enemies(std::make_unique<Alien>(SDL_Rect{ start_x_other += 50, 10,15,15 }, D, game));
        game->include_enemies(std::make_unique<Leader>(SDL_Rect{ start_x += 100, 30,100,50 }, D, game, 10));
    }
}

Bonus::Bonus(Game* game):
        Entity(true, game,
               {rand() % game->W,
                rand() % game->H,
                10,10}),collision_made(true){}

void Bonus::stop_render()       //nustoja piešt bonusą
{
    alive = false;
}

void Bonus::render_me()
{
    auto _data = game->get_data();
    if (alive) {
        _data->get_bonus_item().draw(_data->get_render(), nullptr, &position);
    }
}


Life::Life(Game *game,Ship* ship) : Entity(true, game, {0,0,50,50}),space_ship(ship) {}

void Life::render_me() {
    auto health_data = game->get_data();
    if (space_ship->return_ship_health() == 1)
        health_data->get_life1().draw(health_data->get_render(), nullptr, &position);
    if (space_ship->return_ship_health() == 2)
        health_data->get_life2().draw(health_data->get_render(), nullptr, &position);
    if (space_ship->return_ship_health() == 3)
        health_data->get_life3().draw(health_data->get_render(), nullptr, &position);
    if (space_ship->return_ship_health() == 4)
        health_data->get_life4().draw(health_data->get_render(), nullptr, &position);
    if (space_ship->return_ship_health() == 5)
        health_data->get_life5().draw(health_data->get_render(), nullptr, &position);
}

