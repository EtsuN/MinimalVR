#ifndef PLAYER_H
#define PLAYER_H

#include "Cube.h"
#include "Model.h"

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

};


#endif