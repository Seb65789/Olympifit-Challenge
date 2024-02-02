#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <ctime>
#include "olympicplayer.h"
#include "trivia.h"
#include "aeroassault.h"
#include "obstacle.h"
#include "trackrace.h"
#include "soundmanager.h"
using namespace sf;
using namespace std;

//cette classe est le coeur du jeu
class Game {
private:
    // Éléments graphiques pour le menu principal et d'autres écrans.
	Texture menuTex;
	Sprite menuBackground;
    Texture instructionTex;
    Sprite instructionBackground;
    Texture lowPointsTex;
    Sprite lowPointsBackground;
    Texture lowFitnessTex;
    Sprite lowFitnessBackground;
    Texture mapTex;
    Sprite mapSprite;
    Texture sideEventTex;
    Sprite sideEventSprite;
    Texture gymTex;
    Sprite gymSprite;
    Texture loadingTex;
    Sprite loadingSprite;

    // Rectangles pour la détection de clics sur les différents événements dans le menu et la salle de gym.
    RectangleShape gymEventRect;
    RectangleShape sideEventRect;
    RectangleShape olympicEventRect;

    
    RectangleShape gymEvent1Rect;
    RectangleShape gymEvent2Rect;
    RectangleShape gymEvent3Rect;
    RectangleShape gymEvent4Rect;

    // Objets de jeu pour les différentes activités.
    Trivia* t;
    AeroAssault* a;
    OlympicPlayer* p;
    ObstacleOverdrive* o;
    TrackRace* track;
    
    // Pour l'affichage du texte.
    Font font;
    Text fitnessDisplay;
    Text pointsDisplay;
    int points;

public:
	Game() {
		menuTex.loadFromFile("img/menu.png");
		menuBackground.setTexture(menuTex);
        mapTex.loadFromFile("img/map.png");
        mapSprite.setTexture(mapTex);
        sideEventTex.loadFromFile("img/screen-1.png");
        sideEventSprite.setTexture(sideEventTex);
        gymTex.loadFromFile("img/gym-map.png");
        gymSprite.setTexture(gymTex);
        loadingTex.loadFromFile("img/loading.png");
        loadingSprite.setTexture(loadingTex);
        instructionTex.loadFromFile("img/instructions.png");
        instructionBackground.setTexture(instructionTex);
        lowPointsTex.loadFromFile("img/low-points.png");
        lowPointsBackground.setTexture(lowPointsTex);
        lowFitnessTex.loadFromFile("img/low-fitness.png");
        lowFitnessBackground.setTexture(lowFitnessTex);

        gymEventRect.setSize(Vector2f(300, 400));
        gymEventRect.setPosition(0, 0);

        sideEventRect.setSize(Vector2f(300, 400));
        sideEventRect.setPosition(520, 0);

        olympicEventRect.setSize(Vector2f(300, 400));
        olympicEventRect.setPosition(1020, 0);

        gymEvent1Rect.setSize(Vector2f(200, 250));
        gymEvent1Rect.setPosition(100, 100);

        gymEvent2Rect.setSize(Vector2f(200, 250));
        gymEvent2Rect.setPosition(100, 450);

        gymEvent3Rect.setSize(Vector2f(380, 200));
        gymEvent3Rect.setPosition(800, 30);

        gymEvent4Rect.setSize(Vector2f(450, 300));
        gymEvent4Rect.setPosition(800, 350);

        
        t = new Trivia();
        a = new AeroAssault();
        p = new OlympicPlayer();
        o = new ObstacleOverdrive();
        track = new TrackRace();

        font.loadFromFile("fonts/Squartiqa4F.ttf");
        fitnessDisplay.setFont(font);
        pointsDisplay.setFont(font);
        fitnessDisplay.setCharacterSize(30);
        pointsDisplay.setCharacterSize(30);
        pointsDisplay.setPosition(0, 630);
        fitnessDisplay.setPosition(0, 670);
        points = 0;
	}

    // Affichage du menu principal.
	void displayMenu(RenderWindow& window) {
        window.draw(menuBackground);
        SoundManager bgMusic("music/jazz.wav");
        bgMusic.setVolume(50);
        bgMusic.setLoop();
        bgMusic.playSound();

        while (window.isOpen()) {
            Event event;
            while (window.pollEvent(event)) {
                if (event.type == Event::Closed) {
                    window.close();
                }

                if (event.type == Event::KeyPressed) {
                    if (event.key.code == Keyboard::P) {
                        this->displayInstructions(window);
                    }
                    if (event.key.code == Keyboard::E) {
                        window.close();
                    }
                }
            }
            window.clear();
            window.draw(menuBackground);
            window.display();
        }
	}

    // Affichage des instructions du jeu.
    void displayInstructions(RenderWindow& window) {
        window.draw(instructionBackground);

        while (window.isOpen()) {
            Event event;
            while (window.pollEvent(event)) {
                if (event.type == Event::Closed) {
                    window.close();
                }

                if (event.type == Event::KeyPressed) {
                    if (event.key.code == Keyboard::P) {
                        this->gameRun(window);
                    }
                    if (event.key.code == Keyboard::Escape) {
                        window.close();
                    }
                }
            }
            window.clear();
            window.draw(instructionBackground);
            window.display();
        }
    }

    // Exécution principale du jeu.
    void gameRun(RenderWindow& window) {
        window.clear();
        window.draw(mapSprite);

        while (window.isOpen()) {
            Event event;
            while (window.pollEvent(event)) {
                if (event.type == Event::Closed) {
                    window.close();
                }
                if (event.key.code == Keyboard::Escape) {
                    window.close();
                }

                if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
                    Vector2i mousePos = Mouse::getPosition(window);

                    FloatRect rectBounds1 = gymEventRect.getGlobalBounds();
                    FloatRect rectBounds2 = sideEventRect.getGlobalBounds();
                    FloatRect rectBounds3 = olympicEventRect.getGlobalBounds();

                    if (rectBounds1.contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
                        this->runGym(window);
                        this->drawGame(window);
                    }
                    else if (rectBounds2.contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
                        this->displaySideEventMenu(window, points);
                        this->drawGame(window);
                    }
                    else if (rectBounds3.contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
                        if (p->getFitnessLevel() >= 70) {
                            track = new TrackRace();
                            track->gameRun(window, p);
                            this->drawGame(window);
                        }
                        else {
                            this->showNotEnoughFitness(window);
                            this->drawGame(window);
                        }
                    }
                }

                if (event.key.code == Keyboard::E) {
                    FloatRect playerBounds = p->getPlayerSprite().getGlobalBounds();
                    FloatRect rectBounds1 = gymEventRect.getGlobalBounds();
                    FloatRect rectBounds2 = sideEventRect.getGlobalBounds();
                    FloatRect rectBounds3 = olympicEventRect.getGlobalBounds();

                    if (rectBounds1.intersects(playerBounds)) {
                        this->runGym(window);
                        this->drawGame(window);
                    }
                    else if (rectBounds2.intersects(playerBounds)) {
                        this->displaySideEventMenu(window, points);
                        this->drawGame(window);
                    }
                    else if (rectBounds3.intersects(playerBounds)) {
                        if (p->getFitnessLevel() >= 70) {
                            track = new TrackRace();
                            track->gameRun(window, p);
                            this->drawGame(window);
                        }
                        else {
                            this->showNotEnoughFitness(window);
                            this->drawGame(window);
                        }
                    }
                }

                if (Keyboard::isKeyPressed(Keyboard::Left)) 
                    p->move("l");    
                if (Keyboard::isKeyPressed(Keyboard::Right)) 
                    p->move("r");  
                if (Keyboard::isKeyPressed(Keyboard::Up)) 
                    p->move("u");    
                if (Keyboard::isKeyPressed(Keyboard::Down)) 
                    p->move("d");
            }
            pointsDisplay.setString("Points: " + to_string(p->getEarnedPoints()));
            fitnessDisplay.setString("Fitness Level: " + to_string(p->getFitnessLevel()));

            window.clear();
            window.draw(mapSprite);
            window.draw(p->getPlayerSprite());
            window.draw(pointsDisplay);
            window.draw(fitnessDisplay);
            window.display();
        }
    }

    // Dessin des éléments du jeu sur la fenêtre.
    void drawGame(RenderWindow& window) {
        pointsDisplay.setString("Points: " + to_string(p->getEarnedPoints()));
        fitnessDisplay.setString("Fitness Level: " + to_string(p->getFitnessLevel()));

        window.clear();
        window.draw(mapSprite);
        window.draw(p->getPlayerSprite());
        window.draw(pointsDisplay);
        window.draw(fitnessDisplay);
        window.display();
        return;
    }

    //fonctionnalité de la salle de gym
    void runGym(RenderWindow& window) {
        Clock clock;
        double timer = 0;

        window.clear();
        window.draw(gymSprite);
        window.draw(p->getPlayerSprite());
        window.display();
        
        while (window.isOpen()) {
            Event event;
            while (window.pollEvent(event)) {
                if (event.type == Event::Closed) {
                    window.close();
                }
                if (event.key.code == Keyboard::Escape) {
                    window.close();
                }
                if (event.key.code == Keyboard::R) {
                    return;
                }

                if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
                    Vector2i mousePos = Mouse::getPosition(window);

                    FloatRect rectBounds1 = gymEvent1Rect.getGlobalBounds();
                    FloatRect rectBounds2 = gymEvent2Rect.getGlobalBounds();
                    FloatRect rectBounds3 = gymEvent3Rect.getGlobalBounds();
                    FloatRect rectBounds4 = gymEvent4Rect.getGlobalBounds();

                    if (rectBounds1.contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
                        if (p->getEarnedPoints() >= 100) {
                            this->displayLoadingScreen(window);
                            this->drawGym(window);
                            p->setEarnedPoints(p->getEarnedPoints() - 100);
                            p->setFitnessLevel(p->getFitnessLevel() + 50);
                            changePlayerRunningSpeed();
                        }
                        else {
                            this->showNotEnoughPoints(window);
                            this->drawGym(window);
                        }
                    }
                    else if (rectBounds2.contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
                        if (p->getEarnedPoints() >= 70) {
                            this->displayLoadingScreen(window);
                            this->drawGym(window);
                            p->setEarnedPoints(p->getEarnedPoints() - 70);
                            p->setFitnessLevel(p->getFitnessLevel() + 30);
                            changePlayerRunningSpeed();
                        }
                        else {
                            this->showNotEnoughPoints(window);
                            this->drawGym(window);
                        }
                    }
                    else if (rectBounds3.contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
                        if (p->getEarnedPoints() >= 120) {
                            this->displayLoadingScreen(window);
                            this->drawGym(window);
                            p->setEarnedPoints(p->getEarnedPoints() - 120);
                            p->setFitnessLevel(p->getFitnessLevel() + 80);
                            changePlayerRunningSpeed();
                        }
                        else {
                            this->showNotEnoughPoints(window);
                            this->drawGym(window);
                        }
                    }
                    else if (rectBounds4.contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
                        if (p->getEarnedPoints() >= 150) {
                            this->displayLoadingScreen(window);
                            this->drawGym(window);
                            p->setEarnedPoints(p->getEarnedPoints() - 150);
                            p->setFitnessLevel(p->getFitnessLevel() + 100);
                            changePlayerRunningSpeed();
                        }
                        else {
                            this->showNotEnoughPoints(window);
                            this->drawGym(window);
                        }
                    }
                    
                }

                if (event.key.code == Keyboard::E) {
                    FloatRect playerBounds = p->getPlayerSprite().getGlobalBounds();
                    FloatRect rectBounds1 = gymEvent1Rect.getGlobalBounds();
                    FloatRect rectBounds2 = gymEvent2Rect.getGlobalBounds();
                    FloatRect rectBounds3 = gymEvent3Rect.getGlobalBounds();
                    FloatRect rectBounds4 = gymEvent4Rect.getGlobalBounds();

                    if (rectBounds1.intersects(playerBounds)) {
                        if (p->getEarnedPoints() >= 100) {
                            this->displayLoadingScreen(window);
                            this->drawGym(window);
                            p->setEarnedPoints(p->getEarnedPoints() - 100);
                            p->setFitnessLevel(p->getFitnessLevel() + 50);
                            changePlayerRunningSpeed();
                        }
                        else {
                            this->showNotEnoughPoints(window);
                            this->drawGym(window);
                        }
                    }
                    else if (rectBounds2.intersects(playerBounds)) {
                        if (p->getEarnedPoints() >= 70) {
                            this->displayLoadingScreen(window);
                            this->drawGym(window);
                            p->setEarnedPoints(p->getEarnedPoints() - 70);
                            p->setFitnessLevel(p->getFitnessLevel() + 30);
                            changePlayerRunningSpeed();
                        }
                        else {
                            this->showNotEnoughPoints(window);
                            this->drawGym(window);
                        }
                    }
                    else if (rectBounds3.intersects(playerBounds)) {
                        if (p->getEarnedPoints() >= 120) {
                            this->displayLoadingScreen(window);
                            this->drawGym(window);
                            p->setEarnedPoints(p->getEarnedPoints() - 120);
                            p->setFitnessLevel(p->getFitnessLevel() + 80);
                            changePlayerRunningSpeed();
                        }
                        else {
                            this->showNotEnoughPoints(window);
                            this->drawGym(window);
                        }
                    }
                    else if (rectBounds4.intersects(playerBounds)) {
                        if (p->getEarnedPoints() >= 150) {
                            this->displayLoadingScreen(window);
                            this->drawGym(window);
                            p->setEarnedPoints(p->getEarnedPoints() - 150);
                            p->setFitnessLevel(p->getFitnessLevel() + 100);
                            changePlayerRunningSpeed();
                        }
                        else {
                            this->showNotEnoughPoints(window);
                            this->drawGym(window);
                        }
                    }
                }

                if (Keyboard::isKeyPressed(Keyboard::Left))
                    p->move("l");   
                if (Keyboard::isKeyPressed(Keyboard::Right))
                    p->move("r");  
                if (Keyboard::isKeyPressed(Keyboard::Up))
                    p->move("u");   
                if (Keyboard::isKeyPressed(Keyboard::Down))
                    p->move("d");
            }

            window.clear();
            window.draw(gymSprite);
            window.draw(p->getPlayerSprite());
            window.display();
        }
    }

    void drawGym(RenderWindow& window) {
        window.clear();
        window.draw(gymSprite);
        window.draw(p->getPlayerSprite());
        window.display();
    }

    // Affichage de l'écran de chargement.
    void displayLoadingScreen(RenderWindow& window) {
        Clock clock;
        double timer = 0;
        

        window.clear();
        window.draw(loadingSprite);
        window.display();

        while (window.isOpen()) {
            float time = clock.getElapsedTime().asSeconds();
            clock.restart();
            timer += time;

            Event event;
            while (window.pollEvent(event)) {
                if (event.type == Event::Closed) {
                    window.close();
                }

                if (timer >= 3.0) {
                    return;
                }

                window.clear();
                window.draw(loadingSprite);
                window.display();
            }
        }
    }

    // Affichage en cas de points insuffisants
    void showNotEnoughPoints(RenderWindow& window) {
        Clock clock;
        double timer = 0;
        while (window.isOpen()) {
            Event event;
            while (window.pollEvent(event)) {
                float time = clock.getElapsedTime().asSeconds();
                timer += time;
                clock.restart();

                if (event.type == Event::Closed) {
                    window.close();
                }

                if (timer >= 1.0) {
                    return;
                }

                window.clear();
                window.draw(lowPointsBackground);
                window.display();
            }
        }
    }

    // Fonctionnalité pour les missions secondaires.
    void displaySideEventMenu(RenderWindow& window, int& points) {
        Font font;
        font.loadFromFile("fonts/Squartiqa4F.ttf");

        Text line1;
        Text line2;
        Text line3;
        line1.setFont(font);
        line2.setFont(font);
        line3.setFont(font);
        line1.setString("Olympic Trivia             [1]");
        line2.setString("Aero Assault             [2]");
        line3.setString("Obstacle Overdrive  [3]");
        line1.setPosition(305, 230);
        line2.setPosition(305, 330);
        line3.setPosition(305, 430);
        line1.setCharacterSize(40);
        line2.setCharacterSize(40);
        line3.setCharacterSize(40);

        window.clear();
        window.draw(sideEventSprite);
        window.draw(line1);
        window.draw(line2);
        window.draw(line3);

        while (window.isOpen()) {
            Event event;
            while (window.pollEvent(event)) {
                if (event.type == Event::Closed) {
                    window.close();
                }

                if (event.type == Event::KeyPressed) {
                    if (event.key.code == Keyboard::Num1) {
                        t = new Trivia();
                        t->gameRun(window, points);
                        p->setEarnedPoints(points);
                        return;
                    }
                    if (event.key.code == Keyboard::Num2) {
                        a = new AeroAssault();
                        a->gameRun(window,points);
                        p->setEarnedPoints(points);
                        return;
                    }
                    if (event.key.code == Keyboard::Num3) {
                        o = new ObstacleOverdrive();
                        o->gameRun(window, points);
                        p->setEarnedPoints(points);
                        return;
                    }
                    if (event.key.code == Keyboard::R) {
                        return;
                    }
                }
            }
            window.clear();
            window.draw(sideEventSprite);
            window.draw(line1);
            window.draw(line2);
            window.draw(line3);
            window.display();
        }
    }

    // Ajustement de la vitesse de course du joueur en fonction de son niveau de fitness.
    void changePlayerRunningSpeed() {
        if (p->getFitnessLevel() >= 80) {
            p->setRunningSpeed(9);
        }
        if (p->getFitnessLevel() >= 160) {
            p->setRunningSpeed(11);
        }
        if (p->getFitnessLevel() >= 210) {
            p->setRunningSpeed(14);
        }
        if (p->getFitnessLevel() >= 270) {
            p->setRunningSpeed(17);
        }
    }

    // Affichage en cas de fitness insuffisant.
    void showNotEnoughFitness(RenderWindow& window) {
        Clock clock;
        double timer = 0;
        while (window.isOpen()) {
            Event event;
            while (window.pollEvent(event)) {
                float time = clock.getElapsedTime().asSeconds();
                timer += time;
                clock.restart();

                if (event.type == Event::Closed) {
                    window.close();
                }

                if (timer >= 0.7) {
                    return;
                }

                window.clear();
                window.draw(lowFitnessBackground);
                window.display();
            }
        }
    }
};


#endif
