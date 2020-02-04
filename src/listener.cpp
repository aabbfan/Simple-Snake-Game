#include "listener.h"

Listener::Listener()
{
    g_ListenerList.push_back(this);
}

bool Listener::isAccept(ListenEventType e) noexcept
{
    return false;
}

void Listener::work(ListenEventType e, std::vector<void*> argv)
{

}

void Listener::notify(ListenEventType e, std::vector<void*> argv)
{
    for (auto i : g_ListenerList)
    {
        if (i->isAccept(e) == false) continue;
        i->work(e, argv);
    }
}

std::vector<Listener*> g_ListenerList = { };
