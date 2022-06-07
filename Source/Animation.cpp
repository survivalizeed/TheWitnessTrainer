#include "Animation.h"

void Animation::Add(const AnimationNode& node)
{
	nodes.push_back(node);
}

void Animation::StartAnimation(Dialog& dialog)
{
	fnRemAutoPosition(witness, true);
	witness->Patch("NoNodLimit", 0x14023CCA2, { 0x90,0x90,0x90,0x90 });
	auto lamNear = [](float l, float r) {
		if (abs(l - r) <= 0.1f) return true;
		return false;
	};
	for (int i = 0; i < nodes.size() - 1; ++i) {
		auto& current = nodes[i];
		auto& next = nodes[i + 1];
		Vec3 dir{};
		dir.x = next.position.x - current.position.x;
		dir.y = next.position.y - current.position.y;
		dir.z = next.position.z - current.position.z;
		float nf = dir.Normalize();
		
		float rotHinc{};
		float rotVinc{};

		float curH = current.rotH, curV = current.rotV;

		Vec3 curPos = current.position;

		bool xT, yT, zT, rH, rV;
		xT = yT = zT = rH = rV = false;


		float dist = abs(curH - next.rotH);
		dist /= nf;

		if (curH < next.rotH) {
			if (next.rotH - curH < 180) rotHinc = dist * current.rotHs;
			else rotHinc = dist * -current.rotHs;
		}
		if (next.rotH < curH) {
			if (curH - next.rotH < 180) rotHinc = dist * -current.rotHs;
			else rotHinc = dist * current.rotHs;
		}

		dist = abs(curV - next.rotV);
		dist /= nf;

		if (curV - next.rotV > 0) rotVinc = dist * -current.rotVs;
		else rotVinc = dist * current.rotVs;
		
		if (curH == next.rotH) rH = true;
		if (curV == next.rotV) rV = true;

		while (true) {
			if(!xT)
				curPos.x += dir.x * current.speed.x;
			if (!yT)
				curPos.y += dir.y * current.speed.y;
			if (!zT)
				curPos.z += dir.z * current.speed.z;
			
			witness->Write("XPos", curPos.x);
			witness->Write("YPos", curPos.y);
			witness->Write("YCamPos", curPos.y + 1.69f);
			witness->Write("ZPos", curPos.z);
			
			if(!rH)
				curH += rotHinc;
			if(!rV)
				curV += rotVinc;

			if (curH > 360) curH -= 360;
			if (curH < 0) curH += 360;

			witness->Write("LeftRightRotYaw", DegToWitRad(curH));
			witness->Write("UpDownRotPitch", DegToWitRad(curV));

			if (lamNear(curPos.x, next.position.x)) xT = true;
			if (lamNear(curPos.y, next.position.y)) yT = true;
			if (lamNear(curPos.z, next.position.z)) zT = true;
			if (lamNear(curH, next.rotH)) rH = true;
			if (lamNear(curV, next.rotV)) rV = true;
			if (xT && yT && zT && rH && rV) break;
		}
	}
	if(!dialog.GetEntry("gameChanger", "fly")->second)
		fnRemAutoPosition(witness, false);
	if(!dialog.GetEntry("fun", "noNodLimit")->second)
		witness->Restore("NoNodLimit");
}

void Animation::TowAnim(std::string_view path)
{
	using namespace std;
	ofstream file(path.data() + std::string(".wAnim"));
	for (int i = 0; i < nodes.size(); ++i) {	
		string str = to_string(nodes[i].position.x) + "," + to_string(nodes[i].position.y)
			+ "," + to_string(nodes[i].position.z) + "," + to_string(nodes[i].speed.x) + "," + to_string(nodes[i].speed.y)
			+ "," + to_string(nodes[i].speed.z) + "," + to_string(nodes[i].rotH) + "," + to_string(nodes[i].rotV)
			+ "," + to_string(nodes[i].rotHs) + "," + to_string(nodes[i].rotVs) + "|";
		file << str;
	}
}

void Animation::LoadwAnim(std::string_view path)
{
	using namespace std;
	this->nodes.clear();
	ifstream file(path.data() + std::string(".wAnim"));
	if (!file.good()) {
		error("File not found!", witness);
	}
	stringstream ss;
	ss << file.rdbuf();
	string buf = ss.str();
	vector<float> parts;
	string tmp;
	for (int i = 0; i < buf.size(); ++i) {	
		if (buf[i] == ',') {
			try {
				parts.push_back(stof(tmp));
				tmp.clear();
			}
			catch (...) {
				error("AnimationEntry invalid argument",witness);
			}
		}
		else if (buf[i] == '|') {
			try {
				try {
					parts.push_back(stof(tmp));
					tmp.clear();
				}
				catch (...) {
					error("AnimationEntry invalid argument", witness);
				}
				this->Add({ {parts[0], parts[1], parts[2]},{parts[3], parts[4], parts[5]}, parts[6], parts[7], parts[8], parts[9] });
			}
			catch (...) {
				error("AnimationEntry not complete", witness);
			}
			parts.clear();
		}
		else 
			tmp += buf[i];
	}
}

void Animation::AddPosNode()
{
	this->Add(AnimationNode({ witness->Read<float>("XPos"), witness->Read<float>("YPos"), witness->Read<float>("ZPos") },
		{ 0.0002f, 0.0002f, 0.0002f },
		Animation::WitRadToDegH(witness->Read<float>("LeftRightRotYaw")),
		Animation::WitRadToDegV(witness->Read<float>("UpDownRotPitch")), 0.0002f, 0.0002f));
}

void Animation::Clear()
{
	nodes.clear();
}


float Animation::DegToWitRad(float deg)
{
	deg *= float(M_PI) / 180;
	if (deg > float(M_PI)) deg -= float(M_PI * 2);
	return deg;
}

float Animation::WitRadToDegH(float witRad)
{
	witRad *= 180 / float(M_PI);
	if (witRad < 0) witRad = 360 - abs(witRad);
	return witRad;
}

float Animation::WitRadToDegV(float witRad)
{
	witRad *= 180 / float(M_PI);
	return witRad;
}

