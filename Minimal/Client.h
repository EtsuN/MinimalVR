#pragma once

#include <iostream>
#include <string>

#include "../Shared/Player.h"


#include "pch.h"
#include "rpc/client.h"

#include <glm/gtx/string_cast.hpp>


using std::string;
/*
Always test in release mode
Set the IP address
*/

rpc::client* c;
string s;
int player_num;

vector<bool> weapons;
PlayerInfo op;

int init_client() {
	// Setup an rpc client that connects to "localhost:8080"
	std::cout << "This is Client" << std::endl;
	std::cout << "Connecting..." << std::endl;
	c = new rpc::client("128.54.70.59", 8080);
	player_num = c->call("handshake", "Nabi").get().as<int>();
	std::cout << "Connected to server, and I am: " << player_num << "P" << std::endl;
	return player_num;
}

void run_client(PlayerInfo myInfo, Player * oppo)
{

	// Client side logic
	string input = "hi";

	std::tie(op, weapons) = c->call("push", myInfo, player_num).get().as<std::tuple<PlayerInfo, vector<bool>>/*cast back the respond message to string and Player*/>();




	//printf("ME: %d\n", me->heldWeapon);
	//printf("MYWEAPON: %d\n", weapon_p1);
	//printf("OPPO: %d\n", op.heldWeapon);


	oppo->updatePlayer(inverse(oppo->toWorld) * op.headInWorld, inverse(oppo->toWorld) * op.rhandInWorld, inverse(oppo->toWorld) * op.lhandInWorld);
	oppo_rot = mat3(op.rhandInWorld);
	oppo_handPose = op.rhandInWorld * vec4(0, 0, 0, 1);
	oppo->heldWeapon = op.heldWeapon;


	if (player_num == 1) {
		switch (op.heldWeapon) {
		case 1:
			weapon_p2 = a_axe;
			break;
		case 3:
			weapon_p2 = a_mace;
			break;
		case 5:
			weapon_p2 = a_sword;
			break;
		case -1:
			weapon_p2 = a_none;
			break;
		}
	}

	else {
		switch (op.heldWeapon) {
		case 0:
			weapon_p2 = a_axe;
			break;
		case 2:
			weapon_p2 = a_mace;
			break;
		case 4:
			weapon_p2 = a_sword;
			break;
		case -1:
			weapon_p2 = a_none;
			break;
		}
	}

	if (player_num == 1) {
		switch (weapon_p1) {
		case a_axe:
			me->heldWeapon = 0;
			break;
		case a_mace:
			me->heldWeapon = 2;
			break;
		case a_sword:
			me->heldWeapon = 4;
			break;
		case a_none:
			me->heldWeapon = -1;
			break;
		}
	}

	else {
		switch (weapon_p1) {
		case a_axe:
			me->heldWeapon = 1;
			break;
		case a_mace:
			me->heldWeapon = 3;
			break;
		case a_sword:
			me->heldWeapon = 5;
			break;
		case a_none:
			me->heldWeapon = -1;
			break;
		}
	}


	for (int i = 0; i < 6; i++) {
		weapon_state[i] = weapons[i];
	}
}
