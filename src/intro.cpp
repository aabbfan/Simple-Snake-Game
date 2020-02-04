#include "intro.h"

Intro::Intro()
    : background{}, title{}, subtitle{}, f1{}, f2{}
{
    f1.loadFromFile("./resources/Expo.ttf", 40);
    f2.loadFromFile("./resources/Expo.ttf", 26);
    title.loadFromRenderedText("Wellcome to Snake", f1, SDL_Color{0,0,0,0x0});
    subtitle.loadFromRenderedText("Press any key to continue...", f2, SDL_Color{0,0,0,0});

    background.loadFromFile("./resources/background.png");
}

void Intro::handle_events()
{
    SDL_Event e;

    while (SDL_PollEvent(&e) != 0)
    {
        if (e.type == SDL_QUIT)
            GameState::next_state = GameStates::Quit;
        else if (e.type == SDL_KEYDOWN || e.type == SDL_MOUSEBUTTONUP)
            GameState::next_state = GameStates::Gaming;
    }
}

void Intro::logic() {}

void Intro::render()
{
    mainwindow->clear();
    background.render(0, 0);
    title.render(static_cast<int>((mainwindow->getWidth() - title.getWidth()) / 2),
                 static_cast<int>((mainwindow->getHeight() - title.getHeight()) / 4 * 3));
    subtitle.render(static_cast<int>((mainwindow->getWidth() - subtitle.getWidth()) / 2),
                    static_cast<int>((mainwindow->getHeight() + title.getHeight() - subtitle.getHeight()) / 4 * 3));
    mainwindow->update();
}
