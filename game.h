#pragma once
#include <SFML/Graphics.hpp>
#include "settings.h"
#include <vector>
#include "meteor.h"
#include "player.h"
#include "hp_bar.h"
class Game {
private:
	sf::RenderWindow window;
	std::vector<Meteor*> meteors;
	Player player;
	HpBar hpBar;

public:
	void spawnMeteors(size_t n) {
		for (int i = 0; i < n; i++) {
			int num = rand() % 4 + 1;
			std::string fileName = "images\\spaceMeteors_00" + std::to_string(num) + ".png";
			Meteor::MeteorSize size = (Meteor::MeteorSize)(rand() % 3);
			float x = rand() % 301 - 300.f;
			int choice = rand() % 10000;
			if (choice < 5000)x += 1500.f;
			float y = rand() % 301 - 300.f;
			choice = rand() % 10000;
			if (choice < 5000) y += 1500.f;
			float speedx = rand() % 11 - 5.f;
			float speedy = rand() % 11 - 5.f;
			Meteor* m = new Meteor(fileName, size, sf::Vector2f{ x, y }, sf::Vector2f{ speedx,speedy });
			meteors.push_back(m);
		}
	}
	Game() {
		window.create(sf::VideoMode{ (size_t)window_width,(size_t)window_height }, "f");
		window.setFramerateLimit(fps);
		spawnMeteors(35);

	}
	void chek_events() {
		sf::Event event;
		while (window.pollEvent(event))
		{
			// ???????????? ????? ?? «???????» ? ????? ??????? ?????
			if (event.type == sf::Event::Closed)
				// ????? ????????? ???
				window.close();
		}
	}
	void update() {
		for (int i = 0; i < meteors.size(); i++) {
			meteors.at(i)->update();
		}
		player.update();
		hpBar.update(player.getPlayerHp());
	}
	void chek_collisons() {
		sf::FloatRect player_bounds = player.getHitbox()
			;
		for (auto& meteor : meteors) {
			sf::FloatRect meteor_bounds = meteor->getHitbox();
			if (meteor_bounds.intersects(player_bounds)) {
				player.decrease_hp(meteor->getDamage());
				meteor->setRandomPosition();
				/*if(player.getPlayerHp() <= 0){
					window.clear();
				
				}*/
			}
		
		}
		auto bullet_sprites = player.getBullets();
			for (auto& meteor : meteors) {
				sf::FloatRect meteor_bounds = meteor->getHitbox();
				for (auto& bullet : *bullet_sprites){
					sf::FloatRect bullet_bounds = bullet->getHitbox();
					if (meteor_bounds.intersects(bullet_bounds)) {
						meteor->setRandomPosition();
						//(*bullet_sprites).remove(bullet);
					}
				}
			}

	}
	void draw() {
		window.clear();
		for (int i = 0; i < meteors.size(); i++) {
			window.draw(meteors.at(i)->getSprite());
		}
		player.draw(window);
		hpBar.draw(window,player.getPlayerHp());
		window.display();
	}
	void play() {
		while (window.isOpen())
		{
			chek_events();
			update();
			chek_collisons();
			draw();
		}
	}
};