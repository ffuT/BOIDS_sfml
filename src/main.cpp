#include <iostream>
#include "../headers/Game.hpp"
#include <vector>
#include <string>
#include <iostream>
#include <chrono>
#include <thread>

// i know its alot in a main, but i had an issue early
// when making it a class so made it in main idc
namespace IS{
	enum inputState {
		width = 0,
		height = 1,
		boids,
		end,
	};
}

static void keypressed(sf::Event ev, bool& run, sf::RenderWindow& win,
						std::vector<char>& input, IS::inputState& currentstate);

int width = 800, height = 600, boids = 50;

int main(){
	IS::inputState state = IS::width;
	char title[] = "Boids";
	bool run = true;
	sf::RenderWindow win(sf::VideoMode(800, 600), "launcher", sf::Style::Default);
	sf::Event ev;
	sf::Font arial;
	std::string s_state = "input window width: ";
	sf::Text sft_state(s_state, arial, 42);
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
				keypressed(ev, run, win, inputs, state);
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

		switch (state){
			case 0:
				break;
			case 1:
				//hanlde stuff maybe
				sft_state.setString("input window height: ");
				break;
			case 2:

				sft_state.setString("input amount of boids: ");
				break;
			default:
				run = false;
				win.close();
				break;
		}

		sf::Text t(s, arial, 32);
		t.setFillColor(sf::Color::Black);
		t.setPosition((400 - ((int)t.getGlobalBounds().width / 2)), (300));

		sft_state.setFillColor(sf::Color::Black);
		sft_state.setPosition((400 - ((int)sft_state.getGlobalBounds().width / 2)),	(250));

		win.draw(sft_state);
		win.draw(t);

		win.display();
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}

  Game game(width, height, title, boids);
  game.start();

  return 0;
}

static void keypressed(sf::Event ev, bool& run, sf::RenderWindow& win, std::vector<char>& input, IS::inputState& currentstate) {
	sf::Keyboard::Key key = ev.key.code;

	if (key == sf::Keyboard::Escape) {	//close on escape
		run = false;
		win.close();
	}

	if ((key == sf::Keyboard::Backspace || key == sf::Keyboard::Delete) && input.size() > 0) {
		input.pop_back();
	}

	if (key == sf::Keyboard::Space) {
		input.push_back(' ');
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
		
		std::string str = "";
		for (char c : input) {
			str += c;
		}

		switch (currentstate) {
		case 0:
			try {
				int num = std::stoi(str);
				if (num > 1920)
					num = 1920;
				width = num;
			}
			catch (const std::exception& e) {
				std::cout << e.what();
				break;
			}
			currentstate = static_cast<IS::inputState>(static_cast<int>(currentstate) + 1);
			break;
		case 1:
			try {
				int num = std::stoi(str);
				if (num > 1080)
					num = 1080;
				height = num;
			}
			catch (const std::exception& e) {
				std::cout << e.what();
				break;
			}
			currentstate = static_cast<IS::inputState>(static_cast<int>(currentstate) + 1);
			break;
		case 2:
			try {
				int num = std::stoi(str);
				boids = num;
			}
			catch (const std::exception& e) {
				std::cout << e.what();
				break;
			}
			currentstate = static_cast<IS::inputState>(static_cast<int>(currentstate) + 1);
			break;
		default:
			run = false;
			win.close();
			break;
		} //switch
		input.clear();
	} //if
} //Keypressed