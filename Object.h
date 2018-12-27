#pragma once
#include "Input.h"
#include "ExtraTypes.h"

class Object {
		Position P;
		bool visible = true;
	public:
		virtual bool Update();
		const Position& GetPosition() const;
};
