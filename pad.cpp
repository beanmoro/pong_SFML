#include "pad.h"

Pad::Pad() :    padVelocity(0.0f),
                padAceleration(0.0f),
                padFriction(0.1f),
                WallMetric(200)


    {



}

Pad::~Pad(){




}

void Pad::create(InputType inType, PlaySide pSide){

    padInputType = inType;
    padSide = pSide;

    padPosition.x = 512;
    padPosition.y = 200;
    padBounds.left = 0;
    padBounds.top = 0;
    padBounds.width = 16;
    padBounds.height = 64;

    if(!padTexture.loadFromFile("data/imgs/pad.png", padBounds)){
        cout << "ERROR CARGANDO LA IMAGEN DEL PAD!" << endl;
    }
    padTexture.setSmooth(true);

    padSprite.setTexture(padTexture);
    padSprite.setOrigin(8,32);

    if(padSide == HOR){
        padSprite.setRotation(90);
        padHitBox.width = padBounds.height;
        padHitBox.height = padBounds.width;
    }else{
        padSprite.setRotation(0);
        padHitBox.width = padBounds.width;
        padHitBox.height = padBounds.height;
    }
}

void Pad::update(sf::Vector2f ballVector){

    switch(padInputType){
    case LOCAL:
        localMotion();
        break;
    case NET:
        netMotion();
        break;
    default:
        aiMotion(ballVector);
        break;
    }

    padSprite.setPosition(padPosition);
}

void Pad::localMotion(){

    padVelocity += padAceleration - (padFriction*padVelocity);

    if(padSide == HOR){

        if( sf::Keyboard::isKeyPressed(keyLeft) ){mLeft = true;}else{mLeft = false;};
        if( sf::Keyboard::isKeyPressed(keyRight) ){mRight = true;}else{mRight = false;};

        if(mLeft){
            padAceleration = -0.25;
        }else if(mRight){
            padAceleration = 0.25;
        }else{
            padAceleration = 0;
        }



        padPosition.x += padVelocity;


    }else if(padSide == VER){

        if( sf::Keyboard::isKeyPressed(keyUp) ){mUp = true;}else{mUp = false;}
        if( sf::Keyboard::isKeyPressed(keyDown) ){mDown = true;}else{mDown = false;}

        if(mUp  ){
            padAceleration = -0.25;
        }else if(mDown ){
            padAceleration = 0.25;
        }else{
            padAceleration = 0;
        }

        if(padPosition.y-(padBounds.height/2)-padAceleration < WallMetric){

            padPosition.y = WallMetric+(padBounds.height/2)+padAceleration;

        }else if(padPosition.y+(padBounds.height/2)+padVelocity > 768-WallMetric){
            padPosition.y = 768-WallMetric-(padBounds.height/2)-padVelocity;
        }


        padPosition.y += padVelocity;


    }




}

void Pad::netMotion(){




}

void Pad::aiMotion(sf::Vector2f ballVector){

    padVelocity += padAceleration - (padFriction*padVelocity);
    if(padSide == HOR){

        if(ballVector.x < padPosition.x){

            padAceleration = -0.25;
        }else if(ballVector.x > padPosition.x){

            padAceleration = 0.25;
        }else{

            padAceleration = 0;
        }

        if(padPosition.x-(padBounds.width)-padVelocity < WallMetric){

            padPosition.x = WallMetric+(padBounds.width)+padVelocity;

        }else if(padPosition.x+(padBounds.width)+padVelocity > 1024-WallMetric){

            padPosition.x = 1024-WallMetric-(padBounds.width)-padVelocity;
        }



        padPosition.x += padVelocity;

    }else if(padSide == VER){

        if(ballVector.y > padPosition.y-(padBounds.height/2) && ballVector.y < padPosition.y+(padBounds.height/2)){

            padAceleration = 0;

        }else if(ballVector.y < padPosition.y){

            padAceleration -= 0.1;
        }else if(ballVector.y > padPosition.y){

            padAceleration += 0.1;
        }

        if(padPosition.y-(padBounds.height)-padVelocity < WallMetric){

            padPosition.y = WallMetric+(padBounds.height)+padVelocity;

        }else if(padPosition.y+(padBounds.height)+padVelocity > 768-WallMetric){

            padPosition.y = 768-WallMetric-(padBounds.height)-padVelocity;
        }

        padPosition.y += padVelocity;
    }

}

void Pad::draw(sf::RenderWindow* window){

    window->draw(padSprite);

}

void Pad::setPlayerControl(sf::Keyboard::Key Keys[]){
    keyLeft = Keys[0];
    keyUp = Keys[1];
    keyRight = Keys[2];
    keyDown = Keys[3];

}

void Pad::setPosition(sf::Vector2f _pos){

    padPosition.x = _pos.x;
    padPosition.y = _pos.y;
}
