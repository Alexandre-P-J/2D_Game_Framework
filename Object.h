#pragma once
#include "ExtraTypes.h"
#include "Animation.h"
#include <map>
#include <memory>
#include <iostream>
#include "Box2D/Box2D.h"

class Object;

class ObjectFactory {
public:
    virtual std::shared_ptr<Object> create(b2Body* Body) = 0;
};



class Object {
	protected:
		b2Body* Body = nullptr;
		int16_t LevelZCoordinate;
		Rotation R;
	private:
		static std::map<std::string,ObjectFactory*>& getFactories(); //Singleton
	public:
		Position getPosition() const;
		void setPosition(Position P);
		virtual bool Update() = 0;

		static void registerType(const std::string& name, ObjectFactory* factory);

		static std::weak_ptr<Object> create(const std::string& name, Position Pos);
		static std::weak_ptr<Object> create(const std::string& name, Position Pos, int uuid);
};

#define REGISTER_TYPE(klass) \
    class klass##Factory : public ObjectFactory { \
    public: \
        klass##Factory() \
        { \
            Object::registerType(#klass, this); \
        } \
        virtual std::shared_ptr<Object> create(b2Body* Body) { \
            return std::shared_ptr<klass>(new klass(Body)); \
        } \
    }; \
    static klass##Factory global_##klass##Factory;
