#include "Object.h"
#include "Animation.h"


class DebugEnemy : public Object {
	Animation anim;
public:
	DebugEnemy(b2Body* Body);
	bool Update();
};

REGISTER_TYPE(DebugEnemy)
