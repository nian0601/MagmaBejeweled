#include "stdafx.h"
#include "InputProcessor.h"
#include <InputWrapper.h>
#include "GemComponent.h"
#include "MovementComponent.h"
#include "PositionComponent.h"

#include "TestEvent.h"

InputProcessor::InputProcessor(Magma::World& aWorld)
	: Magma::BaseProcessor(aWorld, Magma::CreateFilter<Magma::Requires<GemComponent, PositionComponent>>())
	, myFirstEntity(static_cast<unsigned int>(-1))
{
}


InputProcessor::~InputProcessor()
{
}

void InputProcessor::Update(float)
{
	if (CU::InputWrapper::GetInstance()->MouseDown(0))
	{
		Magma::Entity clickedEntity = GetClickedEntity();
		if (clickedEntity == -1)
		{
			return;
		}

		if (myFirstEntity == -1)
		{
			myFirstEntity = clickedEntity;
		}
		else if (myFirstEntity != clickedEntity)
		{
			if (IsAdjacent(myFirstEntity, clickedEntity))
			{
				AddComponent<MovementComponent>(myFirstEntity);
				AddComponent<MovementComponent>(clickedEntity);

				MovementComponent& firstMovement = GetComponent<MovementComponent>(myFirstEntity);
				MovementComponent& secondMovement = GetComponent<MovementComponent>(clickedEntity);

				firstMovement.myTargetPosition = GetComponent<PositionComponent>(clickedEntity).myPosition;
				secondMovement.myTargetPosition = GetComponent<PositionComponent>(myFirstEntity).myPosition;

				firstMovement.myTargetIndex = GetComponent<GemComponent>(clickedEntity).myIndex;
				secondMovement.myTargetIndex = GetComponent<GemComponent>(myFirstEntity).myIndex;
			}

			myFirstEntity = static_cast<unsigned int>(-1);
		}
	}
}

void InputProcessor::OnEvent(const Magma::Event& aEvent)
{
	const TestEvent* event = static_cast<const TestEvent*>(&aEvent);
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

	return static_cast<Magma::Entity>(-1);
}

bool InputProcessor::IsAdjacent(Magma::Entity aFirstEntity, Magma::Entity aSecondEntity)
{
	CU::Vector2<int> firstIndex = GetComponent<GemComponent>(aFirstEntity).myIndex;
	CU::Vector2<int> secondIndex = GetComponent<GemComponent>(aSecondEntity).myIndex;

	CU::Vector2<int> diff = firstIndex - secondIndex;

	if ((abs(diff.x) == 1 && abs(diff.y) == 0)
		|| abs(diff.x) == 0 && abs(diff.y) == 1)
	{
		return true;
	}

	return false;
}
