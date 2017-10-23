#ifndef __LIB_XP_H__
#define __LIB_XP_H__

//////////////////////////////////////////////////////////////////////////

#include "c4d.h"

namespace xparticles_lib
{
    

const Int32 OXPEmitter = 1027133;
const Int32 OXPDomain = 1033595;
const Int32 MXPmaterial = 1027417;
const Int32 VXPrender = 1030488;

// X-Particle 2.5 flags for compatibility

enum XPARTICLE_FLAGS_25
{
	XPARTICLE_FLAGS_25_0				= 0,
	XPARTICLE_FLAGS_25_ALIVE		= (1 << 0),
	XPARTICLE_FLAGS_25_BORN		= (1 << 1),
	XPARTICLE_FLAGS_25_DIE			= (1 << 2),
	XPARTICLE_FLAGS_25_GROUP_CHANGED = (1 << 3),
	XPARTICLE_FLAGS_25_NEW			= (1 << 4),
} ENUM_END_FLAGS(XPARTICLE_FLAGS_25);

enum XPARTICLE_BITS
{
	XPARTICLE_BITS_0				= 0,
	XPARTICLE_BITS_TRAIL = 1,
	XPARTICLE_BITS_USEGRAD = 2,
	XPARTICLE_BITS_FREEZE = 4,
	XPARTICLE_BITS_STICK = 8,
	XPARTICLE_BITS_ISSTUCK = 16,
	XPARTICLE_BITS_COLLIDED = 32,
	XPARTICLE_BITS_STICKSOURCE = 64,
	XPARTICLE_BITS_TARGETMODE = 256,
	XPARTICLE_BITS_FREEZE_SPIN = 512,
	XPARTICLE_BITS_FREEZE_SCALE = 1024,
	XPARTICLE_BITS_TP_DISCON = 2048,
	XPARTICLE_BITS_ROTATED = 4096,
	XPARTICLE_BITS_DONESPAWN = 8192,
	XPARTICLE_BITS_DOSTICK = 16384,
	XPARTICLE_BITS_DOFREEZE_MOVE = 32768,
	XPARTICLE_BITS_DOFREEZE_SPIN = 65536,
	XPARTICLE_BITS_DOFREEZE_SCALE = 131072,
	XPARTICLE_BITS_CUTTRAIL = 262144,
	XPARTICLE_BITS_KILLZEROTRAIL = 524288,
	XPARTICLE_BITS_NOSTUCKACTION = (1<<20),
	XPARTICLE_BITS_DIRECTKICK = (1<<21),
	XPARTICLE_BITS_INVISIBLE = (1<<22),
	XPARTICLE_BITS_COLLISION_SKIP = (1<<23),
	XPARTICLE_BITS_COLLISION_STEP_SKIP = (1<<24),
	XPARTICLE_BITS_PPCOLLISION = (1<<25),
	XPARTICLE_BITS_PPOLYCOLLISION = (1<<26),
	XPARTICLE_BITS_POLY_PRIMECOLLISION = (1<<27),
	XPARTICLE_BITS_PP_PRIMECOLLISION = (1<<28),
	XPARTICLE_BITS_DEFORMED = (1<<29),
} ENUM_END_FLAGS(XPARTICLE_BITS);

// end 2.5 compatibility

enum XPARTICLE_FLAGS
{
	XPARTICLE_FLAGS_0				= 0,
	XPARTICLE_FLAGS_TRAIL						= (1 << 0),
	XPARTICLE_FLAGS_USEGRAD					= (1 << 1),
	XPARTICLE_FLAGS_FREEZE					= (1 << 2),
	XPARTICLE_FLAGS_STICK						= (1 << 3),
	XPARTICLE_FLAGS_ISSTUCK					= (1 << 4),
	XPARTICLE_FLAGS_COLLIDED					= (1 << 5),
	XPARTICLE_FLAGS_STICKSOURCE				= (1 << 6),
	XPARTICLE_FLAGS_NEWBRANCH					= (1 << 7),
	XPARTICLE_FLAGS_RESAMPLE					= (1 << 8),
	XPARTICLE_FLAGS_FREEZE_SPIN				= (1 << 9),
	XPARTICLE_FLAGS_FREEZE_SCALE				= (1 << 10),
	XPARTICLE_FLAGS_TP_DISCON					= (1 << 11),
	XPARTICLE_FLAGS_ROTATED					= (1 << 12),
	XPARTICLE_FLAGS_DONESPAWN					= (1 << 13),
	XPARTICLE_FLAGS_DOSTICK					= (1 << 14),
	XPARTICLE_FLAGS_ALIVE		= (1 << 15),
	XPARTICLE_FLAGS_BORN		= (1 << 16),
	XPARTICLE_FLAGS_DIE			= (1 << 17),
	XPARTICLE_FLAGS_GROUP_CHANGED = (1 << 18),
	XPARTICLE_FLAGS_NEW			= (1 << 19),
	XPARTICLE_FLAGS_NOSTUCKACTION				= (1 << 20),
	XPARTICLE_FLAGS_INVISIBLE					= (1 << 21),
	XPARTICLE_FLAGS_SKIP_FINAL			= (1 << 22),
	XPARTICLE_FLAGS_PPCOLLISION				= (1 << 24),
	XPARTICLE_FLAGS_PPOLYCOLLISION			= (1 << 25),
	XPARTICLE_FLAGS_POLY_PRIMECOLLISION		= (1 << 26),
	XPARTICLE_FLAGS_PP_PRIMECOLLISION			= (1 << 27),
	XPARTICLE_FLAGS_DEFORMED					= (1 << 28),
	XPARTICLE_FLAGS_STREAMER					= (1 << 29),
	XPARTICLE_FLAGS_MARKED_DIE = (1 << 30),
	XPARTICLE_FLAGS_FILL		= (1 << 31),
} ENUM_END_FLAGS(XPARTICLE_FLAGS);

class XParticleConstraint
{
	XParticleConstraint();
	~XParticleConstraint();

public:

	Float GetLength();
	Int32 GetIndex();
	Int32 GetFlags();
	Int32 GetID();

	void SetLength(Float len);
	void SetIndex(Int32 index);
	void SetFlags(Int32 flags);
	void SetID(Int32 id);
};

class XParticleColliderConstraint
{
	XParticleColliderConstraint();
	~XParticleColliderConstraint();

public:

	Float GetLength();
	Int32 GetIndex();
	Int32 GetFlags();
	Int32 GetID();
	UInt64 GetColliderID();
	void GetPositionRS(Float &r, Float &s);
	Vector GetLastPosition();

	void SetLength(Float len);
	void SetIndex(Int32 index);
	void SetFlags(Int32 flags);
	void SetID(Int32 id);
	void SetColliderID(UInt64 id);
	void SetPositionRS(Float r, Float s);
	void SetLastPosition(const Vector &pos);
};

Vector MixRS(Float r, Float s, Float ra, Float rb, Float rc, Float rd, Bool quad);
Vector MixRS(Float r, Float s, const Vector &va, const Vector &vb, const Vector &vc, const Vector &vd, Bool quad);
void GetRS(Float &r, Float &s, const Vector &p, const Vector &va, const Vector &vb, const Vector &vc, const Vector &vd, Bool quad);

class XParticle
{
private:

	XParticle();
	~XParticle();

public:

	Vector GetPosition();
	Vector GetVelocity();
	Float GetTime();
	Float GetLife();
	Vector GetColor();
	Float GetRadius();
	Float GetMass();
	Float GetSpeed();
	Int32 GetGroupID();
	Int32 GetID();
	XPARTICLE_FLAGS GetFlags();
	Float GetDensity();			// only valid with fluids enabled
	Int32 GetDisplay();			// get the particle display type (defined in the emitter resource, res folder)
	XPARTICLE_BITS GetBits();
	Matrix GetMatrix();
	Vector GetRotation();
	Float GetDistanceTravelled();
	Vector GetSpin();
	Bool IsSpinEnabled();
	Float GetTemperature();
	Float GetFuel();
	Float GetFire();
	Float GetSmoke();
	Float GetExpansion();
	Vector GetUVW();

	void SetPosition(const Vector &p);
	void SetVelocity(const Vector &v);
	void SetTime(Float time);
	void SetLife(Float life);
	void SetColor(const Vector &col);
	void SetRadius(Float r);
	void SetMass(Float m);
	void SetSpeed(Float s);
	void SetGroupID(Int32 id);
	void SetID(Int32 id);
	void SetFlags(XPARTICLE_FLAGS flags);	// particles can not be created by changing their flags, please use CreateParticle, flags should generally not be changed
	void SetDensity(Float density);
	void SetDisplay(Int32 type);
	void SetBits(XPARTICLE_BITS bits);
	void SetMatrix(const Matrix &m);
	void SetRotation(const Vector &rot);	// HPB
	void SetDistanceTravelled(Float dist);
	void SetSpin(const Vector &spin);
	void SetSpinEnabled(Bool enable);
	void SetTemperature(Float temp);
	void SetFuel(Float fuel);
	void SetFire(Float fire);
	void SetSmoke(Float smoke);
	void SetExpansion(Float expansion);
	void SetUVW(const Vector &uvw);

	GeData *GetCustomData(Int32 index, Int32 *id = NULL, String *name = NULL);
	Int32 GetCustomDataCount();
	Int32 AddCustomData(Int32 id, const String &name, const GeData &data);
	void SetCustomData(Int32 index, const GeData &data);
	Int32 FindCustomData(Int32 id, const String &name);	// find custom data matching id/name (id can be -1 if only the name is to be checked, name can be String() if only the id should be checked)
	Bool RemoveCustomData(Int32 index);

	Int32 GetBirthConstraintsCount();
	Int32 GetDistanceConstraintsCount();
	Int32 GetParticleConstraintsCount();
	Int32 GetColliderConstraintsCount();

	XParticleConstraint *GetBirthConstraint(Int32 index);
	XParticleConstraint *GetDistanceConstraint(Int32 index);
	XParticleConstraint *GetParticleConstraint(Int32 index);
	XParticleColliderConstraint *GetColliderConstraint(Int32 index);

	XParticleConstraint *AddBirthConstraint();
	XParticleConstraint *AddDistanceConstraint();
	XParticleConstraint *AddParticleConstraint();
	XParticleConstraint *AddColliderConstraint();

	void RemoveBirthConstraint(Int32 index);
	void RemoveDistanceConstraint(Int32 index);
	void RemoveParticleConstraint(Int32 index);
	void RemoveColliderConstraint(Int32 index);

	Int32 GetIndex();					// get the interal array index of this particle, iterating should be done using GetFirstAlive() and GetNext()
	XParticle *GetNext();			// get the next used (live) particle
};

};	// xparticles_lib

class XPVideoPost : public BaseVideoPost
{
private:

	XPVideoPost();
	~XPVideoPost();

public:

	static XPVideoPost *Alloc()
	{
		return (XPVideoPost*)BaseVideoPost::Alloc(xparticles_lib::VXPrender);
	}

	static void Free(XPVideoPost *&xpVp)
	{
		BaseVideoPost *vp = xpVp; 
		BaseVideoPost::Free(vp);
		xpVp = NULL;
	}

	void SkipRender();
};

// to use the X-Particle Material Sampling the material must have been initialized (InitRender)

class XPMaterial : public BaseMaterial
{
private:

	XPMaterial();
	~XPMaterial();

public:

	static XPMaterial *Alloc()
	{
		return (XPMaterial*)BaseMaterial::Alloc(xparticles_lib::MXPmaterial);
	}

	static void Free(XPMaterial *&xpMat)
	{
		BaseMaterial *mat = xpMat; 
		BaseMaterial::Free(mat);
		xpMat = NULL;
	}

	Float SampleSize(xparticles_lib::XParticle *xpParticle, const Vector &p, VolumeData *vd, XPVideoPost *render);
	Vector SampleColor(xparticles_lib::XParticle *xpParticle, const Vector &p, VolumeData *vd, XPVideoPost *render, Float radius);
	Float SampleTrans(xparticles_lib::XParticle *xpParticle, const Vector &p, VolumeData *vd, XPVideoPost *render, Float radius);
};

// iterate all particles using GetFirstAlive() followed by GetNext() from the particle
//
// xparticles_lib::XParticle *particle = emitter->GetFirstAlive();
// while (particle != nullptr)
// {
//   // do something
//   particle = particle->GetNext();
// }
//

class XPEmitterObject : public BaseObject
{
private:

	XPEmitterObject();
	~XPEmitterObject();

public:

	static XPEmitterObject *Alloc()
	{
		return (XPEmitterObject*)BaseObject::Alloc(xparticles_lib::OXPEmitter);
	}

	static void Free(XPEmitterObject *&xpObject)
	{
		BaseObject *op = xpObject; 
		BaseObject::Free(op);
		xpObject = NULL;
	}

	Int32 GetParticleCount();		// total particle count
	Int32 GetAliveCount();				// count of 'in use' (live) particles
	Int32 GetDeadCount();				// unused (dead) particles
	Int32 GetMaxCount();

	xparticles_lib::XParticle *GetParticle(Int32 index);		// get a particle at 'index', NOTE: iterating the particles using this function is slower than using GetFirstAlive()
	xparticles_lib::XParticle *GetFirstAlive();						// get the first live particle, iterate through all live particles from this with GetNext()
	xparticles_lib::XParticle *GetLastAlive();

	xparticles_lib::XParticle *CreateParticle();				// create a live particle, position/velocity/life etc. will need setting
	Bool SetParticleCount(Int32 count);									// set the number of live particles, each particle will need init
	Bool SetMaxCount(Int32 count);

	Int32 GetFlags();																		// currently private
	void SetFlags(Int32 flags);													// currently private
};

String XPGetVersion();

class XPC4DParticleModifierMsg
{
public:

	XPC4DParticleModifierMsg()
	{
		_emitter = nullptr;
	}

	XPEmitterObject *_emitter;
};

static const Int32 MSG_XPARTICLES_ISMODIFIER = 1029569;
static const Int32 MSG_XPARTICLES_C4DMODIFY = 1032239;

enum XP_MODIFIERMSG_FLAG
{
	XP_MODIFIERMSG_FLAG_0 = 0,
	XP_MODIFIERMSG_FLAG_PLUGIN_MODIFIER = (1 << 1),
	XP_MODIFIERMSG_FLAG_PLUGIN_THREAD = (1 << 2),
} ENUM_END_FLAGS(XP_MODIFIERMSG_FLAG);

class XPModifierMsgData
{
public:

	XPModifierMsgData()
	{
		_flags = XP_MODIFIERMSG_FLAG_0;
	}

	XP_MODIFIERMSG_FLAG _flags;
};

class XPModifierObject : public ObjectData
{
	INSTANCEOF(XPModifierObject, ObjectData)

public:

	virtual Bool Message(GeListNode *node, Int32 type, void *data)
	{
		if (type == MSG_XPARTICLES_ISMODIFIER && data != nullptr)
		{
			XPModifierMsgData *msgData = (XPModifierMsgData*)data;
			msgData->_flags |= XP_MODIFIERMSG_FLAG_PLUGIN_MODIFIER | XP_MODIFIERMSG_FLAG_PLUGIN_THREAD;
		}

		return SUPER::Message(node, type, data);
	}

	// return FALSE if anything went wrong and this modifier should be skipped
	virtual Bool InitModifyXP(BaseDocument *doc, BaseObject *modObject, BaseContainer *modData, XPEmitterObject *emitter, Float timeDiff)
	{
		return TRUE;
	}
	
	// always called if InitModifyXP returned TRUE
	virtual void FlushModifyXP()
	{
	}

	// startIndex/endIndex is NOTOK when not using the threaded (XP_MODIFIERMSG_FLAG_PLUGIN_THREAD) flag
	// return FALSE to stop (if Message set XP_MODIFIERMSG_FLAG_PLUGIN_THREAD)
	virtual Bool ModifyXP(BaseDocument *doc, BaseObject *modObject, BaseContainer *modData, XPEmitterObject *emitter, Int32 startIndex, Int32 endIndex, Float timeDiff)
	{
		return TRUE;
	}
	/* Threaded particle can be iterated as below
	Bool Gravitation::ModifyXP(BaseDocument *doc, BaseObject *modObject, BaseContainer *modData, XPEmitterObject *emitter, Int32 startIndex, Int32 endIndex, Float timeDiff)
	{
		xparticles_lib::XParticle *particle = emitter->GetParticle(startIndex);

		while (particle != nullptr && particle->GetIndex() <= endIndex)
		{
			particle = particle->GetNext();
		}

		return TRUE;
	}
	*/
};

//////////////////////////////////////////////////////////////////////////

class XPDomainObject : public BaseObject
{
private:

	XPDomainObject();
	~XPDomainObject();

public:

	static XPDomainObject *Alloc()
	{
		return (XPDomainObject*)BaseObject::Alloc(xparticles_lib::OXPEmitter);
	}

	static void Free(XPDomainObject *&xpObject)
	{
		BaseObject *op = xpObject; 
		BaseObject::Free(op);
		xpObject = NULL;
	}

	XPEmitterObject *GetGasEmitter();

	Int64 GetWidth();
	Int64 GetHeight();
	Int64 GetDepth();

	void GetVoxelXYZ(const Vector &p, Int64 &x, Int64 &y, Int64 &z);
	Vector GetVoxelCenter(Int64 x, Int64 y, Int64 z);

	Vector GetVelocity(const Vector &p);
	Vector GetVelocity(Int64 x, Int64 y, Int64 z);
	Float GetSmoke(const Vector &p);
	Float GetSmoke(Int64 x, Int64 y, Int64 z);
	Float GetFire(const Vector &p);
	Float GetFire(Int64 x, Int64 y, Int64 z);
	Float GetFuel(const Vector &p);
	Float GetFuel(Int64 x, Int64 y, Int64 z);
	Float GetTemperature(const Vector &p);
	Float GetTemperature(Int64 x, Int64 y, Int64 z);
	Vector GetUVW(const Vector &p);
	Vector GetUVW(Int64 x, Int64 y, Int64 z);
};

//////////////////////////////////////////////////////////////////////////

// private library definitions

#define LIBRARY_XPARTICLES		1029633

struct XParticlesLibrary : public C4DLibrary
{
	Int32 (*xpemitGetParticleU)(XPEmitterObject *xpObject);
	Int32 (*xpemitGetAliveCountP)(XPEmitterObject *xpObject);
	Int32 (*xpemitGetDeadCount)(XPEmitterObject *xpObject);
	xparticles_lib::XParticle *(*xpemitGetParticleI)(XPEmitterObject *xpObject, Int32 index);
	xparticles_lib::XParticle *(*xpemitCreateParticle)(XPEmitterObject *xpObject);
	Bool (*xpemitSetParticleCount)(XPEmitterObject *xpObject, Int32 count);
	Int32 (*xpemitGetFlags)(XPEmitterObject *xpObject);
	void (*xpemitSetFlags)(XPEmitterObject *xpObject, Int32 flags);

	Vector (*xppartGetVelocity)(xparticles_lib::XParticle *xpParticle);
	Vector (*xppartGetPosition)(xparticles_lib::XParticle *xpParticle);
	Float (*xppartGetLife)(xparticles_lib::XParticle *xpParticle);
	Float (*xppartGetTime)(xparticles_lib::XParticle *xpParticle);
	Vector (*xppartGetColor)(xparticles_lib::XParticle *xpParticle);
	Float (*xppartGetMass)(xparticles_lib::XParticle *xpParticle);
	Float (*xppartGetRadius)(xparticles_lib::XParticle *xpParticle);
	Float (*xppartGetSpeed)(xparticles_lib::XParticle *xpParticle);
	Int32 (*xppartGetGroupID)(xparticles_lib::XParticle *xpParticle);
	Int32 (*xppartGetID)(xparticles_lib::XParticle *xpParticle);
	xparticles_lib::XPARTICLE_FLAGS (*xppartGetFlags25)(xparticles_lib::XParticle *xpParticle);
	Float (*xppartGetDensity)(xparticles_lib::XParticle *xpParticle);

	void (*xppartSetPosition)(xparticles_lib::XParticle *xpParticle, const Vector &p);
	void (*xppartSetVelocity)(xparticles_lib::XParticle *xpParticle, const Vector &v);
	void (*xppartSetTime)(xparticles_lib::XParticle *xpParticle, Float time);
	void (*xppartSetLife)(xparticles_lib::XParticle *xpParticle, Float life);
	void (*xppartSetColor)(xparticles_lib::XParticle *xpParticle, const Vector &col);
	void (*xppartSetRadius)(xparticles_lib::XParticle *xpParticle, Float r);
	void (*xppartSetMass)(xparticles_lib::XParticle *xpParticle, Float m);
	void (*xppartSetSpeed)(xparticles_lib::XParticle *xpParticle, Float s);
	void (*xppartSetGroupID)(xparticles_lib::XParticle *xpParticle, Int32 id);
	void (*xppartSetID)(xparticles_lib::XParticle *xpParticle, Int32 id);
	void (*xppartSetFlags25)(xparticles_lib::XParticle *xpParticle, xparticles_lib::XPARTICLE_FLAGS flags);
	void (*xppartSetDensity)(xparticles_lib::XParticle *xpParticle, Float density);

	Int32 (*xppartGetIndex)(xparticles_lib::XParticle *xpParticle);
	xparticles_lib::XParticle *(*xppartGetNextO)(xparticles_lib::XParticle *xpParticle);

	Int32 (*xppartGetDisplay)(xparticles_lib::XParticle *xpParticle);
	void (*xppartSetDisplay)(xparticles_lib::XParticle *xpParticle, Int32 type);

	xparticles_lib::XParticle *(*xpemitGetFirstAliveQ)(XPEmitterObject *xpObject);
	xparticles_lib::XParticle *(*xpemitGetLastAliveZ)(XPEmitterObject *xpObject);

	Float (*xpvpSampleSize)(XPMaterial *xpMaterial, xparticles_lib::XParticle *xpParticle, const Vector &p, VolumeData *vd, XPVideoPost *render);
	Vector (*xpvpSampleColor)(XPMaterial *xpMaterial, xparticles_lib::XParticle *xpParticle, const Vector &p, VolumeData *vd, XPVideoPost *render, Float radius);
	Float (*xpvpSampleTrans)(XPMaterial *xpMaterial, xparticles_lib::XParticle *xpParticle, const Vector &p, VolumeData *vd, XPVideoPost *render, Float radius);

	GeData *(*xppartGetCustomData)(xparticles_lib::XParticle *xpParticle, Int32 index, Int32 *id, String *name);
	Int32 (*xppartAddCustomData)(xparticles_lib::XParticle *xpParticle, Int32 id, const String &name, const GeData &data);
	void (*xppartSetCustomData)(xparticles_lib::XParticle *xpParticle, Int32 index, const GeData &data);
	Int32 (*xppartFindCustomData)(xparticles_lib::XParticle *xpParticle, Int32 id, const String &name);
	Int32 (*xppartGetCustomDataCount)(xparticles_lib::XParticle *xpParticle);

	Int32 (*xpemitGetParticleCount)(XPEmitterObject *xpObject);
	xparticles_lib::XParticle *(*xpemitGetParticle)(XPEmitterObject *xpObject, Int32 index);
	Int32 (*xpemitGetAliveCount)(XPEmitterObject *xpObject);

	xparticles_lib::XParticle *(*xpemitGetFirstAlive)(XPEmitterObject *xpObject);
	xparticles_lib::XParticle *(*xpemitGetLastAlive)(XPEmitterObject *xpObject);

	xparticles_lib::XParticle *(*xppartGetNext)(xparticles_lib::XParticle *xpParticle);

	String (*xpGetVersion)();

	xparticles_lib::XPARTICLE_BITS (*xppartGetBits)(xparticles_lib::XParticle *xpParticle);
	Matrix (*xppartGetMatrix)(xparticles_lib::XParticle *xpParticle);
	Vector (*xppartGetRotation)(xparticles_lib::XParticle *xpParticle);
	Float (*xppartGetDistanceTravelled)(xparticles_lib::XParticle *xpParticle);

	Bool (*xppartRemoveCustomData)(xparticles_lib::XParticle *xpParticle, Int32 index);

	void (*xppartSetBits)(xparticles_lib::XParticle *xpParticle, xparticles_lib::XPARTICLE_BITS bits);
	void (*xppartSetMatrix)(xparticles_lib::XParticle *xpParticle, const Matrix &m);
	void (*xppartSetRotation)(xparticles_lib::XParticle *xpParticle, const Vector &rot);
	void (*xppartSetDistanceTravelled)(xparticles_lib::XParticle *xpParticle, Float dist);

	Int32 (*xppartGetBirthConstraintsCount)(xparticles_lib::XParticle *xpParticle);
	Int32 (*xppartGetDistanceConstraintsCount)(xparticles_lib::XParticle *xpParticle);
	Int32 (*xppartGetParticleConstraintsCount)(xparticles_lib::XParticle *xpParticle);
	Int32 (*xppartGetColliderConstraintsCount)(xparticles_lib::XParticle *xpParticle);

	xparticles_lib::XParticleConstraint *(*xppartGetBirthConstraint)(xparticles_lib::XParticle *xpParticle, Int32 index);
	xparticles_lib::XParticleConstraint *(*xppartGetDistanceConstraint)(xparticles_lib::XParticle *xpParticle, Int32 index);
	xparticles_lib::XParticleConstraint *(*xppartGetParticleConstraint)(xparticles_lib::XParticle *xpParticle, Int32 index);
	xparticles_lib::XParticleColliderConstraint *(*xppartGetColliderConstraint)(xparticles_lib::XParticle *xpParticle, Int32 index);

	xparticles_lib::XParticleConstraint *(*xppartAddBirthConstraint)(xparticles_lib::XParticle *xpParticle);
	xparticles_lib::XParticleConstraint *(*xppartAddDistanceConstraint)(xparticles_lib::XParticle *xpParticle);
	xparticles_lib::XParticleConstraint *(*xppartAddParticleConstraint)(xparticles_lib::XParticle *xpParticle);
	xparticles_lib::XParticleConstraint *(*xppartAddColliderConstraint)(xparticles_lib::XParticle *xpParticle);

	void (*xppartRemoveBirthConstraint)(xparticles_lib::XParticle *xpParticle, Int32 index);
	void (*xppartRemoveDistanceConstraint)(xparticles_lib::XParticle *xpParticle, Int32 index);
	void (*xppartRemoveParticleConstraint)(xparticles_lib::XParticle *xpParticle, Int32 index);
	void (*xppartRemoveColliderConstraint)(xparticles_lib::XParticle *xpParticle, Int32 index);

	Float (*xpconstraintGetLength)(xparticles_lib::XParticleConstraint *xpConstraint);
	Int32 (*xpconstraintGetIndex)(xparticles_lib::XParticleConstraint *xpConstraint);
	Int32 (*xpconstraintGetFlags)(xparticles_lib::XParticleConstraint *xpConstraint);
	Int32 (*xpconstraintGetID)(xparticles_lib::XParticleConstraint *xpConstraint);

	void (*xpconstraintSetLength)(xparticles_lib::XParticleConstraint *xpConstraint, Float len);
	void (*xpconstraintSetIndex)(xparticles_lib::XParticleConstraint *xpConstraint, Int32 index);
	void (*xpconstraintSetFlags)(xparticles_lib::XParticleConstraint *xpConstraint, Int32 flags);
	void (*xpconstraintSetID)(xparticles_lib::XParticleConstraint *xpConstraint, Int32 id);

	Float (*xpcollconstraintGetLength)(xparticles_lib::XParticleColliderConstraint *xpConstraint);
	Int32 (*xpcollconstraintGetIndex)(xparticles_lib::XParticleColliderConstraint *xpConstraint);
	Int32 (*xpcollconstraintGetFlags)(xparticles_lib::XParticleColliderConstraint *xpConstraint);
	Int32 (*xpcollconstraintGetID)(xparticles_lib::XParticleColliderConstraint *xpConstraint);
	UInt64 (*xpcollconstraintGetColliderID)(xparticles_lib::XParticleColliderConstraint *xpConstraint);
	void (*xpcollconstraintGetPositionRS)(xparticles_lib::XParticleColliderConstraint *xpConstraint, Float &r, Float &s);
	Vector (*xpcollconstraintGetLastPosition)(xparticles_lib::XParticleColliderConstraint *xpConstraint);

	void (*xpcollconstraintSetLength)(xparticles_lib::XParticleColliderConstraint *xpConstraint, Float len);
	void (*xpcollconstraintSetIndex)(xparticles_lib::XParticleColliderConstraint *xpConstraint, Int32 index);
	void (*xpcollconstraintSetFlags)(xparticles_lib::XParticleColliderConstraint *xpConstraint, Int32 flags);
	void (*xpcollconstraintSetID)(xparticles_lib::XParticleColliderConstraint *xpConstraint, Int32 id);
	void (*xpcollconstraintSetColliderID)(xparticles_lib::XParticleColliderConstraint *xpConstraint, UInt64 id);
	void (*xpcollconstraintSetPositionRS)(xparticles_lib::XParticleColliderConstraint *xpConstraint, Float r, Float s);
	void (*xpcollconstraintSetLastPosition)(xparticles_lib::XParticleColliderConstraint *xpConstraint, const Vector &pos);

	Vector (*xpMixRSreal)(Float r, Float s, Float ra, Float rb, Float rc, Float rd, Bool quad);
	Vector (*xpMixRSvector)(Float r, Float s, const Vector &va, const Vector &vb, const Vector &vc, const Vector &vd, Bool quad);
	void (*xpGetRS)(Float &r, Float &s, const Vector &p, const Vector &va, const Vector &vb, const Vector &vc, const Vector &vd, Bool quad);

	Vector (*xppartGetSpin)(xparticles_lib::XParticle *xpParticle);
	Bool (*xppartIsSpinEnabled)(xparticles_lib::XParticle *xpParticle);
	void (*xppartSetSpin)(xparticles_lib::XParticle *xpParticle, const Vector &spin);
	void (*xppartSetSpinEnabled)(xparticles_lib::XParticle *xpParticle, Bool enable);

	Int32 (*xpemitGetMaxCount)(XPEmitterObject *xpObject);
	Bool (*xpemitSetMaxCount)(XPEmitterObject *xpObject, Int32 count);

	void (*xpvpSkipRender)(XPVideoPost *xpVP);

	xparticles_lib::XPARTICLE_FLAGS (*xppartGetFlags)(xparticles_lib::XParticle *xpParticle);
	void (*xppartSetFlags)(xparticles_lib::XParticle *xpParticle, xparticles_lib::XPARTICLE_FLAGS flags);

	void (*xppartSetTemperature)(xparticles_lib::XParticle *xpParticle, Float temp);
	void (*xppartSetFuel)(xparticles_lib::XParticle *xpParticle, Float fuel);
	void (*xppartSetFire)(xparticles_lib::XParticle *xpParticle, Float fire);
	void (*xppartSetSmoke)(xparticles_lib::XParticle *xpParticle, Float smoke);
	void (*xppartSetExpansion)(xparticles_lib::XParticle *xpParticle, Float expansion);
	Float (*xppartGetTemperature)(xparticles_lib::XParticle *xpParticle);
	Float (*xppartGetFuel)(xparticles_lib::XParticle *xpParticle);
	Float (*xppartGetFire)(xparticles_lib::XParticle *xpParticle);
	Float (*xppartGetSmoke)(xparticles_lib::XParticle *xpParticle);
	Float (*xppartGetExpansion)(xparticles_lib::XParticle *xpParticle);
	void (*xppartSetUVW)(xparticles_lib::XParticle *xpParticle, const Vector &uvw);
	Vector (*xppartGetUVW)(xparticles_lib::XParticle *xpParticle);

	XPEmitterObject *(*xpdomainGetGasEmitter)(XPDomainObject *xpDomain);

	Int64 (*xpdomainGetWidth)(XPDomainObject *xpDomain);
	Int64 (*xpdomainGetHeight)(XPDomainObject *xpDomain);
	Int64 (*xpdomainGetDepth)(XPDomainObject *xpDomain);

	void (*xpdomainGetVoxelXYZ)(XPDomainObject *xpDomain, const Vector &p, Int64 &x, Int64 &y, Int64 &z);
	Vector (*xpdomainGetVoxelCenter)(XPDomainObject *xpDomain, Int64 x, Int64 y, Int64 z);

	Vector(*xpdomainGetVelocity)(XPDomainObject *xpDomain, const Vector &p);
	Vector (*xpdomainGetVelocityXYZ)(XPDomainObject *xpDomain, Int64 x, Int64 y, Int64 z);
	Float (*xpdomainGetSmoke)(XPDomainObject *xpDomain, const Vector &p);
	Float (*xpdomainGetSmokeXYZ)(XPDomainObject *xpDomain, Int64 x, Int64 y, Int64 z);
	Float (*xpdomainGetFire)(XPDomainObject *xpDomain, const Vector &p);
	Float (*xpdomainGetFireXYZ)(XPDomainObject *xpDomain, Int64 x, Int64 y, Int64 z);
	Float (*xpdomainGetFuel)(XPDomainObject *xpDomain, const Vector &p);
	Float (*xpdomainGetFuelXYZ)(XPDomainObject *xpDomain, Int64 x, Int64 y, Int64 z);
	Float (*xpdomainGetTemperature)(XPDomainObject *xpDomain, const Vector &p);
	Float (*xpdomainGetTemperatureXYZ)(XPDomainObject *xpDomain, Int64 x, Int64 y, Int64 z);
	Vector (*xpdomainGetUVW)(XPDomainObject *xpDomain, const Vector &p);
	Vector (*xpdomainGetUVWXYZ)(XPDomainObject *xpDomain, Int64 x, Int64 y, Int64 z);
};

//////////////////////////////////////////////////////////////////////////

#endif	// __LIB_XP_H__
