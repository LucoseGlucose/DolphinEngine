#pragma once

#include "Property.h"
#include "Event.h"

template<typename T>
struct ObservableProperty : public Property<T>
{
	ObservableProperty();
	ObservableProperty(function<T()> get, function<void(T)> set);
	ObservableProperty(T defaultVal, function<T()> get, function<void(T)> set);
	ObservableProperty(T defaultVal);

	virtual void Set(T val) override;

	Event<T> onChanged = Event<T>();
};

template<typename T>
inline void ObservableProperty<T>::Set(T val)
{
	this->set(val);
	onChanged.Invoke(val);
}

template<typename T>
inline ObservableProperty<T>::ObservableProperty() : Property<T>() {  }

template<typename T>
inline ObservableProperty<T>::ObservableProperty(function<T()> get, function<void(T)> set) : Property<T>(get, set) {  }

template<typename T>
inline ObservableProperty<T>::ObservableProperty(T defaultVal, function<T()> get, function<void(T)> set) : Property<T>(defaultVal, get, set) {  }

template<typename T>
inline ObservableProperty<T>::ObservableProperty(T defaultVal) : Property<T>(defaultVal) {  }