#pragma once
#include "ExtraTypes.h"

class Object {
		Position P;
		bool visible = true;
	public:
		virtual void Update();
		const Position& GetPosition() const;
};
