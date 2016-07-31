#pragma once
#include "Message.h"
#include <EngineTypes.h>
#include <Matrix.h>
#include <Vector.h>

namespace Magma
{
	class Texture;
}

struct RenderMessage : public Message
{
	RenderMessage();

	RenderMessage(Magma::Texture* aTexture, const CU::Vector4<float>& aSizeAndHotSpot
		, const CU::Vector4<float>& aPositionAndScale);

	Magma::Texture* myTexture;
	const CU::Vector4<float> mySizeAndHotSpot;
	const CU::Vector4<float> myPositionAndScale;
};

inline RenderMessage::RenderMessage()
	: Message(eMessageType::RENDER)
{
}

inline RenderMessage::RenderMessage(Magma::Texture* aTexture, const CU::Vector4<float>& aSizeAndHotSpot
	, const CU::Vector4<float>& aPositionAndScale)
	: Message(eMessageType::RENDER)
	, myTexture(aTexture)
	, mySizeAndHotSpot(aSizeAndHotSpot)
	, myPositionAndScale(aPositionAndScale)
{
}