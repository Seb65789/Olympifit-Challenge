#include <SFML/Graphics.hpp>
#include "game.h"
using namespace std;

int main() {
	Game g;
    sf::RenderWindow window(sf::VideoMode(1280, 720), "OlmypiFit Challenge");
	g.displayMenu(window);
 
	return 0;
}
