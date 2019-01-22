#pragma once
#include "Input.h"
#include "ExtraTypes.h"
#include "Animation.h"

class Object {
	protected:
		Position P;
		Rotation R;
	private:
		bool visible = true;
	public:
		Position getPosition() const;
		virtual bool Update();
};
