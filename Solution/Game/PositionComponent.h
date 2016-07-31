#pragma once

#include <Entity/Include/BaseComponent.h>
#include <Vector.h>

struct PositionComponent : public Magma::BaseComponent
{
	CU::Vector2<float> myPosition;
};