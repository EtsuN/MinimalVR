#pragma once

#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/noise.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <tuple>
#include "../Shared/Player.h"


using namespace std;
using namespace glm;

class Scene {
private:
	vector<mat4> axes;
	vector<mat4> swords;
	vector<mat4> maces;


	vector<vec3> axe_pos;
	vector<vec3> sword_pos;
	vector<vec3> mace_pos;

	vec3 axe_handle;
	vec3 mace_handle;
	vec3 sword_handle;

	mat4 axe_sphere_trans;
	mat4 mace_sphere_trans;
	mat4 sword_sphere_trans;

	mat4 axe_collision_trans;
	mat4 mace_collision_trans;
	vector<mat4> sword_collision_trans;

	vector<mat4> axe_collision;
	vector<mat4> mace_collision;
	vector<mat4> sword_collision;

	vector<mat4> mace_sphere;
	vector<mat4> axe_sphere;
	vector<mat4> sword_sphere;

	vec3 mace_head;
	vec3 axe_head;
	vec3 sword_head;

	float axe_head_radius;
	float mace_head_radius;
	float sword_head_radius;

	vector<mat4> axe_rots;
	vector<mat4> mace_rots;
	vector<mat4> sword_rots;

	int player_1_weapon;
	int player_2_weapon;

	vec3 player_1_head;
	vec3 player_2_head;

	mat4 player_trans;

	float head_radius;

	float pi = 3.141592653589793;
public:
	PlayerInfo players[2];
	vector<bool> render_weapons;

	Scene() {
		axe_handle = vec3(0, -0.1, -0.01);
		mace_handle = vec3(0.005, -0.2, 0);
		sword_handle = vec3(-0.005, -0.22, 0);

		axe_head = vec3(0, 0.3, 0);
		mace_head = vec3(0, 0.42, 0);

		axes.push_back(glm::rotate(90 * pi / 180.0f, vec3(1, 0, 0))* glm::rotate(180 * pi / 180.0f, vec3(0, 0, 1)) * glm::scale(glm::mat4(1.0f), glm::vec3(0.01f)) * glm::mat4(1));
		axes.push_back(glm::rotate(90 * pi / 180.0f, vec3(1, 0, 0))* glm::rotate(180 * pi / 180.0f, vec3(0, 0, 1)) * glm::scale(glm::mat4(1.0f), glm::vec3(0.01f)) * glm::mat4(1));

		maces.push_back(glm::rotate(90 * pi / 180.0f, vec3(1, 0, 0))* glm::rotate(270 * pi / 180.0f, vec3(1, 0, 0)) * glm::scale(glm::mat4(1.0f), glm::vec3(0.7f)) * glm::mat4(1));
		maces.push_back(glm::rotate(90 * pi / 180.0f, vec3(1, 0, 0))* glm::rotate(270 * pi / 180.0f, vec3(1, 0, 0)) * glm::scale(glm::mat4(1.0f), glm::vec3(0.7f)) * glm::mat4(1));

		swords.push_back(glm::rotate(-90 * pi / 180.0f, vec3(0, 1, 0))* glm::rotate(270 * pi / 180.0f, vec3(1, 0, 0)) * glm::scale(glm::mat4(1.0f), glm::vec3(0.1f)) * glm::mat4(1));
		swords.push_back(glm::rotate(-90 * pi / 180.0f, vec3(0, 1, 0))* glm::rotate(270 * pi / 180.0f, vec3(1, 0, 0)) * glm::scale(glm::mat4(1.0f), glm::vec3(0.1f)) * glm::mat4(1));

		axe_pos.push_back(glm::vec3(0, 0, -0.4));
		axe_pos.push_back(vec3(0, 0, -0.2));
		axe_rots.push_back(mat4(1));
		axe_rots.push_back(mat4(1));

		mace_pos.push_back(glm::vec3(0.3, 0.05, -0.4));
		mace_pos.push_back(glm::vec3(0.3, 0.05, -0.2));
		mace_rots.push_back(mat4(1));
		mace_rots.push_back(mat4(1));

		sword_pos.push_back(glm::vec3(-0.3, 0, -0.4));
		sword_pos.push_back(glm::vec3(-0.3, 0, -0.2));
		sword_rots.push_back(mat4(1));
		sword_rots.push_back(mat4(1));

		axe_head_radius = 0.13;
		axe_sphere_trans = glm::translate(axe_handle) *  glm::scale(glm::mat4(1.0f), glm::vec3(0.04f)) * glm::mat4(1);
		axe_collision_trans = (glm::translate(axe_head) * glm::scale(vec3(axe_head_radius)));

		mace_head_radius = 0.08;
		mace_sphere_trans = glm::translate(mace_handle) *  glm::scale(glm::mat4(1.0f), glm::vec3(0.03f)) * glm::mat4(1);
		mace_collision_trans = (glm::translate(mace_head) * glm::scale(vec3(mace_head_radius)));

		sword_head_radius = 0.04;
		sword_sphere_trans = glm::translate(sword_handle) *  glm::scale(glm::mat4(1.0f), glm::vec3(0.03f)) * glm::mat4(1);
		for (int i = 0; i < 9; i++)
			sword_collision_trans.push_back(glm::translate(sword_head + vec3(0, i / 15.0f, 0)) * glm::scale(vec3(sword_head_radius)));

		head_radius = 1.0;

		for (int i = 0; i < 6; i++)
			render_weapons.push_back(true);

		for (int i = 0; i < 2; i++) {
			axe_collision.push_back(mat4(1));
			mace_collision.push_back(mat4(1));
			sword_collision.push_back(mat4(1));

			mace_sphere.push_back(mat4(1));
			axe_sphere.push_back(mat4(1));
			sword_sphere.push_back(mat4(1));
		}
	}

	//check the interaction between the held weapon, and disable the rendering for the broken weapon
	//TODO
	void check_interaction(int weapon1, int weapon2) {
		if (weapon1 == -1 || weapon2 == -1) return;
		int type1 = weapon1 / 2;
		int type2 = weapon2 / 2;
		if (type1 == type2) {
			render_weapons[weapon1] = false;
			render_weapons[weapon2] = false;
		}
		else if (type1 > type2) {
			if (type1 - type2 == 2) { // type1 = sword; type2 = axe
				render_weapons[weapon2] = false;
			}
			else { //1=sword 2=mace; 1=mace 2=axe
				render_weapons[weapon1] = false;
			}
		}
		else {
			if (type2 - type1 == 2) { // type2 = sword; type1 = axe
				render_weapons[weapon1] = false;
			}
			else { //2=sword 1=mace; 2=mace 1=axe
				render_weapons[weapon2] = false;
			}
		}
	}

	void update(PlayerInfo & p, int player) {
		if (player == 1) {
			player_1_head = vec3(p.headInWorld * vec4(0, 0, 0, 1));
			player_1_weapon = p.heldWeapon;
			update_weapon(player_1_weapon, p.rhandInWorld * vec4(0, 0, 0, 1), p.rhandInWorld);
			players[0] = p;
		}

		if (player == 2) {
			player_2_head = vec3(p.headInWorld * vec4(0, 0, 0, 1));
			player_2_weapon = p.heldWeapon;
			update_weapon(player_2_weapon, p.rhandInWorld * vec4(0, 0, 0, 1), p.rhandInWorld);
			players[1] = p;
		}
		bool weapon, player1_dead, player2_dead;
		std::tie(weapon, player1_dead, player2_dead) = check_collision();

		if (player1_dead)
			players[0].dead = 1;
		else if (player2_dead)
			players[1].dead = 1;

		if (weapon) { //TODO
			check_interaction(players[0].heldWeapon, players[1].heldWeapon);
		}
	}

	void update_weapon(int weapon_ix, vec3 pos, mat4 rot) {
		switch (weapon_ix)
		{
		case 0:
			axe_pos[weapon_ix] = pos;
			axe_rots[weapon_ix] = rot;
			break;
		case 1:
			axe_pos[weapon_ix] = pos;
			axe_rots[weapon_ix] = rot;
			break;
		case 2:
			mace_pos[weapon_ix - 2] = pos;
			mace_rots[weapon_ix - 2] = rot;
			break;
		case 3:
			mace_pos[weapon_ix - 2] = pos;
			mace_rots[weapon_ix - 2] = rot;
			break;
		case 4:
			sword_pos[weapon_ix - 4] = pos;
			sword_rots[weapon_ix - 4] = rot;
			break;
		case 5:
			sword_pos[weapon_ix - 4] = pos;
			sword_rots[weapon_ix - 4] = rot;
			break;
		default:
			break;
		}
	}

	std::pair<vec3, mat4> get_pos_and_rot(int weapon_ix) {
		switch (weapon_ix)
		{
		case 0:
			return std::pair<vec3, mat4>(axe_pos[weapon_ix], axe_rots[weapon_ix]);
		case 1:
			return std::pair<vec3, mat4>(axe_pos[weapon_ix], axe_rots[weapon_ix]);
		case 2:
			return std::pair<vec3, mat4>(mace_pos[weapon_ix - 2], mace_rots[weapon_ix - 2]);
		case 3:
			return std::pair<vec3, mat4>(mace_pos[weapon_ix - 2], mace_rots[weapon_ix - 2]);
		case 4:
			return std::pair<vec3, mat4>(sword_pos[weapon_ix - 4], sword_rots[weapon_ix - 4]);
		case 5:
			return std::pair<vec3, mat4>(sword_pos[weapon_ix - 4], sword_rots[weapon_ix - 4]);
		default:
			break;
		}
	}

	mat4 get_weapon_collision(int weapon_ix) {
		switch (weapon_ix) {
		case 0:
			return axe_collision_trans;
		case 1:
			return axe_collision_trans;
		case 2:
			return mace_collision_trans;
		case 3:
			return mace_collision_trans;
		}
	}

	float get_weapon_radius(int weapon_ix) {
		switch (weapon_ix) {
		case 0:
			return axe_head_radius;
		case 1:
			return axe_head_radius;
		case 2:
			return mace_head_radius;
		case 3:
			return mace_head_radius;
		case 4:
			return sword_head_radius;
		case 5:
			return sword_head_radius;
		}
	}

	float shortest_distance(vec3 & pos, mat4 & rot, vector<mat4> & sword, vec4 point) {
		mat4 collision_point = translate(pos) * rot;
		float dist, cur_dist;
		dist = 1000000.0f;
		for (int i = 0; i < 9; i++) {
			cur_dist = distance(collision_point * sword[i] * vec4(0, 0, 0, 1), point);
			if (cur_dist < dist)
				dist = cur_dist;
		}
		return dist;
	}

	//Collision of weapons, with player_1_head and with player_2_head
	std::tuple<bool, bool, bool> check_collision() {
		bool w, h1, h2 = false;

		if (player_1_weapon == -1 || player_2_weapon == -1) {
			if (player_2_weapon != -1) {
				std::pair<vec3, mat4> ret = get_pos_and_rot(player_2_weapon);
				vec3 player_2_wpos = ret.first;
				mat4 player_2_wrot = ret.second;

				if (player_2_weapon >= 4) {
					float dist = shortest_distance(player_2_wpos, player_2_wrot, sword_collision_trans, vec4(player_1_head, 1));
					if (dist < head_radius + sword_head_radius)
						h1 = true;
				}
				else {
					mat4 weapon_2_collision = glm::translate(player_2_wpos) * player_2_wrot * get_weapon_collision(player_2_weapon);
					float dist = distance(weapon_2_collision * vec4(0, 0, 0, 1), vec4(player_1_head, 1));
					if (dist < get_weapon_radius(player_2_weapon) + head_radius) {
						//printf("PLAYER 1 DEAD");
						h1 = true;
					}
				}
			}
			else if (player_1_weapon != -1) {
				std::pair<vec3, mat4> ret = get_pos_and_rot(player_1_weapon);
				vec3 player_1_wpos = ret.first;
				mat4 player_1_wrot = ret.second;

				if (player_1_weapon >= 4) {
					float dist = shortest_distance(player_1_wpos, player_1_wrot, sword_collision_trans, vec4(player_2_head, 1));
					if (dist < head_radius + sword_head_radius)
						h2 = true;
				}
				else {
					mat4 weapon_1_collision = glm::translate(player_1_wpos) * player_1_wrot * get_weapon_collision(player_1_weapon);
					float dist = distance(weapon_1_collision * vec4(0, 0, 0, 1), vec4(player_2_head, 1));
					if (dist < get_weapon_radius(player_1_weapon) + head_radius) {
						//printf("PLAYER 2 DEAD");
						h2 = true;
					}
				}
			}
			return std::tuple<bool, bool, bool>(w, h1, h2);
		}

		if (player_1_weapon < 4 && player_2_weapon < 4) {
			std::pair<vec3, mat4> ret = get_pos_and_rot(player_1_weapon);
			vec3 player_1_wpos = ret.first;
			mat4 player_1_wrot = ret.second;

			ret = get_pos_and_rot(player_2_weapon);
			vec3 player_2_wpos = ret.first;
			mat4 player_2_wrot = ret.second;

			mat4 weapon_1_collision = glm::translate(player_1_wpos) * player_1_wrot * get_weapon_collision(player_1_weapon);
			mat4 weapon_2_collision = glm::translate(player_2_wpos) * player_2_wrot * get_weapon_collision(player_2_weapon);

			float dist = distance(weapon_1_collision * vec4(0, 0, 0, 1), weapon_2_collision * vec4(0, 0, 0, 1));
			if (dist < get_weapon_radius(player_1_weapon) + get_weapon_radius(player_2_weapon)) {
				//printf("WEAPONS COLLIDE");
				w = true;
			}
			dist = distance(weapon_1_collision * vec4(0, 0, 0, 1), vec4(player_2_head, 1));
			if (dist < get_weapon_radius(player_1_weapon) + head_radius) {
				//printf("PLAYER 2 DEAD");
				h2 = true;
			}
			dist = distance(weapon_2_collision * vec4(0, 0, 0, 1), vec4(player_1_head, 1));
			if (dist < get_weapon_radius(player_2_weapon) + head_radius) {
				//printf("PLAYER 1 DEAD");
				h1 = true;
			}
		}

		else if (player_1_weapon >= 4 || player_2_weapon >= 4){
			if (player_1_weapon >= 4) {
				if (player_2_weapon >= 4) {
					std::pair<vec3, mat4> ret = get_pos_and_rot(player_1_weapon);
					vec3 player_1_wpos = ret.first;
					mat4 player_1_wrot = ret.second;

					ret = get_pos_and_rot(player_2_weapon);
					vec3 player_2_wpos = ret.first;
					mat4 player_2_wrot = ret.second;

					float dist;

					for (int i = 0; i < 9; i++) {
						dist = shortest_distance(player_1_wpos, player_1_wrot, sword_collision_trans, translate(player_2_wpos) * player_2_wrot * sword_collision_trans[i] * vec4(0, 0, 0, 1));
						if (dist < 2 * sword_head_radius) {
							w = true;
							break;
						}
					}

					dist = shortest_distance(player_1_wpos, player_1_wrot, sword_collision_trans, vec4(player_2_head, 1));
					if (dist < head_radius + sword_head_radius)
						h2 = true;
					
					dist = shortest_distance(player_2_wpos, player_2_wrot, sword_collision_trans, vec4(player_1_head, 1));
					if (dist < head_radius + sword_head_radius)
						h1 = true;	
				}
				else {
					std::pair<vec3, mat4> ret = get_pos_and_rot(player_1_weapon);
					vec3 player_1_wpos = ret.first;
					mat4 player_1_wrot = ret.second;

					ret = get_pos_and_rot(player_2_weapon);
					vec3 player_2_wpos = ret.first;
					mat4 player_2_wrot = ret.second;

					float dist;

					vec4 weapon_2_collision = translate(player_2_wpos) * player_2_wrot * get_weapon_collision(player_2_weapon) * vec4(0, 0, 0, 1);

					dist = shortest_distance(player_1_wpos, player_1_wrot, sword_collision_trans, weapon_2_collision);
					if (dist < sword_head_radius + get_weapon_radius(player_2_weapon)) {
						w = true;
					}

					dist = shortest_distance(player_1_wpos, player_1_wrot, sword_collision_trans, vec4(player_2_head, 1));
					if (dist < head_radius + sword_head_radius)
						h2 = true;

					dist = distance(weapon_2_collision, vec4(player_1_head, 1));
					if (dist < head_radius + get_weapon_radius(player_2_weapon))
						h1 = true;
				}

			}
			else {
				std::pair<vec3, mat4> ret = get_pos_and_rot(player_1_weapon);
				vec3 player_1_wpos = ret.first;
				mat4 player_1_wrot = ret.second;

				ret = get_pos_and_rot(player_2_weapon);
				vec3 player_2_wpos = ret.first;
				mat4 player_2_wrot = ret.second;

				float dist;

				vec4 weapon_1_collision = translate(player_1_wpos) * player_1_wrot * get_weapon_collision(player_1_weapon) * vec4(0, 0, 0, 1);

				dist = shortest_distance(player_2_wpos, player_2_wrot, sword_collision_trans, weapon_1_collision);
				if (dist < sword_head_radius + get_weapon_radius(player_1_weapon)) {
					w = true;
				}

				dist = shortest_distance(player_2_wpos, player_2_wrot, sword_collision_trans, vec4(player_1_head, 1));
				if (dist < head_radius + sword_head_radius)
					h1 = true;

				dist = distance(weapon_1_collision, vec4(player_2_head, 1));
				if (dist < head_radius + get_weapon_radius(player_1_weapon))
					h2 = true;
			}
		}
		return std::tuple<bool, bool, bool>(w, h1, h2);
	}
};