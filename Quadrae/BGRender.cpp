//
//  BGRender.cpp
//  Quadrae
//
//  Created by Arthur Langereis on 2013/3/16.
//  Copyright (c) 2013 Arthur Langereis. All rights reserved.
//

#include <chrono>
#include <cmath>
#include "Common.h"
#include "Assets.h"
#include "BGRender.h"

namespace BGRender {
	static float bgOffX_s = 0.f;
	static float bgOffY_s = 0.f;
	static float bgScale_s = 1.f;

	// not really shape-related, but I can't be arsed to create a new file for this
	static void render(sf::RenderTarget & rt, float x, float y, float scale) {
		auto & bg = Assets::bgTexture();
		float scaledWidth = bg.GetWidth() * scale;
		float scaledHeight = bg.GetHeight() * scale;
		
		x = fmodf(x, scaledWidth);
		if (x > 0.f) x -= scaledWidth;
		y = fmodf(y, scaledHeight);
		if (y > 0.f) y -= scaledHeight;
		
		int tilesX = ceilf((rt.GetWidth() - x) / scaledWidth);
		int tilesY = ceilf((rt.GetHeight() - y) / scaledHeight);
		
		sf::Sprite sp { bg, { x, y }, { scale, scale } };
		
		while (tilesY--) {
			int ttx = tilesX;
			while (ttx--) {
				rt.Draw(sp);
				sp.Move(scaledWidth, 0.f);
			}
			sp.Move(0.f, scaledHeight);
			sp.SetX(x);
		}
	}
	
	void renderStep(sf::RenderTarget & rt) {
		using namespace std::chrono;
		using std::sinf; using std::cosf;
		
		float t = duration_cast<microseconds>(Time::now().time_since_epoch()).count() / 1000000.f;
		const float displace = 400.f;
		
		bgOffX_s = displace * (cosf(t / 13.f));
		bgOffY_s = displace * (sinf((t + 2.f) / 17.f));
		bgScale_s = 1.f + (0.3f * sinf( (t / 13.f) ));
		
		render(rt, bgOffX_s, bgOffY_s, bgScale_s);
	}
}
