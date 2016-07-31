#include "stdafx.h"
#include "InputProcessor.h"
#include "GemComponent.h"
#include "MovementComponent.h"
#include "PositionComponent.h"

#include <InputWrapper.h>
InputProcessor::InputProcessor(Magma::World& aWorld)
	: Magma::BaseProcessor(aWorld, Magma::CreateFilter<Magma::Requires<GemComponent, PositionComponent>>())
{
}


InputProcessor::~InputProcessor()
{
}

void InputProcessor::Update(float aDelta)
{
	if (CU::InputWrapper::GetInstance()->KeyDown(DIK_S))
	{
		const CU::GrowingArray<Magma::Entity>& entities = GetEntities();

		Magma::Entity first = -1;
		Magma::Entity second = -1;

		while (first == second)
		{
			first = rand() % entities.Size();
			second = rand() % entities.Size();
		}

		AddComponent<MovementComponent>(first);
		AddComponent<MovementComponent>(second);

		GetComponent<MovementComponent>(first).myTargetPosition = GetComponent<PositionComponent>(second).myPosition;
		GetComponent<MovementComponent>(second).myTargetPosition = GetComponent<PositionComponent>(first).myPosition;
	}
}
