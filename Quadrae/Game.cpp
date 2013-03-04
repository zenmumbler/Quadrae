//
//  Game.cpp
//  Quadrae
//
//  Created by Arthur Langereis on 2/25/13.
//  Copyright (c) 2013 Arthur Langereis. All rights reserved.
//

#include "Game.h"

Game::Game(const std::shared_ptr<sf::RenderWindow> & window)
	: window_(window), view_(new View(window_))
{
	
}


void Game::handleEvent(const sf::Event & event) {
	
}


void Game::step() {
	view_->renderBG();
}
