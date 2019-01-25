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
std::weak_ptr<Object> Object::create(const std::string& name) {
	auto it = getFactories().find(name);
	assert(it != getFactories().end() && "Requested invalid Object name");
	auto ptr = it->second->create();
	auto gPTR = EngineUtils::getGame();
	assert(gPTR && "Maybe you are creating an object before a game or in its contructor?");
	int uuid = 0;
	if (! gPTR->Objects.empty())
		uuid = (gPTR->Objects).rbegin()->first;
	assert(uuid < std::numeric_limits<int>::max());
	(gPTR->Objects).insert(std::make_pair(uuid + 1, ptr));

	auto Wptr = std::weak_ptr<Object>(ptr);
	if (name == "Player")
		(EngineUtils::getGame()->Players).push_back(Wptr);
	return Wptr;
}
std::weak_ptr<Object> Object::create(const std::string& name, int uuid) {
	auto it = getFactories().find(name);
	assert(it != getFactories().end() && "Requested invalid Object name");
	auto ptr = it->second->create();
	auto insertion = (EngineUtils::getGame()->Objects).insert(std::make_pair(uuid, ptr));
	assert(insertion.second); //ensure that the UUID was unique
	auto Wptr = std::weak_ptr<Object>(ptr);
	if (name == "Player")
		(EngineUtils::getGame()->Players).push_back(Wptr);
	return Wptr;
}


Position Object::getPosition() const {
	return P;
}

void Object::setPosition(Position P) {
	this->P = P;
}
