#include "Game.h"
#include <ctime>
int main(int argc, char**argv) {
    srand((unsigned int) time(nullptr));
    Game space_invader;
    space_invader.start();
    return 0;
}