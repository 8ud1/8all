#pragma once

#include <vector>

class Game;
class Ball;
class PhysicsObject;


enum class BallGroup{NONE, SOLID , STRIPS};


struct PlayerInfo
{
	BallGroup ballsGroup = BallGroup::NONE;
	int turns = 1;
	int points = 0;
	int fails = 0;

};

class GameRules
{
	Ball* whiteBall;
	std::vector<Ball*>& balls;
	std::vector<Ball*> turnSunkBalls;

	PlayerInfo playerInfo[2];

	int sunkBalls[2]{ 0,0 };
	
	int currentPlayer = 0;
	int winnerPlayer = -1;

	bool foulCommitted = false;
	bool playerScoredThisTurn = false;
	bool gameOver = false;

	bool turnInProgress = false;

	void AssignBallsGroup(Ball* ball);
	int GetTargetPlayerForBall(int ballNum) const;

public:
	GameRules(Ball* whiteBall, std::vector<Ball*>& balls)
		: whiteBall(whiteBall), balls(balls) {	}

	bool IsTurnInProgress() const { return turnInProgress; };
	int GetCurrentPlayer() const { return currentPlayer; }
	bool IsGameOver() const { return gameOver; }
	int GetWinner() const { return winnerPlayer; }

	PlayerInfo& GetPlayerInfo(int player) { return playerInfo[player]; }

	void EvaluateTurn();
	void NextTurn();

	void OnHoleTrigger(PhysicsObject* obj);
	void OnPlayerShot();
	
	void EndGame(int winner);

	void ResetWhiteBall();
	bool CheckWinCondition();
	void CheckBlackBall();

	void SetTurnInProgress(bool value) { turnInProgress = value; };



	

};


