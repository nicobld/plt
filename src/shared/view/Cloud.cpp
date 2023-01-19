#include "Cloud.h"
#include <iostream>
#include <random>


namespace view
{

Cloud::Cloud(sf::Texture cloudTexture, bool home) : cloudTexture(cloudTexture), home(home){
    cloudSprite = new sf::Sprite(this->cloudTexture, sf::IntRect(236 * rand() % 4, 0, 236, 88));
    isHover = false;
    // x =  rand()%1280;
    // y = rand()%175;
    // if(rand()%2)
    //     y += 575;

    std:: minstd_rand rand_mins;
    rand_mins.seed(rand());

    x = rand_mins()%1280;
    if(this->home)
        y = rand_mins()%720;
    else{
        y = rand_mins()%175;
        if(rand_mins()%2)
            y += 575;
    }

    cloudSprite->setPosition(x, y);

    while(speed < 0.1){
        speed = rand_mins()%20;
        speed = (float) speed;
        speed/= 100;
    }

    cloudSprite->setScale(sf::Vector2f(speed/0.15, speed/0.15));
}

void Cloud::update(){
    x += speed;
    if(x> 1280){
        x = - cloudSprite->getGlobalBounds().width;
        // y = rand()%175;
        // if(rand()%2)
        //     y += 575;

        std:: minstd_rand rand_mins;
        rand_mins.seed(rand());

        if(home)
            y = rand_mins()%720;
        else{
            y = rand_mins()%175;
            if(rand_mins()%2)
                y += 575;
        }
    }

    cloudSprite->setPosition((int)x, y);
    
    int opacity = 210;
    if(!home){
        if(isHover)
            cloudSprite->setColor(sf::Color(255, 255, 255, opacity));
        else    
            cloudSprite->setColor(sf::Color(255, 255, 255, 255));
    }
}

void Cloud::render(sf::RenderTarget& target){
    update();
    target.draw(*cloudSprite);
}

void Cloud::hover(int x, int y){
    if(cloudSprite->getGlobalBounds().contains(x, y))
        isHover = true;
    else
        isHover = false;
}


}
