#include "..\hhMath.h"

namespace Hedgehog::Math
{
	CVector CVector::One()
	{
		return CVector(1, 1, 1);
	}

	CVector CVector::Right()
	{
		return CVector(-1, 0, 0);
	}

	CVector CVector::Left()
	{
		return CVector(1, 0, 0);
	}

	CVector CVector::Up()
	{
		return CVector(0, 1, 0);
	}

	CVector CVector::Down()
	{
		return CVector(0, -1, 0);
	}

	CVector CVector::Forward()
	{
		return CVector(0, 0, 1);
	}

	CVector CVector::Backward()
	{
		return CVector(0, 0, -1);
	}

	CVector* CVector::Lerp(CVector* out, CVector* VectorA, CVector* VectorB, float tValue)
	{
		*out = CVector::Lerp(*VectorA, *VectorB, tValue);
		return out;
	}

	CVector CVector::Orthogonal(const CVector& v)
	{
		const CVector out = v.z() < v.x() ? CVector(v.y(), -v.x(), 0) : CVector(0, -v.z(), v.y());
		return out;
	}

	double CVector::Length(CVector* This)
	{
		return This->norm();
	}

	float CVector::Length(const CVector& This)
	{
		return This.norm();
	}

	double CVector::Length() const
	{
		return this->norm();
	}

	// Two-point length
	float CVector::Length(const CVector& A, const CVector& B)
	{
		return (A - B).norm();
	}

	float CVector::Distance(const CVector& A, const CVector& B)
	{
		return Length(A, B);
	}

	CVector CVector::Project(const CVector& a, const CVector& b)
	{
		float m = Magnitude(b);
		return b * (Dot(a, b) / (m * m));
	}

	CVector CVector::Reject(const CVector& a, const CVector& b)
	{
		return a - Project(a, b);
	}

	CVector CVector::ProjectOnPlane(const CVector& vector, const CVector& planeNormal)
	{
		return Reject(vector, planeNormal);
	}

	CVector CVector::ProjectOnPlane(const CVector& planeNormal) const
	{
		return Reject(*this, planeNormal);
	}

	double CVector::Magnitude(const CVector& This)
	{
		return This.norm();
	}

	double CVector::Magnitude() const
	{
		return this->Length();
	}

	CVector* CVector::SetZero(CVector* This)
	{
		*This = CVector::Zero();
		return This;
	}

	void CVector::SetZero()
	{
		*this = CVector::Zero();
	}

	void CVector::Normalize(CVector* This)
	{
		*This = This->normalizedSafe();
	}

	CVector CVector::Normalize(const CVector& This)
	{
		return This.normalizedSafe();
	}

	void CVector::Normalize()
	{
		*this = this->normalizedSafe();
	}

	CVector* CVector::Normalized(CVector* This, CVector* result)
	{
		*result = This->normalizedSafe();
		return result;
	}

	CVector* CVector::Normalized(CVector* result) const
	{
#ifdef _USE_INGAME_MATH
						BB_FUNCTION_PTR(CVector*, __thiscall, func, 0x009BF7E0, const CVector * _This, CVector * result);
		CVector* out = func(this, result);
								return out;
#else
		*result = this->normalizedSafe();
		return result;
#endif
	}

	CVector CVector::Normalized(const CVector& This)
	{
		return This.normalizedSafe();
	}

	CVector* CVector::Add(CVector* result, CVector* value)
	{
		*result += *value;
		return result;
	}

	CVector* CVector::Divide(CVector* result, CVector* value, float scalar)
	{
		if (scalar < FLT_EPSILON)
		{
			*result = CVector::Zero();
			return result;
		}

		*result = *value / scalar;
		return result;
	}

	CVector CVector::Divide(const CVector& value, float scalar)
	{
		if (scalar < FLT_EPSILON)
		{
			return Zero();
		}

		const CVector out = value / scalar;
		return out;
	}

	CVector* CVector::Multiply(CVector* result, CVector* value, float scalar)
	{
		*result = *value * scalar;
		return result;
	}

	CVector* CVector::Multiply(CVector* result, float scalar, CVector* value)
	{
		*result = *value * scalar;
		return result;
	}

	CVector* CVector::Multiply(CVector* vector, float scalar)
	{
		*vector *= scalar;
		return vector;
	}

	double CVector::Dot(const CVector* This, const CVector* value)
	{
		return This->dot(*value);
	}

	double CVector::Dot(const CVector& This, const CVector& value)
	{
		return This.dot(value);
	}

	double CVector::Dot(CVector* value) const
	{
		return this->dot(*value);
	}

	double CVector::LengthSqr(CVector* This)
	{
		return This->squaredNorm();
	}

	double CVector::LengthSqr(const CVector& This)
	{
		return This.squaredNorm();
	}

	double CVector::LengthSqr() const
	{
		return this->squaredNorm();
	}

	double CVector::SqrMagnitude(const CVector& This)
	{
		return This.squaredNorm();
	}

	double CVector::SqrMagnitude() const
	{
		return this->squaredNorm();
	}

	CVector* CVector::Cross(const CVector* This, CVector* result, const CVector* value)
	{
		CVector a = *This;
		CVector b = *value;
		*result = Cross(a, b);
		return result;
	}

	CVector CVector::Cross(const CVector& lhs, const CVector& rhs)
	{
		float x = lhs.y() * rhs.z() - lhs.z() * rhs.y();
		float y = lhs.z() * rhs.x() - lhs.x() * rhs.z();
		float z = lhs.x() * rhs.y() - lhs.y() * rhs.x();
		return CVector(x, y, z);
	}

	CVector CVector::Cross(const CVector& b)
	{
		return CVector::Cross(*this, b);
	}

	CVector CVector::SlerpUnclamped(const CVector& a, const CVector& b, const float t)
	{
		float magA = Magnitude(a);
		float magB = Magnitude(b);

		// HACK: Fix potential NAN stuff.
		if (magA < FLT_EPSILON)
			return b;
		if (magB < FLT_EPSILON)
			return a;

		CVector _a = a / magA;
		CVector _b = b / magB;
		float dot = Dot(_a, _b);
		dot = fmaxf(dot, -1.0);
		dot = fminf(dot, 1.0);
		float theta = acosf(dot) * t;
		CVector relativeVec = Normalized(_b - _a * dot);
		CVector newVec = _a * cosf(theta) + relativeVec * sinf(theta);
		return newVec * (magA + (magB - magA) * t);
	}

	CVector CVector::Slerp(const CVector& a, const CVector& b, const float t)
	{
		if (t < 0)
			return a;
		else if (t > 1)
			return b;
		return SlerpUnclamped(a, b, t);
	}

	float CVector::Angle(const CVector& a, const CVector& b)
	{
		float v = Dot(a, b) / (Magnitude(a) * Magnitude(b));
		v = fmaxf(v, -1.0);
		v = fminf(v, 1.0);
		return acosf(v);
	}

	float CVector::SignedAngle(const CVector& a, const CVector& b, const CVector& axis)
	{
		auto cross = CVector::Cross(a, b);
		auto x = CVector::Dot(axis, cross);
		auto y = CVector::Dot(a, b);

		return atan2(x, y);
	}

	CVector CVector::RotateTowards(const CVector& from, const CVector& to, float maxRadiansDelta)
	{
		float angle = CVector::Angle(from, to);
		if (angle == 0)
			return to;
		maxRadiansDelta = fmaxf(maxRadiansDelta, angle - (float)M_PI);
		float t = fminf(1, maxRadiansDelta / angle);
		return CVector::SlerpUnclamped(from, to, t);
	}

	CVector CVector::LerpTowards(const CVector& from, const CVector& to, float maxRadiansDelta)
	{
		float angle = CVector::Angle(from, to);
		if (angle == 0)
			return to;
		maxRadiansDelta = fmaxf(maxRadiansDelta, angle - (float)M_PI);
		float t = fminf(1, maxRadiansDelta / angle);
		return CVector::LerpUnclamped(from, to, t);
	}

	CVector CVector::SlerpTowards(const CVector& from, const CVector& to, float maxRadiansDelta)
	{
		float angle = CVector::Angle(from, to);
		if (angle == 0)
			return to;
		maxRadiansDelta = fmaxf(maxRadiansDelta, angle - (float)M_PI);
		float t = fminf(1, maxRadiansDelta / angle);
		return CVector::LerpUnclamped(from, to, t);
	}

	CVector CVector::Scale(const CVector& a, const CVector& b)
	{
		return CVector(a.x() * b.x(), a.y() * b.y(), a.z() * b.z());
	}

	CVector CVector::Scale(const CVector& b) const
	{
		return CVector(this->x() * b.x(), this->y() * b.y(), this->z() * b.z());
	}

	CVector CVector::normalizedSafe() const
	{
		if (this->squaredNorm() < 0.0001f)
		{
			return CVector::Zero();
		}

		return this->normalized();

		//CVector This = *this;
		//CVector result = This.LengthSqr() > (DBL_EPSILON + DBL_EPSILON + DBL_EPSILON)
		//	                 ? This.normalized()
		//	                 : CVector(0, 0, 0);
		//return result;
	}

	CVector CVector::LerpUnclamped(const CVector& a, const CVector& b, const float t)
	{
		CVector result = (b - a) * t + a;
		return result;
	}

	CVector CVector::Lerp(const CVector& a, const CVector& b, const float t)
	{
		if (t < 0)
			return a;
		if (t > 1)
			return b;
		return LerpUnclamped(a, b, t);
	}

	CVector CVector::Reflect(const CVector& vector, const CVector& planeNormal)
	{
		return vector - Project(vector, planeNormal) * 2.0f;
	}

	CVector CVector::Reflect(const CVector& planeNormal) const
	{
		return Reflect(*this, planeNormal);
	}
}
