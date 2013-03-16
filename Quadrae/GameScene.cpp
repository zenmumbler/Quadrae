//
//  GameScene.cpp
//  Quadrae
//
//  Created by Arthur Langereis on 2/25/13.
//  Copyright (c) 2013 Arthur Langereis. All rights reserved.
//

#include "Config.h"
#include "GameScene.h"
#include <cmath>

GameScene::GameScene(const std::shared_ptr<sf::RenderWindow> & window)
	: Scene(window)
	, view_(window)
{
	tickInterval_   = Time::Duration(500); // variable, will be set in setLevel(int)
	horizInterval_  = Time::Duration(120);
	dropInterval_   = Time::Duration(50);
	
	initialDelay_   = Time::Duration(1000);
	afterLockDelay_ = Time::Duration(200);
	
	clearLineAnimDuration_ = Time::Duration(1000);
	finalAnimDuration_ = Time::Duration(2000);
	
	level_ = 0;
	lines_ = 0;

	piece_ = ShapeType::None;
	nextPiece_ = ShapeType::None;
	
	phase_ = Phase::GameOver;
}


void GameScene::activate() {
	nextTick_ = Time::now();
	nextHorizMove_ = nextTick_;
	nextDropMove_ = nextTick_;
	
	setLevel(Config::baseLevel());
	lines_ = 0;
	phase_ = Phase::PieceFall;

	piece_ = ShapeType::None;
	nextPiece_ = pieceGen_.next();
	direction_ = Direction::None;
	
	nextPiece();
	nextTick_ += initialDelay_;

	field_.clear();
}


void GameScene::suspend() {
}


void GameScene::handleEvent(const sf::Event & event) {
	auto bindings = Config::keys();

	if (event.Type == sf::Event::KeyPressed) {
		// lame hack to overcome that a keypress in SFML
		// can repeat, i.e. not physical but virtual keypress
		if (event.Key.Code == lastKeyPressed_)
			return;
		lastKeyPressed_ = event.Key.Code;

		if (event.Key.Code == bindings.rotCW)
			tryRotate(true);
		else if (event.Key.Code == bindings.rotCCW)
			tryRotate(false);
		else if (event.Key.Code == bindings.left) {
			direction_ = Direction::Left;
			nextHorizMove_ = Time::now() + horizInterval_;
			tryMove(direction_);
		}
		else if (event.Key.Code == bindings.right) {
			direction_ = Direction::Right;
			nextHorizMove_ = Time::now() + horizInterval_;
			tryMove(direction_);
		}
		else if (event.Key.Code == bindings.drop) {
			direction_ = Direction::Drop;
			tryMove(direction_);
		}

		// Return -> toggle pause or back to titles if Game Over
		else if (event.Key.Code == sf::Key::Return) {
			if (phase_ == Phase::GameOver)
				Scenes::setCurrent("title");
			else
				togglePause();
		}

		// ESC -> back to titles
		else if (event.Key.Code == sf::Key::Escape)
			Scenes::setCurrent("title");
	}
	else if (event.Type == sf::Event::KeyReleased) {
		// part two of avoiding system-originated
		// repeated key presses
		auto key = event.Key.Code;

		if (key == lastKeyPressed_)
			lastKeyPressed_ = sf::Key::Pause; // some random key

		// set Direction back to None only if key released
		// is the one that is affecting Direction now
		if ((direction_ == Direction::Left && key == bindings.left) ||
			(direction_ == Direction::Right && key == bindings.right) ||
			(direction_ == Direction::Drop && key == bindings.drop))
			direction_ = Direction::None;
	}
}


void GameScene::setLevel(int level) {
	level_ = std::max(0, std::min(30, level));
	int ms = std::round(800. * std::pow(0.864, (double)level_));
	tickInterval_ = Time::Duration(ms);
}


void GameScene::togglePause() {
	if (phase_ == Phase::GameOver || phase_ == Phase::TopOut)
		return;
	if (phase_ == Phase::Paused) {
		// pretend pause time did not happen
		auto pauseDuration = Time::now() - pausedAt_;
		nextTick_ += pauseDuration;
		nextHorizMove_ += pauseDuration;
		nextDropMove_ += pauseDuration;

		phase_ = savePhase_;
	}
	else {
		pausedAt_ = Time::now();
		savePhase_ = phase_;
		phase_ = Phase::Paused;
	}
}


void GameScene::tryRotate(bool clockwise) {
	if (piece_ == ShapeType::None)
		return;
	
	int tryRot = pieceRot_;
	if (clockwise)
		tryRot++;
	else
		tryRot--;
	
	if (field_.canFitShapeAt(shapeWithRotation(piece_, tryRot), pieceCol_, pieceRow_))
		pieceRot_ = tryRot;
}


void GameScene::tryMove(Direction dir) {
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
	
	if (field_.canFitShapeAt(shapeWithRotation(piece_, pieceRot_), tryCol, tryRow)) {
		pieceRow_ = tryRow;
		pieceCol_ = tryCol;
		
		if (movedDown)
			nextTick_ = Time::now() + tickInterval_;
	}
}


void GameScene::handleCompletedLines() {
	auto cl = field_.completedLines();
	if (! cl.size())
		return;

	field_.collapseCompletedLines();
	lines_ += cl.size();
	
	// if we crossed a 10-line limit then the level increases
	// old-school style
	if ((lines_ % 10) < cl.size())
		setLevel(level_ + 1);
}


void GameScene::nextPiece() {
	piece_ = nextPiece_;
	nextPiece_ = pieceGen_.next();
	
	pieceRow_ = -1; pieceCol_ = 3;
	pieceRot_ = 40000;
}


void GameScene::tick() {
	if (piece_ == ShapeType::None) {
		nextPiece();
	}
	else {
		auto & shape = shapeWithRotation(piece_, pieceRot_);

		if (field_.canFitShapeAt(shape, pieceCol_, pieceRow_ + 1)) {
			pieceRow_++;
			nextTick_ += tickInterval_;
		}
		else {
			if (! field_.canFitShapeAt(shape, pieceCol_, pieceRow_)) {
				// the shape will overwrite something in the top
				// that means game over
				field_.placeShapeAt(shape, pieceCol_, pieceRow_);
				piece_ = ShapeType::None;
				phase_ = Phase::TopOut;
				nextTick_ += finalAnimDuration_;
			}
			else {
				field_.placeShapeAt(shape, pieceCol_, pieceRow_);
				
				if (field_.completedLines().size()) {
					phase_ = Phase::ClearLines;
					nextTick_ = Time::now() + clearLineAnimDuration_;
				}
				else {
					nextPiece();
					nextTick_ += tickInterval_ + afterLockDelay_;
				}
			}
		}
	}
}


static float timeRatio(const Time::Point & from, const Time::Point & to, const Time::Duration & total) {
	using namespace std::chrono;
	return (float)(duration_cast<Time::Duration>(to - from).count()) / (float)total.count();
}


void GameScene::frame() {
	// First allow player input to move piece
	// then process any forced down movement in the tick.
	// This is to allow for last moment movements.
	// These 2 checks are only for continuous moves, i.e.
	// the player keeps the key down for an amount of time.
	// The initial move is always performed immediately in
	// the event handler.
	
	if (phase_ != Phase::Paused) {
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
			if (phase_ == Phase::ClearLines) {
				handleCompletedLines();
				nextPiece();
				phase_ = Phase::PieceFall;
			}
			else if (phase_ == Phase::TopOut)
				phase_ = Phase::GameOver;
			
			if (phase_ == Phase::PieceFall || phase_ == Phase::ClearLines)
				tick();
		}
	}

	// render scene
	view_.renderBG();
	view_.renderCounters(level_, lines_);

	// playfield
	if (phase_ != Phase::Paused && phase_ != Phase::GameOver)
		view_.renderShape(field_.shape(), 24.f, 24.f);

	// stuff inside the playfield
	if (phase_ == Phase::PieceFall) {
		if (piece_ != ShapeType::None)
			view_.renderGridShape(shapeWithRotation(piece_, pieceRot_), pieceCol_, pieceRow_);
	}
	else if (phase_ == Phase::ClearLines) {
		float p = timeRatio(Time::now(), nextTick_, clearLineAnimDuration_);
		view_.fadeClearedLines(field_, p);
	}
	else if (phase_ == Phase::Paused)
		view_.renderPause();
	else if (phase_ == Phase::TopOut)
		view_.fadePlayField(timeRatio(Time::now(), nextTick_, finalAnimDuration_));
	else if (phase_ == Phase::GameOver)
		view_.renderGameOver();


	// next piece
	if (phase_ == Phase::PieceFall || phase_ == Phase::ClearLines)
		if (nextPiece_ != ShapeType::None)
			view_.renderShape(shapeWithRotation(nextPiece_, 0), 292.f, 50.f);
}
