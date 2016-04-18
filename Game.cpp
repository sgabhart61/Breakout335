#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <iostream>
#include <ctime>

using namespace std;

extern "C" { void asm_main(); 
			 int asm_score(int); 
			 void PlayGame(); }

int main() {
	asm_main();
}

void PlayGame()
{
	int score = 0;
	
    //game window
    sf::RenderWindow window(sf::VideoMode (640,480), "Breakout (Assembly and C++ Version)");

   //declairing objects brick, ball,and paddle
    sf::RectangleShape bricks[500];
    sf::CircleShape ball(8.f);
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

    sf::Vector2f ballSpeed(0.5f,0.5f); //sets ball speed

    //define sides
    sf::RectangleShape top;
    sf::RectangleShape bottom;
    sf::RectangleShape left;
    sf::RectangleShape right;

    //side properties
    left.setSize(sf::Vector2f(0.1, 640));
    left.setFillColor(sf::Color::White);
    left.setPosition(sf::Vector2f(0,0));

    right.setSize(sf::Vector2f(0.1, 640));
    right.setFillColor(sf::Color::White);
    right.setPosition(sf::Vector2f(640,0));

    bottom.setSize(sf::Vector2f(640, 0.1));
    bottom.setFillColor(sf::Color::White);
    bottom.setPosition(sf::Vector2f(0,479));

    top.setSize(sf::Vector2f(640, 0.1));
    top.setFillColor(sf::Color::White);
    top.setPosition(sf::Vector2f(0,0));
    //creating the brick properties 
    for (unsigned i = 0; i < 500; i++)
    {
        bricks[i].setFillColor(sf::Color::Blue);
        bricks[i].setSize(sf::Vector2f(32, 12));
        bricks[i].setOutlineColor(sf::Color::Black);
        bricks[i].setOutlineThickness(1.f);


        if (i == 0)
        {
            bricks[i].setPosition(0, 0);
        }
        else if (i < 50)
        {
            bricks[i].setPosition(bricks[i-1].getPosition().x + bricks[i].getSize().x, 0);
        }
        else if (i==50)
        {
            bricks[i].setPosition(0, 0+bricks[i].getSize().y);
        }
        else if (i > 50 && i < 100)
        {
            bricks[i].setPosition(bricks[i-1].getPosition().x + bricks[i].getSize().x, bricks[i-1].getPosition().y);
        }
        else if (i==100)
        {
            bricks[i].setPosition(0, 12+bricks[i].getSize().y);
        }
        else if (i > 100 && i < 150)
        {
            bricks[i].setPosition(bricks[i-1].getPosition().x + bricks[i].getSize().x, bricks[i-1].getPosition().y);
        }
        else if (i==150)
        {
            bricks[i].setPosition(0, 24+bricks[i].getSize().y);
        }
        else if (i > 150 && i < 200)
        {
            bricks[i].setPosition(bricks[i-1].getPosition().x + bricks[i].getSize().x, bricks[i-1].getPosition().y);
        }

        else if (i==200)
        {
            bricks[i].setPosition(0, 36+bricks[i].getSize().y);
        }
        else if (i > 200 && i < 250)
        {
            bricks[i].setPosition(bricks[i-1].getPosition().x + bricks[i].getSize().x, bricks[i-1].getPosition().y);
        }
        else if (i==250)
        {
            bricks[i].setPosition(0, 48+bricks[i].getSize().y);
        }
        else if (i > 250 && i < 300)
        {
            bricks[i].setPosition(bricks[i-1].getPosition().x + bricks[i].getSize().x, bricks[i-1].getPosition().y);
        }
        else if (i==300)
        {
            bricks[i].setPosition(0, 60+bricks[i].getSize().y);
        }
        else if (i > 300 && i < 350)
        {
            bricks[i].setPosition(bricks[i-1].getPosition().x + bricks[i].getSize().x, bricks[i-1].getPosition().y);
        }
        else if (i==350)
        {
            bricks[i].setPosition(0, 72+bricks[i].getSize().y);
        }
        else if (i > 350 && i < 400)
        {
            bricks[i].setPosition(bricks[i-1].getPosition().x + bricks[i].getSize().x, bricks[i-1].getPosition().y);
        }
        else if (i==400)
        {
            bricks[i].setPosition(0, 84+bricks[i].getSize().y);
        }
        else if (i > 400 && i < 450)
        {
            bricks[i].setPosition(bricks[i-1].getPosition().x + bricks[i].getSize().x, bricks[i-1].getPosition().y);
        }
        else if (i==450)
        {
            bricks[i].setPosition(0, 96+bricks[i].getSize().y);
        }
        else if (i > 450 && i < 500)
        {
            bricks[i].setPosition(bricks[i-1].getPosition().x + bricks[i].getSize().x, bricks[i-1].getPosition().y);
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

       //using the mousemovement to control the paddle.
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

        if(left.getGlobalBounds().intersects(ball.getGlobalBounds()))
        {
            ballSpeed.x = - ballSpeed.x;
        }

        if(right.getGlobalBounds().intersects(ball.getGlobalBounds()))
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


        for (unsigned i = 0; i < 500; i++)
        {
            window.draw(bricks[i]);
        }
	   //drawing objects to window.
        window.draw(top);
        window.draw(bottom);
        window.draw(left);
        window.draw(right);

        window.draw(paddle);
        window.draw(ball);
        window.draw(scoreBox);
        window.display();

		
    }
	
}
