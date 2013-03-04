//
//  Game.cpp
//  Quadrae
//
//  Created by Arthur Langereis on 2/25/13.
//  Copyright (c) 2013 Arthur Langereis. All rights reserved.
//

#include "Game.h"

Game::Game(const std::shared_ptr<sf::RenderWindow> & window)
	: window_(window)
	, view_(new View(window_))
{}


void Game::handleEvent(const sf::Event & event) {
	if (event.Type == sf::Event::KeyPressed) {
		if (event.Key.Code == sf::Key::Z)
			rotation_++;
		else if (event.Key.Code == sf::Key::A)
			rotation_--;
	}
}


void Game::step() {
	view_->renderBG();
	view_->renderShape(shapeWithRotation(ShapeType::TBone, rotation_), 24., 24.);
	view_->renderShape(shapeWithRotation(ShapeType::RightHook, rotation_), 144., 24.);
	view_->renderShape(shapeWithRotation(ShapeType::LeftStair, rotation_), 24., 144.);
	view_->renderShape(shapeWithRotation(ShapeType::Square, rotation_), 144., 144.);
	view_->renderShape(shapeWithRotation(ShapeType::RightStair, rotation_), 24., 264.);
	view_->renderShape(shapeWithRotation(ShapeType::LeftHook, rotation_), 144., 264);
	view_->renderShape(shapeWithRotation(ShapeType::Bar, rotation_), 24., 384.);
}
