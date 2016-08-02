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
			if (IsAdjacent(myFirstEntity, clickedEntity) && LegalMove(myFirstEntity, clickedEntity))
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

bool InputProcessor::LegalMove(Magma::Entity aFirstEntity, Magma::Entity aSecondEntity)
{
	GemComponent& firstGem = GetComponent<GemComponent>(aFirstEntity);
	GemComponent& secondGem = GetComponent<GemComponent>(aSecondEntity);
	CU::Vector2<int> swapDirection = firstGem.myIndex - secondGem.myIndex;

	eGemType temp = firstGem.myType;
	firstGem.myType = secondGem.myType;
	secondGem.myType = temp;

	int horizontalOne = GetGemCount(firstGem, firstGem.myType, { -1, 0 }) + GetGemCount(firstGem, firstGem.myType, { 1, 0 }) + 1;
	int horizontalTwo = GetGemCount(secondGem, secondGem.myType, { -1, 0 }) + GetGemCount(secondGem, secondGem.myType, { 1, 0 }) + 1;

	int verticalOne = GetGemCount(firstGem, firstGem.myType, { 0, -1 }) + GetGemCount(firstGem, firstGem.myType, { 0, 1 }) + 1;
	int verticalTwo = GetGemCount(secondGem, secondGem.myType, { 0, -1 }) + GetGemCount(secondGem, secondGem.myType, { 0, 1 }) + 1;

	temp = firstGem.myType;
	firstGem.myType = secondGem.myType;
	secondGem.myType = temp;

	return (verticalOne >= 3 || verticalTwo >= 3) || (horizontalOne >= 3 || horizontalTwo >= 3);
}

Magma::Entity InputProcessor::GetEntity(const CU::Vector2<int>& aIndex)
{
	const CU::GrowingArray<Magma::Entity>& entities = GetEntities();

	for each (Magma::Entity entity in entities)
	{
		GemComponent& gem = GetComponent<GemComponent>(entity);
		if (gem.myIndex == aIndex)
		{
			return entity;
		}
	}

	return static_cast<Magma::Entity>(-1);
}

int InputProcessor::GetGemCount(const GemComponent& aGem, eGemType aGemType, const CU::Vector2<int>& aDirection)
{
	CU::Vector2<int> newIndex = aGem.myIndex + aDirection;

	Magma::Entity entity = GetEntity(newIndex);
	if (entity == -1)
	{
		return 0;
	}

	const GemComponent& newGem = GetComponent<GemComponent>(entity);
	if (newGem.myType != aGemType)
	{
		return 0;
	}

	return 1 + GetGemCount(newGem, aGemType, aDirection);
}