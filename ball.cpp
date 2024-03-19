#include "ball.h"

Ball::Ball() :  xSpeed(1),
                ySpeed(1),
                Ancho(3),
                WallMetric(200)
{




}

Ball::~Ball(){






}

void Ball::create(){

    ballPosition.x = 400;
    ballPosition.y = 300;

    ballBounds.left = 0;
    ballBounds.top = 0;
    ballBounds.width = 16;
    ballBounds.height = 16;

    ballTexture.loadFromFile("data/imgs/ball.png", ballBounds);
    ballTexture.setSmooth(true);

    ballSprite.setTexture(ballTexture);
    ballSprite.setOrigin(8,8);




}

void Ball::update(){

    ballPosition.x += xSpeed;
    ballPosition.y += ySpeed;

    checkWalls(3);

    ballSprite.setPosition(ballPosition);
}

void Ball::draw(sf::RenderWindow* window){


    window->draw(ballSprite);

}

void Ball::checkCollision(Pad _pad){

    bool inPad = (ballPosition.x   > _pad.padPosition.x-(_pad.padHitBox.width/2)-Ancho+1 &&
       ballPosition.y > _pad.padPosition.y-(_pad.padHitBox.height/2)-Ancho+1 &&
       ballPosition.x   < _pad.padPosition.x+(_pad.padHitBox.width/2)+Ancho-1 &&
       ballPosition.y< _pad.padPosition.y+(_pad.padHitBox.height/2)+Ancho-1 );

    if(!inPad){

            //Left Horizontal HitBox

            if(ballPosition.x+xSpeed+8 > _pad.padPosition.x-(_pad.padHitBox.width/2)-Ancho &&
               ballPosition.y+ySpeed+8 > _pad.padPosition.y-(_pad.padHitBox.height/2)    &&
               ballPosition.x+xSpeed-8 < _pad.padPosition.x-(_pad.padHitBox.width/2)       &&
               ballPosition.y+ySpeed-8 < _pad.padPosition.y+(_pad.padHitBox.height/2)
            ){
                xSpeed *=-1;
            }
            //Right Horizontal HitBox
            if(ballPosition.x+xSpeed+8 > _pad.padPosition.x+(_pad.padHitBox.width/2) &&
               ballPosition.y+ySpeed+8 > _pad.padPosition.y-(_pad.padHitBox.height/2)   &&
               ballPosition.x+xSpeed-8 < _pad.padPosition.x+(_pad.padHitBox.width/2)+Ancho     &&
               ballPosition.y+ySpeed-8 < _pad.padPosition.y+(_pad.padHitBox.height/2)
            ){
                xSpeed *=-1;
            }
            //Top Vertical HitBox
            if( ballPosition.x+xSpeed+8 >_pad.padPosition.x-(_pad.padHitBox.width/2) &&
                ballPosition.y+ySpeed+8 > _pad.padPosition.y-(_pad.padHitBox.height/2)-Ancho &&
                ballPosition.x+xSpeed-8 < _pad.padPosition.x+(_pad.padHitBox.width/2)      &&
                ballPosition.y+ySpeed-8 <_pad.padPosition.y-(_pad.padHitBox.height/2)
               ){

                ySpeed *=-1;
            }
                //Bottom Vertical HitBox
            if( ballPosition.x+xSpeed+8 >_pad.padPosition.x-(_pad.padHitBox.width/2) &&
                ballPosition.y+ySpeed+8 > _pad.padPosition.y+(_pad.padHitBox.height/2) &&
                ballPosition.x+xSpeed-8 < _pad.padPosition.x+(_pad.padHitBox.width/2)      &&
                ballPosition.y+ySpeed-8 <_pad.padPosition.y+(_pad.padHitBox.height/2)+Ancho
               ){
                ySpeed *=-1;

            }
       }else{

            xSpeed *= -1;
            ySpeed *= -1;
            for(int i = 0; i < 15; i++){
                ballPosition.x += xSpeed;
                ballPosition.y += ySpeed;
                cout << "Try " << i << endl;
            }
            cout << endl << endl;

       }

}

sf::Vector2f Ball::getPosition(){


    return ballPosition;
}

void Ball::checkWalls(int _nPlayers){


    switch(_nPlayers){

    case 3:
        if( ballPosition.y+ySpeed+8 > 768 - WallMetric){
            ySpeed *= -1;
        }

        if( ballPosition.x+xSpeed+8 > 0 &&
            ballPosition.y+ySpeed+8 > WallMetric &&
            ballPosition.x+xSpeed+8 < WallMetric &&
            ballPosition.y+ySpeed+8 < WallMetric + Ancho
        ){
            ySpeed *= -1;

        }

        if( ballPosition.x+xSpeed+8 > WallMetric &&
            ballPosition.y+ySpeed+8 > 0 &&
            ballPosition.x+xSpeed+8 < WallMetric + Ancho &&
            ballPosition.y+ySpeed+8 < WallMetric
        ){

            xSpeed *= -1;
        }


        if( ballPosition.x+xSpeed+8 > 1024-WallMetric-Ancho &&
            ballPosition.y+ySpeed+8 > 0 &&
            ballPosition.x+xSpeed+8 < 1024-WallMetric &&
            ballPosition.y+ySpeed+8 < WallMetric
        ){

            xSpeed *= -1;
        }

        if( ballPosition.x+xSpeed+8 > 1024-WallMetric &&
            ballPosition.y+ySpeed+8 > WallMetric &&
            ballPosition.x+xSpeed+8 < 1024 &&
            ballPosition.y+ySpeed+8 < WallMetric+Ancho
        ){

            ySpeed *= -1;
        }





        break;

    case 4:

        if( ballPosition.x > 0 && ballPosition.y > 0 && ballPosition.x < 100 && ballPosition.y < 100
        ||  ballPosition.x > 1024-100 && ballPosition.y > 0 && ballPosition.x < 1024 && ballPosition.y < 100
        ||  ballPosition.x > 0 && ballPosition.y > 768-100 && ballPosition.x < 100 && ballPosition.y < 768
        ||  ballPosition.x > 1024-100 && ballPosition.y > 768-100 && ballPosition.x < 1024 && ballPosition.y < 768){


        }

        break;

    case 2:

        if( ballPosition.y+ySpeed < WallMetric || ballPosition.y+ySpeed > 768-WallMetric-8){

            ySpeed *= -1;
        }

        if( ballPosition.x+xSpeed < WallMetric+8 || ballPosition.x+xSpeed > 1024-WallMetric-8){
            xSpeed *= -1;

        }

        break;

    }

    if(ballPosition.x < 0 || ballPosition.y < 0 || ballPosition.x > 1024 || ballPosition.y > 768){

        ballPosition.x = 1024/2;
        ballPosition.y = 768/2;
        xSpeed *= -1;
        ySpeed *= -1;

    }

}

