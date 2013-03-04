// Quadrae
// (c) 2013 by Arthur Langereis

#include <memory>

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "Common.h"
#include "Game.h"


static bool running_;
static std::shared_ptr<sf::RenderWindow> window_;
static std::unique_ptr<Game> game_;


static void handleEvents() {
	sf::Event event;
	
	while (window_->GetEvent(event)) {
		if (event.Type == sf::Event::Closed)
			running_ = false;
		
		if (event.Type == sf::Event::KeyPressed) {
			if (event.Key.Code == sf::Key::Escape)
				running_ = false;
		}
		
		if (running_) // not handled by this method
			game_->handleEvent(event);
	}
}


static void mainLoop() {
	running_ = true;
	
	while (running_) {
		handleEvents();
		Time::step();
		game_->step();
		window_->Display();
	}
}


static void init() {
	window_.reset(new sf::RenderWindow(sf::VideoMode(400, 528), "Quadrae", sf::Style::Close));
	game_.reset(new Game(window_));
}


int main(int argc, const char * argv[]) {
	init();
	mainLoop();
}
