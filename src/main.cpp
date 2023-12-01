#include <iostream>
#include "../headers/Game.hpp"
#include <vector>
#include <string>
#include <iostream>
#include <chrono>
#include <thread>

// i know its alot in a main, but i had an issue early
// when making it a class so made it in main idc

void keypressed(sf::Event ev, bool &run, sf::RenderWindow &win, std::vector<char> &input) {
	sf::Keyboard::Key key = ev.key.code;

	if (key == sf::Keyboard::Escape) {	//close on escape
		run = false;
		win.close();
	}

	if (key == sf::Keyboard::Backspace || key == sf::Keyboard::Delete) {
		if (input.size() > 0)	//dond krash bls :3
		input.pop_back();
	}

	if (key >= sf::Keyboard::A && key <= sf::Keyboard::Z) {
		std::cout << static_cast<char>(key + 'a') << "\n";
		input.push_back(static_cast<char>(key + 'a'));
	}
	if (key >= sf::Keyboard::Num0 && key <= sf::Keyboard::Num9) {
		std::cout << static_cast<char>(key - 26 + '0') << "\n";
		input.push_back(static_cast<char>(key - 26 + '0'));
	}
	if (key == sf::Keyboard::Enter) {
		//check if valid input, update value, and go to next state
	}

}

int main(){
	int width = 800, height = 600, boids = 50;
	char title[] = "title";


	bool run = true;
	sf::RenderWindow win(sf::VideoMode(800, 600), "launcher", sf::Style::Default);
	sf::Event ev;
	sf::Font arial;
	std::vector<char> inputs;
	std::string s = "";

	if (!arial.loadFromFile(".\\External\\extra\\arial.ttf") && !arial.loadFromFile("C:\\Windows\\Fonts\\arial.ttf")){
		return 1;
	}

	while (run) {
		if (win.waitEvent(ev)) {
			switch (ev.type) {
			case sf::Event::Closed:
				run = false;
				win.close();
				break;
			case sf::Event::KeyPressed:
				keypressed(ev, run, win, inputs);
				s = "";
				for (char chr : inputs) {
					s += chr;
				}
				break;
			case sf::Event::KeyReleased:
				break;
			}
		}
		win.clear(sf::Color::White);

		//switch case for states: width, height, etc.

		sf::Text t(s, arial, 32);
		t.setFillColor(sf::Color::Black);
		t.setPosition((400 - ((int)t.getGlobalBounds().width / 2)),	//centered
									(300 - ((int)t.getGlobalBounds().height / 2)));

		win.draw(t);

		win.display();
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}

  Game game(width, height, title, boids);
  game.start();

  return 0;
}