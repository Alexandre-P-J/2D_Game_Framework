#include "Object.h"
#include "Engine.h"
#include <iostream>
#include <cassert>
#include <limits>

std::map<std::string,ObjectFactory*>& Object::getFactories() { //Singleton
	static std::map<std::string,ObjectFactory*> factories;
	return factories;
}

void Object::registerType(const std::string& name, ObjectFactory* factory) {
	getFactories()[name] = factory;
}
std::weak_ptr<Object> Object::create(const std::string& name, Position Pos) {
	auto gPTR = EngineUtils::getGame().lock();
	assert(gPTR && "Maybe you are creating an object before a game or in its contructor?");
	int uuid = 0;
	if (! gPTR->Objects.empty())
		uuid = (gPTR->Objects).rbegin()->first + 1;
	return create(name, Pos, uuid);
}
std::weak_ptr<Object> Object::create(const std::string& name, Position Pos, int uuid) {
	auto gPTR = EngineUtils::getGame().lock();
	assert(gPTR && "Maybe you are creating an object before a game or in its contructor?");

	auto it = getFactories().find(name);
	assert(it != getFactories().end() && "Requested invalid Object name");

	b2BodyDef* BodyDef = new b2BodyDef();
	BodyDef->position.Set(std::get<0>(Pos), std::get<1>(Pos));
	auto Body = gPTR->getWorldFromLevel(std::get<2>(Pos))->CreateBody(BodyDef);

	auto ptr = it->second->create(Body);
	ptr->LevelZCoordinate = std::get<2>(Pos);

	auto insertion = (gPTR->Objects).insert(std::make_pair(uuid, ptr));
	assert(insertion.second); //ensure that the UUID was unique

	auto Wptr = std::weak_ptr<Object>(ptr);
	if (name == "Player")
		(gPTR->Players).push_back(Wptr);
	return Wptr;
}


Position Object::getPosition() const {
	assert(Body); // this not ensures Body validity
	auto pos2D = Body->GetPosition();
	Position Pos = {pos2D.x, pos2D.y, LevelZCoordinate};
	return Pos;
}

Rotation Object::getRotation() const {
	assert(Body); // this not ensures Body validity
	Rotation Rot;
	Rot = Body->GetAngle();
	return Rot;
}

void Object::setPosition(Position P) { //WIP, IF Z CHANGES WE ARE FKED
	assert(Body); // this not ensures Body validity
	b2Vec2 pos = {std::get<0>(P), std::get<1>(P)};
	Body->SetTransform(pos, Body->GetAngle());
}

void Object::setRotation(Rotation R) {
	assert(Body); // this not ensures Body validity
	Body->SetTransform(Body->GetPosition(), R.get());
}
