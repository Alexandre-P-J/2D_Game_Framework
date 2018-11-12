#include "Event.h"

Event::Event(){}


void Event::operator()() const {
	for (auto & e : BindedFunctions)
		e();
}

std::list<std::function<void()>>::iterator Event::Bind(std::function<void()> F) {
	auto it = BindedFunctions.end();
	BindedFunctions.insert(it, F);
	return it;
}

void Event::UnBind(std::list<std::function<void()>>::iterator it) {
	BindedFunctions.erase(it);
}
