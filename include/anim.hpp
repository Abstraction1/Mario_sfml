#ifndef ANIM_HPP
#define ANIM_HPP

#include <SFML/Graphics.hpp>

class Animation
{
	public:
		std::vector <sf::IntRect> frames, framesFlip;
		float currentFrame, speed;
		bool flip, isPlaying;
		sf::Sprite sprite;

		Animation(sf::Texture &t, int x, int y, int w, int h, int count_, float speed, int step);
		void tick(float time);
};

class AnimationManager
{
	public:
		sf::String currentAnim;
		std::map <sf::String, Animation> animList;
		
		AnimationManager();
		void create(sf::String name, sf::Texture &t, int x, int y, int w, int h, int count_, float speed, int step);
		void draw(sf::RenderWindow &window, int x = 0, int y = 0);
		void set(sf::String name);
		void flip(bool b);
		void tick(float time);
		void pause();
		void play();
};

#endif 
