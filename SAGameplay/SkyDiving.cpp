#include "SkyDiving.h"


HOOK(void, __fastcall, _ClassicAddCallback, 0x00DEA4B0, Sonic::Player::CSonicClassic* This, void*,
	const Hedgehog::Base::THolder<Sonic::CWorld>& in_rWorldHolder,
	Sonic::CGameDocument* in_pGameDocument, const boost::shared_ptr<Hedgehog::Database::CDatabase>& in_spDatabase)
{
	original_ClassicAddCallback(This, 0, in_rWorldHolder, in_pGameDocument, in_spDatabase);

	This->m_PostureStateMachine.RegisterStateFactory
	(
		std::move(hh::base::CSharedString(Sonic::Player::CSonicClassicPostureDiving::ms_pStateName)),
		[] { return boost::make_shared<Sonic::Player::TPostureDiving<Sonic::Player::CPlayerSpeedPosture3DCommon>>(bb_null_ctor{}); }
	);

	This->m_spAnimationStateMachine->GetAnimationState("SkyDivingStart")->SetTransitionState("SkyDiving");
	This->m_spAnimationStateMachine->SetBlend("SkyDivingStart", "SkyDiving", 0.2f);
	This->m_spAnimationStateMachine->SetBlend("SkyDiving", "Fall", 0.3f);
}

// Patch dive state parameter indexes
static void __declspec(naked) FloatGetParameterPatch()
{
	static constexpr int fn = 0x0053A9F0;
	__asm
	{
		push eax
		mov eax, [esi]
		push ecx
		mov ecx, 0x016D86FC
		cmp eax, ecx
		jz jump

		pop ecx
		pop eax
		jmp[fn]

		jump:
		mov eax, [esp + 12]
			mov ecx, 0x21
			sub eax, ecx
			mov[esp + 12], eax
			pop ecx
			pop eax
			jmp[fn]
	}
}
// Safeguard
HOOK(void*, __fastcall, _PlayAisacSoundLooping, 0x00763D50, void* This, void*, const Hedgehog::Base::CSharedString& in_rName, float in_Strength)
{
	if (!This)
		return nullptr;
	original_PlayAisacSoundLooping(This, 0, in_rName, in_Strength);
}

HOOK(void, __fastcall, _SonicClassicProcMsgStartDiveMode, 0x00DDA510, Sonic::Player::CSonicClassic* This, void*, const MsgStartDiveMode& msg)
{
	auto* pContext = This->GetContext();
	if (*(uint32_t*)pContext == idModernContext || !((!pContext->m_Is2DMode || msg.m_DiveModeData.Force2DMode) && !pContext->StateFlag(eStateFlag_Diving)))
		return;

	pContext->m_DiveModeData = msg.m_DiveModeData;

	pContext->ChangeState("DivingFloat");
	auto* pPosture = static_cast<Sonic::Player::CSonicClassicPostureDiving*>(pContext->ChangePosture("Diving", false));

	pPosture->m_Field080 = msg.m_DiveModeData.m_VectorA;
	pPosture->m_Field090 = msg.m_DiveModeData.m_Field30;
	pPosture->m_TargetAngle = atan2(msg.m_DiveModeData.Direction.x(), msg.m_DiveModeData.Direction.z());

	FUNCTION_PTR(void, __thiscall, ChangeCollision, 0x00DDB610, Sonic::Player::CPlayer*, int);
	ChangeCollision(This, 4);
}


void SkyDiving::Init()
{
	INSTALL_HOOK(_ClassicAddCallback)
	INSTALL_HOOK(_SonicClassicProcMsgStartDiveMode)

    // Patch skydive anims
    WRITE_MEMORY(0x01285892 + 6, char*, "sc_dive_loop")
    WRITE_MEMORY(0x01285960 + 6, char*, "sc_dive_loop")
    WRITE_MEMORY(0x012859C7 + 6, char*, "sc_dive_loop")
    WRITE_MEMORY(0x012858F9 + 6, char*, "sc_dive_loop")

    WRITE_MEMORY(0x01285A29 + 6, char*, "sc_jump_loop")
    WRITE_MEMORY(0x01285A95 + 6, char*, "sc_jump_loop")
}