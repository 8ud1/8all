#include "GameRules.h"
#include "Ball.h"

#include "Utilities.h"
#include "GameUIManager.h"


void GameRules::AssignBallsGroup(Ball* ball)
{
	int ballNum = ball->GetId();

	if (ballNum <= 6)
	{
		playerInfo[currentPlayer].ballsGroup = BallGroup::SOLID;
		playerInfo[1 - currentPlayer].ballsGroup = BallGroup::STRIPS;
	}
	else if (ballNum >= 8 && ballNum <= 14)
	{
		playerInfo[currentPlayer].ballsGroup = BallGroup::STRIPS;
		playerInfo[1 - currentPlayer].ballsGroup = BallGroup::SOLID;
	}
}

int GameRules::GetTargetPlayerForBall(int ballNum) const
{
	bool isSolid = (ballNum <= 6);
	bool isStripe = (ballNum >= 8 && ballNum <= 14);

	if (playerInfo[0].ballsGroup == BallGroup::NONE && playerInfo[1].ballsGroup == BallGroup::NONE) {
		if (!turnSunkBalls.empty()) {
			int firstBallNum = turnSunkBalls.front()->GetId();
			bool firstIsSolid = (firstBallNum <= 6);
			bool firstIsStripe = (firstBallNum >= 8 && firstBallNum <= 14);

			if (firstIsSolid) return currentPlayer;
			if (firstIsStripe) return currentPlayer;
		}

		return currentPlayer;
	}

	if (isSolid && playerInfo[0].ballsGroup == BallGroup::SOLID) return 0;
	else if (isSolid && playerInfo[1].ballsGroup == BallGroup::SOLID) return 1;
	else if (isStripe && playerInfo[0].ballsGroup == BallGroup::STRIPS) return 0;
	else
		return 1;
}

bool GameRules::HasBallsRemaining(int player)
{

	BallGroup checketGroup = playerInfo[player].ballsGroup;

	std::vector<int> groupIndex;

	switch (checketGroup)
	{
	case BallGroup::NONE:
		return true;
		break;
	case BallGroup::SOLID:
		groupIndex = { 0,1,2,3,4,5,6 };
		break;
	case BallGroup::STRIPS:
		groupIndex = { 8,9,10,11,12,13,14 };
		break;
	}

	for (auto& ball : balls)
	{
		if (std::find(groupIndex.begin(), groupIndex.end(), ball->GetId()) != groupIndex.end()) 
		{
			if (!ball->RigidBody()->GetIsStatic()) return true;
		}
	}

	return false;
}

void GameRules::EvaluateTurn()
{
	if (gameOver) return;

	playerScoredThisTurn = false;

	for (auto* ball : turnSunkBalls)
	{
		int ballNum = ball-> GetId();

		if (playerInfo[currentPlayer].ballsGroup == BallGroup::NONE)
		{
			AssignBallsGroup(ball);
		}

		if (playerInfo[currentPlayer].ballsGroup == BallGroup::SOLID && ballNum <= 6) {
			
			++playerInfo[currentPlayer].points;
			playerScoredThisTurn = true;
		}
		else  if (playerInfo[currentPlayer].ballsGroup == BallGroup::STRIPS && ballNum >= 8 && ballNum <= 14)
		{
			++playerInfo[currentPlayer].points;
			playerScoredThisTurn = true;
		}
		else 
		{
			++ playerInfo[currentPlayer].fails;
			foulCommitted = true;
		}
	}

	if (foulCommitted || !playerScoredThisTurn)
	{
		currentPlayer = 1 - currentPlayer;
	}
	else
	{
		currentPlayer = currentPlayer;
	}
}

void GameRules::NextTurn()
{
	turnInProgress = false;
	foulCommitted = false;
	turnSunkBalls.clear();
}


void GameRules::ResetWhiteBall()
{
	whiteBall->transform->position = SDL_FPoint{ 350.0f,Utilities::SCREEN_HEIGHT * 0.5f };
	whiteBall->RigidBody()->ResetStates();
}


void GameRules::OnHoleTrigger(PhysicsObject* obj)
{
	Ball* ball = dynamic_cast<Ball*>(obj);
	if (!ball) return;
	
	int ballNum = ball->GetId();

	if (obj == whiteBall)
	{
		foulCommitted = true;
		ResetWhiteBall();
	}
	else if(ballNum == 7)
	{
		CheckBlackBall();
	}
	else
	{
		turnSunkBalls.push_back(ball);
		ball->RigidBody()->SetStatic(true);


		bool isSolid = (ballNum >= 1 && ballNum <= 6);
		bool isStripe = (ballNum >= 8 && ballNum <= 14);

		int targetPlayer = GetTargetPlayerForBall(ballNum); 
				
		if (isSolid) ++sunkBalls[0];
		else if (isStripe) ++sunkBalls[1];

		float ballX = (targetPlayer == 0) ? 100.0f : Utilities::SCREEN_WIDTH - 100.0f;
		float ballY = 300.0f + (isSolid ? sunkBalls[0] : sunkBalls[1]) * 25.0f;

		ball->transform->position = { ballX, ballY };
	}
}

void GameRules::OnPlayerShot()
{
	turnInProgress = true;
	++playerInfo[currentPlayer].turns;
}


void GameRules::CheckBlackBall()
{
	turnInProgress = false;
	gameOver = true;

	if (HasBallsRemaining(currentPlayer))
	{
		winnerPlayer = 1 - currentPlayer;
		uiManager->ShowGameOver(winnerPlayer,true);
	}
	else
	{
		winnerPlayer = currentPlayer;
		uiManager->ShowGameOver(winnerPlayer, false);
	}
	
}

