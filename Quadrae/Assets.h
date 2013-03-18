//
//  Assets.h
//  Quadrae
//
//  Created by Arthur Langereis on 2013/3/10.
//  Copyright (c) 2013 Arthur Langereis. All rights reserved.
//

#ifndef __Quadrae__Assets__
#define __Quadrae__Assets__

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

namespace Assets {
	bool loadAll();

	const sf::Image & tileTexture();
	const sf::Image & bgTexture();

	const sf::Font & font();

	void playMove();
	void playLock();
	void playClear();
	void playClear4();
};


#endif /* defined(__Quadrae__Assets__) */
