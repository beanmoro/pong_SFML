#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include "includes.h"

#include "pad.h"
#include "ball.h"

enum GameState {PLAY, EXIT};

class Game {

public:
    Game();
    ~Game();

    void run();

private:

    void initSystems();
    void gameLoop();
    void inputEvents();
    void drawGame();

    int scrWidth, scrHeight;
    GameState gState;

    sf::RenderWindow gWindow;

    int nPlayer;

    int WallMetric;
    Pad player0, player1, player2;
    Ball ball;

    struct PlayerControls{

        sf::Keyboard::Key key[4];

    }playerControl0, playerControl1, playerControl2, playerControl3;







};




#endif // GAME_H_INCLUDED
