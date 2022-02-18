#pragma once
#include "Drawable.h"
#include "..\Component\Transform.h"

class Box : public Drawable
{
public:
	Box();
public:
	Transform trans;
};