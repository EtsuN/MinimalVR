#ifndef PLAYER_H
#define PLAYER_H

#include "Cube.h"
#include "Model.h"


#include "rpc/client.h"
struct PlayerInfo {
	int heldWeapon;
	glm::mat4 headInWorld;
	glm::mat4 rhandInWorld;
	glm::mat4 lhandInWorld;

	MSGPACK_DEFINE_MAP(heldWeapon,
		headInWorld[0][0], headInWorld[0][1], headInWorld[0][2], headInWorld[0][3],
		headInWorld[1][0], headInWorld[1][1], headInWorld[1][2], headInWorld[1][3],
		headInWorld[2][0], headInWorld[2][1], headInWorld[2][2], headInWorld[2][3],
		headInWorld[3][0], headInWorld[3][1], headInWorld[3][2], headInWorld[3][3],

		rhandInWorld[0][0], rhandInWorld[0][1], rhandInWorld[0][2], rhandInWorld[0][3],
		rhandInWorld[1][0], rhandInWorld[1][1], rhandInWorld[1][2], rhandInWorld[1][3],
		rhandInWorld[2][0], rhandInWorld[2][1], rhandInWorld[2][2], rhandInWorld[2][3],
		rhandInWorld[3][0], rhandInWorld[3][1], rhandInWorld[3][2], rhandInWorld[3][3],

		lhandInWorld[0][0], lhandInWorld[0][1], lhandInWorld[0][2], lhandInWorld[0][3],
		lhandInWorld[1][0], lhandInWorld[1][1], lhandInWorld[1][2], lhandInWorld[1][3],
		lhandInWorld[2][0], lhandInWorld[2][1], lhandInWorld[2][2], lhandInWorld[2][3],
		lhandInWorld[3][0], lhandInWorld[3][1], lhandInWorld[3][2], lhandInWorld[3][3]
		);
};

class Player
{
private:
	Model* head;
	Model* handSphere;
public:

	bool isMe;
	
	int heldWeapon;
	glm::mat4 weaponToPlayer;
	glm::mat4 headToPlayer;
	glm::mat4 rhandToPlayer;
	glm::mat4 lhandToPlayer;

	glm::mat4 toWorld;

	//constant
	float handScale = 0.1;
	float headScale = 0.5;

	Player(glm::mat4 M, bool isMe, Model* sphere) {
		toWorld = M;
		isMe = isMe;
		handSphere = sphere;
		head = nullptr; //TODO

		headToPlayer = glm::mat4(1);
		rhandToPlayer = glm::translate(glm::mat4(1), glm::vec3(1, -1, 0));
		lhandToPlayer = glm::translate(glm::mat4(1), glm::vec3(-1, -1, 0));
	};

	void updatePlayer(glm::mat4 h, glm::mat4 r, glm::mat4 l) {
		headToPlayer = h;
		rhandToPlayer = r;
		lhandToPlayer = l;
	};

	void draw(unsigned int shader, const glm::mat4& p = glm::mat4(1), const glm::mat4& v = glm::mat4(1)) {
		glUseProgram(shader);

		//Assuming uniform is set


		//Head 
		if (!isMe) {
			glUniform3fv(glGetUniformLocation(shader, "objectColor"), 1, &(glm::vec3(1, 1, 1))[0]);
			glUniformMatrix4fv(glGetUniformLocation(shader, "model"), 1, GL_FALSE, &(getHeadPose())[0][0]);
			handSphere->Draw(shader);
		}

		//Left Hand
		glUniform3fv(glGetUniformLocation(shader, "objectColor"), 1, &(glm::vec3(1, 0, 1))[0]);
		glUniformMatrix4fv(glGetUniformLocation(shader, "model"), 1, GL_FALSE, &(getLHandPose())[0][0]);
		handSphere->Draw(shader);

		//Right Hand
		glUniform3fv(glGetUniformLocation(shader, "objectColor"), 1, &(glm::vec3(1, 1, 0))[0]);
		glUniformMatrix4fv(glGetUniformLocation(shader, "model"), 1, GL_FALSE, &(getRHandPose())[0][0]);
		handSphere->Draw(shader);
	};


	glm::mat4 getHeadPose() {
		return toWorld * headToPlayer * glm::scale(glm::mat4(1), glm::vec3(headScale));
	};
	glm::mat4 getLHandPose() {
		return toWorld * lhandToPlayer * glm::scale(glm::mat4(1), glm::vec3(handScale));
	};
	glm::mat4 getRHandPose() {
		return toWorld * rhandToPlayer * glm::scale(glm::mat4(1), glm::vec3(handScale));
	};

	PlayerInfo getPlayerInfo() {
		PlayerInfo info;
		info.headInWorld = getHeadPose();
		info.rhandInWorld = getRHandPose();
		info.lhandInWorld = getLHandPose();
		info.heldWeapon = heldWeapon;
		return info;
	};

};


#endif