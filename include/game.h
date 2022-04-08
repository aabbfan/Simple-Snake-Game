#ifndef GAME_H_
#define GAME_H_
#include "gamestate.h"
#include "texture.h"
#include "utils.h"
#include "font.h"
#include <list>

enum GameResultType
{
    gaming,
    lost,
    won
};

class Node;
class Food;
class CollisionListener;
class AudioListener;
class Object;
class Game : public GameState
{
public:
    virtual void handle_events() override;
    virtual void logic() override;
    virtual void render() override;

    Game();
    ~Game();
    Game(const Game&) = delete;
    Game(Game&&) = default;

    void snakeMove(); // control the move of the snake
    void snakeIncrease();

    void setGameLost();
    void addFood();
    void snakeCollideFood(std::shared_ptr<Food> _food);
private:
    Texture background;  // backgroud of the game
    Texture titleLost;  // be shown on the screen after player won or failed the game
    Font font4TitleLost;
    std::list<Node*> snake;
    std::list<std::shared_ptr<Food>> food;
    GameResultType gameResult;

    int speed;

    int direction; // define that direction angle range
                     // is -180 ~ 180. 0 is right, 90 is up etc.
    Uint32 fpsTimer;
    const Uint8 fps = 21;

    // functions =======
    void snakeRender();
    void foodRender();
    void lostRender();
    Pos calculateNextHeadPos(Pos head_pos);
    void handleOperatingEvents(SDL_Event e);
    virtual void controlFPS();

    // listeners
    std::shared_ptr<AudioListener> foodSoundListener;
    std::shared_ptr<AudioListener> lostSoundListener;
    std::shared_ptr<CollisionListener> collisionListener;

    std::shared_ptr<Object> lostGameAudio;
    std::shared_ptr<Object> fakeHead; // to check if the snake bump into foods
};

#endif