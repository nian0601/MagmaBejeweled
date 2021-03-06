#pragma once

#include <Entity/Include/BaseProcessor.h>
#include <Entity/Include/CustomEntityTypes.h>

#include "GemComponent.h"

class InputProcessor : public Magma::BaseProcessor
{
public:
	InputProcessor(Magma::World& aWorld);
	~InputProcessor();

	void Update(float aDelta) override;

	void OnEvent(const Magma::Event& aEvent) override;

private:
	Magma::Entity GetClickedEntity();
	bool IsAdjacent(Magma::Entity aFirstEntity, Magma::Entity aSecondEntity);
	bool LegalMove(Magma::Entity aFirstEntity, Magma::Entity aSecondEntity);
	Magma::Entity GetEntity(const CU::Vector2<int>& aIndex);

	int GetGemCount(const GemComponent& aGem, eGemType aGemType, const CU::Vector2<int>& aDirection);

	Magma::Entity myFirstEntity;
};

