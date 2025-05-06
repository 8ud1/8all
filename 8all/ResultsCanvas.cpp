#include "ResultsCanvas.h"
#include <iostream>

#include "Utilities.h"
#include "Resources.h"

#include "Game.h"
#include "UITextButton.h"
#include "Ranking.h"

void ResultsCanvas::SaveScore()
{
	uiElements.clear();

	std::unique_ptr<Ranking> ranking = std::make_unique<Ranking>(Resources::RANKING_FILE_PATH);

	ranking->Load();

	ranking->AddEntry(inputName, 1280);

	rankingEntries =  ranking->GetEntries();

	ranking->Save();

	ranking.reset();

	Instantiate<UITextButton>(
		SDL_FPoint{ Utilities::SCREEN_WIDTH * 0.4f - 100.0f, Utilities::SCREEN_HEIGHT * 0.7f - 25.0f },
		SDL_FPoint{ 200.0f,50.0f },
		[this]() {game.RequestChangeScene(SceneType::MAIN_MENU); },
		("Main Menu"),
		SDL_Color({ 170,170,170,255 }),
		SDL_Color({ 0,170,0,255 })
	);

	Instantiate<UITextButton>(
		SDL_FPoint{ Utilities::SCREEN_WIDTH * 0.6f - 100.0f, Utilities::SCREEN_HEIGHT * 0.7f - 25.0f },
		SDL_FPoint{ 200.0f,50.0f },
		[this]() { game.RequestRestartScene(SceneType::GAME); },
		("Retry"),
		SDL_Color({ 170,170,170,255 }),
		SDL_Color({ 0,170,0,255 })
	);
}

void ResultsCanvas::InitCanvas()
{
	Instantiate<UITextButton>(
		SDL_FPoint{ Utilities::SCREEN_WIDTH * 0.5f - 100.0f, Utilities::SCREEN_HEIGHT * 0.7f - 25.0f },
		SDL_FPoint{ 200.0f,50.0f },
		[this]() { SaveScore(); },
		("Save Score"),
		SDL_Color({ 170,170,170,255 }),
		SDL_Color({ 0,170,0,255 })
	);
}

ResultsCanvas::ResultsCanvas(Game& gameRef, bool startActive)
	: Canvas(startActive), game(gameRef)
{
	InitCanvas();
}

void ResultsCanvas::Update(float deltaTime)
{
	if (inputName.length() >= 3)
	{
		for (auto& uiElement : uiElements)
		{
			uiElement->Update(deltaTime);
		}
	}
}

void ResultsCanvas::Render(Renderer& renderer)
{

	//BG
	renderer.DrawRect(SDL_FRect{ 0.0f,0.0f, Utilities::SCREEN_WIDTH, Utilities::SCREEN_HEIGHT }, SDL_Color{ 0,0,0,150 });


	if (rankingEntries.empty())
	{
		//Tilte
		std::string title = "Player 0" + std::to_string(winner + 1) + " Won!";
		renderer.DrawText(title.c_str(), Resources::TITLE, SDL_Color{ 255,255,255,255 }, Utilities::SCREEN_WIDTH * 0.5f, Utilities::SCREEN_HEIGHT * 0.2f);
		renderer.DrawText("Enter your Name", Resources::FONT, SDL_Color{ 255,255,255,255 }, Utilities::SCREEN_WIDTH * 0.5f, Utilities::SCREEN_HEIGHT * 0.4f);
		renderer.DrawText(inputName, Resources::FONT, SDL_Color{ 255,255,255,255 }, Utilities::SCREEN_WIDTH * 0.5f, Utilities::SCREEN_HEIGHT * 0.45f);

		std::string name = inputName;
	}
	else
	{
		renderer.DrawText("Ranking", Resources::TITLE_BIG, SDL_Color{ 255,255,255,255 }, Utilities::SCREEN_WIDTH * 0.5f, Utilities::SCREEN_HEIGHT * 0.2f);


		int it = rankingEntries.size() < 5 ? rankingEntries.size() : 5;
		std::string text;
		for (int i = 0; i < it; i++)
		{
			text = std::to_string(i + 1) + " -> " + rankingEntries[i].playerName + "_____________________" + std::to_string(rankingEntries[i].score);
			renderer.DrawText(text, Resources::FONT, SDL_Color{ 255,255,255,255 }, Utilities::SCREEN_WIDTH * 0.5f, Utilities::SCREEN_HEIGHT * 0.4f + (i * 30));
		}
	}
	

	for (auto& uiElement : uiElements)
	{
		uiElement->Render(renderer);
	}
}

void ResultsCanvas::HandleInputs(const SDL_Event& event)
{
	switch (event.type)
	{
	case SDL_EVENT_KEY_DOWN:

		switch (event.key.scancode)
		{
		case SDL_SCANCODE_DELETE:
		case SDL_SCANCODE_BACKSPACE:
			if (!inputName.empty()) inputName.pop_back();
			break;
		}
		break;
	case SDL_EVENT_TEXT_INPUT:
		
		if (inputName.length() < 14)
		{
			if (event.text.text[0] == ' ')
			{
				inputName += "_";
			}
			else
			{
				inputName += event.text.text;
			}
		}
		break;
	}
}

void ResultsCanvas::ShowResults(int finalWiner, PlayerInfo playerInfo)
{
	winner = finalWiner;
	Canvas::Show();
	SDL_StartTextInput(game.GetWindow());

}

void ResultsCanvas::GoToMainMenu()
{
	game.RequestChangeScene(SceneType::MAIN_MENU);
}
