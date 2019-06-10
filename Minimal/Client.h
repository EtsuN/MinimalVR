#pragma once

#include <iostream>
#include <string>

#include "../Shared/Player.h"


#include "pch.h"
#include "rpc/client.h"

#include <glm/gtx/string_cast.hpp>

				   // Shared struct


using std::string;
/*
Always test in release mode
Set the IP address
*/

rpc::client* c;
string s;

int init_client() {
	// Setup an rpc client that connects to "localhost:8080"
	std::cout << "This is Client" << std::endl;
	std::cout << "Connecting..." << std::endl;
	c = new rpc::client("localhost", 8080);
	int player_num = c->call("handshake", "Nabi").get().as<int>();
	std::cout << "Connected to server, and I am: " << player_num << "P" << std::endl;
	return player_num;
}

PlayerInfo run_client(PlayerInfo myInfo)
{

	// Client side logic
	string input = "hi";

	string result;
	string p;
	std::tie(result, p) = c->call("echo", input, p).get().as<std::tuple<string, string>/*cast back the respond message to string and Player*/>();

	PlayerInfo op;
	return op;
}
