//
//  GameScene.cpp
//  Quadrae
//
//  Created by Arthur Langereis on 2/25/13.
//  Copyright (c) 2013 Arthur Langereis. All rights reserved.
//

#include "GameScene.h"

Game::Game(const std::shared_ptr<sf::RenderWindow> & window)
	: Scene(window)
	, view_(new View(window))
{
	tickInterval_  = Time::Duration(500);
	horizInterval_ = Time::Duration(200);
	dropInterval_  = Time::Duration(50);
	
	level_ = 0;
	lines_ = 0;

	piece_ = ShapeType::None;
	nextPiece_ = ShapeType::None;
}


void Game::activate() {
	nextTick_ = Time::now();
	nextHorizMove_ = nextTick_;
	nextDropMove_ = nextTick_;

	piece_ = ShapeType::None;
	nextPiece_ = randomShapeType();
	direction_ = Direction::None;

	level_ = 0; // <-- get this from shared config
	lines_ = 0;

	grid_.clear();
}


void Game::suspend() {
}


void Game::handleEvent(const sf::Event & event) {
	if (event.Type == sf::Event::KeyPressed) {
		// lame hack to overcome that a keypress in SFML
		// can repeat, i.e. not physical but virtual keypress
		if (event.Key.Code == lastKeyPressed_)
			return;
		lastKeyPressed_ = event.Key.Code;

		if (event.Key.Code == sf::Key::Z)
			tryRotate(true);
		else if (event.Key.Code == sf::Key::A)
			tryRotate(false);
		else if (event.Key.Code == sf::Key::Left) {
			direction_ = Direction::Left;
			nextHorizMove_ = Time::now() + horizInterval_;
			tryMove(direction_);
		}
		else if (event.Key.Code == sf::Key::Right) {
			direction_ = Direction::Right;
			nextHorizMove_ = Time::now() + horizInterval_;
			tryMove(direction_);
		}
		else if (event.Key.Code == sf::Key::Down) {
			direction_ = Direction::Drop;
			tryMove(direction_);
		}

		// ESC -> back to titles
		else if (event.Key.Code == sf::Key::Escape)
			Scenes::setCurrent("title");
	}
	else if (event.Type == sf::Event::KeyReleased) {
		// part two of avoiding system-originated
		// repeated key presses
		if (event.Key.Code == lastKeyPressed_)
			lastKeyPressed_ = sf::Key::Pause; // some random key
		
		if (event.Key.Code == sf::Key::Left || event.Key.Code == sf::Key::Right || event.Key.Code == sf::Key::Down)
			direction_ = Direction::None;
	}
}


void Game::tryRotate(bool clockwise) {
	if (piece_ == ShapeType::None)
		return;
	
	int tryRot = pieceRot_;
	if (clockwise)
		tryRot++;
	else
		tryRot--;
	
	if (grid_.canFitShapeAt(shapeWithRotation(piece_, tryRot), pieceCol_, pieceRow_)) {
		pieceRot_ = tryRot;
	}
}


void Game::tryMove(Direction dir) {
	if (piece_ == ShapeType::None)
		return;
		
	int tryCol = pieceCol_;
	int tryRow = pieceRow_;
	bool movedDown = false;
	
	if (dir == Direction::Left)
		tryCol--;
	else if (dir == Direction::Right)
		tryCol++;
	else if (dir == Direction::Drop) {
		tryRow++;
		movedDown = true;
	}
	
	if (grid_.canFitShapeAt(shapeWithRotation(piece_, pieceRot_), tryCol, tryRow)) {
		pieceRow_ = tryRow;
		pieceCol_ = tryCol;
		
		if (movedDown)
			nextTick_ = Time::now() + tickInterval_;
	}
}


void Game::handleCompletedLines() {
	auto cl = grid_.completedLines();
	if (! cl.size())
		return;

	grid_.collapseCompletedLines();
	lines_ += cl.size();
}


void Game::nextPiece() {
	piece_ = nextPiece_;
	nextPiece_ = randomShapeType();
	
	pieceRow_ = -1; pieceCol_ = 3;
	pieceRot_ = 40000;
}


void Game::tick() {
	if (piece_ == ShapeType::None) {
		// piece is None at start to allow for 1 tick pause
		// before gameplay
		nextPiece();
	}
	else {
		auto & shape = shapeWithRotation(piece_, pieceRot_);

		if (grid_.canFitShapeAt(shape, pieceCol_, pieceRow_ + 1))
			pieceRow_++;
		else {
			grid_.placeShapeAt(shape, pieceCol_, pieceRow_);
			nextPiece();
			
			handleCompletedLines();
		}
	}
}


void Game::frame() {
	// First allow player input to move piece
	// then process any forced down movement in the tick.
	// This is to allow for last moment movements.
	// These 2 checks are only for continuous moves, i.e.
	// the player keeps the key down for an amount of time.
	// The initial move is always performed immediately in
	// the event handler.
	if (Time::now() >= nextHorizMove_) {
		if (direction_ == Direction::Left || direction_ == Direction::Right)
			tryMove(direction_);
		nextHorizMove_ += horizInterval_;
	}
	if (Time::now() >= nextDropMove_) {
		if (direction_ == Direction::Drop)
			tryMove(direction_);
		nextDropMove_ += dropInterval_;
	}

	if (Time::now() >= nextTick_) {
		tick();
		nextTick_ += tickInterval_;
	}

	// render scene
	view_->renderBG();
	view_->renderShape(grid_.shape(), 24.f, 24.f);
	
	if (piece_ != ShapeType::None)
		view_->renderShape(shapeWithRotation(piece_, pieceRot_), 24. * (pieceCol_ + 1), 24. * (pieceRow_ + 1));
	
	if (nextPiece_ != ShapeType::None)
		view_->renderShape(shapeWithRotation(nextPiece_, 0), 300.f, 50.f);

	view_->renderLineCounter(lines_);
}
