#include "maze.h"

#include <fstream>
#include <memory>

#include <SDL_image.h>

#include "coin.h"
#include "ground.h"
#include "monster_random.h"
#include "monster_clever.h"
#include "wall.h"


maze::maze(const std::string& p_filepath, SDL_Renderer* p_renderer, SDL_Window* p_window) :
	m_renderer(p_renderer),
	m_texture_manager(p_renderer),
	m_window(p_window)
{
	std::ifstream stream(p_filepath);

	int row = 0;
	for (std::string line; std::getline(stream, line); ) {
		m_maze.push_back(line);
	}

	initialize_texture_manager();
}


maze::~maze() {
	m_is_running = false;
}


void maze::initialize_texture_manager() {
	m_texture_manager.load(' ', "img/ground.png");
	m_texture_manager.load('*', "img/wall.png");
	m_texture_manager.load('$', "img/coin.png");
	m_texture_manager.load('P', "img/player.png");
	m_texture_manager.load('S', "img/monster.png");
	m_texture_manager.load('C', "img/monster-bfs.png");
}


void maze::initialize() {
	int x = 0, y = 0;

	m_objects_static = std::vector<std::vector<game_object::ptr>>(m_maze.size(), std::vector<game_object::ptr>(m_maze[0].size(), nullptr));

	for (int i = 0; i < m_maze.size(); i++) {
		m_objects_fundamental.push_back(std::vector<game_object::ptr>());

		for (int j = 0; j < m_maze[0].size(); j++) {
			auto& value = m_maze[i][j];

			SDL_Rect rect{ x, y, OBJECT_SIZE, OBJECT_SIZE };

			x += OBJECT_SIZE;

			if (value != '*') {
				m_objects_fundamental.back().push_back(std::make_shared<ground>(' ', rect, m_texture_manager));
			}

			switch (value) {
			case 'S':
				m_monsters.push_back(std::make_shared<monster_random>('S', rect, m_texture_manager, &m_maze, position{ j, i }));
				break;

			case 'C':
				m_monsters.push_back(std::make_shared<monster_clever>('C', rect, m_texture_manager, &m_maze, position{ j, i }));
				break;

			case 'P':
				m_player = { j, i };
				break;

			case '$':
				m_objects_static[i][j] = std::make_shared<coin>(value, rect, m_texture_manager);
				break;

			case '*':
				m_objects_fundamental.back().push_back(std::make_shared<wall>(value, rect, m_texture_manager));
				break;
			}

			if (value != '*' && value != ' ' && value != '$') {
				value = ' '; // clean dynamic objects.
			}
		}

		x = 0;
		y += OBJECT_SIZE;
	}

	render();
}

void maze::check_score() {
	if (m_maze[m_player.y][m_player.x] == '$') {
		m_score += 100;
		m_maze[m_player.y][m_player.x] = ' ';
		SDL_Rect rect{ m_player.x * OBJECT_SIZE, m_player.y * OBJECT_SIZE, OBJECT_SIZE, OBJECT_SIZE };
		m_objects_static[m_player.y][m_player.x] = std::make_shared<ground>(' ', rect, m_texture_manager);
		std::string title("Maze Roamer | Score: ");
		title.append(std::to_string(m_score));
		SDL_SetWindowTitle(m_window, title.c_str());
	}
}

void maze::update() {
	for (auto& monster_ptr : m_monsters) {
		monster_ptr->notify_player_moving(m_player);
		monster_ptr->update();

		if (monster_ptr->get_logical_location() == m_player) {
			game_over();
		}
	}
	check_score();
}


void maze::render() {
	render_static_objects();

	render_object('P', m_player.x * OBJECT_SIZE, m_player.y * OBJECT_SIZE);

	for (const auto& monster_ptr : m_monsters) {
		monster_ptr->render();
	}

	SDL_RenderPresent(m_renderer);
}


void maze::render_static_objects() {
	int x = 0, y = 0;

	for (int i = 0; i < m_objects_fundamental.size(); i++) {
		for (int j = 0; j < m_objects_fundamental[i].size(); j++) {
			auto& object_fundamental = m_objects_fundamental[i][j];
			object_fundamental->render();

			auto& object_static = m_objects_static[i][j];
			if (object_static != nullptr) {
				object_static->render();
			}
		}

		x = 0;
		y += OBJECT_SIZE;
	}
}


void maze::render_object(const char p_obj_id, const int p_x, const int p_y) {
	SDL_Rect rect{ p_x, p_y, OBJECT_SIZE, OBJECT_SIZE };

	switch (p_obj_id) {
	case 'P': {
		m_texture_manager.draw(p_obj_id, rect);
		break;
	}
	}
}


bool maze::is_running() const {
	return m_is_running;
}


void maze::game_over() {
	SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Game Over", "Game Over", nullptr);
	m_is_running = false;
}


bool maze::is_inside(const position& p_pos) const {
	return ((p_pos.x >= 0 && p_pos.x < m_maze.front().size()) &&
		(p_pos.y >= 0 && p_pos.y < m_maze.size()));
}


bool maze::is_wall(const position& p_pos) const {
	if (!is_inside(p_pos)) {
		return false;
	}

	return m_maze[p_pos.y][p_pos.x] == '*';
}


void maze::move_right() {
	position next_pos = { m_player.x + 1, m_player.y };
	move(m_player, next_pos);
}


void maze::move_left() {
	position next_pos = { m_player.x - 1, m_player.y };
	move(m_player, next_pos);
}


void maze::move_up() {
	position next_pos = { m_player.x, m_player.y - 1 };
	move(m_player, next_pos);
}


void maze::move_down() {
	position next_pos = { m_player.x, m_player.y + 1 };
	move(m_player, next_pos);
}


void maze::move(const position& p_prev, const position& p_next) {
	if (is_wall(p_next)) {
		return;
	}

	for (auto& monster : m_monsters) {
		if (p_next == monster->get_logical_location()) {
			game_over();
			return;
		}
	}

	m_player = p_next;
}



int maze::get_height() const {
	return OBJECT_SIZE * m_maze.size();
}


int maze::get_width() const {
	return OBJECT_SIZE * m_maze.front().size();
}
