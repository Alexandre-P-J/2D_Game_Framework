#include "Object.h"
#include "Engine.h"
#include <iostream>

std::map<std::string,ObjectFactory*> Object::factories;

void Object::registerType(const std::string& name, ObjectFactory* factory) {
	factories[name] = factory;
}

std::shared_ptr<Object> Object::create(const std::string& name, int game) {
	auto ptr = factories[name]->create();
	(EngineUtils::getGame(game)->OBJList).push_back(ptr);
	return ptr;
}


Position Object::getPosition() const {
	return P;
}
