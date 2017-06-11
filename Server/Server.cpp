// Server.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "rpc/client.h"
#include "rpc/server.h"
#include <iostream>
#include <string>
#include <glm/glm.hpp>
#include <vector>
#include <array>
using std::string;

struct CMat4 {
	std::array<float, 16> elements = { 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1 };
	MSGPACK_DEFINE_ARRAY(elements);
};

struct GameState {
	bool missileFlag = false, bulletFlag = false;
	CMat4 vrModel;
	CMat4 leapModel;
	MSGPACK_DEFINE_ARRAY(missileFlag, bulletFlag, vrModel, leapModel);
};


int main() {

	rpc::server srv(8080);

	GameState gameState;

	srv.bind("updateGameState", [&gameState](int id, CMat4 input, bool flag) {
		if (id == 1) {
			gameState.vrModel = input;
			gameState.bulletFlag = flag;
		}
		else {
			gameState.leapModel = input;
			gameState.missileFlag = flag;
		}
	});

	srv.bind("getGameState", [&gameState](int id) {
		GameState currState = gameState;
		if (id == 1) {
			gameState.missileFlag = false;
		}
		else {
			gameState.bulletFlag = false;
		}
		return currState;
	});

	srv.run();
	return 0;
}