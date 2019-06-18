//
// Created by Deividas on 2017-05-05.
//
#include "Gamedata.h"
#include <iostream>

Image::Image() :
        texture(nullptr) {}
Image :: ~Image() {
    SDL_DestroyTexture(texture);
}
void Image::draw(SDL_Renderer* ren, SDL_Rect* srect, SDL_Rect* drect) const
{
    SDL_RenderCopy(ren, texture, srect, drect);
}
void Image::loadBMP(SDL_Renderer* ren, const std::string& filename) {
    // Uþkraunam BMP á atmintá
    auto surface = SDL_LoadBMP(filename.c_str());
    if (surface) {
        // Ið paveiksliuko padarom tekstûrà, kurià galima pieðti á ekranà
        texture = SDL_CreateTextureFromSurface(ren, surface);
        // Paveiksliuko daugiau nebereikia, nes turim tekstûrà
        SDL_FreeSurface(surface);
    }
}
Gamedata::Gamedata(Game* game) :game(game)
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
        std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
    win = SDL_CreateWindow("Space invaders", 50, 50, game->W, game->H, SDL_WINDOW_SHOWN);
    if (win == nullptr) {
        std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
    }
    ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (ren == nullptr) {
        SDL_DestroyWindow(win);
        std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
    }
    ship.loadBMP(ren, "Space_ship.bmp");		//užkraunams laivas
    bullet.loadBMP(ren, "laser.bmp");			//užkraunama laivo kulka
    _blast_image.loadBMP(ren, "big_laser.bmp");
    //first level enemy
    enemy.loadBMP(ren, "Enemy.bmp");			//užkraunamas priešas
    enemy_bullet.loadBMP(ren, "Alien.beam.bmp");        //priešo kulka
    //second level enemy
    leader_image.loadBMP(ren, "bosas.bmp");             //užkraunams bosas, kai hp >5
    leader_image2.loadBMP(ren, "bosas2.bmp");           //užkraunamas bosas, kai hp <=5
    leader_bullet.loadBMP(ren, "leader_bullet.bmp");
    //--------------------------
    _bonus_item.loadBMP(ren, "bonusas.bmp");
    //ship lifes
    life1.loadBMP(ren, "1.bmp");
    life2.loadBMP(ren, "2.bmp");
    life3.loadBMP(ren, "3.bmp");
    life4.loadBMP(ren, "4.bmp");
    life5.loadBMP(ren, "5.bmp");

}
//destuktorius, kuris sunaikina paveiksliukus bei kitą turinį
Gamedata::~Gamedata() {
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();
}
