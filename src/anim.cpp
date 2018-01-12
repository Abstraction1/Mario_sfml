#include <SFML/Graphics.hpp>
#include "../include/anim.hpp"

		Animation::Animation(sf::Texture &t, int x, int y, int w, int h, int count_, float speed, int step)
		{
			this->speed = speed;
			sprite.setTexture(t);
			currentFrame = 0;
			isPlaying = true;
			flip = false;
			
			for(int i = 0; i < count_; i++)
			{
				frames.push_back(sf::IntRect(x + i * step, y, w, h));
				framesFlip.push_back(sf::IntRect(x + i * step + w, y, -w, h));
			}
		}

		void Animation::tick(float time)
		{
			if(!isPlaying)
			{
				return;
			}

			currentFrame += speed * time;

			if(currentFrame > frames.size())
			{
				currentFrame -= frames.size();
			}

			int i = currentFrame;
			sprite.setTextureRect(frames[i]);
			if(flip)
			{
				sprite.setTextureRect(framesFlip[i]);
			}
		}

		AnimationManager::AnimationManager()
		{

		}

		void AnimationManager::create(sf::String name, sf::Texture &t, int x, int y, int w, int h, int count_, float speed, int step)
		{		
			animList[name] = Animation(t, x, y, w, h, count_, speed, step);
			currentAnim = name;
		}

		void AnimationManager::draw(sf::RenderWindow &window, int x = 0, int y = 0)
		{
			animList[currentAnim].sprite.setPosition(x, y);
			window.draw(animList[currentAnim].sprite);
		}

		void AnimationManager::set(sf::String name)
		{
			currentAnim = name;
		}
		
		void AnimationManager::flip(bool b)
		{
			animList[currentAnim].flip = b;		
		}

		void AnimationManager::tick(float time)
		{
			animList[currentAnim].tick(time);
		}

		void AnimationManager::pause()
		{
			animList[currentAnim].isPlaying = false;
		}

		void AnimationManager::play()
		{
			animList[currentAnim].isPlaying = true;
		}
