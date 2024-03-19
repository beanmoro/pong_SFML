
#ifndef PAD_H_INCLUDED
#define PAD_H_INCLUDED

#include "includes.h"



enum InputType {LOCAL, NET, AI};
enum PlaySide {HOR, VER};

class Pad{

public:

    Pad();
    ~Pad();

    void create(InputType inType, PlaySide pSide);
    void update(sf::Vector2f ballVector);
    void draw(sf::RenderWindow* window);

    sf::Vector2f padPosition;
    sf::IntRect padHitBox;

    void setPlayerControl(sf::Keyboard::Key Keys[]);
    void setPosition(sf::Vector2f _pos);

private:
    void localMotion();
    void netMotion();
    void aiMotion(sf::Vector2f ballVector);

    sf::IntRect padBounds;

    int padSpeed;

    InputType padInputType;
    sf::Sprite padSprite;
    sf::Texture padTexture;

    PlaySide padSide;

    float padVelocity, padAceleration, padFriction;
    float padDefaultSpeed;

    //Only for local

    sf::Keyboard::Key keyLeft, keyUp, keyRight, keyDown;
    bool mLeft, mUp, mRight, mDown;

    int WallMetric;



};



#endif // PAD_H_INCLUDED
