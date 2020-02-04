#include "game.h"
#include "mainwindow.h"
#include "node.h"
#include "food.h"
#include "gameListener.h"
#include <SDL.h>
#include <cmath>
#include <cstdlib>
#include <iostream>

Game::Game() : background()
{
    background.loadFromFile("./resources/background.png");
    font4TitleLost.loadFromFile("./resources/Expo.ttf", 40);
    titleLost.loadFromRenderedText("You have lost the game", font4TitleLost, SDL_Color{0,0,0,0x0});

    // create snake ==============================
    // create snake's head
    Node* head = new Node(mainwindow->windowMiddleX, mainwindow->windowMiddleY, purple);
    head->setHead();
    snake.push_back(head);

    speed = 1;
    direction = 90;
    head->setdirection(direction);
    for (int i = 0; i < 5; i++) snakeIncrease();
    // ===============================================

    GameListener::getInstance()->bindGame(this);
    gameResult = GameResultType::gaming;
}

Game::~Game()
{
    for (auto i : snake)
    {
        delete i;
    }

    for (auto i : food)
    {
        delete i;
    }
}

void Game::handle_events()
{
    SDL_Event e;

    while (SDL_PollEvent(&e) != 0)
    {
        if (e.type == SDL_QUIT)
            GameState::next_state = GameStates::Quit;
        else if(e.type == SDL_KEYDOWN)
        {
            handleOperatingEvents(e);
        }
        
    }
}

void Game::logic()
{
    if (gameResult != GameResultType::won && gameResult != GameResultType::lost)
    {
        snakeMove();
        addFood();
    }
}

void Game::render()
{
    mainwindow->clear();

    background.render(0, 0);

    snakeRender();
    foodRender();

    if (gameResult == GameResultType::lost) lostRender();  
    mainwindow->update();
}

void Game::snakeRender()
{
    for (auto& i : snake)
    {
        i->render();
    }
}

Pos Game::calculateNextHeadPos(Pos head_pos)
{
    using namespace std;

    const float pi = 3.1415926;

    int radius = snake.front()->getRadius();
    Pos new_pos;
    new_pos.x = head_pos.x + radius * speed * cos(direction * pi / 180);
    new_pos.y = head_pos.y - radius * speed * sin(direction * pi / 180);

    return new_pos;
}

/*
 * method : pop the last node and push a new head, so the snake moves
 */
void Game::snakeMove()
{
    snakeIncrease();    // snake increase (add head)
    auto it = snake.end();
    it--;   // now this is the last node

    delete *it;
    snake.pop_back();   // delete the last node
                        // so the snake moves
    snake.front()->notify(Object_moved);    // notify listeners snake moves
}

void Game::handleOperatingEvents(SDL_Event e)
{
    switch (e.key.keysym.sym)
    {
    case SDLK_LEFT:
        direction += 30;
        formatAngle(direction);
        break;
    
    case SDLK_RIGHT:
        direction -= 30;
        formatAngle(direction);
        break;

    case SDLK_a:
        direction += 30;
        formatAngle(direction);
        break;
    
    case SDLK_d:
        direction -= 30;
        formatAngle(direction);
        break;
    default:
        break;
    }
}

void Game::snakeIncrease()
{
    // calculate the position of snake's head
    auto it = snake.begin();
    Pos new_head_pos = calculateNextHeadPos((*it)->getPos());

    // push a dummy at last of que first
    Node* dummy = new Node(new_head_pos.x, new_head_pos.y, purple);
    snake.push_back(dummy);

    // convert pre_head to bodynode
    ColorType tmp_ = (*(++it))->getColor(); // the second node
    it--;   // the first node
    (*it)->cancelHead(tmp_);
    
    snake.pop_back();   // pop the dummy

    dummy->setHead();
    dummy->setdirection(direction);
    snake.push_front(dummy);    // push front dummy(head) so
                                // so, the snake increase
}

void Game::controlFPS()
{
    Uint8 local_fps = 1000 / fps;
    if (SDL_GetTicks() - fpsTimer < local_fps)
    {
        SDL_Delay(local_fps-SDL_GetTicks()+fpsTimer);
    }
    fpsTimer = SDL_GetTicks();
}

void Game::lostRender()
{
    titleLost.render(static_cast<int>((mainwindow->getWidth() - titleLost.getWidth()) / 2),
                 static_cast<int>((mainwindow->getHeight() - titleLost.getHeight()) / 4 * 3));
    mainwindow->update();
    GameState::next_state = GameStates::Intro;

    SDL_Delay(3000);

    // to clear the keyboard buffer
    SDL_Event e;
    while (SDL_PollEvent(&e) != 0)
    {
        if (e.type == SDL_QUIT)
            GameState::next_state = GameStates::Quit; 
    }

    SDL_Delay(1000);
}

void Game::setGameLost()
{
    gameResult = GameResultType::lost;
}

void Game::foodRender()
{
    for (auto i : food)
    {
        i->render();
    }
}

void Game::addFood()
{
    // get random number
    int rand_num = rand() % 40;

    if (rand_num >= 39)
    {
        Food* tmp_ = new Food();
        food.push_back(tmp_);
        tmp_->notify(ObjectEvent::Object_show);
    }
}

void Game::snakeCollideFood(Food* _food)
{
    snakeIncrease();    // increase the snake
    
    // romve the food
    for (auto it = food.begin(); it != food.end(); it++)
    {
        if (*it == _food)
        {
            _food->notify(ObjectEvent::Object_disppear);
            delete _food;
            food.erase(it);
            break;
        }
    }
}