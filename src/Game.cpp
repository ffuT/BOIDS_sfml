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
Game::Game(const int width_in, const int height_in, const char title_in[], int boid_amount) :
m_width(width_in), m_height(height_in),
window(sf::VideoMode(width_in, height_in), title_in, sf::Style::Default),
ev() {
	//do stuff
	windowptr = &window;
	srand(time(0));

	for (Boid& b : boids) {
		b.pos = vect(rand() % m_width, rand() % m_height);
		b.col = sf::Color(rand() % 200 + 55, rand() % 40 + 5, rand() % 40 + 5);
		if(rand() % 2 == 0) {
			b.dir = vect(rand(), rand());
		} else {
			b.dir = vect(-rand(), -rand());
		}
		b.dir.normalize();
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

	for (Boid& b : boids) {	//for all boids do this
		//reset position
		if (b.pos.x < 0)
			b.pos.x += m_width;
		if (b.pos.y < 0)
			b.pos.y += m_height;
		if (b.pos.x > m_width)
			b.pos.x -= m_width;
		if (b.pos.y > m_height)
			b.pos.y -= m_height;
		
		//cohesion
		vect pull(0, 0);
		for (Boid& o : boids) {	//iterate over all boids again BIG O(n^2)
			if (b == o)	//if itself go next
				continue;

			vect dist(o.pos - b.pos);
			float distmag = dist.mag();

			constexpr float maxdist = 75;

			//cohesion
			//if (distmag <= maxdist * 2)
				pull += (o.pos - b.pos);

			if(distmag >= maxdist)
				continue;

			//seperation
				vect push(b.pos - o.pos);	//pushforce direction
				push.normalize();
			//alignment
				vect align(o.dir * alignStr);

			//apply forces
				b.dir += (push * seperationStr / distmag);
				b.dir += align * distmag;
				b.dir.normalize();
		}
		//cohesion
		if(!(pull == vect(0,0))){
			pull.normalize();
			b.dir += pull * cohesionStr;
			b.dir.normalize();
		}
		b.draw(windowptr);
	}

	window.display();
}

void Game::stop() {
	running = false;
	window.close();
}