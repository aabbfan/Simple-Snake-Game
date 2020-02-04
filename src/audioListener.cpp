#include "audioListener.h"

AudioListener* AudioListener::ptr_audioListener = nullptr;

AudioListener::AudioListener()
              : eat("./resources/eat.wav"), lost("./resources/lost.wav")
{

}

AudioListener::~AudioListener()
{
}

AudioListener* AudioListener::getInstance()
{
    if (AudioListener::ptr_audioListener == nullptr)
    {
        AudioListener::ptr_audioListener = new AudioListener();
    }
    return AudioListener::ptr_audioListener;
}

bool AudioListener::isAccept(ListenEventType e) noexcept
{
    if (e == ListenEventType::collideFood) return true;
    if (e == ListenEventType::collideWall) return true;
    return false;
}

void AudioListener::work(ListenEventType e, std::vector<void*> argv)
{
    if (e == ListenEventType::collideFood)
    {
        eat.play();
    }

    if (e == ListenEventType::collideWall)
    {
        lost.play();
    }
}
