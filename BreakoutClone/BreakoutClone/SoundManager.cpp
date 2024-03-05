#include "SoundManager.h"



SoundManager::SoundManager() : sampleInstance(nullptr) {

    al_install_audio();
    al_init_acodec_addon();
    al_reserve_samples(1); // Reserve one sample instance
}

SoundManager::~SoundManager() {
    if (sampleInstance) {
        al_destroy_sample_instance(sampleInstance);
    }
    al_uninstall_audio();
}

void SoundManager::playSound(const std::string& filePath) {
    ALLEGRO_SAMPLE* sample = al_load_sample(filePath.c_str());
    if (!sample) {
        return;
    }


    // Create a new sample instance for playback
    ALLEGRO_SAMPLE_INSTANCE* sampleInstance = al_create_sample_instance(sample);
    al_set_sample_instance_playmode(sampleInstance, ALLEGRO_PLAYMODE_ONCE);
    al_attach_sample_instance_to_mixer(sampleInstance, al_get_default_mixer());

    // Play the sample
    al_play_sample_instance(sampleInstance);

    // Wait until the sample finishes playing
    while (al_get_sample_instance_playing(sampleInstance)) {
        // Sleep or yield the CPU to avoid busy-waiting
        // You may want to replace this with a more efficient waiting mechanism
        al_rest(0.01); // Adjust the sleep time as needed
    }

    // Unload the sample and sample instance after playback
    al_destroy_sample(sample);
    al_destroy_sample_instance(sampleInstance);
}
