#pragma once

#include <Entity/Include/BaseComponent.h>

#include <Vector.h>

struct MovementComponent : public Magma::BaseComponent
{
	CU::Vector2<float> myTargetPosition;
	CU::Vector2<int> myTargetIndex;
};