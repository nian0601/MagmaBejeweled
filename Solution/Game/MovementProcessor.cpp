#include "stdafx.h"
#include "MovementProcessor.h"

#include "MovementComponent.h"
#include "PositionComponent.h"
#include "GemComponent.h"

MovementProcessor::MovementProcessor(Magma::World& aWorld)
	: Magma::BaseProcessor(aWorld, Magma::CreateFilter<Magma::Requires<MovementComponent, PositionComponent, GemComponent>>())
{
}


MovementProcessor::~MovementProcessor()
{
}

void MovementProcessor::Update(float aDelta)
{
	const CU::GrowingArray<Magma::Entity>& entities = GetEntities();

	for each (Magma::Entity entity in entities)
	{
		CU::Vector2<float> position = GetComponent<PositionComponent>(entity).myPosition;
		CU::Vector2<float> target = GetComponent<MovementComponent>(entity).myTargetPosition;

		CU::Vector2<float> direction = CU::GetNormalized(target - position);

		position += direction * 100.f * aDelta;

		CU::Vector2<float> newDir = target - position;
		if (CU::Length2(newDir) < 1.f || CU::Dot(CU::GetNormalized(newDir), direction) < 0)
		{
			position = target;

			GetComponent<GemComponent>(entity).myIndex = GetComponent<MovementComponent>(entity).myTargetIndex;

			RemoveComponent<MovementComponent>(entity);
		}

		GetComponent<PositionComponent>(entity).myPosition = position;
	}
}
