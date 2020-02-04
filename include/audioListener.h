#ifndef AUDIOLISTENER_H_
#define AUDIOLISTENER_H_
#include "listener.h"
#include "music.h"

class AudioListener : public Listener
{
public:
    AudioListener();
    ~AudioListener();

    static AudioListener* getInstance();
    virtual bool isAccept(ListenEventType e) noexcept override;
    virtual void work(ListenEventType e, std::vector<void*> argv) override;
private:
    Sound eat;
    Sound lost;

    static AudioListener* ptr_audioListener;
};
#endif