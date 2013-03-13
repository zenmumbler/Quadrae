// Quadrae
// (c) 2013 by Arthur Langereis

#include <memory>
#include <vector>

#include <SFML/Graphics.hpp>

#include "Common.h"
#include "Config.h"
#include "Assets.h"

#include "TitleScene.h"
#include "GameScene.h"


static bool running_s;
static std::shared_ptr<sf::RenderWindow> window_s;


static void handleEvents() {
	sf::Event event;
	
	while (window_s->GetEvent(event)) {
		if (event.Type == sf::Event::Closed)
			running_s = false;
		
		if (running_s) // not handled by this method
			Scenes::current()->handleEvent(event);
	}
}


static void mainLoop() {
	running_s = true;
	
	while (running_s) {
		Time::step();
		Config::stepBGAnim();
		handleEvents();
		Scenes::current()->frame();
		window_s->Display();
	}
}


static bool init() {
	// in SFML 1.x, the Window is the App, which is unfortunate
	window_s.reset(new sf::RenderWindow(sf::VideoMode(400, 528), "Quadrae", sf::Style::Close));
	window_s->SetFramerateLimit(60);
	
	// try and load assets
	if (! Assets::loadAll())
		return false;
	
	// services
	Random::seed();
	Config::load();
	
	// set up scenes
	Scenes::add("title", std::make_shared<Title>(window_s));
	Scenes::add("game", std::make_shared<GameScene>(window_s));
	Scenes::setCurrent("title");
	
	return true;
}


int main(int argc, const char * argv[]) {
	if (init())
		mainLoop();
}
