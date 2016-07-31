#pragma once

#include <IGame.h>
#include <GrowingArray.h>

#include <Subscriber.h>

#include <Entity/Include/World.h>

namespace Magma
{
	class RendererProxy;
}

class Game : public Magma::IGame, public Subscriber
{
public:
	Game();
	~Game();

	void Init(Magma::Engine& aEngine) override;
	bool Update(float aDelta) override;
	void OnResize(float aWidth, float aHeight) override;

	void ReceiveMessage(const RenderMessage& aMessage);

private:
	Magma::RendererProxy* myRendererProxy;

	Magma::World myWorld;
};

