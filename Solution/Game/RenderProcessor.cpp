#include "stdafx.h"
#include "RenderProcessor.h"

#include "PositionComponent.h"
#include "SpriteComponent.h"

#include <Entity/Include/ComponentFilter.h>

#include <PostMaster.h>
#include <RenderMessage.h>

RenderProcessor::RenderProcessor(Magma::World& aWorld)
	: Magma::BaseProcessor(aWorld, Magma::CreateFilter<Magma::Requires<PositionComponent, SpriteComponent>>())
{
}


RenderProcessor::~RenderProcessor()
{
}

void RenderProcessor::Update(float aDelta)
{
	const CU::GrowingArray<Magma::Entity>& entities = GetEntities();

	for each (Magma::Entity entity in entities)
	{
		const PositionComponent& posComponent = GetComponent<PositionComponent>(entity);
		const SpriteComponent& spriteComponent = GetComponent<SpriteComponent>(entity);

		CU::Vector4<float> posAndScale;
		posAndScale.x = posComponent.myPosition.x;
		posAndScale.y = posComponent.myPosition.y;
		posAndScale.z = spriteComponent.myScale.x;
		posAndScale.w = spriteComponent.myScale.y;

		CU::Vector4<float> sizeAndHotSpot;
		sizeAndHotSpot.x = spriteComponent.mySize.x;
		sizeAndHotSpot.y = spriteComponent.mySize.y;
		sizeAndHotSpot.z = spriteComponent.myHotSpot.x;
		sizeAndHotSpot.w = spriteComponent.myHotSpot.y;

		Magma::Texture* texture = spriteComponent.myTexture;

		PostMaster::GetInstance()->SendMessage(RenderMessage(texture, sizeAndHotSpot, posAndScale));
	}
}
