#pragma once
#include <list>
#include <functional>

class Event {
	std::list<std::function<void()>> BindedFunctions;
	public:
		Event();
		void operator()() const;
		std::list<std::function<void()>>::iterator Bind(std::function<void()> F);
		void UnBind(std::list<std::function<void()>>::iterator it);
};
