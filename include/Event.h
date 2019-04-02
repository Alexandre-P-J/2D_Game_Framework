#pragma once
#include <list>
#include <map>
#include "FastDelegate.h"
#include "FastDelegateBind.h"
#include <cassert>
#include <limits>

/*
 * Syntax: Event<int, double&, float> MyEvent; Creates an event that binds functions
 *         of return type void, first argument integer by value, second double
 *         By Reference and third float by value.
 *         Can be used on procedures with up to 7 arguments.
*/



template <typename ...Base> class Event {};

template<>
class Event<> {
	using DelegateType = fastdelegate::FastDelegate0<void>;
	std::list<DelegateType> BindedFunctions;
	std::map<uint32_t,typename std::list<DelegateType>::iterator> ListIterators;
	uint32_t lastID = 0;
	public:
		int size() const {
			return BindedFunctions.size();
		}
		uint32_t Bind(DelegateType Delegate) {
			assert(lastID != std::numeric_limits<uint32_t>::max());
			auto it = BindedFunctions.insert(BindedFunctions.end(), Delegate);
			++lastID;
			ListIterators.insert(std::make_pair(lastID, it));
			return lastID;
		}
		template <class X, class Y>
		uint32_t inline Bind(Y* x, void (X::*func)()) {
			return Bind(fastdelegate::FastDelegate0<void>(x, func));
		}

		uint32_t inline Bind(void (*func)()) {
			return Bind(fastdelegate::FastDelegate0<void>(func));
		}

		void UnBind(const uint32_t ID) {
			auto it = ListIterators.find(ID);
			if (it != ListIterators.end()) {
				auto iterator = it->second;
				ListIterators.erase(it);
				BindedFunctions.erase(iterator);
			}
			if (lastID == ID && lastID > 0)
				--lastID;
		}

		void inline operator()() {
			for (DelegateType Delegate : BindedFunctions)
				Delegate();
		}
};

template<typename Arg0>
class Event<Arg0> {
	using DelegateType = fastdelegate::FastDelegate1<Arg0,void>;
	std::list<DelegateType> BindedFunctions;
	std::map<uint32_t,typename std::list<DelegateType>::iterator> ListIterators;
	uint32_t lastID = 0;
	public:
		int size() const {
			return BindedFunctions.size();
		}
		uint32_t Bind(DelegateType Delegate) {
			assert(lastID != std::numeric_limits<uint32_t>::max());
			auto it = BindedFunctions.insert(BindedFunctions.end(), Delegate);
			++lastID;
			ListIterators.insert(std::make_pair(lastID, it));
			return lastID;
		}
		template <class X, class Y>
		uint32_t inline Bind(Y* x, void (X::*func)(Arg0 arg0)) {
			return Bind(fastdelegate::FastDelegate1<Arg0,void>(x, func));
		}

		uint32_t inline Bind(void (*func)(Arg0 arg0)) {
			return Bind(fastdelegate::FastDelegate1<Arg0,void>(func));
		}

		void UnBind(const uint32_t ID) {
			auto it = ListIterators.find(ID);
			if (it != ListIterators.end()) {
				auto iterator = it->second;
				ListIterators.erase(it);
				BindedFunctions.erase(iterator);
			}
			if (lastID == ID && lastID > 0)
				--lastID;
		}

		void inline operator()(Arg0 arg0) {
			for (DelegateType Delegate : BindedFunctions)
				Delegate(arg0);
		}
};

template<typename Arg0, typename Arg1>
class Event<Arg0, Arg1> {
	using DelegateType = fastdelegate::FastDelegate2<Arg0, Arg1, void>;
	std::list<DelegateType> BindedFunctions;
	std::map<uint32_t,typename std::list<DelegateType>::iterator> ListIterators;
	uint32_t lastID = 0;
	public:
		int size() const {
			return BindedFunctions.size();
		}
		uint32_t Bind(DelegateType Delegate) {
			assert(lastID != std::numeric_limits<uint32_t>::max());
			auto it = BindedFunctions.insert(BindedFunctions.end(), Delegate);
			++lastID;
			ListIterators.insert(std::make_pair(lastID, it));
			return lastID;
		}
		template <class X, class Y>
		uint32_t inline Bind(Y* x, void (X::*func)(Arg0 arg0, Arg1 arg1)) {
			return Bind(fastdelegate::FastDelegate2<Arg0,Arg1,void>(x, func));
		}

		uint32_t inline Bind(void (*func)(Arg0 arg0,Arg1 arg1)) {
			return Bind(fastdelegate::FastDelegate2<Arg0,Arg1,void>(func));
		}


		void UnBind(const uint32_t ID) {
			auto it = ListIterators.find(ID);
			if (it != ListIterators.end()) {
				auto iterator = it->second;
				ListIterators.erase(it);
				BindedFunctions.erase(iterator);
			}
			if (lastID == ID && lastID > 0)
				--lastID;
		}

		void inline operator()(Arg0 arg0, Arg1 arg1) {
			for (DelegateType Delegate : BindedFunctions)
				Delegate(arg0, arg1);
		}
};


template<typename Arg0, typename Arg1, typename Arg2>
class Event<Arg0,Arg1,Arg2> {
	using DelegateType = fastdelegate::FastDelegate3<Arg0, Arg1, Arg2, void>;
	std::list<DelegateType> BindedFunctions;
	std::map<uint32_t,typename std::list<DelegateType>::iterator> ListIterators;
	uint32_t lastID = 0;
	public:
		int size() const {
			return BindedFunctions.size();
		}
		uint32_t Bind(DelegateType Delegate) {
			assert(lastID != std::numeric_limits<uint32_t>::max());
			auto it = BindedFunctions.insert(BindedFunctions.end(), Delegate);
			++lastID;
			ListIterators.insert(std::make_pair(lastID, it));
			return lastID;
		}
		template <class X, class Y>
		uint32_t inline Bind(Y* x, void (X::*func)(Arg0 arg0, Arg1 arg1, Arg2 arg2)) {
			return Bind(fastdelegate::FastDelegate3<Arg0,Arg1,Arg2,void>(x, func));
		}

		uint32_t inline Bind(void (*func)(Arg0 arg0,Arg1 arg1,Arg2 arg2)) {
			return Bind(fastdelegate::FastDelegate3<Arg0,Arg1,Arg2,void>(func));
		}


		void UnBind(const uint32_t ID) {
			auto it = ListIterators.find(ID);
			if (it != ListIterators.end()) {
				auto iterator = it->second;
				ListIterators.erase(it);
				BindedFunctions.erase(iterator);
			}
			if (lastID == ID && lastID > 0)
				--lastID;
		}

		void inline operator()(Arg0 arg0, Arg1 arg1, Arg2 arg2) {
			for (DelegateType Delegate : BindedFunctions)
				Delegate(arg0, arg1, arg2);
		}
};

template<typename Arg0, typename Arg1, typename Arg2, typename Arg3>
class Event<Arg0,Arg1,Arg2,Arg3> {
	using DelegateType = fastdelegate::FastDelegate4<Arg0, Arg1, Arg2, Arg3, void>;
	std::list<DelegateType> BindedFunctions;
	std::map<uint32_t,typename std::list<DelegateType>::iterator> ListIterators;
	uint32_t lastID = 0;
	public:
		int size() const {
			return BindedFunctions.size();
		}
		uint32_t Bind(DelegateType Delegate) {
			assert(lastID != std::numeric_limits<uint32_t>::max());
			auto it = BindedFunctions.insert(BindedFunctions.end(), Delegate);
			++lastID;
			ListIterators.insert(std::make_pair(lastID, it));
			return lastID;
		}
		template <class X, class Y>
		uint32_t inline Bind(Y* x, void (X::*func)(Arg0 arg0, Arg1 arg1, Arg2 arg2, Arg3 arg3)) {
			return Bind(fastdelegate::FastDelegate4<Arg0,Arg1,Arg2,Arg3,void>(x, func));
		}

		uint32_t inline Bind(void (*func)(Arg0 arg0,Arg1 arg1,Arg2 arg2,Arg3 arg3)) {
			return Bind(fastdelegate::FastDelegate4<Arg0,Arg1,Arg2,Arg3,void>(func));
		}


		void UnBind(const uint32_t ID) {
			auto it = ListIterators.find(ID);
			if (it != ListIterators.end()) {
				auto iterator = it->second;
				ListIterators.erase(it);
				BindedFunctions.erase(iterator);
			}
			if (lastID == ID && lastID > 0)
				--lastID;
		}

		void inline operator()(Arg0 arg0, Arg1 arg1, Arg2 arg2, Arg3 arg3) {
			for (DelegateType Delegate : BindedFunctions)
				Delegate(arg0, arg1, arg2, arg3);
		}
};

template<typename Arg0, typename Arg1, typename Arg2, typename Arg3, typename Arg4>
class Event<Arg0,Arg1,Arg2,Arg3,Arg4> {
	using DelegateType = fastdelegate::FastDelegate5<Arg0, Arg1, Arg2, Arg3, Arg4, void>;
	std::list<DelegateType> BindedFunctions;
	std::map<uint32_t,typename std::list<DelegateType>::iterator> ListIterators;
	uint32_t lastID = 0;
	public:
		int size() const {
			return BindedFunctions.size();
		}
		uint32_t Bind(DelegateType Delegate) {
			assert(lastID != std::numeric_limits<uint32_t>::max());
			auto it = BindedFunctions.insert(BindedFunctions.end(), Delegate);
			++lastID;
			ListIterators.insert(std::make_pair(lastID, it));
			return lastID;
		}
		template <class X, class Y>
		uint32_t inline Bind(Y* x, void (X::*func)(Arg0 arg0, Arg1 arg1, Arg2 arg2, Arg3 arg3, Arg4 arg4)) {
			return Bind(fastdelegate::FastDelegate5<Arg0,Arg1,Arg2,Arg3,Arg4,void>(x, func));
		}

		uint32_t inline Bind(void (*func)(Arg0 arg0,Arg1 arg1,Arg2 arg2,Arg3 arg3,Arg4 arg4)) {
			return Bind(fastdelegate::FastDelegate5<Arg0,Arg1,Arg2,Arg3,Arg4,void>(func));
		}


		void UnBind(const uint32_t ID) {
			auto it = ListIterators.find(ID);
			if (it != ListIterators.end()) {
				auto iterator = it->second;
				ListIterators.erase(it);
				BindedFunctions.erase(iterator);
			}
			if (lastID == ID && lastID > 0)
				--lastID;
		}

		void inline operator()(Arg0 arg0, Arg1 arg1, Arg2 arg2, Arg3 arg3, Arg4 arg4) {
			for (DelegateType Delegate : BindedFunctions)
				Delegate(arg0, arg1, arg2, arg3, arg4);
		}
};

template<typename Arg0, typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5>
class Event<Arg0,Arg1,Arg2,Arg3,Arg4,Arg5> {
	using DelegateType = fastdelegate::FastDelegate6<Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, void>;
	std::list<DelegateType> BindedFunctions;
	std::map<uint32_t,typename std::list<DelegateType>::iterator> ListIterators;
	uint32_t lastID = 0;
	public:
		int size() const {
			return BindedFunctions.size();
		}
		uint32_t Bind(DelegateType Delegate) {
			assert(lastID != std::numeric_limits<uint32_t>::max());
			auto it = BindedFunctions.insert(BindedFunctions.end(), Delegate);
			++lastID;
			ListIterators.insert(std::make_pair(lastID, it));
			return lastID;
		}
		template <class X, class Y>
		uint32_t inline Bind(Y* x, void (X::*func)(Arg0 arg0, Arg1 arg1, Arg2 arg2, Arg3 arg3, Arg4 arg4, Arg5 arg5)) {
			return Bind(fastdelegate::FastDelegate6<Arg0,Arg1,Arg2,Arg3,Arg4,Arg5,void>(x, func));
		}

		uint32_t inline Bind(void (*func)(Arg0 arg0,Arg1 arg1,Arg2 arg2,Arg3 arg3,Arg4 arg4,Arg5 arg5)) {
			return Bind(fastdelegate::FastDelegate6<Arg0,Arg1,Arg2,Arg3,Arg4,Arg5,void>(func));
		}


		void UnBind(const uint32_t ID) {
			auto it = ListIterators.find(ID);
			if (it != ListIterators.end()) {
				auto iterator = it->second;
				ListIterators.erase(it);
				BindedFunctions.erase(iterator);
			}
			if (lastID == ID && lastID > 0)
				--lastID;
		}

		void inline operator()(Arg0 arg0, Arg1 arg1, Arg2 arg2, Arg3 arg3, Arg4 arg4, Arg5 arg5) {
			for (DelegateType Delegate : BindedFunctions)
				Delegate(arg0, arg1, arg2, arg3, arg4, arg5);
		}
};

template<typename Arg0, typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5, typename Arg6>
class Event<Arg0,Arg1,Arg2,Arg3,Arg4,Arg5,Arg6> {
	using DelegateType = fastdelegate::FastDelegate7<Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, void>;
	std::list<DelegateType> BindedFunctions;
	std::map<uint32_t,typename std::list<DelegateType>::iterator> ListIterators;
	uint32_t lastID = 0;
	public:
		int size() const {
			return BindedFunctions.size();
		}
		uint32_t Bind(DelegateType Delegate) {
			assert(lastID != std::numeric_limits<uint32_t>::max());
			auto it = BindedFunctions.insert(BindedFunctions.end(), Delegate);
			++lastID;
			ListIterators.insert(std::make_pair(lastID, it));
			return lastID;
		}
		template <class X, class Y>
		uint32_t inline Bind(Y* x, void (X::*func)(Arg0 arg0, Arg1 arg1, Arg2 arg2, Arg3 arg3, Arg4 arg4, Arg5 arg5, Arg6 arg6)) {
			return Bind(fastdelegate::FastDelegate7<Arg0,Arg1,Arg2,Arg3,Arg4,Arg5,Arg6,void>(x, func));
		}

		uint32_t inline Bind(void (*func)(Arg0 arg0,Arg1 arg1,Arg2 arg2,Arg3 arg3,Arg4 arg4,Arg5 arg5, Arg6 arg6)) {
			return Bind(fastdelegate::FastDelegate7<Arg0,Arg1,Arg2,Arg3,Arg4,Arg5,Arg6,void>(func));
		}


		void UnBind(const uint32_t ID) {
			auto it = ListIterators.find(ID);
			if (it != ListIterators.end()) {
				auto iterator = it->second;
				ListIterators.erase(it);
				BindedFunctions.erase(iterator);
			}
			if (lastID == ID && lastID > 0)
				--lastID;
		}

		void inline operator()(Arg0 arg0, Arg1 arg1, Arg2 arg2, Arg3 arg3, Arg4 arg4, Arg5 arg5, Arg6 arg6) {
			for (DelegateType Delegate : BindedFunctions)
				Delegate(arg0, arg1, arg2, arg3, arg4, arg5, arg6);
		}
};
