#pragma once

#include <Entity/Include/BaseProcessor.h>
#include <Entity/Include/CustomEntityTypes.h>

class InputProcessor : public Magma::BaseProcessor
{
public:
	InputProcessor(Magma::World& aWorld);
	~InputProcessor();

	void Update(float aDelta) override;

private:
	Magma::Entity GetClickedEntity();
	Magma::Entity myFirstEntity;
};

