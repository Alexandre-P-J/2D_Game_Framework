#include "ObjectManager.h"
void ObjectManager::Add(std::unique_ptr<Object>& Obj) {
	L.push_back(std::move(Obj));
}

void ObjectManager::Run() {
		std::list<std::unique_ptr<Object>>::iterator it = L.begin();
		while(it != L.end()) {
			(*it)->Update();
			++it;
		}
}
