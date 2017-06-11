#include "BallGame.h"

/* 
BallGame . ReadMe

Initializes the balls with radius position and color
shape = playerball
Fix cooler color system
shape2 = runs around and hits are recorded, has goals where it wants to go
Catcher balls = smaller and bigger = goes from left to right, smaller balls -> increase size of player. Bigger ball = KILL

TODO
Fix bug: Stackoverflow bug on exit
spara highscore på file (kanske inte funkade pga buggen över) (kod finns men read funka inte och output gav stackoverflow error)



Moving space background
Color shifting player ball
	Roliga texture på bollar

Power ups? Faster etc, rewards at high hit rates. 
	Finish levels etc, buy upgrades blabla

Läs om anti alizing och vertical sync
	Testa skillnad om man har window.setVerticalSyncEnabled(true); eller window.setFramerateLimit(60); (inte båda)

*/

// Ball parameters: int windowWidth, int windowHeight, int playerRadius, int rangeOutsideScreen, sf::Color color, bool isBigger, bool leftToRight
BallGame::BallGame(sf::RenderWindow * window, int windowWidth, int windowHeight, sf::Font font) 
{
	this->window = window;
	this->windowWidth = windowWidth;
	this->windowHeight = windowHeight;
	this->font = font;
	
	initConstants();
	initStart();

}

void BallGame::renderingMethod(float step, float sizeChange, float smallestRadius, std::vector<Ball> ballArray) {
	while (window->isOpen()) { // Main loop for rendering

		sf::Event event;
		while (window->pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window->close();
		} 

		// Keypresses
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			sf::Vector2f pos = shape.getPosition();
			shape.setFillColor(sf::Color::Green);
			float newX = pos.x;
			if (pos.x - step >= 0) {
				newX = newX - step;
			}
			shape.setPosition(newX, pos.y);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			sf::Vector2f pos = shape.getPosition();
			shape.setFillColor(sf::Color::Blue);
			float newX = pos.x;
			if (pos.x + step <= ((float)windowWidth - shape.getRadius() * 2)) {
				newX = newX + step;
			}
			shape.setPosition(newX, pos.y);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			sf::Vector2f pos = shape.getPosition();
			shape.setFillColor(sf::Color::Magenta);
			float newY = pos.y;
			if (pos.y - step >= 0) {
				newY = newY - step;
			}
			shape.setPosition(pos.x, newY);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			sf::Vector2f pos = shape.getPosition();
			shape.setFillColor(sf::Color::Cyan);
			float newY = pos.y;
			if (pos.y + step <= ((float)windowHeight - shape.getRadius() * 2)) {
				newY = newY + step;
			}
			shape.setPosition(pos.x, newY);
		}
		
		// Movement for the tiny ball
		shape2.setPosition(stepCalcPos(shape2.getPosition().x, xBallPos, step), stepCalcPos(shape2.getPosition().y, yBallPos, step));
		if (shape2.getPosition().x == xBallPos && shape2.getPosition().y == yBallPos) {
			newCirclePos(shape2);
		}

		// Collision between the 2 balls, shape and shape2 (calculating hits)
		if (pow((shape.getPosition().x + shape.getRadius()) - (shape2.getPosition().x + shape2.getRadius()), 2) +
			pow((shape.getPosition().y + shape.getRadius()) - (shape2.getPosition().y + shape2.getRadius()), 2) <= pow(shape.getRadius() + shape2.getRadius(), 2)) {
			hits++;
			readyToSpawn = true;
			text.setString(buildGoalString(hits, goalNumber, levelNumber));
			sf::Vector2f newPos = sf::Vector2f(rand() % (int)(windowWidth - ceil(shape.getRadius() * 2)), rand() % (int)(windowWidth - ceil(shape.getRadius() * 2)));
			newCirclePos(shape2);
			shape2.setPosition(newPos);
		}
		
		
		// More balls at hits
		if (readyToSpawn && hits % hitsForMoreBalls == 0 && hits != 0) {
			readyToSpawn = false;
			if (hits < goalNumber) {
				ballArray.push_back(Ball(windowWidth, windowHeight, shape.getRadius(), rand() % 300,
					randomBool(2),
					randomBool(2),
					ballSpeed));
			}
			else { // RESET NEW LEVEL
				goalNumber += 10;
				ballSpeed *= 1.1;
				hits = 0;
				levelNumber++;
				setSizeGoal(startSize, limitSize);
				animateForcedMovement = true;
				if (hitsForMoreBalls-2 < 1) {
					hitsForMoreBalls = 1;
				}
				else {
					hitsForMoreBalls -= 2;
				}
				
				text.setString(buildGoalString(hits, goalNumber, levelNumber));
				resetBallArray(&ballArray, ballSpeed);
			}		
		}

		if (animateSizeChange) {
			if (shape.getRadius() != sizeGoal) {
				float nmb = stepCalcPos(shape.getRadius(), sizeGoal, changeRate);
				//std::cout << shape.getRadius() <<" "<< sizeGoal << " " << changeRate << " " << nmb << std::endl;
				shape.setRadius(nmb);
				if (nmb < startSize) {
					// Lose Game
					animateForcedMovement = true;
					setHighScore(levelNumber, hits);
					restartGame = true;
				}
			}
			else { // Rätt size
				animateSizeChange = false;
			}
		}

		if (animateForcedMovement) {
			if (shape.getPosition() != startPos) {
				sf::Vector2f newPos = sf::Vector2f(stepCalcPos(shape.getPosition().x, startPos.x, step * 2), stepCalcPos(shape.getPosition().y, startPos.y, step * 2));
				shape.setPosition(newPos);
				for (Ball & b : ballArray) { 
					b.moveOut(shape.getRadius());
				}
			}
			else { // Rätt pos
				animateForcedMovement = false;
			}
		}
		else {
			// Movement for dynamic balls		
			for (Ball & b : ballArray) { // Ska det vara &? referens right
				b.move(shape.getRadius());
			}

			// collision between player and balls to increase and decrease player ball size

			for (Ball & b : ballArray) {
				if (pow((shape.getPosition().x + shape.getRadius()) - (b.getX() + b.getRadius()), 2) +
					pow((shape.getPosition().y + shape.getRadius()) - (b.getY() + b.getRadius()), 2) <= pow(shape.getRadius() + b.getRadius(), 2)) {
					if (shape.getRadius() >= b.getRadius()) { // Eat it
															  //std::cout << (sizeGoal + b.getRadius() / sizeChange) << std::endl;
						setSizeGoal(sizeGoal + b.getRadius() / sizeChange, limitSize);
						b.resetMove(shape.getRadius());
					}
					else if (shape.getRadius() < b.getRadius()) { // Shrink
						if (b.isDestroyer()) { // Destroyers (red) instantly makes you lose
							animateForcedMovement = true;
							setHighScore(levelNumber, hits);
							restartGame = true;
						}
						else { // Bigger (Magenta) only shrinks you BUT dont go below default size
							setSizeGoal(sizeGoal - b.getRadius() / sizeChange, limitSize);
							b.resetMove(shape.getRadius());
						}


					}
				}
			}
		}
		
		if (restartGame) {
			break;
		}

		window->clear();
		window->draw(shape);
		window->draw(shape2);
		for (Ball & b : ballArray) {
			window->draw(b.getBall());
		}
		window->draw(text);
		window->display();
	}
	initStart();
}


BallGame::~BallGame()
{
	// Ta bort ballArray, sparar dock nu dynamisk eftersom vector så behöver nog inte hantera
}

void BallGame::initConstants() {
	
	step = 0.05 * 2.f;
	sizeChange = 10;
	smallestRadius = 10.f;
	enemyBallStart = 200.f;
	startGoal = 30;
	startSize = 25.f;
	startPos = sf::Vector2f(windowWidth / 2 - startSize, windowHeight / 2 - startSize);
	ballSpeed = step / 3;
	changeRate = 0.005;
	sizeGoal = startSize;
	limitSize = windowHeight / 3;

	shape.setRadius(startSize);
	shape.setPosition(startPos);
	shape.setFillColor(sf::Color::White);
	shape2.setRadius(smallestRadius);
	shape2.setPosition(enemyBallStart, enemyBallStart);
	shape2.setFillColor(sf::Color::Blue);
}

void BallGame::initStart()
{
	hits = 0;
	hitsForMoreBalls = 10;
	goalNumber = startGoal;
	levelNumber = 1;
	restartGame = false;
	animateSizeChange = true;
	setSizeGoal(startSize, limitSize);
	animateForcedMovement = true;

	
	newCirclePos(shape2); 
	// Goal for shape
	
	/*	
	std::ifstream fileReader("highScore.txt");
	int a, b;
	if (fileReader.peek() == std::ifstream::traits_type::eof()) { // Kollar om tom fil
	highScoreLevel = 1;
	highScoreHits = 0;
	}
	else {
	while (fileReader >> a >> b) {
	highScoreLevel = a;
	highScoreHits = b;
	}
	}
	fileReader.close(); // behövs, om rätt skrivet
	*/
	if (highScoreLevel == 0 && highScoreHits == 0) {
		highScoreLevel = 1;
		highScoreHits = 0;
	}
	readyToSpawn = true;

	text.setString(buildGoalString(hits, goalNumber, levelNumber));
	text.setFillColor(sf::Color::Green);
	text.setFont(font);
	text.setPosition(10, 0);

	std::vector<Ball> ballArray;
	resetBallArray(&ballArray, ballSpeed);

	renderingMethod(step, sizeChange, smallestRadius, ballArray);
}

void BallGame::setSizeGoal(float wantedSize, float limit) {
	if (wantedSize > limit) {
		wantedSize = limit;
	}
	sizeGoal = wantedSize;
	animateSizeChange = true;
}

// Ball param: int windowWidth, int windowHeight, int playerRadius, int rangeOutsideScreen, bool isBigger, bool lefty, float ballSpeed
void BallGame::resetBallArray(std::vector<Ball>* ballArray, float ballSpeed) {
	ballArray->clear(); // tror det måste kollas om den här verkligen tar bort ordentligt
	ballArray->push_back(Ball(windowWidth, windowHeight, shape.getRadius(), rand() % 300, false, true, ballSpeed));
	ballArray->push_back(Ball(windowWidth, windowHeight, shape.getRadius(), rand() % 300, false, true, ballSpeed));
}

sf::String BallGame::buildGoalString(int hits, int goalNumber, int levelNumber)
{
	return (sf::String("Hits: ") + std::to_string(hits) + sf::String(". Goal: ") + std::to_string(goalNumber) + sf::String(". Level: ") + std::to_string(levelNumber)
		+ sf::String(". \tHighScore(Level/Hits): ") + std::to_string(highScoreLevel) + sf::String("/") + std::to_string(highScoreHits));
}


void BallGame::setHighScore(int currentLevelNumber, int currentHits)
{
	if (currentLevelNumber > highScoreLevel || (currentLevelNumber == highScoreLevel && currentHits > highScoreHits)) { // New Record was set
		/*std::ofstream fileWriter;
		fileWriter.open("highScores.txt");
		fileWriter << currentLevelNumber << " " << currentHits << std::endl;
		fileWriter.close();*/
		
		highScoreLevel = currentLevelNumber;
		highScoreHits = currentHits;
	}
}

bool BallGame::randomBool(int numberForFalse) { // 2 = 50% , 3 = 33% ...
	int number = rand() % numberForFalse;
	if (number == numberForFalse-1) {
		return true;
	}
	return false;
}

// Calculates ball coordinates for the small ball (not really modular since xBallPos is only used by shape2)
void BallGame::newCirclePos(sf::CircleShape shape) {
	xBallPos = rand() % (int)(windowWidth - ceil(shape.getRadius() * 2));
	yBallPos = rand() % (int)(windowHeight - ceil(shape.getRadius() * 2));
}

// Calculates the next coordinate when you are in @currentPosition and you are aiming to go to @goal with @step
float BallGame::stepCalcPos(float currentPosition, float goal, float step) {
	step = step * 2;
	if (currentPosition < goal) {
		if ((currentPosition + step) > goal) {
			return goal;
		}
		else {
			return (currentPosition + step);
		}
	}
	else if (currentPosition > goal) {
		if ((currentPosition - step) < goal) {
			return goal;
		}
		else {
			return (currentPosition - step);
		}
	}
	else if (currentPosition == goal) {
		return currentPosition;
	}
}