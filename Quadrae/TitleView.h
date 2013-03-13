//
//  TitleView.h
//  Quadrae
//
//  Created by Arthur Langereis on 2013/3/8.
//  Copyright (c) 2013 Arthur Langereis. All rights reserved.
//

#ifndef __Quadrae__TitleView__
#define __Quadrae__TitleView__

#include <memory>
#include <SFML/Graphics.hpp>
#include "Common.h"


class TitleView {
	std::shared_ptr<sf::RenderWindow> window_;
	
public:
	TitleView(const std::shared_ptr<sf::RenderWindow> & window);

	void renderBG() const;
	void renderLetters(const std::vector<std::vector<uint8_t>> & map, float percentage) const;
	void renderCopyright() const;
	void renderPressStart() const;
	void renderLogoTile(float x, float y) const;
};


#endif /* defined(__Quadrae__TitleView__) */
