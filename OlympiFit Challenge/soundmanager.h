#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H

#include <SFML/Audio.hpp>
#include <unordered_map>
#include <iostream>
#include <string>
using namespace std;
using namespace sf;

//to manage sound effects and music
class SoundManager {
private:
    SoundBuffer buffer;
    Sound sound;

public:
    SoundManager(string filePath) {
        buffer.loadFromFile("music/background.mp3");
        sound.setBuffer(buffer);
    }

    //play a loaded sound
    void playSound() {
        sound.play();
    }

    void setLoop() {
        sound.setLoop(1);
    }

    void setVolume(float volume) {
        sound.setVolume(volume);
    }

    ~SoundManager() = default;

};

#endif
