#pragma once

//sfml includes
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
//other
#include "../headers/vect.hpp"

class Boid{

public:
  Boid(float, float, float, float, sf::Color);
  Boid();
  ~Boid();

  bool operator==(Boid);

  void draw(sf::RenderWindow*);

  float moveSpeed = 1;
  vect pos;
  vect dir;
  sf::Color col;
};
