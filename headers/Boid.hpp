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

  float moveSpeed = 0.5;
  sf::Color col;
  vect pos;
  vect dir;
};
