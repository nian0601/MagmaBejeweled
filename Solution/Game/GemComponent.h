#pragma once

#include <Entity/Include/BaseComponent.h>
#include <Vector.h>

enum class eGemType
{
	BLUE,
	GREEN,
	PURPLE,
	RED,
	YELLOW
};

struct GemComponent : public Magma::BaseComponent
{
	eGemType myType;
	CU::Vector2<int> myIndex;
};