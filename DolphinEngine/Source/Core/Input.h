#pragma once

#include "App.h"

class Input
{
	static inline dvec2 lastScroll{ dvec2(0) };

public:

	Input() = delete;

	static void Init();
	static void Update();

	static inline dvec2 mousePosition{ dvec2(0) };
	static inline dvec2 lastMousePos{ dvec2(0) };
	static inline dvec2 mouseDelta{ dvec2(0) };
	static inline dvec2 scrollDelta{ dvec2(0) };
};