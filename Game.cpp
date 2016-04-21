#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <iostream>
#include <ctime>
#include "menu.h"



using namespace std;

extern "C" { void asm_main(); 
			 int asm_score(int); 
			 void PlayGame(); }

int main() {
	asm_main();
}

int main()
{
    //game window
    sf::RenderWindow window(sf::VideoMode (640,480), "Breakout!");
    //game menu screen 
   // menu Menu(window.getSize().x, window.getSize().y);
   
   //declaring objects such as ball and paddle
    sf::RectangleShape bricks[500];
    sf::CircleShape ball(8.f);
    //using a 2 dimisional vector instead of array because its abilty to add beyond it size
    sf::RectangleShape paddle(sf::Vector2f(60, 10));
    
    sf::Font font;
    font.loadFromFile("LemonMilk.otf");
    sf::Text scoreBox("0", font);
    scoreBox.setPosition(sf::Vector2f(0,455));
    scoreBox.setCharacterSize(25);
    scoreBox.setColor(sf::Color::Green);

    paddle.setFillColor(sf::Color::Blue);//paddle is now blue
    ball.setFillColor(sf::Color::Red);//ball is now red 

    paddle.setPosition((window.getSize().x / 2) - (paddle.getSize().x / 2), window.getSize().y - (30 + paddle.getSize().y));
    ball.setPosition(paddle.getPosition().x, paddle.getPosition().y - 30);// using the paddle postition to determine where the ball is placed.

    sf::Vector2f ballSpeed(0.9f,0.9f); //sets ball speed

    //define sides
    sf::RectangleShape top;
    sf::RectangleShape bottom;
    sf::RectangleShape leftSide;
    sf::RectangleShape rightSide;
    //side properties
    leftSide.setSize(sf::Vector2f(0.1, 640));
    leftSide.setFillColor(sf::Color::White);
    leftSide.setPosition(sf::Vector2f(0,0));

    rightSide.setSize(sf::Vector2f(0.1, 640));
    rightSide.setFillColor(sf::Color::White);
    rightSide.setPosition(sf::Vector2f(640,0));

    bottom.setSize(sf::Vector2f(640, 0.1));
    bottom.setFillColor(sf::Color::White);
    bottom.setPosition(sf::Vector2f(0,479));

    top.setSize(sf::Vector2f(640, 0.1));
    top.setFillColor(sf::Color::White);
    top.setPosition(sf::Vector2f(0,0));
    //creating the brick properties 
    for (int i = 0; i < 500; i++)
    {
        bricks[i].setFillColor(sf::Color::Blue);
        bricks[i].setSize(sf::Vector2f(32, 12));
        bricks[i].setOutlineColor(sf::Color::Black);
        bricks[i].setOutlineThickness(1.f);

	}
	
       //Displays Bricks 
     for ( int i = 0; i < 10; i++)
    {
        bricks[i+200].setPosition(0,i*13);
	  
        for(int j = i*20+1; j < 20+i*20; j++)
        {
            bricks[j].setPosition(bricks[j-1].getPosition().x + bricks[j].getSize().x, i*13);
		
        }
	   
	  
    }

    ball.setPosition(paddle.getPosition()); //the ball will start where the paddle is

    while(window.isOpen()) //game loop
    {
        sf::Event Event;
        while(window.pollEvent(Event))
        {
            switch (Event.type)
            {
            case sf::Event::Closed:
                window.close();
                break;
            }
        }

       //using the mouse movement to control the paddle.
        if (sf::Mouse::getPosition(window).x > 0 && sf::Mouse::getPosition(window).x < (window.getSize().x - paddle.getSize().x))
            paddle.setPosition(sf::Mouse::getPosition(window).x, paddle.getPosition().y);
	 //this for loop handles the brick/ball collison 
        for (int i = 0; i < 500; i++)
        {
            if(bricks[i].getGlobalBounds().intersects(ball.getGlobalBounds()))
            {
                ballSpeed.y = -ballSpeed.y; //change direction of movement

                bricks[i].setSize(sf::Vector2f(0,0));//brick that has been hit goes away
				score = asm_score(score);
				string s = to_string(score);
				scoreBox.setString(s);
                i = 499;   //terminates loop when all bricks are hit
            }
        }
	  //series of if statments helps the ball stay within the game window.
        if(top.getGlobalBounds().intersects(ball.getGlobalBounds()))
        {
            ballSpeed.y = - ballSpeed.y;
        }

        if(bottom.getGlobalBounds().intersects(ball.getGlobalBounds()))
        {
            ballSpeed.y = - ballSpeed.y;
            ball.setPosition(paddle.getPosition());
        }

        if(leftSide.getGlobalBounds().intersects(ball.getGlobalBounds()))
        {
            ballSpeed.x = - ballSpeed.x;
        }

        if(rightSide.getGlobalBounds().intersects(ball.getGlobalBounds()))
        {
            ballSpeed.x = - ballSpeed.x;
        }
        //this if stament handles the paddle/ball collison
        if(paddle.getGlobalBounds().intersects(ball.getGlobalBounds()))
        {
            ballSpeed.y = -ballSpeed.y; //change direction
        }

        ball.move(ballSpeed.x, ballSpeed.y);
	     
        window.clear(sf::Color::White);

	    
        for (unsigned i = 0; i < 250; i++)
        {
            window.draw(bricks[i]);
        }
	  // Menu.draw(window);
	   //drawing objects to window.
        window.draw(top);
        window.draw(bottom);
        window.draw(leftSide);
        window.draw(rightSide);
        window.draw(paddle);
        window.draw(ball);
        window.draw(scoreBox);
        window.display();

		
    }
	
}
