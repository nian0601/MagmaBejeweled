#pragma once

#include <Entity/Include/BaseProcessor.h>

namespace Magma
{
	class World;
}

class RenderProcessor : public Magma::BaseProcessor
{
public:
	RenderProcessor(Magma::World& aWorld);
	~RenderProcessor();

	void Update(float aDelta) override;
};

