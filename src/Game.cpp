//little boid project with big O(n^2) or worse idk

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

//oof constructor
Game::Game(const int width_in, const int height_in, const char title_in[], unsigned int boid_amount_in) :
m_width(width_in), m_height(height_in),
window(sf::VideoMode(width_in, height_in), title_in, sf::Style::Default), boid_amount(boid_amount_in), boids(new Boid[boid_amount_in]),
ev() {
	//do stuff
	windowptr = &window;
	srand(time(0));

	//initialize boids with random pos, color, speed, and direction
	for (int i = 0; i <= boid_amount - 1; i++) {
		boids[i].pos = vect(rand() % m_width, rand() % m_height);
		boids[i].col = sf::Color(rand() % 150 + 105, rand() % 100 + 5, rand() % 50 + 5);
		boids[i].moveSpeed += (((float) (rand() % 1000) / 4000));
		std::cout << boids[i].moveSpeed << "\n";
		if(rand() % 2 == 0) {
			boids[i].dir = vect(rand(), rand());
		} else {
			boids[i].dir = vect(-rand(), -rand());
		}
		boids[i].dir.normalize();
	}
}	 

Game::~Game() {
	//die!
}

void Game::start() {
	//gameloop
	int fps = 0;
	running = true;
	auto onesec = std::chrono::steady_clock::now() + std::chrono::seconds(1);
	auto lastTime = std::chrono::steady_clock::now();
	float accumulatedTime = 0.0f;

	while (running) {		//window loop
		auto now = std::chrono::steady_clock::now();
		auto deltaTime = std::chrono::duration<float>(now - lastTime).count();
		//window events
		if (window.pollEvent(ev)) {
			switch (ev.type) {
			case sf::Event::Closed:
				stop();
				break;
			case sf::Event::MouseButtonPressed:
				break;
			case sf::Event::KeyPressed:
				if (ev.key.code == sf::Keyboard::Escape) {	//close on escape
					stop();
				}
				break;
			case sf::Event::KeyReleased:
				break;
			case sf::Event::Resized:
				break;
			}
		}
		//limit render if constant window events
		if (accumulatedTime >= targetFramerate) {
			render();
			fps++;
			accumulatedTime -= targetFramerate;
			if (now >= onesec) {
				std::cout << fps << "\n";
				fps = 0;
				onesec += std::chrono::seconds(1);
			}

		}
		lastTime = now;
		accumulatedTime += deltaTime;
	}
}

void Game::render() {
	window.clear(sf::Color(0, 0, 0));	//clear window

	for (int i = 0; i <= boid_amount - 1; i++) {	//for all boids do this
		//reset position
		if (boids[i].pos.x < 0)
			boids[i].pos.x += m_width;
		if (boids[i].pos.y < 0)
			boids[i].pos.y += m_height;
		if (boids[i].pos.x > m_width)
			boids[i].pos.x -= m_width;
		if (boids[i].pos.y > m_height)
			boids[i].pos.y -= m_height;
		
		//cohesion
		vect pull(0, 0);
		for (int j = 0; j <= boid_amount - 1; j++) {	//iterate over all boids again BIG O(n^2)
			if (boids[i] == boids[j])	//if itself go next
				continue;

			vect dist(boids[j].pos - boids[i].pos);
			float distmag = dist.mag();


			//cohesion
			if (distmag	<= maxCohesionDist)
				pull += (boids[j].pos - boids[i].pos);

			if(distmag >= 65)
				continue;

			//seperation
				vect push(boids[i].pos - boids[j].pos);	//pushforce direction
				push.normalize();
			//alignment
				vect align(boids[j].dir * alignStr);

			//apply forces
				boids[i].dir += (push * seperationStr / distmag);
				boids[i].dir += align * distmag;
				boids[i].dir.normalize();
		}
		//cohesion
		if(!(pull == vect(0,0))){
			pull.normalize();
			boids[i].dir += pull * cohesionStr;
			boids[i].dir.normalize();
		}
		boids[i].draw(windowptr);
	}

	window.display();
}

void Game::stop() {
	running = false;
	window.close();
}