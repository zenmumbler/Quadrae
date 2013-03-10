//
//  Assets.cpp
//  Quadrae
//
//  Created by Arthur Langereis on 2013/3/10.
//  Copyright (c) 2013 Arthur Langereis. All rights reserved.
//

#include "Assets.h"

namespace Assets {

	static sf::Image tilesTex_s, bgTex_s;
	static sf::Font font_s;

	const sf::Image & tileTexture() { return tilesTex_s; }
	const sf::Image & bgTexture() { return bgTex_s; }
	
	const sf::Font & font() { return font_s; }

	bool loadAll() {
		bool ok = true;
		
		if (ok) ok = font_s.LoadFromFile("/Library/Fonts/Arial.ttf");
		if (ok)	ok = tilesTex_s.LoadFromFile("texture.png");
		if (ok)	ok = bgTex_s.LoadFromFile("bg.png");
		
		if (ok) {
			tilesTex_s.SetSmooth(false);
		}

		return ok;
	}
}
