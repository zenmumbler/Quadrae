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
	, grid_(20)
	, gridTiles_(20)
{
	Random::seed();

	tickLength_ = Time::Duration(500);
	nextTick_ = Time::now();
	
	piece_ = ShapeType::None;
	
	for (auto & gtLine : gridTiles_)
		gtLine.resize(10, ShapeType::None);
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
	}

	if (piece_ != ShapeType::None && grid_.canFitShapeAt(shapeWithRotation(piece_, tryRot), tryCol, tryRow)) {
		pieceRot_ = tryRot;
		pieceRow_ = tryRow;
		pieceCol_ = tryCol;
		
		if (movedDown)
			nextTick_ = Time::now() + tickLength_;
	}
}


void Game::placeShapeTiles(ShapeType type, const ShapeGrid & shape, int x, int y) {
	for (int row = y; row < y + 4; row++)
		if (row >= 0 && row < grid_.height())
			for (int col = x; col < x + 4; col++) {
				if (col >= 0 && col < 10 && testShapeAt(shape, col - x, row - y))
					gridTiles_[row][col] = type;
			}
}


void Game::tick() {
	if (piece_ == ShapeType::None) {
		piece_ = static_cast<ShapeType>(Random::intInRange(0, 6));
		pieceRow_ = -1; pieceCol_ = 3;
		pieceRot_ = 40000;
	}
	else {
		auto shape = shapeWithRotation(piece_, pieceRot_);

		if (grid_.canFitShapeAt(shape, pieceCol_, pieceRow_ + 1))
			pieceRow_++;
		else {
			grid_.placeShapeAt(shape, pieceCol_, pieceRow_);
			placeShapeTiles(piece_, shape, pieceCol_, pieceRow_);
			piece_ = ShapeType::None;
		}
	}
}


void Game::step() {
	if (Time::now() >= nextTick_) {
		tick();
		nextTick_ += tickLength_;
	}
	
	view_->renderBG();
	int row = 0, col = 0;
	for (auto & gtLine : gridTiles_) {
		col = 0;
		for (auto tile : gtLine) {
			if (tile != ShapeType::None)
				view_->renderTile(tile, 24. * (col + 1), 24. * (row + 1));
			col++;
		}
		row++;
	}
	
	if (piece_ != ShapeType::None)
		view_->renderShape(piece_, shapeWithRotation(piece_, pieceRot_), 24. * (pieceCol_ + 1), 24. * (pieceRow_ + 1));
}
