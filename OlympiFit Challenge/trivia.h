#ifndef TRIVIA_H
#define TRIVIA_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "soundmanager.h"
using namespace std;
using namespace sf;

//a side quest in which player has to answer questions
//to gain points

class Trivia {
private:
	vector<string> questions;
	vector<vector<string>> options;
	vector<int> correctAnswers;
	Texture backgroundTex;
	Sprite background;

public:
	Trivia() {
		questions = {};
		correctAnswers = {};
		backgroundTex.loadFromFile("img/screen-1.png");
		background.setTexture(backgroundTex);
	}

	void gameRun(RenderWindow& window, int& points) {
		setQuestionsAndAnswers();
		window.draw(background);

		std::srand(static_cast<unsigned int>(std::time(nullptr)));

		unsigned int currentQuestion = 0;
		unsigned int correctAnswersCounter = 0;
		bool triviaOver = false;
		while (window.isOpen()) {
			::Event event;
			while (window.pollEvent(event)) {
				if (event.type == ::Event::Closed) {
					window.close();
				}
				else if (!triviaOver && event.type == Event::KeyPressed && event.key.code == Keyboard::R) {
					return;
				}
				else if (event.type == ::Event::KeyPressed && !triviaOver) {
					if (event.key.code == ::Keyboard::Num1 || event.key.code == ::Keyboard::Num2 ||
						event.key.code == ::Keyboard::Num3 || event.key.code == ::Keyboard::Num4) {
						int selectedOption = event.key.code - ::Keyboard::Num1;
						if (selectedOption == correctAnswers[currentQuestion]) {
							correctAnswersCounter++;
						}

						// Move to the next question
						currentQuestion++;
						if (currentQuestion >= questions.size()) {
							triviaOver = true;
						}
					}
				}
				else if (event.type == ::Event::KeyPressed) {
					if (event.key.code == Keyboard::R) {
						cout << correctAnswersCounter << endl;
						points += correctAnswersCounter * 12;
						return;
					}
				}
			}

			window.clear();
			window.draw(background);

			if (!triviaOver) {
				::Font font;
				if (font.loadFromFile("fonts/Squartiqa4F.ttf")) {
					::Text questionText;
					questionText.setFont(font);
					questionText.setCharacterSize(30);
					questionText.setFillColor(::Color::White);
					questionText.setPosition(280, 160);
					questionText.setString("Q. " + questions[currentQuestion]);
					window.draw(questionText);

					displayOptions(window, currentQuestion);
				}
			}
			else {
				Font font;
				if (font.loadFromFile("fonts/Squartiqa4F.ttf")) {
					Text overText;
					Text score;
					overText.setFont(font);
					overText.setCharacterSize(30);
					overText.setFillColor(::Color::White);
					overText.setPosition(500, 270);
					overText.setString("   Trivia Over");
					window.draw(overText);

					score.setFont(font);
					score.setCharacterSize(30);
					score.setFillColor(::Color::White);
					score.setPosition(460, 320);
					score.setString("    Your Score: " + to_string(correctAnswersCounter * 15) + " \n(" + to_string(correctAnswersCounter) + " out of 7 correct)");
					window.draw(score);
				}
			}
			
			window.display();
		}
	}

	void setQuestionsAndAnswers() {
		questions.push_back("In which city were the first\n    modern Olympic Games held in\n    1896?");
		options.push_back({ "1. Paris", "2. Rome", "3. Athens", "4. London" });
		correctAnswers.push_back(2);

		questions.push_back("What is the symbol of the\n    Olympic Games consisting of\n    five interlocking rings of\n    different colors?");
		options.push_back({ "1. Olympic Hoops", "2. World Circles", "3. Linked Rings", "4. Olympic Rings" }); // Correct Answer: D
		correctAnswers.push_back(3);

		questions.push_back("Which country has won the most\n    gold medals in the history of\n    the Summer Olympics?");
		options.push_back({ "1. China", "2. Russia", "3. United States", "4. Germany" }); // Correct Answer: C
		correctAnswers.push_back(2);

		questions.push_back("The Winter Olympic Games were\n    first held in which year?");
		options.push_back({ "1. 1920", "2. 1924", "3. 1932", "4. 1940" }); // Correct Answer: B
		correctAnswers.push_back(1);

		questions.push_back("Who is the only athlete to\n    have won gold medals in both\n    the Summer and Winter Olympics\n    in different sports?");
		options.push_back({ "1. Michael Phelps", "2. Usain Bolt", "3. Simone Biles", "4. Eddie Eagan" }); // Correct Answer: D
		correctAnswers.push_back(3);

		questions.push_back("What is the Olympic motto, which\n    is Latin for \"Faster, Higher,\n    Stronger\"?");
		options.push_back({ "1. Audaces Fortuna Iuvat", "2. Semper Fidelis", "3. Veni, Vidi, Vici", "4. Citius, Altius, Fortius" }); // Correct Answer: D
		correctAnswers.push_back(3);

		questions.push_back("In which year did the Olympic\n    Games have to be canceled due\n    to World War II?");
		options.push_back({ "1. 1936", "2. 1940 and 1944", "3. 1952", "4. 1960" }); // Correct Answer: B
		correctAnswers.push_back(1);

	}

	void displayOptions(::RenderWindow& window,int currentQuestion) {
		::Font font;
		if (!font.loadFromFile("fonts/Squartiqa4F.ttf")) {
			std::cerr << "Error loading font" << std::endl;
			return;
		}

		::Text optionText;
		optionText.setFont(font);
		optionText.setCharacterSize(25);
		optionText.setFillColor(::Color::White);

		for (std::size_t i = 0; i < options[currentQuestion].size(); ++i) {
			optionText.setString(options[currentQuestion][i]);
			optionText.setPosition(280, 300.f + static_cast<float>(i * 50));
			window.draw(optionText);
		}
	}
};

#endif
