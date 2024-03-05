#pragma once
#include <allegro5/allegro.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <string>

class SoundManager {
private:
    ALLEGRO_SAMPLE_INSTANCE* sampleInstance;

public:
    SoundManager();
    ~SoundManager();

    void playSound(const std::string& filePath);
};