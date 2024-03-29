struct Player //[base: 0x140062D0A8, offsets: { 0x148, 0x970, 0x228, 0x10, 0x50, 0x20, 0x30 }, byte_offset: -0x44]
{
	float* x_Pos; //this + 0x40
	float* y_Pos; //this + 0x44
	float* z_Pos; //this + 0x48
	float* x_Cam_Pos; //this + 0x140630490
	float* y_Cam_Pos; //this + 0x140630494
	float* z_Cam_Pos; //this + 0x140630498
	
	float* sprint_speed; //this + 0x150
	float* pitch; //0x1406303C0
	float* yaw; //0x1406303BC
	int* pitchlimiter; //0x14023CCA2
	
	long __fastcall puzzle_rotation_autocorrect(float a1, float a2); //0x140246470
	
	long __fastcall puzzle_solved(long param1, char param2, long param3); //0x1400BF330
	//Deciding line: 0x1400BF552
	
	char __fastcall environmental_puzzle_solved(char a1, __int64 a2); //0x14022DBF0
	//Deciding line: 0x14022DCFF
};

struct World
{
	bool __fastcall save_game(LPCCH lpMultiByteStr, long a2, const void *a3, DWORD a4); //0x140066350

	// Probably a function deep down in the callstack. 
	long __fastcall sound(long a1); //0x1402A94B0
	
}
