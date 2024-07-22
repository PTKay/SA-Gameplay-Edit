#pragma once

// TODO: Migrate

namespace Sonic::Message
{
	class MsgGetGroundInfo : public Hedgehog::Universe::MessageTypeGet
	{
	public:
		HH_FND_MSG_MAKE_TYPE(0x0167FB50);

		Hedgehog::Math::CVector m_GroundNormal;
		float m_Distance{};
		bool m_OnGround{};
		uint32_t m_GroundAttribute{};
	};

	class MsgGetCameraTargetPosition : public Hedgehog::Universe::MessageTypeGet
	{
	public:
		HH_FND_MSG_MAKE_TYPE(0x0167F690);

		Hedgehog::Math::CVector* m_pPosition{};
		float m_Offset = 0;
		bool m_boolA = false;
		bool m_NoOffset = false;
		bool m_UseModelMatrix = true;

		MsgGetCameraTargetPosition(hh::math::CVector* in_pPosition) : m_pPosition(in_pPosition) {}
		MsgGetCameraTargetPosition(hh::math::CVector* in_pPosition, bool in_NoOffset) : m_pPosition(in_pPosition), m_NoOffset(in_NoOffset) {}
	};
	class MsgGetVelocity : public Hedgehog::Universe::MessageTypeGet
	{
	public:
		HH_FND_MSG_MAKE_TYPE(0x016818A0);
		Hedgehog::Math::CVector* m_pVelocity{};

		MsgGetVelocity(Hedgehog::Math::CVector* in_pVelocity) : m_pVelocity(in_pVelocity) {}
	};
	class MsgGetFrontDirection : public Hedgehog::Universe::MessageTypeGet
	{
	public:
		HH_FND_MSG_MAKE_TYPE(0x0167F5AC)
			Hedgehog::Math::CVector* m_pFrontDirection{};

		MsgGetFrontDirection(Hedgehog::Math::CVector* in_pFrontDirection) : m_pFrontDirection(in_pFrontDirection) {}
	};
	class MsgGet2DPathPNT : public Hedgehog::Universe::MessageTypeGet
	{
	public:
		HH_FND_MSG_MAKE_TYPE(0x0167F558)
			float* m_pDistance{};
		Hedgehog::Math::CVector* m_pPosition{};
		Hedgehog::Math::CVector* m_pUp{};
		Hedgehog::Math::CVector* m_pForward{};

		MsgGet2DPathPNT(float* in_pDistance, Hedgehog::Math::CVector* in_pPosition, Hedgehog::Math::CVector* in_pUp, Hedgehog::Math::CVector* in_pForward)
			: m_pDistance(in_pDistance), m_pPosition(in_pPosition), m_pUp(in_pUp), m_pForward(in_pForward) {}
	};

	class MsgGetForCamera2DState : public Hedgehog::Universe::MessageTypeGet
	{
	public:
		HH_FND_MSG_MAKE_TYPE(0x0167F730)
			bool m_IsValid = false;
	};

	class MsgGetDriftState : public hh::fnd::MessageTypeGet
	{
	public:
		HH_FND_MSG_MAKE_TYPE(0x0167F660);

		bool m_IsDrifting;
		bool m_Cond2;
		bool m_IsRight;

		MsgGetDriftState()
		{
			m_IsDrifting = false;
			m_Cond2 = false;
			m_IsRight = false;
		}
	};

	class MsgGetForCamera3DState : public hh::fnd::MessageTypeGet
	{
	public:
		HH_FND_MSG_MAKE_TYPE(0x0167F718);

		bool m_IsNearBorder;
		BB_INSERT_PADDING(15) {};
		Hedgehog::Math::CVector m_WorldInput;
		bool m_IgnoreWorldInput;
		BB_INSERT_PADDING(15) {};

		MsgGetForCamera3DState()
		{
			using namespace hh::math;
			m_IsNearBorder = false;
			m_WorldInput = CVector::Zero();
			m_IgnoreWorldInput = false;
		}
	};

	BB_ASSERT_OFFSETOF(MsgGetForCamera3DState, m_IsNearBorder, 0x10);
	BB_ASSERT_OFFSETOF(MsgGetForCamera3DState, m_WorldInput, 0x20);
	BB_ASSERT_OFFSETOF(MsgGetForCamera3DState, m_IgnoreWorldInput, 0x30);

	class MsgGetDashModeInfo : public hh::fnd::MessageTypeGet
	{
	public:
		HH_FND_MSG_MAKE_TYPE(0x0167F79C);

		bool m_IsOnPath;
		bool m_Bool2;
		hh::math::CVector m_ClosestPointOnPath; // 0x20
		hh::math::CVector m_UpDirection; // 0x30
		hh::math::CVector m_FrontDirection; // 0x40
		float m_PathRadius;
		bool m_Bool3;

		MsgGetDashModeInfo()
		{
			using namespace hh::math;
			m_IsOnPath = false;
			m_Bool2 = false;
			m_Bool3 = false;
			m_ClosestPointOnPath = CVector::Zero();
			m_UpDirection = CVector::Zero();
			m_FrontDirection = CVector::Zero();
			m_PathRadius = 0;
		}
	};

	BB_ASSERT_OFFSETOF(MsgGetDashModeInfo, m_IsOnPath, 0x10);
	BB_ASSERT_OFFSETOF(MsgGetDashModeInfo, m_Bool2, 0x11);
	BB_ASSERT_OFFSETOF(MsgGetDashModeInfo, m_ClosestPointOnPath, 0x20);
	BB_ASSERT_OFFSETOF(MsgGetDashModeInfo, m_UpDirection, 0x30);
	BB_ASSERT_OFFSETOF(MsgGetDashModeInfo, m_FrontDirection, 0x40);
	BB_ASSERT_OFFSETOF(MsgGetDashModeInfo, m_PathRadius, 0x50);
	BB_ASSERT_OFFSETOF(MsgGetDashModeInfo, m_Bool3, 0x54);

	class MsgGetHomingAttackTargetInfo : public hh::fnd::MessageTypeGet
	{
	public:
		HH_FND_MSG_MAKE_TYPE(0x0167FB88);

		uint32_t m_TargetID = 0;
		hh::math::CVector m_Position = hh::math::CVector::Zero();
	};

	class MsgGetPreviousVelocity : public hh::fnd::MessageTypeGet
	{
	public:
		HH_FND_MSG_MAKE_TYPE(0x016818B0);

		hh::math::CVector* m_Velocity = nullptr;

		MsgGetPreviousVelocity(Hedgehog::Math::CVector* vec)
			: m_Velocity(vec)
		{
		}

		MsgGetPreviousVelocity(Hedgehog::Math::CVector& vec)
			: m_Velocity(&vec)
		{
		}
	};

	class MsgGetUpDirection : public hh::fnd::MessageTypeGet
	{
	public:
		HH_FND_MSG_MAKE_TYPE(0x0167F580);

		hh::math::CVector* m_Direction = nullptr;

		MsgGetUpDirection(Hedgehog::Math::CVector* vec)
			: m_Direction(vec)
		{
		}

		MsgGetUpDirection(Hedgehog::Math::CVector& vec)
			: m_Direction(&vec)
		{
		}
	};

	class MsgGetModelUpDirection : public hh::fnd::MessageTypeGet
	{
	public:
		HH_FND_MSG_MAKE_TYPE(0x0167F594);

		hh::math::CVector* m_Direction = nullptr;

		MsgGetModelUpDirection(Hedgehog::Math::CVector* vec)
			: m_Direction(vec)
		{
		}

		MsgGetModelUpDirection(Hedgehog::Math::CVector& vec)
			: m_Direction(&vec)
		{
		}
	};

	class MsgIsOnBoard : public hh::fnd::MessageTypeGet
	{
	public:
		HH_FND_MSG_MAKE_TYPE(0x0167F680);

		bool* m_IsOnBoard = nullptr;

		MsgIsOnBoard(bool* out)
			: m_IsOnBoard(out)
		{
		}

		MsgIsOnBoard(bool& out)
			: m_IsOnBoard(&out)
		{
		}
	};

	class MsgIsPlayerDead : public hh::fnd::MessageTypeGet
	{
	public:
		HH_FND_MSG_MAKE_TYPE(0x0167FF94);

		bool m_IsDead;

		MsgIsPlayerDead()
		{
			m_IsDead = false;
		}
	};

	BB_ASSERT_SIZEOF(MsgIsOnBoard, 0x14);
	BB_ASSERT_SIZEOF(MsgGetVelocity, 0x14);
	BB_ASSERT_SIZEOF(MsgGetGroundInfo, 0x30);
	BB_ASSERT_SIZEOF(MsgGetDriftState, 0x14);
	BB_ASSERT_SIZEOF(MsgGetDashModeInfo, 0x60);
	BB_ASSERT_SIZEOF(MsgGetForCamera3DState, 0x40);
	BB_ASSERT_SIZEOF(MsgGetCameraTargetPosition, 0x1C);
	BB_ASSERT_SIZEOF(MsgGetHomingAttackTargetInfo, 0x30);

	class MsgNotifyObjectEvent : public hh::fnd::MessageTypeSet
	{
	public:
		HH_FND_MSG_MAKE_TYPE(0x016811C0);

		int m_EventType = 0;
		bool m_Condition = false;

		MsgNotifyObjectEvent(int type) : m_EventType(type), m_Condition(false) {}
	};

	class MsgHitNotifyRigidBody : public hh::fnd::MessageTypeSet
	{
	public:
		HH_FND_MSG_MAKE_TYPE(0x016368D4);
	};


	class MsgGetPlayerType : public Hedgehog::Universe::MessageTypeGet
	{
	public:
		HH_FND_MSG_MAKE_TYPE(0x0167FF00);
	};

	class MsgApplyImpulse : public Hedgehog::Universe::MessageTypeSet
	{
	public:
		HH_FND_MSG_MAKE_TYPE(0x01680D84);

		Hedgehog::Math::CVector m_Vec01;
		Hedgehog::Math::CVector m_Vec02;
		float m_OutOfControl;
		float m_Unk09 = 0;
		int m_ImpulseFlags;
		float m_Unk11 = 0;
		bool m_SetVelocity;
		bool m_ActiveOnGround;
		char field_42 = 0;
		char field_43 = 0;
		char m_Unk13 = 0;
		char field_45 = 0;
		char field_46 = 0;
		char field_47 = 0;
		int m_Unk14 = 0;
		int m_Unk15 = 0;
		Hedgehog::Math::CVector m_Unk16 = hh::math::CVector::Zero();
		float m_Unk20 = -1.0f;
		int m_Unk21 = 0;
		int m_Unk22 = 0;
		int m_Unk23 = 0;

		MsgApplyImpulse(const hh::math::CVector& VecA, const hh::math::CVector& VecB, float outOfControl, int flags, bool setVelocity, bool activeOnGround = true)
			: m_Vec01(VecA),
			m_Vec02(VecB),
			m_OutOfControl(outOfControl),
			m_ImpulseFlags(flags),
			m_SetVelocity(setVelocity),
			m_ActiveOnGround(activeOnGround)
		{}
	};


	class MsgDamage : public hh::fnd::MessageTypeSet
	{
	public:
		HH_FND_MSG_MAKE_TYPE(0x01681E80);

		//Hedgehog::Base::SSymbolNode* m_DamageType {};
		uint32_t m_DamageType{};
		int m_Flag{};
		Hedgehog::Math::CVector m_PositionA{};
		Hedgehog::Math::CVector m_PositionB{};
		Hedgehog::Math::CVector m_Velocity{};
		int m_Unk3{};

		MsgDamage(uint32_t in_DamageType, const Hedgehog::Math::CVector& position, const Hedgehog::Math::CVector& velocity)
			: m_DamageType(in_DamageType), m_Flag(0), m_PositionA(position), m_PositionB(position), m_Velocity(velocity), m_Unk3(0)
		{}

		MsgDamage(uint32_t in_DamageType, const Hedgehog::Math::CVector& position)
			: m_DamageType(in_DamageType), m_Flag(0), m_PositionA(position), m_PositionB(position), m_Velocity(Hedgehog::Math::CVector::Zero()), m_Unk3(0)
		{}
	};
	BB_ASSERT_SIZEOF(MsgDamage, 0x60);


	class MsgDamageSuccess : public Hedgehog::Universe::MessageTypeSet
	{
	public:
		HH_FND_MSG_MAKE_TYPE(0x1681E6C);

		Hedgehog::Math::CVector m_Position;
		size_t m_Field20;
		size_t m_Field24; // value from MsgDamage + 0x14?
		float m_AwardBoostRatio; // used when m_AwardBoostType = 8, award boost by (MaxBoost * ratio)
		size_t m_AwardBoostType; // has to do with awarding boost
		bool m_Flag; // unknown?
		bool m_Field31; // always false?
		size_t m_DisableHitParticle;
		size_t m_DisableBounce;
		BB_INSERT_PADDING(0x4);

		// the same order as sub_4F9E90
		MsgDamageSuccess
		(
			Hedgehog::Math::CVector const& in_Position,
			bool in_Flag,
			size_t in_DisableHitParticle = 0,
			size_t in_DisableBounce = 0,
			size_t in_AwardBoostType = 0,
			float in_AwardBoostRatio = 0.0f,
			size_t in_Field20 = 0,
			size_t in_Field24 = 0
		)
			: m_Position(in_Position)
			, m_Flag(in_Flag)
			, m_Field20(in_Field20)
			, m_AwardBoostType(in_AwardBoostType)
			, m_Field24(in_Field24)
			, m_AwardBoostRatio(in_AwardBoostRatio)
			, m_Field31(0)
			, m_DisableHitParticle(in_DisableHitParticle)
			, m_DisableBounce(in_DisableBounce)
		{}
	};
	BB_ASSERT_OFFSETOF(MsgDamageSuccess, m_Position, 0x10);
	BB_ASSERT_OFFSETOF(MsgDamageSuccess, m_Field20, 0x20);
	BB_ASSERT_OFFSETOF(MsgDamageSuccess, m_Field24, 0x24);
	BB_ASSERT_OFFSETOF(MsgDamageSuccess, m_AwardBoostRatio, 0x28);
	BB_ASSERT_OFFSETOF(MsgDamageSuccess, m_AwardBoostType, 0x2C);
	BB_ASSERT_OFFSETOF(MsgDamageSuccess, m_Flag, 0x30);
	BB_ASSERT_OFFSETOF(MsgDamageSuccess, m_Field31, 0x31);
	BB_ASSERT_OFFSETOF(MsgDamageSuccess, m_DisableHitParticle, 0x34);
	BB_ASSERT_OFFSETOF(MsgDamageSuccess, m_DisableBounce, 0x38);
	BB_ASSERT_SIZEOF(MsgDamageSuccess, 0x40);

	// Have these here just for the "Is<>" method
	class MsgHitEventCollision : public Hedgehog::Universe::MessageTypeSet
	{
	public:
		HH_FND_MSG_MAKE_TYPE(0x01682064);

		int m_ID;
		int m_ID2;

		// Default constructor, most hit/leave events don't require IDs at all.
		MsgHitEventCollision() : m_ID(0), m_ID2(0) {}

		MsgHitEventCollision(int id, int id2) : m_ID(id), m_ID2(id2) {}
	};
	class MsgLeaveEventCollision : public Hedgehog::Universe::MessageTypeSet
	{
	public:
		HH_FND_MSG_MAKE_TYPE(0x0168207C);

		int m_ID;

		MsgLeaveEventCollision() : m_ID(0) {}
		MsgLeaveEventCollision(int id) : m_ID(id) {}
	};

	class __declspec(align(4)) MsgStartExternalControl : public Hedgehog::Universe::MessageTypeSet
	{
	public:
		HH_FND_MSG_MAKE_TYPE(0x01680810);

		boost::shared_ptr<CMatrixNodeTransform> m_spControlNode;
		bool TerrainCollisionEnable;
		bool ForceGroundMaybe;
		bool ChangeToSpin;
		bool DisableSuperSonic = false;
		bool ObserveBoost = false;
		bool ObserveSpin = false;
		bool ObserveInput = false;
		bool EscapeEnabled = false;
		bool NoDamage = false;
		int ChangeCollisionFlags;
		int DamageType;
		char m_Field_2C = 1;
		char m_Field_2D = 0;
		char m_Field_2E = 1;
		char m_Field_2F = 0;

		MsgStartExternalControl(
			const boost::shared_ptr<CMatrixNodeTransform>& in_spControlNode,
			bool in_TerrainCollisionEnable, bool in_ForceGroundMaybe, bool in_ChangeToSpin, int in_ChangeCollisionFlags
		)
			: m_spControlNode(in_spControlNode),
			TerrainCollisionEnable(in_TerrainCollisionEnable),
			ForceGroundMaybe(in_ForceGroundMaybe),
			ChangeToSpin(in_ChangeToSpin),
			ChangeCollisionFlags(in_ChangeCollisionFlags),
			DamageType(*reinterpret_cast<int*>(0x01E61B5C))
		{}

		MsgStartExternalControl(
			const boost::shared_ptr<CMatrixNodeTransform>& in_spControlNode,
			bool in_TerrainCollisionEnable, bool in_ForceGroundMaybe, bool in_ChangeToSpin
		)
			: m_spControlNode(in_spControlNode),
			TerrainCollisionEnable(in_TerrainCollisionEnable),
			ForceGroundMaybe(in_ForceGroundMaybe),
			ChangeToSpin(in_ChangeToSpin),
			ChangeCollisionFlags(0),
			DamageType(*reinterpret_cast<int*>(0x01E61B5C))
		{}

		MsgStartExternalControl(
			const boost::shared_ptr<CMatrixNodeTransform>& in_spControlNode,
			bool in_TerrainCollisionEnable, bool in_ForceGroundMaybe
		)
			: m_spControlNode(in_spControlNode),
			TerrainCollisionEnable(in_TerrainCollisionEnable),
			ForceGroundMaybe(in_ForceGroundMaybe),
			ChangeToSpin(false),
			ChangeCollisionFlags(0),
			DamageType(*reinterpret_cast<int*>(0x01E61B5C))
		{}

		// These aren't in the base game, but can prove useful.
		MsgStartExternalControl(
			const boost::shared_ptr<CMatrixNodeTransform>& in_spControlNode,
			bool in_TerrainCollisionEnable, bool in_ForceGroundMaybe, bool in_ChangeToSpin, int in_ChangeCollisionFlags,
			int in_DamageType
		)
			: m_spControlNode(in_spControlNode),
			TerrainCollisionEnable(in_TerrainCollisionEnable),
			ForceGroundMaybe(in_ForceGroundMaybe),
			ChangeToSpin(in_ChangeToSpin),
			ChangeCollisionFlags(in_ChangeCollisionFlags),
			DamageType(in_DamageType)
		{}

		MsgStartExternalControl(
			const boost::shared_ptr<CMatrixNodeTransform>& in_spControlNode
		)
			: m_spControlNode(in_spControlNode),
			TerrainCollisionEnable(true),
			ForceGroundMaybe(false),
			ChangeToSpin(false),
			ChangeCollisionFlags(0),
			DamageType(*reinterpret_cast<int*>(0x01E61B5C))
		{}
	};

	class MsgFinishExternalControl : public Hedgehog::Universe::MessageTypeSet
	{
	public:
		HH_FND_MSG_MAKE_TYPE(0x01680828)

			enum class EChangeState
		{
			FALL = 0x0,
			JUMP = 0x1,
			DEAD = 0x2,
			FINISH = 0x3,
			STAND = 0x4,
			ROCKETLAUNCH = 0x5,
			ROCKETLAUNCH2 = 0x6,
			SPIKEWALK = 0x7,
			SPIKEJUMP = 0x8,
			SPIKEFALL = 0x9,
		};

		EChangeState ExitState = EChangeState::FALL;
		bool EnableHomingAttack = false;
		bool SetBallModel = false;
		bool ForceFinish = false;
		int RocketLaunchInt = 0;
		Hedgehog::Math::CVector UpVector = Hedgehog::Math::CVector::Zero();

		MsgFinishExternalControl() = default;

		MsgFinishExternalControl(EChangeState in_ChangeState)
			: ExitState(in_ChangeState)
		{}

		MsgFinishExternalControl(EChangeState in_ChangeState, bool in_EnableHomingAttack)
			: ExitState(in_ChangeState), EnableHomingAttack(in_EnableHomingAttack)
		{}

		MsgFinishExternalControl(EChangeState in_ChangeState, bool in_EnableHomingAttack, bool in_SetBallModel)
			: ExitState(in_ChangeState), EnableHomingAttack(in_EnableHomingAttack), SetBallModel(in_SetBallModel)
		{}
	};

	class MsgChangeMotionInExternalControl : public Hedgehog::Universe::MessageTypeSet
	{
	public:
		HH_FND_MSG_MAKE_TYPE(0x016808B8);

		Hedgehog::Base::CSharedString AnimationName;
		enum ChangeType
		{
			SPIN = 0,
			RISINGFAN = 1,
			CUSTOM = 2
		} m_ChangeType = CUSTOM;
		bool m_Field18 = true;
		bool m_Field19 = false;
		bool m_Field1A = false;
		bool m_UseOriginalBlendSpeed = true;

		MsgChangeMotionInExternalControl(const Hedgehog::Base::CSharedString& animName) : AnimationName(animName) {}

		MsgChangeMotionInExternalControl(const Hedgehog::Base::CSharedString& animName, ChangeType type)
			: AnimationName(animName), m_ChangeType(type) {}

		MsgChangeMotionInExternalControl(const Hedgehog::Base::CSharedString& animName, ChangeType type, bool a, bool b, bool c, bool overrideBlend)
			: AnimationName(animName), m_ChangeType(type), m_Field18(a), m_Field19(b), m_Field1A(c), m_UseOriginalBlendSpeed(!overrideBlend) {}

		MsgChangeMotionInExternalControl(const Hedgehog::Base::CSharedString& animName, bool a, bool b, bool c, bool overrideBlend)
			: AnimationName(animName), m_Field18(a), m_Field19(b), m_Field1A(c), m_UseOriginalBlendSpeed(!overrideBlend) {}

		MsgChangeMotionInExternalControl(const Hedgehog::Base::CSharedString& animName, bool overrideBlend)
			: AnimationName(animName), m_UseOriginalBlendSpeed(!overrideBlend) {}
	};


	class MsgIsExternalControl : public Hedgehog::Universe::MessageTypeGet
	{
	public:
		HH_FND_MSG_MAKE_TYPE(0x01680B4C);

		bool IsTrue = false;
	};
	BB_ASSERT_SIZEOF(MsgIsExternalControl, 0x14);


	// Debug related stuff
	class MsgDebugView : public Hedgehog::Universe::MessageTypeSet
	{
	public:
		HH_FND_MSG_MAKE_TYPE(0x016820B4);

		int m_Type;
		bool m_Active;

		MsgDebugView() : m_Type(1), m_Active(true) {}
		MsgDebugView(int Type) : m_Type(Type), m_Active(true) {}
	};

	class MsgSetObjectSave : public Hedgehog::Universe::MessageTypeSet
	{
	public:
		HH_FND_MSG_MAKE_TYPE(0x0167EDB4);

		Hedgehog::Base::CSharedString m_Name;
		bool m_Success;

		MsgSetObjectSave(const Hedgehog::Base::CSharedString& name) : m_Name(name), m_Success(false) {}
	};

	class MsgSaveSetLayer : public Hedgehog::Universe::MessageTypeSet
	{
	public:
		HH_FND_MSG_MAKE_TYPE(0x0167F03C);

		uint32_t m_LayerIndex;
		bool m_Success;

		MsgSaveSetLayer() : m_LayerIndex(0), m_Success(false) {}
		MsgSaveSetLayer(int count) : m_LayerIndex(count), m_Success(false) {}
	};

	class MsgGatherActorID : public Hedgehog::Universe::MessageTypeGet
	{
	public:
		HH_FND_MSG_MAKE_TYPE(0x01681F24);

		hh::vector<uint32_t>** m_pIDs;

		MsgGatherActorID(hh::vector<uint32_t>* idVector) : m_pIDs(&idVector) {}
	};
}

namespace Sonic::Player
{
	class IPosture : public Hedgehog::Universe::TStateMachine<CPlayerContext>::TState
	{
	public:
		Hedgehog::Base::CSharedString m_ClassName;

		IPosture(const bb_null_ctor& nil) : Hedgehog::Universe::TStateMachine<CPlayerContext>::TState(nil) {}
		IPosture(const Hedgehog::Base::CSharedString& name) : m_ClassName(name) {}

		CPlayerSpeedContext* GetContext() const
		{
			return static_cast<CPlayerSpeedContext*>(m_pContext);
		}
	};

	class CPlayerSpeedPostureCommon : public IPosture
	{
		static constexpr int _vtbl = 0x016D3B6C;
	public:
		float m_Unk1 = 0.0f;
		float m_Unk2 = 0.0f;
		float m_Unk3 = 0.0f;
		Hedgehog::Math::CVector m_Vector = Hedgehog::Math::CVector(0, 0, 0);

		CPlayerSpeedPostureCommon(const bb_null_ctor& nil) : IPosture(nil) {}

		CPlayerSpeedPostureCommon() : IPosture("CPlayerSpeedPostureCommon")
		{
			*reinterpret_cast<int*>(this) = _vtbl;
		}

		CPlayerSpeedPostureCommon(const Hedgehog::Base::CSharedString& name) : IPosture(name)
		{
			*reinterpret_cast<int*>(this) = _vtbl;
		}

		virtual void ChangeVelocity(Hedgehog::Math::CVector* in_pVelocity) {}
	};

	class CPlayerSpeedPosture3DCommon : public CPlayerSpeedPostureCommon
	{
		static constexpr int _vtbl = 0x016D392C;
	public:
		CPlayerSpeedPosture3DCommon(const bb_null_ctor& nil) : CPlayerSpeedPostureCommon(nil) {}

		CPlayerSpeedPosture3DCommon() : CPlayerSpeedPostureCommon("CPlayerSpeedPosture3DCommon")
		{
			*reinterpret_cast<int*>(this) = _vtbl;
		}

		CPlayerSpeedPosture3DCommon(const Hedgehog::Base::CSharedString& name) : CPlayerSpeedPostureCommon(name)
		{
			*reinterpret_cast<int*>(this) = _vtbl;
		}

		void UpdateState() override
		{
			BB_FUNCTION_PTR(void, __thiscall, func, 0x00E37FD0, void* This);
			func(this);
		}
	};
}

namespace hk2010_2_0
{
	class hkpCachingShapePhantom;
}

namespace Sonic
{
	class CPhantomCallback;
	class CCharacterProxy;

	class CAabbAndCastUnit : public CPhysicsUnit
	{
	public:
		hk2010_2_0::hkReferencedObject* m_pReferencedObject48{};
		hk2010_2_0::hkpCachingShapePhantom* m_pCachingShapePhantom{};
		boost::shared_ptr<CPhantomCallback> m_spPhantomCallback{};
	};

	static constexpr int pCCharacterProxyIntegrate = 0x010E3CF0;
	static void __declspec(noinline) fCCharacterProxyIntegrate(CCharacterProxy* in_pProxy, float in_DeltaTime)
	{
		__asm
		{
			mov eax, in_pProxy
			push in_DeltaTime
			call[pCCharacterProxyIntegrate]
		}
	}

	class CCharacterProxy : public CAabbAndCastUnit
	{
	public:

		void Integrate(float in_DeltaTime)
		{
			fCCharacterProxyIntegrate(this, in_DeltaTime);
		}
		void ScanContacts(void* out_pContactData, float in_DeltaTime, const Hedgehog::Math::CVector& in_rDirection)
		{
			BB_FUNCTION_PTR(void, __stdcall, func, 0x010E2160, CCharacterProxy * This, void* contactData, float deltaTime, const Hedgehog::Math::CVector & direction);
			func(this, out_pContactData, in_DeltaTime, in_rDirection);
		}

		int __EntityListener;
		int __PhantomListener;
		float var60;
		int var64;
		float m_Float68;
		float var6c;
		float var70;
		float var74;
		float var78;
		float var7c;
		float var80;
		float cosAngleThing;
		int var88;
		int var8c;
		Hedgehog::Math::CVector m_UpAxis;
		float varA0;
		int varA4;
		float m_NormalStrength;
		float varAc;
		int m_DamageID;
		int varB4;
		int varB8;
		int varBc;
		Hedgehog::Math::CVector varC0;
		int varD0;
		int varD4;
		int varD8;
		int varDc;
		Hedgehog::Math::CVector varE0;
		int varF0;
		int varF4;
		int varF8;
		int varFc;
		int var100;
		int var104;
		int var108;
		int var10c;
		Hedgehog::Math::CVector var110;
		Hedgehog::Math::CVector m_Position;
		Hedgehog::Math::CVector m_Velocity;
		Hedgehog::Math::CVector var140;
		float m_VelocityStrengthScale;
		int var154;
		int var158;
		int var15c;
		Hedgehog::Math::CVector var160;
		Hedgehog::Math::CVector var170;
		Hedgehog::Math::CVector var180;
		int var190;
		int var194;
		int var198;
		int var19c;
		int m_Field1A0;
		int m_Field1A4;
		int m_Field1A8;
		int m_Field1AC;
		int m_Field1B0;
		int m_Field1B4;
		int m_Field1B8;
		int m_Field1BC;
		Hedgehog::Math::CVector m_Field1C0;
		Hedgehog::Math::CQuaternion m_Rotation;
		Hedgehog::Math::CVector m_Field1E0;
		float m_Field1F0;
		int m_Field1F4;
		int m_Field1F8;
		int m_Field1FC;
	};

	class __declspec(align(16)) CCameraController : public Hedgehog::Universe::TStateMachine<CCamera>::TState
	{
	public:
		bool m_IsCollision;
		float m_FOV;
		bool m_Cond02;
		bool m_Cond03;
		char m_Cond04;
		Hedgehog::Math::CVector m_CameraPosition1;
		Hedgehog::Math::CVector m_UpVector1;
		Hedgehog::Math::CVector m_TargetPosition1;
		Hedgehog::Math::CVector m_CameraPosition2;
		Hedgehog::Math::CVector m_UpVector2;
		Hedgehog::Math::CVector m_TargetPosition2;
		int m_CameraSetObjectID;
		int field_D4;
		int field_E8;
		int field_EC;
	};

	class __declspec(align(16)) CPlayer2DNormalCamera : public Sonic::CCameraController
	{
	public:
		struct SParams
		{
			bool IsBaseSpacePlayer;
			bool IsPositionBasePlayer;
			float BaseSpacePathPosition;
			Hedgehog::Math::CVector SphericalPosition;
			float TargetUpOffset;
			float TargetFrontOffset;
			float TargetFrontOffsetSpeedScale;
			float TargetFrontOffsetMax;
		};
		struct SGlobalParams
		{
			float TargetFrontOffsetSensitive;
			float TargetUpMoveRate;
			float TargetUpMaxGroundDistance;
			float SlopeSensitiveVelocityScaleOffset;
			float TargetUpMaxOffsetPositive;
			float SlopeSensitiveAir;
			float TargetUpMaxOffsetNegative;
			float SlopeSensitiveMax;
			float TargetUpOffsetSensitive;
			float SlopeSensitiveVelocityScale;
			float SphericalPositionSensitiveY;
			float PlayerPositionSensitive;
			float SlopeSensitive;
			float SphericalPositionSensitiveZ;
			float PlayerVelocitySensitive;
			float SlopeRollRate;
		};

		SParams* m_pParams;
		int m_Field0E4;
		int m_Field0E8;
		int m_Field0EC;
		SParams m_Params;
		Hedgehog::Math::CVector m_TargetFrontOffset;
		float m_TargetUpGroundDistance;
		int m_Field134;
		int m_Field138;
		int m_Field13C;
		Hedgehog::Math::CVector m_AngularPosition;
		Hedgehog::Math::CVector m_PointPosition;
		Hedgehog::Math::CVector m_2DPathUp;
		Hedgehog::Math::CVector m_2DPathFwd;
		Hedgehog::Math::CVector m_TargetUpVector;
		Hedgehog::Math::CVector m_Velocity;
		Hedgehog::Math::CVector m_SphericalPosition;
		int m_Field1B0;
		int m_Field1B4;
		int m_Field1B8;
		int m_Field1BC;
		int m_Field1C0;
		bool m_UseStaticParams;
		int m_Field1C8;
		int m_Field1CC;
	};
	BB_ASSERT_OFFSETOF(CPlayer2DNormalCamera, m_Field1B0, 0x1B0);
	BB_ASSERT_SIZEOF(CPlayer2DNormalCamera, 0x1D0);

	class CBoostCameraPlugin : public Hedgehog::Universe::CStateMachineBase::CStateBase
	{
	public:
		int start;
		int field_64;
		int field_68;
		int field_6C;
		int field_70;
		int field_74;
		int field_78;
		float m_DefaultCameraTransitionTime;
		bool m_IsBoosting;
		float m_BoostTimer;
		int field_88;
		int field_8C;
		int field_90;
		int field_94;
		int field_98;
		int field_9C;
		int field_A0;
		int field_A4;
		int field_A8;
		int field_AC;
		int field_B0;
		int field_B4;
		int field_B8;
		int field_BC;
		int field_C0;
		int field_C4;
		int field_C8;
		int field_CC;
		int field_D0;
		int field_D4;
		int field_D8;
		int field_DC;
		int field_E0;
		int field_E4;
		int field_E8;
		int field_EC;
	};

	class CPlayer3DNormalCamera : public Hedgehog::Universe::TStateMachine<CCamera>::TState
	{
	public:
		struct SParamsBasic
		{
			float Fovy; // Usually 45.0f
			float Distance; // Usually 3.0f
			float VerticalOffset; // Usually 1.7f (for Modern Sonic?)
			float TargetPitch; // Usually 0.0f in official stages, sometimes 15.0f?
			float TargetYaw; // Usually 0.0f

			// These were added in gens and are only active when on the skateboard really.
			// In fact, Gens sets these to ridiculous numbers and does a float comparison, doing nothing if they're ~10K.
			// That's pretty goofy, so the code's been modified to ignore those floats if you're on board instead.
			// I can only imagine they *intended* for this to be some kind of future proof thing...? Weird.

			float TargetUpFinalOffset; // NORMAL: 100000.0f - ON BOARD: -0.38f
			float TargetDownFarNearBorder; // NORMAL: 100000.0f - ON BOARD: 30.00f
		};
		struct SParamsSide
		{
			float TargetSideSensitive;
			float TargetSideSensitiveInQuickStep;
			float m_ParamDashPathSideMoveRate;
		};
		struct SParamsGlobal
		{
			float TARGET_FRONT_OFFSET_SCALE;
			float TARGET_FRONT_OFFSET_SENSITIVE;
			float SLOPE_SENSITIVE;
			float SLOPE_SENSITIVE_VELOCITY_SCALE;
			float SLOPE_SENSITIVE_VELOCITY_SCALE_VELOCITY_OFFSET;
			float SLOPE_SENSITIVE_MAX;
			float SLOPE_SENSITIVE_AIR;
			float SLOPE_CAMERAUP_RATE;
			float SLOPE_AFFECT_MIN_VELOCITY;
			float SLOPE_AFFECT_MAX_VELOCITY;
			float TARGET_UP_OFFSET_IN_AIR;
			float TARGET_UP_OFFSET_SENSITIVE;
			float TARGET_UP_FINAL_OFFSET;
			float TARGET_UP_SENSITIVE;
			float TARGET_DOWN_SENSITIVE_GROUND_NEAR;
			float TARGET_DOWN_SENSITIVE_GROUND_FAR_NEAR_BORDER;
			float CAMERA_MAX_PITCH;
			float CAMERA_MIN_PITCH;
			float CAMERA_TARGET_PITCH_SENSITIVE;
			float CAMERA_PITCH_MOVE_VELOCITY_MIN;
			float CAMERA_DISTANCE_MAX_RATE;
			float CAMERA_DISTANCE_MAX_RATE_WATER;
			float CAMERA_DISTANCE_SCALE;
			float CAMERA_DISTANCE_MINIMUM;
			float CAMERA_DISTANCE_NEGATIVE_PITCH_SCALE;
			float CAMERA_DISTANCE_POSITIVE_PITCH_SCALE;
			float CAMERA_DISTANCE_BASIC_RANGE;
			float CAMERA_POSITION_VELOCITY_RATE;
			float TARGET_SIDE_OFFSET_SCALE;
			float TARGET_SIDE_OFFSET_VELOCITY_SCALE;
			float TARGET_SIDE_OFFSET_SENSITIVE;
			float TARGET_SIDE_OFFSET_RECOVER_SENSITIVE;
			float TARGET_SENSITIVE;
			float TARGET_UP_POSITIVE_SENSITIVE_GROUND;
			float TARGET_UP_NEGATIVE_SENSITIVE_GROUND;
			float TARGET_UP_POSITIVE_SENSITIVE_VELSCALE_GROUND;
			// Filler data in Gens.
		private:
			void* m_Unknown = {};
		public:
			float TARGET_UP_POSITIVE_SENSITIVE_AIR;
			float TARGET_UP_NEGATIVE_SENSITIVE_AIR;
			float TARGET_UP_DIFF_POSITIVE_MAX;
			float TARGET_UP_DIFF_NEGATIVE_MAX;
			float TARGET_SIDE_DIFF_MAX;
			float POSITION_SENSITIVE;
			float POSITION_UP_POSITIVE_SENSITIVE;
			float POSITION_UP_NEGATIVE_SENSITIVE;
			float POSITION_UP_DIFF_POSITIVE_MAX;
			float POSITION_UP_DIFF_NEGATIVE_MAX;
			float DISTANCE_OFFSET_BASE_VELOCITY;
			float DISTANCE_OFFSET;
			float DISTANCE_OFFSET_MAX;
			float DISTANCE_OFFSET1_SENSITIVE;
			float DISTANCE_OFFSET2_SENSITIVE;
			float DRIFT_YAW_SENSITIVE_BASE;
			float DRIFT_YAW_SENSITIVE_SPEED_SCALE;
			float DRIFT_FINISH_YAW_VELOCITY_SENSITIVE;
			float DRIFT_TARGET_SIDE_OFFSET_SCALE;
			float COLLISION_RADIUS;
			float HOMING_ATTACK_TARGET_SENSITIVE;
			float CAMERA_POSITION_VELOCITY_RATE_IN_DASHMODE;
			float DASHPATH_BINRM_SENSITIVE;
			float DASHPATH_EASE_TIME;

			// These need to be re-assigned in Gens as they're located elsewhere.
			float TARGET_FRONT_OFFSET_BIAS;
			float TARGET_DOWN_SENSITIVE_GROUND_FAR;
			float DRIFT_YAW_OFFSET;
		};

		class CListener
		{
		public:
			//void* vftable;

			virtual ~CListener() = default;

			Hedgehog::Math::CVector m_Target{};
			Hedgehog::Math::CVector m_Position{};
			Hedgehog::Math::CVector m_Velocity{};
			boost::shared_ptr<void> m_spRayCastCollision{};
		};

		bool m_AcceptCollision = false;
		float m_FovInRadians{};
		bool field_68{};
		int field_6C{};
		Hedgehog::Math::CVector m_CameraPositionVisual = Hedgehog::Math::CVector::Zero();
		Hedgehog::Math::CVector m_CameraUpVector = Hedgehog::Math::CVector::Zero();
		Hedgehog::Math::CVector m_CameraTargetPosition = Hedgehog::Math::CVector::Zero();
		Hedgehog::Math::CVector m_CameraPositionInputReference = Hedgehog::Math::CVector::Zero();
		Hedgehog::Math::CVector m_CameraUpVector2 = Hedgehog::Math::CVector::Zero();
		Hedgehog::Math::CVector m_CameraTargetPosition2 = Hedgehog::Math::CVector::Zero();
		char field_D0[16]{};
		SParamsBasic* m_pParamsNormal{};
		char field_E4[28]{};
		SParamsSide* m_pParamsSide{};
		char field_104[12]{};
		SParamsBasic* m_pParamsBoard{};
		float m_DriftRotationAngle{};
		float m_CameraTargetPositionY{};
		int field_11C{};
		Hedgehog::Math::CVector m_TargetFrontOffset = Hedgehog::Math::CVector::Zero();
		Hedgehog::Math::CVector m_TargetSideOffset = Hedgehog::Math::CVector::Zero();
		Hedgehog::Math::CVector m_CameraPositionCollision = Hedgehog::Math::CVector::Zero();
		Hedgehog::Math::CVector m_TargetOffsetPosition = Hedgehog::Math::CVector::Zero();
		Hedgehog::Math::CVector m_WorkingUpVector = Hedgehog::Math::CVector::Zero();
		CCharacterProxy* m_pCharacterProxy{};
		int field_174{};
		CBoostCameraPlugin* m_pBoostCameraPlugin{};
		void* unk_void{};
		bool m_IsQuickstepping{};
		bool m_IsOnBoard{};
		__int16 gap182{};
		float m_TargetSideQuickstepTimer{};
		float m_CameraTargetPitch{};
		float m_DistanceOffset1{};
		float m_DistanceOffset2{};
		char field_194[8]{};
		int field_19C{};
		Hedgehog::Math::CVector m_FloorVector = Hedgehog::Math::CVector::Zero();
		float m_CameraOrbitX{};
		float m_CameraOrbitY{};
		char field_1B8[8]{};
		Hedgehog::Math::CVector m_DashPathRightVector = Hedgehog::Math::CVector::Zero();

		Hedgehog::Math::CVector m_DashPathEasePositionTarget = Hedgehog::Math::CVector::Zero();
		Hedgehog::Math::CVector m_DashPathEasePositionCamera = Hedgehog::Math::CVector::Zero();

		bool m_IsDashPathEasing{};
		bool m_IsFacingForwardOnPath{};
		float m_DashPathEaseTime{};
		CListener* m_pListener{};
		char field_1FC{};
		char field_1FD{};
		char field_1FE{};
		char field_1FF{};
	};
	BB_ASSERT_OFFSETOF(CPlayer3DNormalCamera, m_FovInRadians, 0x64);
	BB_ASSERT_OFFSETOF(CPlayer3DNormalCamera, m_CameraPositionVisual, 0x70);
	BB_ASSERT_OFFSETOF(CPlayer3DNormalCamera, m_pListener, 0x1F8);

	BB_ASSERT_OFFSETOF(CPlayer3DNormalCamera::CListener, m_Target, 16);
	BB_ASSERT_OFFSETOF(CPlayer3DNormalCamera::CListener, m_Position, 32);
	BB_ASSERT_OFFSETOF(CPlayer3DNormalCamera::CListener, m_Velocity, 48);
}
