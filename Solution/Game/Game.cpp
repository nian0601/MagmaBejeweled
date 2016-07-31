#include "stdafx.h"

#include <Engine.h>
#include "Game.h"
#include <PostMaster.h>
#include <RenderMessage.h>
#include <Rendering/RendererProxy.h>

Game::Game()
{
}


Game::~Game()
{
	PostMaster::GetInstance()->Destroy();
}

void Game::Init(Magma::Engine& aEngine)
{
	myRendererProxy = &aEngine.GetRendererProxy();
}

bool Game::Update(float aDelta)
{
	CU::InputWrapper* input = CU::InputWrapper::GetInstance();

	if (input->KeyIsPressed(DIK_ESCAPE))
	{
		return false;
	}

	return true;
}

void Game::OnResize(float aWidth, float aHeight)
{
	//throw std::logic_error("The method or operation is not implemented.");
}

void Game::ReceiveMessage(const RenderMessage& aMessage)
{
	myRendererProxy->RenderModel(aMessage.myModelID, aMessage.myEffectID, aMessage.myOrientation, aMessage.myScale);
}