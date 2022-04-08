#ifndef AUDIOLISTENER_H_
#define AUDIOLISTENER_H_
#include "listener.h"

class Sound;
enum AudioType
{
    AUDIO_TYPE_EAT = 0,
    AUDIO_TYPE_LOST
};

class AudioListener : public Listener
{
public:
    AudioListener(AudioType type);
    ~AudioListener();

    virtual void update();
    
private:
    Sound* sound;
};
#endif