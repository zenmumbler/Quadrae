//
//  Shape.h
//  Quadrae
//
//  Created by Arthur Langereis on 2013/3/4.
//  Copyright (c) 2013 Arthur Langereis. All rights reserved.
//

#ifndef __Quadrae__Shape__
#define __Quadrae__Shape__

#include <vector>

enum class ShapeType {
	None       = 0,
	TBone      = 1,
	RightHook  = 2,
	LeftStair  = 3,
	Square     = 4,
	RightStair = 5,
	LeftHook   = 6,
	Bar        = 7,
};


class Tile {
	uint8_t data_;

public:
	constexpr Tile() : data_(0) {}
	constexpr Tile(uint8_t val) : data_(val) {}
	constexpr Tile(const Tile & rhs) : data_(rhs.data_) {}
	
	Tile & operator=(const Tile & rhs) { data_ = rhs.data_; return *this; }
	Tile & operator=(uint8_t val) { data_ = val; return *this; }
	
	constexpr bool occupied() { return type() != ShapeType::None; }
	
	constexpr ShapeType type() { return static_cast<ShapeType>(data_ & 7); }
	Tile & setType(ShapeType type) { data_ = (data_ & ~7) | static_cast<uint8_t>(type); return *this; }
	
	constexpr size_t rotation() { return (data_ >> 3) & 3; }
	Tile & setRotation(size_t rot) { data_ = (data_ & ~24) | ((rot & 3) << 3); return *this; }
	
	constexpr size_t segment() { return (data_ >> 5) & 3; }
	Tile & setSegment(size_t seg) { data_ = (data_ & ~96) | ((seg & 3) << 5); return *this; }
};


class Shape {
	std::vector<std::vector<Tile>> data_;
	
public:
	using Row = std::vector<Tile>;
	
	Shape(size_t cols, size_t rows);
	Shape(const std::vector<std::vector<Tile>> & data) : data_(data) {}
	Shape(const std::initializer_list<Row> init) : data_(init) {}
	
	size_t rows() const { return data_.size(); }
	size_t cols() const { return data_[0].size(); }
	
	Tile & at(size_t col, size_t row);
	Tile at(size_t col, size_t row) const;

	Row & row(size_t row) { return data_.at(row); }
	const Row & row(size_t row) const { return data_.at(row); }

	Shape rotateCW(int pivotX, int pivotY) const;
	
	decltype(data_)::iterator begin() { return data_.begin(); }
	decltype(data_)::iterator end() { return data_.end(); }

	decltype(data_)::const_iterator begin() const { return data_.cbegin(); }
	decltype(data_)::const_iterator end() const { return data_.cend(); }
};


const Shape & shapeWithRotation(ShapeType type, size_t rotation);


#endif /* defined(__Quadrae__Shape__) */
