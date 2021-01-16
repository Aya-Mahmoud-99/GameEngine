//
// Created by Aya on 1/15/2021.
//

#include "Sound.h"
#include <bass.h>
#include <iostream>
bool Sound::audio_device=false;
Sound::Sound(const char *fileName,bool loop) {
    if(!audio_device){
       if(!BASS_Init(-1,44100,0,NULL,NULL)){
            std::cout<<"Error loading file"<<std::endl;
        }
        audio_device=true;
    }
    if(loop)channel=BASS_StreamCreateFile(false,fileName,0,0,BASS_SAMPLE_LOOP);
    if(!loop)channel=BASS_StreamCreateFile(false,fileName,0,0,BASS_SAMPLE_FLOAT);
    if(!channel){
        std::cout<<"No Channel"<<std::endl;
    }
}
Sound::~Sound() {
    BASS_Free();
}
void Sound::play() {
    BASS_ChannelPlay(channel,false);
}
void::Sound::pause(){
   BASS_ChannelPause(channel);
}
void Sound::stop() {
   BASS_ChannelStop(channel);
}
