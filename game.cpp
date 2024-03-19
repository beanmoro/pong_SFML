#include "game.h"

Game::Game() :  scrWidth(1024),
                scrHeight(768),
                gState(PLAY),
                nPlayer(3),
                WallMetric(200)
                {


}

Game::~Game(){



}

void Game::run(){
    initSystems();

    gameLoop();

}


void Game::initSystems(){

    gWindow.create(sf::VideoMode(scrWidth, scrHeight), "Ping Pong");
    player0.create(LOCAL, VER);
    player1.create(AI, VER);
    player2.create(AI, HOR);
    ball.create();

    playerControl0.key[0] = sf::Keyboard::A;
    playerControl0.key[1] = sf::Keyboard::W;
    playerControl0.key[2] = sf::Keyboard::D;
    playerControl0.key[3] = sf::Keyboard::S;

    playerControl1.key[0] = sf::Keyboard::Left;
    playerControl1.key[1] = sf::Keyboard::Up;
    playerControl1.key[2] = sf::Keyboard::Right;
    playerControl1.key[3] = sf::Keyboard::Down;

    player0.setPlayerControl(playerControl0.key);
    player1.setPlayerControl(playerControl1.key);

    player0.setPosition(sf::Vector2f(WallMetric, 384));
    player1.setPosition(sf::Vector2f(1024-WallMetric, 384));
    player2.setPosition(sf::Vector2f(1024/2, WallMetric));


}

void Game::gameLoop(){

    while(gState != EXIT){

        inputEvents();
        player0.update(ball.getPosition());
        player1.update(ball.getPosition());
        player2.update(ball.getPosition());
        ball.update();
        ball.checkCollision(player0);
        ball.checkCollision(player1);
        ball.checkCollision(player2);
        drawGame();
    }
    cout << "GAME OVER!" << endl;

}

void Game::inputEvents(){
    sf::Event e;

    while(gWindow.pollEvent(e)){
        if(e.type == sf::Event::Closed){
            gState = EXIT;
        }

    }


}

void Game::drawGame(){
    gWindow.clear(sf::Color::Black);
    player0.draw(&gWindow);
    player1.draw(&gWindow);
    player2.draw(&gWindow);
    ball.draw(&gWindow);
    gWindow.display();
}
