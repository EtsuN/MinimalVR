#include "../Shared/ServerClientConnection.h"
#include "pch.h"
#include "rpc/server.h"

#include <glm/gtx/string_cast.hpp>

// Shared struct


using std::string;
/*
Always test in release mode
Set the IP address
*/

int init_client() {
	return 0;
}

void run_client()
{


}

void run_server() {	/* empty */ }

#define PORT 8080
rpc::server* srv;

int connectedPlayers = 0;

void init_server() {
	srv = new rpc::server(PORT);
	std::cout << "Listening to port: " << PORT << std::endl;
	
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

	// Blocking call to start the server: non-blocking call is srv.async_run(threadsCount);

	std::cout << "Running the server now " << std::endl;
	srv->async_run(3);

}