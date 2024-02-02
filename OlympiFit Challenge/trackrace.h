#ifndef TRACKRACE_H
#define TRACKRACE_H

#include <SFML/Graphics.hpp>
#include "olympicplayer.h"
using namespace sf;

//the antagonist of the game 
//runners that oppose you in the olympics
//their functionality is done using this class and its functions
class Opponent {
private:
	Texture opponentTex;
	Sprite opponentSprite;
	float speed;

public:
	Opponent(string imagePath, double x, double y, double s) {
		opponentTex.loadFromFile(imagePath);
		opponentSprite.setTexture(opponentTex);
		opponentSprite.setPosition(x, y);
		opponentSprite.setScale(0.5, 0.5);
		speed = s;
	}

	void move()
	{
		float delta_x = 0, delta_y = 0;
		delta_x += 1;
		delta_x *= speed;
		opponentSprite.move(delta_x, delta_y);
	}

	Sprite getOpponentSprite() {
		return opponentSprite;
	}

};

//the main event which decides the player's place
//in the game is implemented using this class
class TrackRace {
private:
	Texture trackTex;
	Sprite trackBackground;
	Opponent* opp1;
	Opponent* opp2;
	Opponent* opp3;
	Opponent* opp4;
	RectangleShape finishLine;
	Font font;
	Text text1;
	Text text2;
	Text positionText;

public:
	TrackRace() {
		trackTex.loadFromFile("img/track-background.png");
		trackBackground.setTexture(trackTex);

		opp1 = new Opponent("img/opp1.png", 30,415,7);
		opp2 = new Opponent("img/opp2.png", 30, 435, 10);
		opp3 = new Opponent("img/opp3.png", 40, 465, 15);
		opp4 = new Opponent("img/opp4.png", 50, 485, 12);
		
		finishLine.setSize(Vector2f(40, 300));
		finishLine.setPosition(1250, 365);

		font.loadFromFile("fonts/Squartiqa4F.ttf");
		text1.setString("GAME OVER");
		text1.setCharacterSize(70);
		text1.setFont(font);
		text1.setPosition(400, 210);

		text2.setString("You finished: ");
		text2.setCharacterSize(40);
		text2.setFont(font);
		text2.setPosition(420, 310);

		positionText.setCharacterSize(40);
		positionText.setFont(font);
		positionText.setPosition(800, 310);
	}

	void gameRun(RenderWindow& window, OlympicPlayer*& p) {
		bool go = false;
		bool stop = false;
		int raceCounter = 0;
		bool oppositionBool[4] = { 1,1,1,1 };
		bool playerBool = 1;
		p->playerSprite.setPosition(55, 515);

		while (window.isOpen()) {
			Event event;
			while (window.pollEvent(event)) {
				if (event.type == Event::Closed) {
					window.close();
				}

				if (!go) {
					if (Keyboard::isKeyPressed(Keyboard::Right))
						go = true;
				}

				if (go && !stop) {
					if (finishLine.getGlobalBounds().intersects(opp1->getOpponentSprite().getGlobalBounds()) && oppositionBool[0]) {
						raceCounter += 1;
						oppositionBool[0] = 0;
					}
					if (finishLine.getGlobalBounds().intersects(opp2->getOpponentSprite().getGlobalBounds()) && oppositionBool[1]) {
						raceCounter += 1;
						oppositionBool[1] = 0;
					}
					if (finishLine.getGlobalBounds().intersects(opp3->getOpponentSprite().getGlobalBounds()) && oppositionBool[2]) {
						raceCounter += 1;
						oppositionBool[2] = 0;
					}
					if (finishLine.getGlobalBounds().intersects(opp4->getOpponentSprite().getGlobalBounds()) && oppositionBool[3]) {
						raceCounter += 1;
						oppositionBool[3] = 0;
					}
					if (finishLine.getGlobalBounds().intersects(p->getPlayerSprite().getGlobalBounds()) && playerBool) {
						raceCounter += 1;
						gameOver(window, raceCounter,p);
					}
				}

				if (go && !stop) {
					if (Keyboard::isKeyPressed(Keyboard::Right)) {
						p->run();
						opp1->move();
						opp2->move();
						opp3->move();
						opp4->move();
					}
				}

				window.clear();
				window.draw(trackBackground);
				window.draw(opp1->getOpponentSprite());
				window.draw(opp2->getOpponentSprite());
				window.draw(opp3->getOpponentSprite());
				window.draw(opp4->getOpponentSprite());
				window.draw(p->getPlayerSprite());
				window.display();
			}
		}
	}

	void gameOver(RenderWindow& window, int position, OlympicPlayer*& p) {
		switch (position) {
		case 1:
			positionText.setString(to_string(position) + "st");
			break;
		case 2:
			positionText.setString(to_string(position) + "nd");
			break;
		case 3:
			positionText.setString(to_string(position) + "rd");
			break;
		case 4:
			positionText.setString(to_string(position) + "th");
			break;
		case 5:
			positionText.setString(to_string(position) + "th");
			break;
		default:
			break;
		}
		Texture medalTex;
		Sprite medalSprite;
		bool medal = false;
		if (position == 1) {
			medal = true;
			medalTex.loadFromFile("img/gold.png");
			medalSprite.setTexture(medalTex);
			medalSprite.setPosition(900, 200);
		}
		else if (position == 2) {
			medal = true;
			medalTex.loadFromFile("img/silver.png");
			medalSprite.setTexture(medalTex);
			medalSprite.setPosition(900, 200);
		}
		else if (position == 3) {
			medal = true;
			medalTex.loadFromFile("img/bronze.png");
			medalSprite.setTexture(medalTex);
			medalSprite.setPosition(900, 200);
		}
		while (window.isOpen()) {
			Event event;
			while (window.pollEvent(event)) {
				if (event.type == Event::Closed) {
					window.close();
				}

				if (Keyboard::isKeyPressed(Keyboard::Escape)) {
					window.close();
				}

				window.clear();

				window.draw(trackBackground);
				window.draw(opp1->getOpponentSprite());
				window.draw(opp2->getOpponentSprite());
				window.draw(opp3->getOpponentSprite());
				window.draw(opp4->getOpponentSprite());
				window.draw(p->getPlayerSprite());
				window.draw(text1);
				window.draw(text2);
				window.draw(positionText);
				if (medal) {
					window.draw(medalSprite);
				}
				window.display();
			}
		}
	}
};

#endif