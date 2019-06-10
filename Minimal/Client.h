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

int init_client() {
	// Setup an rpc client that connects to "localhost:8080"
	std::cout << "This is Client" << std::endl;
	std::cout << "Connecting..." << std::endl;
	c = new rpc::client("128.54.70.59", 8080);
	player_num = c->call("handshake", "Nabi").get().as<int>();
	std::cout << "Connected to server, and I am: " << player_num << "P" << std::endl;
	return player_num;
}

PlayerInfo run_client(PlayerInfo myInfo)
{

	// Client side logic
	string input = "hi";

	PlayerInfo op;
	std::tie(op, weapons) = c->call("push", myInfo, player_num).get().as<std::tuple<PlayerInfo, vector<bool>>/*cast back the respond message to string and Player*/>();

	return op;
}
