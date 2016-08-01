#include "stdafx.h"
#include "InputProcessor.h"
#include "GemComponent.h"
#include "MovementComponent.h"
#include "PositionComponent.h"

#include <InputWrapper.h>
InputProcessor::InputProcessor(Magma::World& aWorld)
	: Magma::BaseProcessor(aWorld, Magma::CreateFilter<Magma::Requires<GemComponent, PositionComponent>>())
	, myFirstEntity(-1)
{
}


InputProcessor::~InputProcessor()
{
}

void InputProcessor::Update(float aDelta)
{
	if (CU::InputWrapper::GetInstance()->MouseDown(0))
	{
		Magma::Entity clickedEntity = GetClickedEntity();

		if (myFirstEntity == -1)
		{
			myFirstEntity = clickedEntity;
		}
		else if (myFirstEntity != clickedEntity)
		{
			AddComponent<MovementComponent>(myFirstEntity);
			AddComponent<MovementComponent>(clickedEntity);

			GetComponent<MovementComponent>(myFirstEntity).myTargetPosition = GetComponent<PositionComponent>(clickedEntity).myPosition;
			GetComponent<MovementComponent>(clickedEntity).myTargetPosition = GetComponent<PositionComponent>(myFirstEntity).myPosition;

			myFirstEntity = -1;
		}
	}
}

Magma::Entity InputProcessor::GetClickedEntity()
{
	const CU::GrowingArray<Magma::Entity>& entities = GetEntities();

	CU::Vector2<float> mousePosition = CU::InputWrapper::GetInstance()->GetMousePosition();

	for each (Magma::Entity entity in entities)
	{
		CU::Vector2<float> position = GetComponent<PositionComponent>(entity).myPosition;
		CU::Vector2<float> size = CU::Vector2<float>(36.f, 36.f);

		if (position.x + size.x < mousePosition.x) continue;
		if (position.x > mousePosition.x) continue;
		if (position.y + size.y < mousePosition.y) continue;
		if (position.y > mousePosition.y) continue;

		return entity;
	}

	return -1;
}
