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
	void Subscribe(const function<void(T)>& func);
	void Unsubscribe(const function<void(T)>& func);
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
void Event<T>::Subscribe(const function<void(T)>& func)
{
	funcs.push_back(func);
}

template <typename T>
void Event<T>::Unsubscribe(const function<void(T)>& func)
{
	funcs.erase(remove(funcs.begin(), funcs.end(), func));
}
