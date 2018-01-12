#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "../include/anim.hpp"

float offsetX=0, offsetY=0;
const int H = 17;
const int W = 150;

sf::String TileMap[H] = {
"000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000",
"0                                                                                                                                                    0",
"0                                                                                    w                                                               0",
"0                   w                                  w                   w                                                                         0",
"0                                      w                                       kk                                                                    0",
"0                                                                             k  k    k    k                                                         0",
"0                      c                                                      k      kkk  kkk  w                                                     0",
"0                                                                       r     k       k    k                                                         0",
"0                                                                      rr     k  k                                                                   0",
"0                                                                     rrr      kk                                                                    0",
"0               c    kckck                                           rrrr                                                                            0",
"0                                      t0                           rrrrr                                                                            0",
"0G                                     00              t0          rrrrrr            G                                                               0",
"0           d    g       d             00              00         rrrrrrr                                                                            0",
"PPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPP",
"PPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPP",
"PPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPP",
}; 

class PLAYER 
{
public:

	float dx,dy;
	sf::FloatRect rect;
	bool onGround;
	sf::Sprite sprite;
	float currentFrame;
	
	PLAYER(sf::Texture &image)
   	{
		sprite.setTexture(image);
		rect = sf::FloatRect(100,180,16,16);

		dx = dy = 0.1;
		currentFrame = 0;
   	}

	void update(float time)
   	{	
		rect.left += dx * time;	
     	Collision(0);
   
	    if (!onGround) dy=dy+0.0005*time;	
	    rect.top += dy*time;
	    onGround=false;
        Collision(1);
	
        currentFrame += time * 0.005;
        
		if (currentFrame > 3) 
		{
			currentFrame -= 3;
		}

   		if (dx>0) 
		{
			sprite.setTextureRect(sf::IntRect(112+31*int(currentFrame),144,16,16));
		}
			    
		if (dx<0)
		{
			sprite.setTextureRect(sf::IntRect(112+31*int(currentFrame)+16,144,-16,16));
		}

		sprite.setPosition(rect.left - offsetX, rect.top - offsetY);
		  
	 	dx=0;
   }


   	void Collision(int num)
	{
	
		for (int i = rect.top/16 ; i<(rect.top+rect.height)/16; i++)
		{
			for (int j = rect.left/16; j<(rect.left+rect.width)/16; j++)
				{
					if ((TileMap[i][j]=='P') || (TileMap[i][j]=='k') || (TileMap[i][j]=='0') || (TileMap[i][j]=='r') || (TileMap[i][j]=='t'))
					{ 
						if (dy > 0 && num == 1)
						{
							rect.top =   i*16 -  rect.height;  
							dy = 0;   
							onGround = true; 
						}
						
						if (dy < 0 && num == 1)
						{
							rect.top = i*16 + 16;   
							dy = 0;
						}
						
						if (dx > 0 && num == 0)
						{ 
							rect.left =  j * 16 - rect.width; 
						}
						
						if (dx < 0 && num == 0)
						{ 
							rect.left =  j * 16 + 16;
						}
					}
				
				if (TileMap[i][j] == 'c') 
				{								 
					// TileMap[i][j]=' ';                      	 
				}
			}
		}
	}
};

class ENEMY
{
public:
	float dx,dy;
	sf::FloatRect rect;
	sf::Sprite sprite;
	float currentFrame;
	bool life;

   	void set(sf::Texture &image, int x, int y)
   	{
		sprite.setTexture(image);
		rect = sf::FloatRect(x,y,16,16);

    	dx = 0.05;
		currentFrame = 0;
		life = true;
   	}

   	void update(float time)
   	{	
		rect.left += dx * time;
     	
		Collision();
		currentFrame += time * 0.005;
     	
		if (currentFrame > 2) 
		{
			currentFrame -= 2;
		}

    	sprite.setTextureRect(sf::IntRect(18*int(currentFrame),   0, 16,16));
    	
		if (!life) 		
		{
			sprite.setTextureRect(sf::IntRect(58, 0, 16,16));
		}

		sprite.setPosition(rect.left - offsetX, rect.top - offsetY);
	  
   	}

	void Collision()
	{
		for (int i = rect.top/16 ; i<(rect.top+rect.height)/16; i++)
		{
			for (int j = rect.left/16; j<(rect.left+rect.width)/16; j++)
			{
				if ((TileMap[i][j]=='P') || (TileMap[i][j]=='0'))
				{ 
					if (dx>0)
					{
						rect.left =  j*16 - rect.width; dx*=-1; 
					} else if (dx<0)
					{
						rect.left =  j*16 + 16;  dx*=-1; 
					}
				}						
			}
		}
	}
};

int main()
{  
	sf::RenderWindow window(sf::VideoMode(250, 150), "SFML works!");

	sf::Texture q;
	q.loadFromFile("./resources/images/fang.png");
	
	AnimationManager anim;
	anim.create("walk", q, 0, 244, 40, 50, 6, 0.005, 40);
	anim.create("jump", q, 0, 528, 29, 30, 4, 0.0045, 38);
	anim.create("duck", q, 0, 436, 80, 20, 1, 0.005, 40);
	anim.create("stay", q, 0, 187, 42, 52, 3, 0.002, 42);
	anim.create("shoot", q, 0, 572, 45, 52, 5, 0.004, 45);
	
	sf::Music music;
	music.openFromFile("./resources/sound/Mario_Theme.ogg");
	music.play();

	sf::Clock clock;

    while (window.isOpen())
    { 	
		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();

		time = time/500;  // здесь регулируем скорость игры

		if (time > 20) time = 20; 
		
		sf::Event event;
		while(window.pollEvent(event))
		{
			if(event.type == sf::Event::Closed)
			{
				window.close();
			}
		}
		
		anim.set("stay");
		
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			anim.set("walk");
		}
		
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			anim.set("walk");
		}
		
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			anim.set("jump");
		}
		
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			anim.set("duck");
		}
		
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			anim.set("shoot");
		}
		
		anim.tick(time);

		window.clear(sf::Color(255, 255, 255));
		anim.draw(window, 50, 100);
		window.display();
	}
    return 0;
}

