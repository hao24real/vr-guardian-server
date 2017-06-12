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
	std::array<float, 16> elements = { 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f };
	MSGPACK_DEFINE_ARRAY(elements);
};

struct GameState {
	bool missileFlag = false, bulletFlag = false;

	CMat4 vrHeadModel;
	CMat4 vrBodyModel;
	CMat4 vrGunModel;
	
	CMat4 leapLauncher;
	CMat4 leapBody;

	MSGPACK_DEFINE_ARRAY(missileFlag, bulletFlag, vrHeadModel,
		vrBodyModel, vrGunModel, leapLauncher, leapBody);
};


int main() {

	rpc::server srv(8080);

	GameState gameState;

	srv.bind("updateVRGameState", [&gameState](CMat4 vrHeadModel, 
		CMat4 vrBodyModel, CMat4 vrGunModel, bool bulletFlag) {
		gameState.vrHeadModel = vrHeadModel;
		gameState.vrBodyModel = vrBodyModel;
		gameState.vrModel = vrGunModel;
		gameState.bulletFlag = bulletFlag;

	});

	srv.bind("updateLeapGameState", [&gameState](CMat4 leapLauncher, CMat4 leapBody, bool missileFlag) {
		gameState.leapModel = leapLauncher;
		gameState.leapBody = leapBody;
		gameState.missileFlag = missileFlag;
	});

	srv.bind("getVRGameState", [&gameState]() {
		GameState currState = gameState;
		gameState.missileFlag = false;
		return currState;
	});

	srv.bind("getLeapGameState", [&gameState](){
		GameState currState = gameState;
		gameState.bulletFlag = false;
		return currState;
	});

	srv.run();
	return 0;
}