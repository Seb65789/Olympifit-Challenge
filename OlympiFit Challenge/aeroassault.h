#ifndef AEROASSAULT_H
#define AEROASSAULT_H

// Inclusion de la bibliothèque SFML pour la gestion graphique et du son.
#include <SFML/Graphics.hpp>
#include "soundmanager.h"
using namespace sf;
using namespace std;

//Une quête secondaire dans laquelle le joueur doit détruire des avions ennemis. 
//Détruisez-les tous pour obtenir le maximum de points.

// Définition de la classe Bullet pour gérer les balles tirées par le joueur
class Bullet {
public:
	Texture tex;
	Sprite sprite;
	float speed = 1;

	// Constructeur qui initialise la balle avec une texture spécifique
	Bullet(std::string filePath) {
		tex.loadFromFile(filePath);
		sprite.setTexture(tex);
		sprite.setPosition(120, 233); //120,233
		sprite.setScale(0.09, 0.125);
	}

	// Méthode pour déplacer la balle sur l'écran
	void move(int tempX, int tempY) {
		float delta_x = 0, delta_y = 0;
		delta_x += 1; // Mouvement horizontal constant
		delta_x *= speed; // Vitesse de déplacement

		// Conditions pour repositionner la balle si elle sort de l'écran
		if (sprite.getPosition().y < 0)
			sprite.setPosition(tempX + 80.0f, tempY + 40.0f);
		else if (sprite.getPosition().y > 720) {
			sprite.setPosition(tempX + 80.0f, tempY + 40.0f);
		}
		else if (sprite.getPosition().x > 1280)
			sprite.setPosition(tempX, tempY);
		else if (sprite.getPosition().x < 0)
			sprite.setPosition(tempX + 80.0f, tempY + 40.0f);
		sprite.move(delta_x, delta_y);
	}


};

// Classe pour gérer les balles ennemies.
class EnemyBullet {
public:
	Texture tex;
	Sprite sprite;
	int tempX;
	int tempY;
	float speed = 1;

	// Constructeur qui initialise la balle ennemie avec une texture et une position.
	EnemyBullet(std::string filePath, double x, double y) {
		tex.loadFromFile(filePath);
		sprite.setTexture(tex);
		sprite.setPosition(x, y); //120,233
		sprite.setScale(1.5, 2);
		tempX = x;
		tempY = y;
	}

	// Méthode pour déplacer la balle ennemie sur l'écran
	void move(bool& out) {
		float delta_x = 0, delta_y = 0;
		delta_x -= 1; // Mouvement horizontal vers la gauche.
		delta_x *= speed;
		if (sprite.getPosition().y < 0)
			sprite.setPosition(tempX, tempY);
		else if (sprite.getPosition().y > 720) {
			sprite.setPosition(tempX, tempY);
		}
		else if (sprite.getPosition().x > 1280)
			sprite.setPosition(tempX, tempY);
		else if (sprite.getPosition().x < 0) {
			sprite.setPosition(tempX, tempY);
			out = true;
		}
		sprite.move(delta_x, delta_y);
	}
};

// Classe pour représenter les ennemis dans le jeu.
class Enemy
{
public:
	Texture tex;
	Sprite sprite;
	float speed = 0.3;
	EnemyBullet* eB;

	Enemy(std::string png_path, double x, double y)
	{
		tex.loadFromFile(png_path);
		sprite.setTexture(tex);
		sprite.setPosition(x, y);
		sprite.setScale(1.5, 1.5);
		eB = new EnemyBullet("img/enemy-bullet.png", x + 20, y + 33);
	}

	// Méthode statique pour initialiser un vecteur d'ennemis.
	void setEnemies(vector<Enemy*>& e) {
		// Création et ajout d'ennemis à différentes positions.
		Enemy* e1 = new Enemy("img/enemy.png", 1120, 0);
		e.push_back(e1);

		e1 = new Enemy("img/enemy.png", 960, 100);
		e.push_back(e1);

		e1 = new Enemy("img/enemy.png", 800, 200);
		e.push_back(e1);

		e1 = new Enemy("img/enemy.png", 1120, 200);
		e.push_back(e1);

		e1 = new Enemy("img/enemy.png", 640, 300);
		e.push_back(e1);

		e1 = new Enemy("img/enemy.png", 960, 300);
		e.push_back(e1);

		e1 = new Enemy("img/enemy.png", 800, 400);
		e.push_back(e1);

		e1 = new Enemy("img/enemy.png", 1120, 400);
		e.push_back(e1);

		e1 = new Enemy("img/enemy.png", 960, 500);
		e.push_back(e1);

		e1 = new Enemy("img/enemy.png", 1120, 600);

		e.push_back(e1);
	}
};

// Classe pour représenter le joueur.
class Player {
public:
	Texture tex;
	Sprite sprite;
	float speed = 0.75; // Vitesse de déplacement du joueur.

	Player(std::string filePath) {
		tex.loadFromFile(filePath);
		sprite.setTexture(tex);
		sprite.setPosition(100, 200);
		sprite.setScale(0.25, 0.25);
	}

	// Méthode pour déplacer le joueur en fonction des entrées clavier.
	void move(std::string s) {
		float delta_x = 0, delta_y = 0;
		if (s == "l")
			delta_x -= 1;
		//deplacer le joueur vers la gauche

		else if (s == "r")
			delta_x += 1;
		//deplacer le joueur vers la droite
		else if (s == "u")
			delta_y = -1;
		else if (s == "d")
			delta_y += 1;

		delta_x *= speed;
		delta_y *= speed;

		 // Gestion du dépassement des limites de l'écran.
		if (sprite.getPosition().y < 0)
		{
			sprite.setPosition(sprite.getPosition().x, 720);
		}
		else if (sprite.getPosition().x < 0)
		{
			sprite.setPosition(1280, sprite.getPosition().y);
		}
		else if (sprite.getPosition().y > 720)
		{
			sprite.setPosition(sprite.getPosition().x, 0);
		}
		else if (sprite.getPosition().x > 1280)
		{
			sprite.setPosition(0, sprite.getPosition().y);
		}

		sprite.move(delta_x, delta_y);

	}
};

// Classe principale du jeu, gérant la logique globale du jeu.
class AeroAssault{
public:
	Texture tex;
	Sprite background;
	Player* p;
	Bullet* b;
	vector<Enemy*> e;
	FloatRect playerBounds;
	FloatRect bulletBounds;
	FloatRect enemyBulletBounds;
	vector<FloatRect> enemyBounds;
	vector<bool> enemyBool;
	double x, y;
	int enemyCount;
	int score;
	bool enemyBulletOut;
	int deadEnemyCount;
	int deadIndex[10];
	bool deadIndexBool;
	bool gameOver;
	bool collision;
	Font font;
	Text scoring;

	AeroAssault() {
		tex.loadFromFile("img/aerobackground.jpg");
		background.setTexture(tex);
		p = new Player("img/player.png");
		b = new Bullet("img/bullet.png");
		x = 800;
		y = 0;
		enemyCount = 10;
		setEnemies(e);
		collision = false;
		enemyBulletOut = false;
		deadEnemyCount = 0;
		for (int i = 0; i < 10; i++) {
			deadIndex[i] = -1;
			bool a = true;
			enemyBool.push_back(a);
		}
		deadIndexBool = false;
		score = 0;
		gameOver = false;
		playerBounds = { -1.0f, -1.0f, 0.0f, 0.0f };
		bulletBounds = { -1.0f, -1.0f, 0.0f, 0.0f };
		enemyBulletBounds = { -1.0f, -1.0f, 0.0f, 0.0f };
		gameOver = false;
		font.loadFromFile("fonts/Squartiqa4F.ttf");
		scoring.setCharacterSize(20);
		scoring.setFont(font);
		scoring.setPosition(70, 683);
		scoring.setFillColor(Color::Yellow);
	}

	// Méthode pour lancer le jeu.
	void gameRun(RenderWindow& window, int& points) {
		srand(100);
		int index = rand() % enemyCount;
		int prevIndex = -1;
		Event E;
		while (window.isOpen())
		{
			while (window.pollEvent(E))
			{
				if (E.type == Event::Closed)
					window.close();
			}

			checkEnemyBulletOut(index, prevIndex, deadIndexBool);

			if (Keyboard::isKeyPressed(Keyboard::Left)) //Si la touche gauche est enfoncée
				p->move("l");    // le joueur se déplacera vers la gauche
			if (Keyboard::isKeyPressed(Keyboard::Right)) // Si la touche droite est enfoncée
				p->move("r");  // le joueur se déplacera vers la droite
			if (Keyboard::isKeyPressed(Keyboard::Up)) // Si la touche haut est enfoncée
				p->move("u");    // le joueur se déplacera vers le haut
			if (Keyboard::isKeyPressed(Keyboard::Down)) // Si la touche bas est enfoncée
				p->move("d");  // le joueur se déplacera vers le bas

			if (deadEnemyCount == 10) {
				gameOver = true;
			}

			b->move(p->sprite.getPosition().x + 20, p->sprite.getPosition().y + 33);
			if (e[index] != nullptr) {
				e[index]->eB->move(enemyBulletOut);
			}

			setBulletAndEnemyBounds();
			checkPlayerBulletEnemyCollision();
			checkEnemyBulletPlayerCollision(index);
			scoring.setString("Score: " + to_string(score));

			if (gameOver) {
				gameOverScreen(window, points);
				return;
			}
			drawEverything(window);
		}

	}

	// Méthode pour initialiser les ennemis.
	void setEnemies(vector<Enemy*>& e) {
		Enemy* e1 = new Enemy("img/enemy.png", 1120, 0);
		e.push_back(e1);

		e1 = new Enemy("img/enemy.png", 960, 100);
		e.push_back(e1);

		e1 = new Enemy("img/enemy.png", 800, 200);
		e.push_back(e1);

		e1 = new Enemy("img/enemy.png", 1120, 200);
		e.push_back(e1);

		e1 = new Enemy("img/enemy.png", 640, 300);
		e.push_back(e1);

		e1 = new Enemy("img/enemy.png", 960, 300);
		e.push_back(e1);

		e1 = new Enemy("img/enemy.png", 800, 400);
		e.push_back(e1);

		e1 = new Enemy("img/enemy.png", 1120, 400);
		e.push_back(e1);

		e1 = new Enemy("img/enemy.png", 960, 500);
		e.push_back(e1);

		e1 = new Enemy("img/enemy.png", 1120, 600);

		e.push_back(e1);
	}

	// Méthode pour vérifier si une balle ennemie est sortie de l'écran.
	void checkEnemyBulletOut(int& index, int& prevIndex, bool& deadIndexBool) {
		if (enemyBulletOut) {
			while (index == prevIndex || deadIndexBool) {
				index = rand() % enemyCount;
				for (int i = 0; i < enemyCount; i++) {
					if (index == deadIndex[i]) {
						deadIndexBool = true;
						break;
					}
					deadIndexBool = false;
				}

			}
			enemyBulletOut = false;
		}
		prevIndex = index;
	}

	// Méthode pour définir les limites des balles et des ennemis.
	void setBulletAndEnemyBounds() {
		bulletBounds = b->sprite.getGlobalBounds();
		for (int i = 0; i < enemyCount; i++) {
			if (e[i] != nullptr) {
				FloatRect bounds = e[i]->sprite.getGlobalBounds();
				enemyBounds.push_back(bounds);
			}
			else {
				enemyBounds[i] = { -1.0f, -1.0f, 0.0f, 0.0f };
			}
		}
	}

	// Méthode pour vérifier la collision entre les balles du joueur et les ennemis.
	void checkPlayerBulletEnemyCollision() {
		for (int i = 0; i < enemyCount; i++) {
			if (bulletBounds.intersects(enemyBounds[i])) {
				e[i] = nullptr;
				b->sprite.setPosition(p->sprite.getPosition().x + 20, p->sprite.getPosition().y + 33);
				enemyBounds[i] = { -1.0f, -1.0f, 0.0f, 0.0f };
				enemyBool[i] = false;
				deadEnemyCount += 1;
				deadIndex[i] = i;
				score += 10;
			}
		}
	}

	// Méthode pour vérifier la collision entre les balles ennemies et le joueur.
	void checkEnemyBulletPlayerCollision(int index) {
		playerBounds = p->sprite.getGlobalBounds();
		if (e[index] != nullptr) {
			enemyBulletBounds = e[index]->eB->sprite.getGlobalBounds();
		}

		if (enemyBulletBounds.intersects(playerBounds)) {
			gameOver = true;
		}
	}

	// Méthode pour dessiner tous les éléments du jeu.
	void drawEverything(RenderWindow& window) {
		window.clear();
		window.draw(background);
		window.draw(b->sprite);
		window.draw(p->sprite);

		for (auto& enemy : e) {
			if (enemy != nullptr) {
				window.draw(enemy->eB->sprite);
				window.draw(enemy->sprite);
			}
		}
		window.draw(scoring);
		window.display();
	}

	// Méthode pour afficher l'écran de fin de partie.
	void gameOverScreen(RenderWindow& window, int& points) {
		while (gameOver) {
			window.clear();
			window.draw(background);
			scoring.setCharacterSize(50);
			scoring.setPosition(500, 320);
			scoring.setString("Final Score: " + to_string(score));
			window.draw(scoring);
			window.display();
			if (Keyboard::isKeyPressed(Keyboard::R)) {
				points += score;
				return;
			}
		}
	}
};

#endif
