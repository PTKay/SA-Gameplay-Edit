#pragma once
#include "Extra/BlueBlurExtensions.h"

namespace Sonic::Player
{
	// Child class of a few states that doesnt really make sense.
	class CPlayerSpeedPostureBridge : public IPosture
	{
	public:
		CPlayerSpeedPostureCommon* m_pBridgePosture = nullptr;

		CPlayerSpeedPostureBridge(const bb_null_ctor& nil) : IPosture(nil) {}
		CPlayerSpeedPostureBridge(const Hedgehog::Base::CSharedString& name) : IPosture(name) {}
	};

	BB_ASSERT_OFFSETOF(CPlayerSpeedPostureBridge, m_pBridgePosture, 0x64);

	// Holding this for now
	__declspec(noinline) void DoGravityThing(CPlayerSpeedContext* context, float deltaTime, float multiplier);

	class __declspec(dllexport) CSonicClassicPostureDiving : public CPlayerSpeedPostureBridge
	{
	public:
		static inline const char* ms_pStateName = "Diving";

		float m_Field068{};
		float m_Field06C{};
		float m_Field070{};
		float m_Field074{};
		int m_Field078{};
		int m_Field07C{};
		Hedgehog::Math::CVector m_Field080{};
		float m_Field090{};
		float m_TargetAngle{};
		float m_HorizontalRotationRate{};

		CSonicClassicPostureDiving(const bb_null_ctor& nil) : CPlayerSpeedPostureBridge(nil) {}
		CSonicClassicPostureDiving() : CPlayerSpeedPostureBridge("CSonicClassicPostureDiving") {}

		CSonicClassicPostureDiving(const Hedgehog::Base::CSharedString& name) : CPlayerSpeedPostureBridge(name) {}

		BB_OVERRIDE_FUNCTION_PTR_NOARG(void, Hedgehog::Universe::CStateMachineBase::CStateBase, EnterState, 0x00DF69D0);
		BB_OVERRIDE_FUNCTION_PTR_NOARG(void, Hedgehog::Universe::CStateMachineBase::CStateBase, LeaveState, 0x00DF6990);

		void UpdateState();
	};
	BB_ASSERT_SIZEOF(CSonicClassicPostureDiving, 0xA0);

	static void __declspec(naked) DivePostureCtor_ASM()
	{
		static constexpr int fn = 0x0051BC30;
		__asm
		{
			mov edi, ecx
			jmp[fn]
		}
	}
	static BB_FUNCTION_PTR(void*, __fastcall, fpDivePostureCtor, DivePostureCtor_ASM, CSonicClassicPostureDiving* This);
	static void __declspec(noinline) HackConstructor(CSonicClassicPostureDiving* This)
	{
		int vtableOriginal = *(int*)This;
		fpDivePostureCtor(This);
		*(int*)This = vtableOriginal;

		// attempted hack
		WRITE_MEMORY(&((int**)This)[0][1], int, 0x0051C3E0); // replace dtor
	}


	template <typename T>
	class TPostureDiving : public CSonicClassicPostureDiving
	{
	public:
		TPostureDiving(const bb_null_ctor& nil) : CSonicClassicPostureDiving(nil)
		{
			HackConstructor(this);
			m_ClassName = "CSonicClassicPostureDiving";
		}
		TPostureDiving() : CSonicClassicPostureDiving() {}
	};
	BB_ASSERT_SIZEOF(TPostureDiving<void>, 0xA0);
}