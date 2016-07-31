#include "stdafx.h"
#include "MovementProcessor.h"

#include "MovementComponent.h"
#include "PositionComponent.h"

MovementProcessor::MovementProcessor(Magma::World& aWorld)
	: Magma::BaseProcessor(aWorld, Magma::CreateFilter<Magma::Requires<MovementComponent, PositionComponent>>())
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

		position += direction * 25.f * aDelta;

		if (CU::Length2(position - target) < 1.f)
		{
			position = target;
			RemoveComponent<MovementComponent>(entity);
		}

		GetComponent<PositionComponent>(entity).myPosition = position;
	}
}
