#include "PostureDiving.h"

#include "include/MathUtil.h"
#include "extra/BlueBlurExtensions.h"

namespace Sonic::Player
{
	// Holding this for now
	__declspec(noinline) void DoGravityThing(CPlayerSpeedContext* context, float deltaTime, float multiplier)
	{
		uint32_t func = 0x00E59C30;
		__asm
		{
			mov eax, context
			push multiplier
			push deltaTime
			call func
		}
	}

	void DiveFuncSetSomeDeltatimeThing(float* a1, Hedgehog::Universe::TStateMachine<CPlayerContext>::TState* a2, float* a3, float a4)
	{
		double v4; // st7
		float v5; // [esp+Ch] [ebp-10h]
		float v6; // [esp+10h] [ebp-Ch]

		const float deltaTime = a2->GetDeltaTime();
		v4 = static_cast<CPlayerSpeedContext*>(a2->GetContext())->StateFlag(eStateFlag_DivingFloat) ? 160.0 : 120.0;
		v6 = v4;
		v5 = v4;
		MathUtil::WrapFloatGivenCrap(a3, *a1, a4, 30.0, v5, v6, deltaTime);
		*a1 = deltaTime * *a3 + *a1;
	}
}

static __declspec(noinline) __declspec(naked) void fGetActiveAnimStateBlend()
{
	static constexpr int fn = 0x00E73690;
	__asm
	{
		mov eax, ecx
		jmp [fn]
	}
}
BB_FUNCTION_PTR(void*, __thiscall, GetActiveAnimStateBlend, fGetActiveAnimStateBlend, Sonic::Player::CPlayerSpeedContext* This);

void Sonic::Player::CSonicClassicPostureDiving::UpdateState()
{
	using namespace hh::math;
	CPlayerSpeedContext* pContext = GetContext();
	const float deltaTime = GetDeltaTime();


	// Clean this up later

	float diveVelocityFront; // xmm0_4
	CVector* rightDir; // eax
	CVector* leftDir; // eax
	bool v9; // zf
	CVector v10; // xmm1
	float v12; // xmm2_4
	float v15; // xmm2_4

	float v17; // xmm0_4
	float v18; // xmm0_4
	float v19; // xmm1_4
	float v20; // xmm0_4
	float v21; // xmm0_4
	CPlayerSpeedContext* v23; // eax
	float v25; // xmm0_4
	float v26; // xmm0_4
	float v27; // xmm0_4
	float v28; // xmm0_4
	float v29; // xmm0_4
	float v30; // xmm0_4
	float v31; // xmm0_4
	double v33; // st7
	double v35; // st7
	float v45; // xmm0_4
	Sonic::CMatrixNodeTransform* spMatrixNode; // ebx
	float a2; // [esp+10h] [ebp-108h]
	float scalara; // [esp+14h] [ebp-104h]
	float scalarb; // [esp+14h] [ebp-104h]
	float scalar; // [esp+14h] [ebp-104h]
	float scalarc; // [esp+14h] [ebp-104h]
	float scalard; // [esp+14h] [ebp-104h]
	float scalare; // [esp+14h] [ebp-104h]
	float v63; // [esp+2Ch] [ebp-ECh]
	float v64; // [esp+2Ch] [ebp-ECh]
	float v65; // [esp+2Ch] [ebp-ECh]
	float v67; // [esp+30h] [ebp-E8h]
	float v68; // [esp+30h] [ebp-E8h]
	float v69; // [esp+30h] [ebp-E8h]
	float v70; // [esp+30h] [ebp-E8h]
	bool divingFloat; // [esp+37h] [ebp-E1h]
	CVector value; // [esp+58h] [ebp-C0h] BYREF
	CVector diveVelocity; // [esp+68h] [ebp-B0h] BYREF
	//CVector _; // [esp+78h] [ebp-A0h] BYREF
	float diveVelocitySide; // [esp+94h] [ebp-84h]
	CVector velocityVec; // [esp+98h] [ebp-80h] BYREF

	// Hardcoded params
	const float DivingDamageTime = 1;
	const float DivingDamageVelocityDecreaseRate = 0.5;
	const float DivingDiveBeginGravityScale = 2.4;
	const float DivingDiveBeginHorzVelocityRate = 0.85;
	const float DivingDiveEndSpeed = 20;
	const float DivingDiveMaxVelocityDown = 90.1;
	const float DivingDiveVelocityFront = 0.7;
	const float DivingDiveVelocitySide = 0.7;
	const float DivingFloatMaxVelocityDown = 40;
	const float DivingFloatVelocityFront = 0.4;
	const float DivingFloatVelocitySide = 0.4;
	const float DivingRotationMax = 20;


	FUNCTION_PTR(void, __cdecl, sub_6F2730, 0x6F2730, CVector * a1, CVector * a2, float a3, float a4);

	m_Field080 = pContext->m_DiveModeData.m_VectorA;
	m_TargetAngle = atan2(pContext->m_DiveModeData.Direction.x(), pContext->m_DiveModeData.Direction.z());
	m_Field090 = pContext->m_DiveModeData.m_Field30;
	pContext->m_VerticalRotation = CQuaternion::Identity();
	diveVelocity = CVector::Up();
	CMatrix44 _v4 = pContext->m_VerticalRotation.ToRotationMatrix();
	pContext->m_ModelUpDirection = _v4.TransformVector(CVector::Up());
	pContext->m_spMatrixNode->m_Transform.SetRotation(pContext->m_VerticalRotation * pContext->m_HorizontalRotation);
	pContext->m_spMatrixNode->NotifyChanged();

	a2 = deltaTime;
	DoGravityThing(pContext, a2, 0.0);
	divingFloat = pContext->StateFlag(eStateFlag_DivingFloat);
	if (divingFloat)
	{
		diveVelocitySide = DivingFloatVelocitySide;
		diveVelocityFront = DivingFloatVelocityFront;
	}
	else
	{
		diveVelocitySide = DivingDiveVelocitySide;
		diveVelocityFront = DivingDiveVelocityFront;
	}
	v63 = diveVelocityFront;
	diveVelocity = CVector::Identity();
	CVector _rightVector = pContext->GetRightDirection();
	rightDir = &_rightVector;
	scalara = m_Field06C * diveVelocitySide;
	CVector::Multiply(&velocityVec, rightDir, scalara);
	diveVelocity = (*&velocityVec + diveVelocity);
	CVector _frontDir = pContext->GetFrontDirection();
	leftDir = &_frontDir;
	scalarb = m_Field068 * diveVelocityFront;
	CVector::Multiply(&velocityVec, leftDir, scalarb);
	v9 = !pContext->m_VelocityChanged;
	v10 = velocityVec + diveVelocity;
	diveVelocity = v10;
	if (!v9)
	{
		pContext->HandleVelocityChanged();
		v10 = diveVelocity;
	}
	value = pContext->m_HorizontalVelocity;
	v12 = value.squaredNorm();
	scalar = deltaTime;
	if (v12 <= v10.squaredNorm())
		sub_6F2730(&value, &diveVelocity, 20.0, scalar);
	else
		sub_6F2730(&value, &diveVelocity, 2.0, scalar);
	if (pContext->m_VelocityChanged)
		pContext->HandleVelocityChanged();
	pContext->m_HorizontalVelocity = value;
	pContext->m_HorizontalOrVerticalVelocityChanged = true;
	pContext->m_VelocityChanged = false;
	if (divingFloat)
	{
		v67 = DivingFloatMaxVelocityDown;
		v15 = pContext->m_spParameter->Get<float>(ePlayerSpeedParameter_Gravity);
		float _v16 = pContext->GetVelocity().y();
		v17 = v67 * v67;
		v18 = v15 / v17;
		v19 = _v16 * _v16;
		v20 = v18 * v19;
		v68 = v20;
	}
	else
	{
		v69 = DivingDiveMaxVelocityDown;
		v21 = pContext->m_spParameter->Get<float>(ePlayerSpeedParameter_Gravity) / v69;
		v68 = fabs(pContext->GetVelocity().y()) * v21;
	}
	if (pContext->m_VelocityChanged)
		pContext->HandleVelocityChanged();
	double norm = pContext->m_VerticalVelocity.norm();
	float __a3 = norm / deltaTime;
	if (__a3 <= (double)v68)
		v68 = __a3;
	if (pContext->m_VelocityChanged)
		pContext->HandleVelocityChanged();
	value = pContext->m_VerticalVelocity.normalizedSafe();
	CVector::Multiply(&velocityVec, &value, -v68);
	CVector::Multiply(&diveVelocity, &velocityVec, deltaTime);
	pContext->AddVelocity(diveVelocity);
	v23 = pContext;

	CVector WorldInput = v23->m_WorldInput;

	value = (pContext->m_spMatrixNode->m_Transform.m_Position - m_Field080);
	value.y() = 0;
	float a3 = CVector::Length(&value);
	diveVelocity = value.normalizedSafe();
	v25 = (m_Field090 - a3) / 3.0;
	if (v25 > 1.0)
		v25 = 1.0;
	if (v25 < 0.0)
		v25 = 0.0;
	v70 = v25;
	if (diveVelocitySide > (double)v63)
		v63 = diveVelocitySide;
	v26 = DivingRotationMax;
	v9 = pContext->m_HorizontalOrVerticalVelocityChanged == 0;
	v27 = v26 * (v63 * v70);
	diveVelocitySide = v27;
	if (!v9)
	{
		pContext->m_Velocity = (pContext->m_HorizontalVelocity + pContext->m_VerticalVelocity);
		pContext->m_HorizontalOrVerticalVelocityChanged = false;
		pContext->m_VelocityChanged = false;
	}
	velocityVec = pContext->m_Velocity;
	v64 = CVector::Dot(&velocityVec, &diveVelocity);
	if (v64 >= 0.0)
		v28 = v64;
	else
		v28 = 0.0;
	velocityVec = (velocityVec - (diveVelocity * v28));

	CVector thing;
	if (v28 <= (double)diveVelocitySide)
		thing = diveVelocity * v28;
	else
		thing = diveVelocity * diveVelocitySide;
	pContext->m_Velocity = (thing + velocityVec);
	pContext->m_VelocityChanged = true;
	pContext->m_HorizontalOrVerticalVelocityChanged = false;
	v29 = m_Field090 - 3.0;
	if (v29 < 0.0)
		v29 = 0.0;
	if (a3 > (double)v29)
	{
		v65 = CVector::Dot(WorldInput, diveVelocity);
		if (v65 >= 0.0)
			v30 = v65;
		else
			v30 = 0.0;
		WorldInput = (WorldInput - (diveVelocity * v30));
		v31 = v30 * v70;
		WorldInput = ((diveVelocity * v31) + WorldInput);
	}
	// ..This isnt used.
	/*v66 = CVector::Dot(&value, &diveVelocity);
	CVector::Multiply((CVector*)&_, &diveVelocity, v66);
	*/
	// .. Neither is this???
	/*
	if (_m_Field090 <= (double)*(float*)a3)
		*(float*)a3 = _m_Field090;
	CVector::Multiply((CVector*)&_, &diveVelocity, *(float*)a3);
	*/
	v33 = CVector::Dot(WorldInput, pContext->GetRightDirection());

	DiveFuncSetSomeDeltatimeThing(&m_Field06C, this, &m_Field074, v33 * DivingRotationMax);

	v35 = CVector::Dot(WorldInput, pContext->GetFrontDirection());
	float fuckidk = v35 * DivingRotationMax;
	DiveFuncSetSomeDeltatimeThing(&m_Field068, this, &m_Field070, fuckidk);

	const float sign = divingFloat ? -1.0f : 1.0f;
	pContext->m_VerticalRotation = CQuaternion::FromAngleAxis(m_Field068 * sign * 0.01745329238474369, pContext->GetRightDirection())
		* CQuaternion::FromAngleAxis(-m_Field06C * sign * 0.01745329238474369, pContext->GetFrontDirection());
	pContext->m_ModelUpDirection = pContext->m_VerticalRotation.ToRotationMatrix().TransformVector(CVector::Up());

	pContext->m_spMatrixNode->m_Transform.SetRotation(pContext->m_VerticalRotation* pContext->m_HorizontalRotation);
	pContext->m_spMatrixNode->NotifyChanged();

#if 0
	CVector frontDir = pContext->GetFrontDirection();
	float frontDirectionAngle = atan2(frontDir.x(), frontDir.z());
	MathUtil::WrapFloatGivenCrap(&m_HorizontalRotationRate,
		frontDirectionAngle,
		//-180.0f * MathUtil::DegreesToRadians,
		m_TargetAngle,

		90.0f * MathUtil::DegreesToRadians,
		180.0f * MathUtil::DegreesToRadians,
		360.0f * MathUtil::DegreesToRadians,
		//0.0f, 90.0f * MathUtil::DegreesToRadians, 360.0f * MathUtil::DegreesToRadians,

		deltaTime);

	rotationAxis = frontDirectionAngle + m_HorizontalRotationRate * deltaTime;
	pContext->m_HorizontalRotation = CQuaternion::FromAngleAxis(rotationAxis, CVector::Up());
#endif

	CQuaternion targetHorizontalRotation = CQuaternion::FromAngleAxis(180.0f * MathUtil::DegreesToRadians, CVector::Up());
	//pContext->m_HorizontalRotation = CQuaternion::RotateTowards(pContext->m_HorizontalRotation, targetHorizontalRotation, 180.0f * MathUtil::DegreesToRadians * deltaTime);
	pContext->m_HorizontalRotation = CQuaternion::Slerp(pContext->m_HorizontalRotation, targetHorizontalRotation, 1.0f - exp(-4.0f * deltaTime));

	spMatrixNode = pContext->m_spMatrixNode.get();
	spMatrixNode->m_Transform.SetRotation(pContext->m_VerticalRotation * pContext->m_HorizontalRotation);
	spMatrixNode->NotifyChanged();

	// Base state
	m_pBridgePosture->m_Time = m_Time;
	m_pBridgePosture->UpdateState();
}

extern "C" __declspec(dllexport) Sonic::Player::CSonicClassicPostureDiving * VerifyRTTI()
{
	auto* pState = new Hedgehog::Universe::TStateMachine<Sonic::Player::CPlayerContext>::TState;
	return dynamic_cast<Sonic::Player::CSonicClassicPostureDiving*>(pState);
}