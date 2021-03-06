#include "stdafx.h"

#include <Rendering/AssetContainer.h>
#include <Engine.h>
#include "Game.h"
#include <PostMaster.h>
#include <RenderMessage.h>
#include <Rendering/RendererProxy.h>

#include "InputProcessor.h"
#include "RenderProcessor.h"
#include "MovementProcessor.h"

#include "GemComponent.h"
#include "SpriteComponent.h"
#include "PositionComponent.h"

#include "TestEvent.h"

Game::Game()
{
}


Game::~Game()
{
	PostMaster::GetInstance()->UnSubscribe(this, 0);
	PostMaster::GetInstance()->Destroy();
}

void Game::Init(Magma::Engine& aEngine)
{
	PostMaster::GetInstance()->Subscribe(this, eMessageType::RENDER);
	myRendererProxy = &aEngine.GetRendererProxy();
	
	myWorld.AddProcessor<InputProcessor>();
	myWorld.AddProcessor<RenderProcessor>();
	myWorld.AddProcessor<MovementProcessor>();

	for (int y = 0; y < 8; ++y)
	{
		for (int x = 0; x < 8; ++x)
		{
			Magma::Entity entity = myWorld.CreateEntity();
			myWorld.AddComponent<SpriteComponent>(entity);
			myWorld.AddComponent<PositionComponent>(entity);
			myWorld.AddComponent<GemComponent>(entity);

			SpriteComponent& sprite = myWorld.GetComponent<SpriteComponent>(entity);
			GemComponent& gem = myWorld.GetComponent<GemComponent>(entity);
			gem.myIndex = CU::Vector2<int>(x, y);
			switch (rand() % 5)
			{
			case 0:
				sprite.myTexture = aEngine.GetAssetContainer().RequestTexture("Data/Resource/Texture/Blue.dds");
				gem.myType = eGemType::BLUE;
				break;
			case 1:
				sprite.myTexture = aEngine.GetAssetContainer().RequestTexture("Data/Resource/Texture/Green.dds");
				gem.myType = eGemType::GREEN;
				break;
			case 2: 
				sprite.myTexture = aEngine.GetAssetContainer().RequestTexture("Data/Resource/Texture/Purple.dds");
				gem.myType = eGemType::PURPLE;
				break;
			case 3:
				sprite.myTexture = aEngine.GetAssetContainer().RequestTexture("Data/Resource/Texture/Red.dds");
				gem.myType = eGemType::RED;
				break;
			case 4:
				sprite.myTexture = aEngine.GetAssetContainer().RequestTexture("Data/Resource/Texture/Yellow.dds");
				gem.myType = eGemType::YELLOW;
				break;
			default:
				sprite.myTexture = aEngine.GetAssetContainer().RequestTexture("Data/Resource/Texture/Blue.dds");
				gem.myType = eGemType::BLUE;
				break;
			}
			
			sprite.mySize = CU::Vector2<float>(36.f, 36.f);
			sprite.myScale = CU::Vector2<float>(1.f, 1.f);

			PositionComponent& position = myWorld.GetComponent<PositionComponent>(entity);
			position.myPosition = CU::Vector2<float>(x * 36.f, y * 36.f);
			position.myPosition += CU::Vector2<float>(250.f, 250.f);
		}
	}
	
}

bool Game::Update(float aDelta)
{
	CU::InputWrapper* input = CU::InputWrapper::GetInstance();

	if (input->KeyIsPressed(DIK_ESCAPE))
	{
		return false;
	}

	myWorld.Update(aDelta);

	myWorld.SendEvent(TestEvent());
	return true;
}

void Game::OnResize(float aWidth, float aHeight)
{
	//throw std::logic_error("The method or operation is not implemented.");
}

void Game::ReceiveMessage(const RenderMessage& aMessage)
{
	myRendererProxy->RenderSprite(aMessage.myTexture, CU::Matrix44<float>(), aMessage.mySizeAndHotSpot, aMessage.myPositionAndScale);
}