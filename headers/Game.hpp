#pragma once

//sfml includes
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
//other cludes
#include <iostream>
#include <math.h>
#include <chrono>
//my clude
#include "../headers/Game.hpp"
#include "../headers/Boid.hpp"
#include "../headers/vect.hpp"


class Game{
public :
  Game(const int width_in, const int height_in, const char title_in[], const int boid_amount);
  ~Game();

  void start();
  void stop();
  void render();

private :
  const int m_width;
  const int m_height;
  const float MAXFPS = 120.0;	//targetframerate		
  const float targetFramerate = 1.0f / MAXFPS;	//target frametime
  bool running = false;

  sf::RenderWindow window;
  sf::RenderWindow* windowptr;
  sf::Event ev;
  
  Boid boids[250];
  const float seperationStr = 2.5;  //pushdir * str / dist
  const float alignStr = 0.00004; //dir * str * dist
  const float cohesionStr = 0.05; //pulldir * str

};

