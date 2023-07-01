#include "world.hpp"
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include "player.hpp"

World::World()
{
	if (!tile_set.loadFromFile("content/dirt-tiles.png"))
	{
		std::cout << "ERROR:: Cannot load tileset from file" << "\n";
	}
	tile.setTexture(tile_set);
}

void World::createMap(sf::String tile_map[], const int map_width, const int map_height, int tile_width, int tile_height, sf::RenderWindow& window, Player& p1_rect, Player& p2_rect, bool& player1_tile_collision, bool& player2_tile_collision, int player_width)
{
	// Loop through tile_map and assign tile texture to tile
	// according to what string it is assigned to
	for (int i = 0; i < map_height; i++)
	{
		for (int j = 0; j != map_width; j++)
		{
			if (tile_map[i][j] == 'G')
			{
				tile.setTextureRect(sf::IntRect(0 * tile_width, 0 * tile_height, tile_width, tile_height));
			}

			if (tile_map[i][j] == 'B')
			{
				tile.setTextureRect(sf::IntRect(1 * tile_width, 0 * tile_height, tile_width, tile_height));
			}

			if (tile_map[i][j] == '0' || tile_map[i][j] == ' ')
			{
				continue;
			}

			// Set tile position
			tile.setPosition(sf::Vector2f(j * tile_width, i * tile_height));
			playerCollision(p1_rect, player1_tile_collision, player_width);
			player2Collision(p2_rect, player2_tile_collision, player_width);
			window.draw(tile);
		}
	}
}

void World::playerCollision(Player& p1_rect, bool& player1_tile_collision, int player_width)
{
	tile_top = tile.getPosition().y;
	auto player1 = p1_rect.player;

	// Detect collision between player and tile
	if (player1.getGlobalHitbox().intersects(tile.getGlobalBounds()))
	{
		player1_tile_collision = true;
		p1_rect.player.setPosition(sf::Vector2f(p1_rect.player.getPosition().x, tile.getPosition().y - player_width / 2));
	}
}

void World::player2Collision(Player& p2_rect, bool& player2_tile_collision, int player_width)
{
	tile_top = tile.getPosition().y;
	auto player2 = p2_rect.player;

	// Detect collision between player and tile
	if (player2.getGlobalHitbox().intersects(tile.getGlobalBounds()))
	{
		player2_tile_collision = true;
		player2.setPosition(sf::Vector2f(player2.getPosition().x, tile.getPosition().y - player_width / 2));
	}
}