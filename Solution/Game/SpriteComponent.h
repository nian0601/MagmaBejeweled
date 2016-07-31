#pragma once

#include <Entity/Include/BaseComponent.h>
#include <Vector.h>

namespace Magma
{
	class Texture;
}

struct SpriteComponent : public Magma::BaseComponent
{
	Magma::Texture* myTexture;
	CU::Vector2<float> mySize;
	CU::Vector2<float> myHotSpot;
	CU::Vector2<float> myScale;
};