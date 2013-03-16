//
//  GameView.h
//  Quadrae
//
//  Created by Arthur Langereis on 2/25/13.
//  Copyright (c) 2013 Arthur Langereis. All rights reserved.
//

#ifndef __Quadrae__View__
#define __Quadrae__View__

#include <memory>
#include <SFML/Graphics.hpp>
#include "Common.h"
#include "Shape.h"
#include "PlayField.h"

class GameView {
	std::shared_ptr<sf::RenderWindow> window_;

public:
	GameView(const std::shared_ptr<sf::RenderWindow> & window);
	
	void renderBox(float x, float y, float w, float h, const std::string & title = "") const;

	void renderBG() const;
	void renderCounters(int level, int lines) const;
	void renderPause() const;
	void renderGameOver() const;

	void renderShape(const Shape & shape, float x, float y) const;
	void renderGridShape(const Shape & shape, int col, int row) const;

	void fadeClearedLines(const PlayField & field, float progress) const;
	void fadePlayField(float progress) const;
};

#endif /* defined(__Quadrae__View__) */
