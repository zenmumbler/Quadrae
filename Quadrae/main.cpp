// Quadrae
// (c) 2013 by Arthur Langereis

#include <memory>
#include <vector>

#include <SFML/Graphics.hpp>

#include "Common.h"
#include "Scene.h"
#include "Game.h"


static bool running_s;
static std::shared_ptr<sf::RenderWindow> window_s;


static void handleEvents() {
	sf::Event event;
	
	while (window_s->GetEvent(event)) {
		if (event.Type == sf::Event::Closed)
			running_s = false;
		
		if (event.Type == sf::Event::KeyPressed) {
			if (event.Key.Code == sf::Key::Escape)
				running_s = false;
		}
		
		if (running_s) // not handled by this method
			Scenes::current()->handleEvent(event);
	}
}


static void mainLoop() {
	running_s = true;
	
	while (running_s) {
		Time::step();
		handleEvents();
		Scenes::current()->frame();
		window_s->Display();
	}
}


static void init() {
	// in SFML 1.x, the Window is the App, which is unfortunate
	window_s.reset(new sf::RenderWindow(sf::VideoMode(400, 528), "Quadrae", sf::Style::Close));
	window_s->SetFramerateLimit(60);
	
	// set up scenes
	Scenes::add("game", std::make_shared<Game>(window_s));
	Scenes::setCurrent("game");
	
	// misc
	Random::seed();
}


int main(int argc, const char * argv[]) {
	init();
	mainLoop();
}
