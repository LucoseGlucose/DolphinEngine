#pragma once

#include <vector>
#include <functional>

using namespace std;

template <typename T>
class Event
{
	vector<function<void(T)>> funcs;

public:

	void Invoke(T params);
	int Subscribe(const function<void(T)>& func);
	void Unsubscribe(int index);
};

template <typename T>
void Event<T>::Invoke(T params)
{
	for (size_t i = 0; i < funcs.size(); i++)
	{
		funcs[i](params);
	}
}

template <typename T>
int Event<T>::Subscribe(const function<void(T)>& func)
{
	funcs.push_back(func);
	return funcs.size() - 1;
}

template <typename T>
void Event<T>::Unsubscribe(int index)
{
	funcs.erase(funcs.begin() + index);
}
