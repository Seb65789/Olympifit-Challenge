#ifndef OLYMPICPLAYER_H
#define OLYMPICPLAYER_H

#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;

//le personnage principal du jeu
//est construit en utilisant cette classe
class OlympicPlayer {
private:
	Texture playerTex;
	int earnedPoints;
	int fitnessLevel;
	float speed;
	float runningSpeed;

public:
	Sprite playerSprite;

	OlympicPlayer() {
		playerTex.loadFromFile("img/opp5.png");
		playerSprite.setTexture(playerTex);
		playerSprite.setPosition(600, 500);
		playerSprite.setScale(0.5, 0.5);
		speed = 10;
		runningSpeed = 6;
		fitnessLevel = 30;
		earnedPoints = 0;
	}

	void move(std::string s) {
		float delta_x = 0, delta_y = 0;
		if (s == "l")
			delta_x -= 1;
		else if (s == "r")
			delta_x += 1;
		else if (s == "u")
			delta_y = -1;
		else if (s == "d")
			delta_y += 1;

		delta_x *= speed;
		delta_y *= speed;

		if (playerSprite.getPosition().y < 0)
		{
			playerSprite.setPosition(playerSprite.getPosition().x, 720);
		}
		else if (playerSprite.getPosition().x < 0)
		{
			playerSprite.setPosition(780, playerSprite.getPosition().y);
		}
		else if (playerSprite.getPosition().y > 720)
		{
			playerSprite.setPosition(playerSprite.getPosition().x, 0);
		}
		else if (playerSprite.getPosition().x > 1280)
		{
			playerSprite.setPosition(0, playerSprite.getPosition().y);
		}

		playerSprite.move(delta_x, delta_y);

	}

	void run () {
		float delta_x = 0, delta_y = 0;
		delta_x += 1;
		delta_x *= runningSpeed;
		playerSprite.move(delta_x, delta_y);
	}

	Sprite getPlayerSprite() {
		return playerSprite;
	}

	int getEarnedPoints() {
		return earnedPoints;
	}

	void setEarnedPoints(int points) {
		earnedPoints = points;
	}

	int getFitnessLevel() {
		return fitnessLevel;
	}

	void setFitnessLevel(int fitness) {
		fitnessLevel = fitness;
	}

	void setRunningSpeed(int s) {
		runningSpeed = s;
	}
};

#endif
