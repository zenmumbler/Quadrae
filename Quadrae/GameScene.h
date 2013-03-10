//
//  GameScene.h
//  Quadrae
//
//  Created by Arthur Langereis on 2/25/13.
//  Copyright (c) 2013 Arthur Langereis. All rights reserved.
//

#ifndef __Quadrae__Game__
#define __Quadrae__Game__

#include <SFML/Graphics.hpp>
#include "Scene.h"
#include "Common.h"
#include "Quadrae.h"
#include "GameView.h"

enum class Direction {
	None,
	Left,
	Right,
	Drop
};


class Game : public Scene {
	std::unique_ptr<View> view_;
	Quadrae grid_;

	Time::Duration tickInterval_, horizInterval_, dropInterval_;
	Time::Point nextTick_, nextHorizMove_, nextDropMove_;

	ShapeType piece_, nextPiece_;
	Direction direction_;
	int pieceRot_, pieceRow_, pieceCol_;
	
	int level_, lines_;
	
	sf::Key::Code lastKeyPressed_;
	
	void handleCompletedLines();

	void tryRotate(bool clockwise);
	void tryMove(Direction dir);
	void nextPiece();

public:
	Game(const std::shared_ptr<sf::RenderWindow> & window);
	
	virtual void handleEvent(const sf::Event & event) override;

	void tick();
	virtual void activate() override;
	virtual void suspend() override;
	virtual void frame() override;
};


#endif /* defined(__Quadrae__Game__) */
