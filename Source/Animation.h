#pragma once

#include "Includes.h"

class Dialog;

struct Vec3 {
	float x, y, z;

	float Normalize() {
		float r = sqrtf(x * x + y * y + z * z);
		x /= r;
		y /= r;
		z /= r;
		return r;
	}
};

struct AnimationNode {
	Vec3 position, speed;
	float rotH, rotV, rotHs, rotVs;

	AnimationNode(Vec3 position, Vec3 speed, float rotH, float rotV, float rotHs, float rotVs) 
		: position(position), speed(speed), rotH(rotH), rotV(rotV), rotHs(rotHs), rotVs(rotVs) {}

};

class Animation {
	std::shared_ptr<Trainer> witness;
	std::vector<AnimationNode> nodes;
public:
	Animation(std::shared_ptr<Trainer> witness) : witness(witness) {}

	void Add(const AnimationNode& node);

	void StartAnimation(Dialog& dialog);

	void TowAnim(std::string_view path);

	void LoadwAnim(std::string_view path);

	void AddPosNode();
	
	static float DegToWitRad(float deg);

	static float WitRadToDegH(float witRad);

	static float WitRadToDegV(float witRad);
};

