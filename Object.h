#pragma once
#include "ExtraTypes.h"
#include "Animation.h"
#include <map>
#include <memory>

class Object;

class ObjectFactory {
public:
    virtual std::shared_ptr<Object> create() = 0;
};

class Object {
	protected:
		Position P;
		Rotation R;
	private:
		bool visible = true;
	public:
		Position getPosition() const;
		virtual bool Update() = 0;

		static std::map<std::string,ObjectFactory*> factories;

		static void registerType(const std::string& name, ObjectFactory* factory);

		static std::weak_ptr<Object> create(const std::string& name, int game = 0);
};

#define REGISTER_TYPE(klass) \
    class klass##Factory : public ObjectFactory { \
    public: \
        klass##Factory() \
        { \
            Object::registerType(#klass, this); \
        } \
        virtual std::shared_ptr<Object> create() { \
            return std::shared_ptr<klass>(new klass()); \
        } \
    }; \
    static klass##Factory global_##klass##Factory;
