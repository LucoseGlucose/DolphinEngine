#pragma once

#include<functional>

using namespace std;

template<typename T>
struct ReadOnlyProperty
{
private:
	T value;
	function<T()> get;

public:

	ReadOnlyProperty();
	ReadOnlyProperty(function<T()> get);

	operator T();

	T Get();
};

template<typename T>
inline ReadOnlyProperty<T>::ReadOnlyProperty()
{
	get = [this]() { return value; };
}

template<typename T>
inline ReadOnlyProperty<T>::ReadOnlyProperty(function<T()> get)
{
	this->get = get;
}

template<typename T>
inline ReadOnlyProperty<T>::operator T()
{
	return Get();
}

template<typename T>
inline T ReadOnlyProperty<T>::Get()
{
	return this->get();
}
