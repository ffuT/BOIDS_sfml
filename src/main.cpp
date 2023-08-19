#include <iostream>
#include "../headers/Game.hpp"

int main(){

  Game game(1024, 768, "Boids");
  game.start();

  return 0;
}