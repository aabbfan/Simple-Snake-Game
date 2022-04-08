#include "audioListener.h"
#include "music.h"

AudioListener::AudioListener(AudioType type) : Listener()
{
    switch(type)
    {
    case AUDIO_TYPE_EAT:
        sound = new Sound("./resources/eat.wav");
        break;
    case AUDIO_TYPE_LOST:
        sound = new Sound("./resources/lost.wav");
    default:
        break;
    }
}

AudioListener::~AudioListener()
{
    delete sound;
}

void AudioListener::update()
{
    sound->play();
}

