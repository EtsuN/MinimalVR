#include "../Shared/ServerClientConnection.h"
#include "pch.h"
#include "rpc/server.h"
#include "../Shared/Player.h"
#include <glm/gtx/string_cast.hpp>
#include "Scene.h"

// Shared struct
Scene * new_game;

using std::string;
/*
Always test in release mode
Set the IP address
*/

int init_client() {
	return 0;
}

PlayerInfo run_client(PlayerInfo myInfo)
{
	return myInfo;
}

void run_server() {	/* empty */ }

#define PORT 8080
rpc::server* srv;

int connectedPlayers = 0;

int main() {
	srv = new rpc::server(PORT);
	std::cout << "Listening to port: " << PORT << std::endl;
	
	new_game = new Scene();

	srv->bind("handshake", [](string const& s) {
		std::cout << "Connected to client: " << s << std::endl;
		connectedPlayers++;
		return connectedPlayers;
	});

	// Define a rpc function: auto echo(string const& s, Player& p){} (return type is deduced)
	srv->bind("echo"/*function name*/, [/*put = here if you want to capture environment by value, & by reference*/]
	(string const& s, string const& p) /*function parameters*/
	{
		std::cout << "Get message: " << s << std::endl;
		std::cout << "After: " << p << std::endl;

		// return value : that will be returned back to client side
		return std::make_tuple(string("> ") + s, p);
	});

	srv->bind("push", [](PlayerInfo & p, int player_no) {
		new_game->update(p, player_no);
		//printf("HELLO: %d\n", player_no);
		
		return std::make_tuple(new_game->players[player_no == 1 ? 1 : 0], new_game->render_weapons);
	});

	// Blocking call to start the server: non-blocking call is srv.async_run(threadsCount);

	std::cout << "Running the server now " << std::endl;
	srv->run();

	return 0;

}