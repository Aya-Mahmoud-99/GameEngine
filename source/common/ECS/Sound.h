//
// Created by Aya on 1/15/2021.
//

#ifndef GFX_LAB_SOUND_H
#define GFX_LAB_SOUND_H


class Sound {

private:
    unsigned int channel;
    static bool audio_device;
public:
    Sound(const char* fileName,bool loop);
    ~Sound();
    void play();
    void stop();
    void pause();
};


#endif //GFX_LAB_SOUND_H
