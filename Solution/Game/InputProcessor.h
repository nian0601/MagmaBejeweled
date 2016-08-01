#pragma once

#include <Entity/Include/BaseProcessor.h>
#include <Entity/Include/CustomEntityTypes.h>

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

	Magma::Entity myFirstEntity;
};

