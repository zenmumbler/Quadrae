//
//  Game.cpp
//  Quadrae
//
//  Created by Arthur Langereis on 2/25/13.
//  Copyright (c) 2013 Arthur Langereis. All rights reserved.
//

#include "Game.h"

Game::Game(const std::shared_ptr<sf::RenderWindow> & window)
	: Scene(window)
	, view_(new View(window))
{
	tickLength_ = Time::Duration(500);
	piece_ = ShapeType::None;
}


void Game::handleEvent(const sf::Event & event) {
	int tryCol = pieceCol_;
	int tryRow = pieceRow_;
	int tryRot = pieceRot_;
	bool movedDown = false;

	if (event.Type == sf::Event::KeyPressed) {
		if (event.Key.Code == sf::Key::Z)
			tryRot++;
		else if (event.Key.Code == sf::Key::A)
			tryRot--;
		else if (event.Key.Code == sf::Key::Left)
			tryCol--;
		else if (event.Key.Code == sf::Key::Right)
			tryCol++;
		else if (event.Key.Code == sf::Key::Down) {
			tryRow++;
			movedDown = true;
		}

		// ESC -> back to titles
		else if (event.Key.Code == sf::Key::Escape)
			Scenes::setCurrent("title");
	}

	if (piece_ != ShapeType::None && grid_.canFitShapeAt(shapeWithRotation(piece_, tryRot), tryCol, tryRow)) {
		pieceRot_ = tryRot;
		pieceRow_ = tryRow;
		pieceCol_ = tryCol;
		
		if (movedDown)
			nextTick_ = Time::now() + tickLength_;
	}
}


void Game::handleCompletedLines() {
	auto cl = grid_.completedLines();
	if (! cl.size())
		return;
	grid_.collapseCompletedLines();
}


void Game::activate() {
	nextTick_ = Time::now();
	piece_ = ShapeType::None;

	grid_.clear();
}


void Game::suspend() {
}


void Game::tick() {
	if (piece_ == ShapeType::None) {
		piece_ = static_cast<ShapeType>(Random::intInRange(1, 7));
		pieceRow_ = -1; pieceCol_ = 3;
		pieceRot_ = 40000;
	}
	else {
		auto & shape = shapeWithRotation(piece_, pieceRot_);

		if (grid_.canFitShapeAt(shape, pieceCol_, pieceRow_ + 1))
			pieceRow_++;
		else {
			grid_.placeShapeAt(shape, pieceCol_, pieceRow_);
			piece_ = ShapeType::None;
			
			handleCompletedLines();
		}
	}
}


void Game::frame() {
	if (Time::now() >= nextTick_) {
		tick();
		nextTick_ += tickLength_;
	}
	
	view_->renderBG();
	view_->renderShape(grid_.shape(), 24.f, 24.f);
	
	if (piece_ != ShapeType::None)
		view_->renderShape(shapeWithRotation(piece_, pieceRot_), 24. * (pieceCol_ + 1), 24. * (pieceRow_ + 1));
}
