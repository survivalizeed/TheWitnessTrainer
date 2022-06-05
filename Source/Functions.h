#pragma once

#include "Includes.h"

class Dialog;

void fnRemAutoPosition(std::shared_ptr<Trainer> witness, bool active);

void fnFlyControls(std::shared_ptr<Trainer> witness, Dialog& dialog, mINI::INIStructure& ini);

void fnSprintControls(std::shared_ptr<Trainer> witness, Dialog& dialog, mINI::INIStructure& ini, int& sprintKey);

void fnRestoreAll(std::shared_ptr<Trainer> witness);

void fnStickToProcess(Dialog& dialog, bool& hide);

void fnSprintKey(std::shared_ptr<Trainer> witness, mINI::INIStructure& ini, int& sprintKey);

void fnTeleport(std::shared_ptr<Trainer> witness, Dialog& dialog, mINI::INIStructure& ini, float x, float y, float z, float yaw, float pitch);

void fnExportRes(int id, const char* type, const char* destination);