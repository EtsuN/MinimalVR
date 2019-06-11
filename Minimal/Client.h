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
	c = new rpc::client("128.54.70.58", 8080);
	player_num = c->call("handshake", "Nabi").get().as<int>();
	std::cout << "Connected to server, and I am: " << player_num << "P" << std::endl;
	return player_num;
}

void run_client(Player* me, Player * oppo)
{
	PlayerInfo* myInfo = me->getPlayerInfo();
	std::tie(op, weapons) = c->call("push", *myInfo, player_num).get().as<std::tuple<PlayerInfo, vector<bool>>/*cast back the respond message to string and Player*/>();




	//printf("ME: %d\n", me->heldWeapon);
	//printf("MYWEAPON: %d\n", weapon_p1);
	//printf("OPPO: %d\n", op.heldWeapon);


}
