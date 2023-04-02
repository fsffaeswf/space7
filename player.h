#pragma once
#include "settings.h"
#include "cmath"
#include "bullet.h"
#include "list"
#include "textobj.h"

class Player {
private:
	sf::Sprite sprite;
	sf::Texture texture;
	float angle;
	float speedx, speedy;
	float speed;
	std::list <Bullet*> bullets;
	sf::Clock timer;
	int hp =100;
	TextObj hp_text;
public:
	Player():hp_text(std::to_string(hp),hp_text_pos) {
		sprite.setScale(0.5f, 0.5f);
		texture.loadFromFile(player_file_name);
		sprite.setTexture(texture);
		sf::FloatRect bounds = sprite.getLocalBounds();
		sprite.setOrigin(bounds.width / 2, bounds.height / 2);
		sprite.setPosition(window_width/2, window_height/2);
		angle = 0;
		speedx = 0.f;
		speedy = 0.f;
		speed = 0.f;
		timer.restart();

	}
	void update() {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
			angle -= 3;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
			angle += 3;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
			speed += 1;
			if (speed >= 10)speed = 10;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
			speed -=0.25f;
			if (speed <= 0)speed = 0;
		}
		sf::FloatRect bounds = sprite.getLocalBounds();
		sf::Vector2f pos = sprite.getPosition();
		
		speedx = sin((angle * pi) / 180) * speed;
		speedy = -cos((angle * pi) / 180) * speed;
		fire();
		for (auto bullet : bullets) {
			bullet->update();
		}
		 if (
			(pos.x - bounds.width / 2 <= 0 && pos.y - bounds.height / 2 <= 0) ||
			(pos.x + bounds.width / 2 >= window_width && pos.y - bounds.height / 2 <= 0) ||
			(pos.x - bounds.width / 2 <= 0 && pos.y + bounds.width / 2 >= window_height) ||
			(pos.x + bounds.width / 2 >= window_width && pos.y + bounds.width / 2 >= window_height)
			) {
			sprite.setPosition(pos.x, pos.y);
		}
		//лева€
		else if (pos.x - bounds.width / 2 <= 0) {
			sprite.setPosition (bounds.width / 2, pos.y); }
		//права€
		 else if (pos.x + bounds.width / 2 >= window_width) {
			sprite.setPosition (window_width - bounds.width / 2, pos.y); }
		//верхн€€
		else if (pos.y - bounds.height / 2 <= 0) { 
			sprite.setPosition (pos.x, bounds.height / 2); }
		//нижн€€
		 else if (pos.y + bounds.width / 2 >= window_height) {
			sprite.setPosition (pos.x, window_height - bounds.width / 2); }
		
		
		sprite.setRotation(angle);
		sprite.move(speedx, speedy);
		hp_text.update(std::to_string(hp));
	}
	void fire(){
		int now = timer.getElapsedTime().asMilliseconds();
		if(now > FIRE_COOLDOWN)
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) ||
			sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
			auto bullet = new Bullet(sprite.getPosition(), angle);
			bullets.push_back(bullet);
			timer.restart();
		}
		
	}
	void draw(sf::RenderWindow& window) {
		
		for (auto bullet : bullets) {
			window.draw(bullet->getSprite());
		}
		window.draw(sprite);
		hp_text.draw(window);
	}

	void decrease_hp(int damage) { hp -= damage;}
	sf::FloatRect getHitbox() { return sprite.getGlobalBounds(); }
	int getPlayerHp() { return hp; }
	std::list <Bullet*>* getBullets() { return &bullets; };//
	
};

