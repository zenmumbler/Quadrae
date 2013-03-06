//
//  Game.h
//  Quadrae
//
//  Created by Arthur Langereis on 2/25/13.
//  Copyright (c) 2013 Arthur Langereis. All rights reserved.
//

#ifndef __Quadrae__Game__
#define __Quadrae__Game__

#include <SFML/Graphics.hpp>
#include "Common.h"
#include "Quadrae.h"
#include "View.h"

enum class Direction {
	None,
	Left,
	Right,
	Down,
	Drop
};


class Game {
	std::shared_ptr<sf::RenderWindow> window_;
	std::unique_ptr<View> view_;
	Quadrae grid_;
	std::vector<std::vector<ShapeType>> gridTiles_;

	Time::Duration tickLength_;
	Time::Point nextTick_;

	ShapeType piece_;
	Direction direction_;
	int pieceRot_, pieceRow_, pieceCol_;
	
	void placeShapeTiles(ShapeType type, const ShapeGrid & shape, int x, int y);

public:
	Game(const std::shared_ptr<sf::RenderWindow> & window);
	
	void handleEvent(const sf::Event & event);

	void tick();
	void step();
};


#endif /* defined(__Quadrae__Game__) */
