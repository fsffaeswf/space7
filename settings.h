#pragma once
#include <SFML/Graphics.hpp>
const float window_width = 1200;
const float window_height = 900;
const float fps = 60.f;
std::string player_file_name = "images\\spaceShips_009.png";
const double pi = 3.1415926535897932384626;
const float top_border = -300.f;
const float bottom_border = 1200.f;
const float left_border = -300.f;
const float right_border = 1500.f;
std::string bullet_file_name = "images\\spaceMissiles_003.png";
std::string heart_file_name = "images\\heart.png";
const float bullet_speed = 15.f;
const int FIRE_COOLDOWN = 200;
const int player_max_hp = 200;//
const int char_size = 48;
const sf::Vector2f hp_text_pos{ 0.f,30.f };
std::string game_over_text = "GAME OVER";
const float frame_width = 150;
const float frame_height = 20;
