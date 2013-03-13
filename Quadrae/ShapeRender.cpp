//
//  ShapeRender.cpp
//  Quadrae
//
//  Created by Arthur Langereis on 2013/3/10.
//  Copyright (c) 2013 Arthur Langereis. All rights reserved.
//

#include <map>
#include <cmath>
#include "Assets.h"
#include "ShapeRender.h"

namespace ShapeRender {

	sf::IntRect texRectForTile(const Tile t) {
		static std::map<ShapeType, std::vector<sf::Vector2i>> tileUV_s;
		
		if (tileUV_s.size() == 0) {
			tileUV_s.insert({ ShapeType::None,       { { 0,3 }, { 0,3 }, { 0,3 }, { 0,3 } } });
			tileUV_s.insert({ ShapeType::TBone,      { { 1,4 }, { 2,4 }, { 3,4 }, { 2,5 } } });
			tileUV_s.insert({ ShapeType::RightHook,  { { 0,0 }, { 1,0 }, { 2,0 }, { 2,1 } } });
			tileUV_s.insert({ ShapeType::LeftStair,  { { 3,3 }, { 4,3 }, { 4,4 }, { 5,4 } } });
			tileUV_s.insert({ ShapeType::Square,     { { 0,1 }, { 1,1 }, { 0,2 }, { 1,2 } } });
			tileUV_s.insert({ ShapeType::RightStair, { { 3,1 }, { 4,1 }, { 4,0 }, { 5,0 } } });
			tileUV_s.insert({ ShapeType::LeftHook,   { { 0,4 }, { 0,3 }, { 1,3 }, { 2,3 } } });
			tileUV_s.insert({ ShapeType::Bar,        { { 2,2 }, { 3,2 }, { 4,2 }, { 5,2 } } });
		}
		
		auto txy = tileUV_s[t.type()][t.segment()];
		
		return { txy.x * 24, txy.y * 24, (txy.x + 1) * 24, (txy.y + 1) * 24 };
	}

	
	sf::Sprite genTileSprite(const Tile & tile, float x, float y) {
		sf::Sprite ts { Assets::tileTexture(), { x + 12.f, y + 12.f } };
		ts.SetSubRect(texRectForTile(tile));
		ts.SetCenter(12.f, 12.f);
		ts.SetRotation(-90.f * tile.rotation());
		return ts;
	}

	
	void render(const Shape & shape, float x, float y, const std::function<void(sf::Sprite&&)> act) {
		for (auto row = 0u; row < shape.rows(); row++) {
			for (auto col = 0u; col < shape.cols(); col++) {
				Tile tile = shape.at(col, row);
				if (tile.occupied())
					act(genTileSprite(tile, x + (col * 24.f), y + (row * 24.f)));
			}
		}
	}
	
	
	void render(sf::RenderTarget & rt, const Shape & shape, float x, float y) {
		render(shape, x, y, [&rt](const sf::Sprite & sp) {
			rt.Draw(sp);
		});
	}

	
	// not really shape-related, but I can't be arsed to create a new file for this
	void renderTiledBG(sf::RenderTarget & rt, float x, float y, float scale) {
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
}
