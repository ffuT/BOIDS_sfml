#include <iostream>
#include "../headers/Game.hpp"

int main(){

  Game game(1280, 720, "Boids", 250);
  game.start();

  return 0;
}