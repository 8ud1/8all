#include "GameUIManager.h"

#include<string>

#include "GameRules.h"
#include "Ball.h"

GameUIManager::GameUIManager(Game& game, GameRules* gameRules, Ball* whiteball)
	: gameRules(gameRules)
{
	pauseCanvas = std::make_unique<PauseCanvas>(
		[&]() {pauseCanvas->Hide(); },
		[&]() {game.RequestChangeScene(SceneType::MAIN_MENU); },
		[&]() {SDL_Log("Restart"); },
		false
	);


	ballSpinUi = std::make_unique<UIBallSpin>(
		SDL_FPoint{ Utilities::SCREEN_WIDTH * 0.5f, Utilities::SCREEN_HEIGHT - 45.0f },
		SDL_FPoint{ 75.0f, 75.0f }
	);

	shotController = std::make_unique<ShotController>(gameRules,whiteball, ballSpinUi.get());
}

void GameUIManager::Update(float deltaTime)
{
	pauseCanvas->Update(deltaTime);
	if (!shotController->IsCharging())
		ballSpinUi->Update(deltaTime);
}


void GameUIManager::Render(Renderer& renderer)
{

	if (pauseCanvas->IsActive())
		pauseCanvas->Render(renderer);
	else
	{
		ballSpinUi->Render(renderer);
		shotController->Render(renderer);
	}

	SDL_Color player01Color = { 255,255,255,255 };
	SDL_Color player02Color = { 255,255,255,255 };

	if (currentPlayer == 0)
	{
		player02Color.a = 50;
	}
	else
	{
		player01Color.a = 50;

	}

	renderer.DrawText("PLAYER 01", Resources::FONT_REGULAR, player01Color, 100, 50);
	renderer.DrawText("Turn : " + std::to_string(playerInfo[0].turns), Resources::FONT_REGULAR, player01Color, 100, 100);
	renderer.DrawText("Points : " + std::to_string(playerInfo[0].points), Resources::FONT_REGULAR, player01Color, 100, 150);
	renderer.DrawText("Fails : " + std::to_string(playerInfo[0].fails), Resources::FONT_REGULAR, player01Color, 100, 200);

	float player2X = Utilities::SCREEN_WIDTH - 100;
	renderer.DrawText("PLAYER 02", Resources::FONT_REGULAR, player02Color, player2X, 50);
	renderer.DrawText("Turn " + std::to_string(playerInfo[1].turns), Resources::FONT_REGULAR, player02Color, player2X, 100);
	renderer.DrawText("Points : " + std::to_string(playerInfo[1].points), Resources::FONT_REGULAR, player02Color, player2X, 150);
	renderer.DrawText("Fails : " + std::to_string(playerInfo[1].fails), Resources::FONT_REGULAR, player02Color, player2X, 200);
}

void GameUIManager::ShowGameOver(int winner)
{
	//ocultar toda la ui i mostrar canvas de resultados.
}

void GameUIManager::TooglePause()
{
	if (pauseCanvas->IsActive())
	{
		pauseCanvas->Hide();
	}
	else
	{
		pauseCanvas->Show();
		shotController->Disable();
	}
}

void GameUIManager::PrepareNextTurn(int nextPlayer, PlayerInfo& pi, PlayerInfo& pi2)
{
	currentPlayer = nextPlayer;
	ballSpinUi->Reset();

	playerInfo[0] = pi;
	playerInfo[1] = pi2;
 }
