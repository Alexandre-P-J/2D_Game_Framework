#include "Object.h"
#include "Animation.h"


class DebugEnemy : public Object {
	Animation anim;
public:
	DebugEnemy();
	bool Update();
};

REGISTER_TYPE(DebugEnemy)
