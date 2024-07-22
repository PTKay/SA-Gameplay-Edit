#pragma once
#include "PostureDiving.h"

// TODO: move
class __declspec(align(8)) MsgStartDiveMode : public Hedgehog::Universe::MessageTypeSet
{
public:
	Sonic::Player::CPlayerSpeedContext::SDiveModeData m_DiveModeData;
};

namespace SkyDiving
{
	void Init();
};