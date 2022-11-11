#pragma once

#include<functional>

using namespace std;

template<typename T>
struct Property
{
private:
	T value;
	function<T()> get;
	function<void(T)> set;

public:

	Property();
	Property(function<T()> get, function<void(T)> set);
	Property(T defaultVal, function<T()> get, function<void(T)> set);
	Property(T defaultVal);

	T Get();
	void Set(T val);
};

template<typename T>
inline Property<T>::Property()
{
	get = [this]() { return value; };
	set = [this](T val) { value = val; };
}

template<typename T>
inline Property<T>::Property(function<T()> get, function<void(T)> set)
{
	this->get = get;
	this->set = set;
}

template<typename T>
inline Property<T>::Property(T defaultVal, function<T()> get, function<void(T)> set)
{
	this->get = get;
	this->set = set;
	Set(defaultVal);
}

template<typename T>
inline Property<T>::Property(T defaultVal)
{
	get = [this]() { return value; };
	set = [this](T val) { value = val; };
	Set(defaultVal);
}

template<typename T>
inline T Property<T>::Get()
{
	return this->get();
}

template<typename T>
inline void Property<T>::Set(T val)
{
	this->set(val);
}
