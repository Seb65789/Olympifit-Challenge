#ifndef OBSTACLE_H
#define OBSTACLE_H

#include <SFML/Graphics.hpp>
#include <time.h>
#include <ctime>
#include "soundmanager.h"
using namespace sf;
using namespace std;

//Une quête secondaire simple dans laquelle le joueur doit esquiver des obstacles
//et gagner des points, le nombre de points augmente plus vous restez en vie

// Classe représentant le joueur dans le mini-jeu d'obstacles.
class ObstaclePlayer {
private:
	Texture playerTex;
	Sprite playerSprite;
	double speed;
	int health;


public:
    // Constructeur initialisant le joueur avec une texture spécifique et des paramètres de base.
    ObstaclePlayer() {
		playerTex.loadFromFile("img/player1.png");
		playerSprite.setTexture(playerTex);
		playerSprite.setPosition(570, 580);
		playerSprite.setScale(0.25, 0.25);
		speed = 1;
		health = 100;
	}

	Sprite& getSprite() {
		return playerSprite;
	}

    // Méthode pour déplacer le joueur à gauche ou à droite
    void move(std::string s){
        float delta_x = 0, delta_y = 0;
        if (s == "l")
            delta_x -= 1;
        else if (s == "r")
            delta_x += 1;

        delta_x *= speed;
        delta_y *= speed;

        if (playerSprite.getPosition().x < 250) {
            playerSprite.setPosition(900, playerSprite.getPosition().y);
        }
        else if (playerSprite.getPosition().x > 900) {
            playerSprite.setPosition(250, playerSprite.getPosition().y);
        }

        playerSprite.move(delta_x, delta_y);
    }

};

// Classe représentant un obstacle dans le jeu
class Obstacle {
private:
	Texture tex;
	Sprite sprite;
	double speed;

public:
    // Constructeur initialisant un obstacle avec une texture et une position.
	Obstacle(string filePath, double x, double y, double a = 1, double b = 1, double c = 1) {
		tex.loadFromFile(filePath);
		sprite.setTexture(tex);
		sprite.setPosition(x, y);
		sprite.setScale(b, c);
		speed = a;
	}

    // Méthode pour déplacer l'obstacle vers le bas
	void move() {
		double delta_x = 0, delta_y = 0;
		delta_y += 1;
		delta_y *= speed;
		sprite.move(delta_x, delta_y);
	}

	Sprite& getSprite() {
		return sprite;
	}

};

class ObstacleOverdrive {
private:
    Texture backgroundTex;
    Sprite backgroundSprite;
    Obstacle* obstacle1;
    Obstacle* obstacle2;
    Obstacle* obstacle3;
    Obstacle* obstacle4;
    ObstaclePlayer* player; // Pointeur vers le joueur.

public:
    ObstacleOverdrive() {
        backgroundTex.loadFromFile("img/background.jpg");
        backgroundSprite.setTexture(backgroundTex);

        obstacle1 = new Obstacle("img/fire1.png", 450, 0, 1, 0.5, 0.5);
        obstacle2 = new Obstacle("img/fire2.png", 570, 0, 0.9);
        obstacle3 = new Obstacle("img/fire3.png", 300, 0, 0.75, 0.5, 0.5);
        obstacle4 = new Obstacle("img/fire4.png", 850, 0, 1, 0.5, 0.5);
        player = new ObstaclePlayer();
    }

    // Méthode pour exécuter le mini-jeu d'obstacles.
    void gameRun(RenderWindow& window, int& points) {
        Clock clock;
        double timer = 0;
        double obstacle1_timer = 0, obstacle2_timer = 0, obstacle3_timer = 0;
        double obstacle4_timer = 0, obstacle5_timer = 0;

        while (window.isOpen()) {
            float time = clock.getElapsedTime().asSeconds();
            clock.restart();
            timer += time;
            obstacle1_timer += time;
            obstacle2_timer += time;
            obstacle3_timer += time;
            obstacle4_timer += time;
            obstacle5_timer += time;

            Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                }
            }

            if (Keyboard::isKeyPressed(Keyboard::R)) {
                return;
            }

            if (Keyboard::isKeyPressed(Keyboard::Left)) //Si la touche gauche est enfoncée
                player->move("l");    // le joueur se déplacera à gauche
            if (Keyboard::isKeyPressed(Keyboard::Right)) // Si la touche droite est enfoncée
                player->move("r");  // le joueur se déplacera à droite

            //obstacle timer
            if (obstacle1_timer >= 2.7)
            {
                int x_cor = 450, y_cor = 0;
                obstacle1->getSprite().setPosition(x_cor, y_cor);
                obstacle1_timer = 0;
            }
            obstacle1->move();

            if (obstacle2_timer >= 2.1)
            {
                int x_cor = 570, y_cor = 0;
                obstacle2->getSprite().setPosition(x_cor, y_cor);
                obstacle2_timer = 0;
            }
            obstacle2->move();

            if (obstacle3_timer >= 1.8)
            {
                int x_cor = 300, y_cor = 0;
                obstacle3->getSprite().setPosition(x_cor, y_cor);
                obstacle3_timer = 0;
            }
            obstacle3->move();

            if (obstacle4_timer >= 1.5)
            {
                int x_cor = 850, y_cor = 0;
                obstacle4->getSprite().setPosition(x_cor, y_cor);
                obstacle4_timer = 0;
            }
            obstacle4->move();



            //Vérification de l'intersection entre le joueur et les obstacles
            if (obstacle1->getSprite().getGlobalBounds().intersects(player->getSprite().getGlobalBounds())) {
                this->gameOver(window, timer, points);
                return;
            }
            
            if (obstacle2->getSprite().getGlobalBounds().intersects(player->getSprite().getGlobalBounds())) {
                this->gameOver(window, timer, points);
                return;
            }

            if (obstacle3->getSprite().getGlobalBounds().intersects(player->getSprite().getGlobalBounds())) {
                this->gameOver(window, timer, points);
                return;
            }

            if (obstacle4->getSprite().getGlobalBounds().intersects(player->getSprite().getGlobalBounds())) {
                this->gameOver(window, timer, points);
                return;
            }

            //Rendu des éléments
            window.clear();
            window.draw(backgroundSprite);
            window.draw(obstacle1->getSprite());
            window.draw(obstacle2->getSprite());
            window.draw(obstacle3->getSprite());
            window.draw(obstacle4->getSprite());
            window.draw(player->getSprite());
            window.display();
        }
    }

    // Méthode pour afficher l'écran de fin de jeu
    void gameOver(RenderWindow& window, double timer, int& points) {
        int score = timer;
        score *= 16;
        points += score;
        Font font;
        font.loadFromFile("fonts/Squartiqa4F.ttf");
        Text gameOverText;
        Text scoreText;
        gameOverText.setFont(font);
        scoreText.setFont(font);
        gameOverText.setString("GAME OVER");
        gameOverText.setCharacterSize(40);
        gameOverText.setPosition(500, 310);

        scoreText.setString("Score: " + to_string(score));
        scoreText.setCharacterSize(30);
        scoreText.setPosition(530, 410);

        window.clear();
        window.draw(backgroundSprite);
        window.draw(gameOverText);
        window.draw(scoreText);
        window.display();

        while (window.isOpen()) {
            Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                }
            }

            if (Keyboard::isKeyPressed(Keyboard::R)) {
                return;
            }

            window.clear();
            window.draw(backgroundSprite);
            window.draw(gameOverText);
            window.draw(scoreText);
            window.display();
        }
    }

};

#endif
