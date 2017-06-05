// Server.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "rpc/server.h"
#include <iostream>
#include <string>
#include <glm/glm.hpp>
#include <vector>
#include <array>
using std::string;


struct CMat4 {
	std::array<float, 16> elements;
	MSGPACK_DEFINE_ARRAY(elements);
};


class GameState {

	CMat4 model1;
	CMat4 model2;
public:

	void setModel1(CMat4 model1)
	{
		this->model1 = model1;
	}

	void setModel2(CMat4 model2)
	{
		this->model2 = model2;
	}
	CMat4 getModel1() {
		return this->model1;
	}

	CMat4 getModel2() {
		return this->model2;
	}

};


int main() {

	rpc::server srv(8080);

	GameState gameState;

	srv.bind("setModel1", [&gameState](CMat4 input) {
		gameState.setModel1(input);
	});

	srv.bind("setModel2", [&gameState](CMat4 input) {
		gameState.setModel2(input);
	});

	srv.bind("getModel1", [&gameState]() {
		return gameState.getModel1();
	});

	srv.bind("getModel2", [&gameState]() {
		return gameState.getModel2();
	});

	srv.run();
	return 0;
}