#ifndef BALL_H_INCLUDED
#define BALL_H_INCLUDED

#include "includes.h"
#include "pad.h"

class Ball{

public:
    Ball();
    ~Ball();

    void create();
    void update();
    void draw(sf::RenderWindow* window);
    void checkCollision(Pad _pad);
    void checkWalls(int _nPlayers);

    sf::Vector2f getPosition();

private:

    sf::Vector2f ballPosition;
    sf::IntRect ballBounds;

    sf::Texture ballTexture;
    sf::Sprite ballSprite;

    int xSpeed, ySpeed;
    int Ancho;
    int WallMetric;
};


#endif // BALL_H_INCLUDED
