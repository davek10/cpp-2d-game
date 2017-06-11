#pragma once
#include "Ball.h"
#include <iostream>
#include <fstream>

class BallGame
{
public:
	BallGame(sf::RenderWindow* window, int windowWidth, int windowHeight, sf::Font font);
	~BallGame();
	void initConstants();
	void initStart();
	void renderingMethod(float step, float sizeChange, float smallestRadius, std::vector<Ball> ballArray);
	void newCirclePos(sf::CircleShape shape);
	float stepCalcPos(float currentPosition, float goal, float step);
	bool randomBool(int numberForFalse);
	void resetBallArray(std::vector<Ball>* ballArray, float ballSpeed);
	sf::String buildGoalString(int hits, int goalNumber, int levelNumber);
	void setHighScore(int levelNumber, int hits);
	void setSizeGoal(float wantedSie, float limit);
private:
	sf::RenderWindow* window;
	int windowWidth;
	int windowHeight;
	sf::Text text;
	sf::Font font;
	sf::CircleShape shape;

	sf::CircleShape shape2;
	float xBallPos; // Used for shape2
	float yBallPos;

	int hits;
	int goalNumber;
	int levelNumber;
	int highScoreLevel;
	int highScoreHits;
	bool restartGame;

	bool readyToSpawn;
	float ballSpeed;
	float startSize;
	sf::Vector2f startPos;
	int hitsForMoreBalls;

	float limitSize;
	bool animateSizeChange;
	float sizeGoal; 
	bool animateForcedMovement;
	float changeRate;

	float step;
	float sizeChange;
	float smallestRadius;
	float enemyBallStart;
	float startGoal;
};

