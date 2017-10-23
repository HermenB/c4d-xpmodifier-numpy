#include "lib_xp.h"

//////////////////////////////////////////////////////////////////////////

XParticlesLibrary *lib_xp = NULL;

static XParticlesLibrary *CheckXPLib(Int32 offset)
{
	return (XParticlesLibrary*)CheckLib(LIBRARY_XPARTICLES, offset, (C4DLibrary**)&lib_xp);
}

#define XPLibCall(b) 		XParticlesLibrary *lib = CheckXPLib(LIBOFFSET(XParticlesLibrary, b)); \
															if (!lib || !lib->b) return; \
															(lib->b)

#define XPLibCallR(a,b)  XParticlesLibrary *lib = CheckXPLib(LIBOFFSET(XParticlesLibrary, b)); \
															if (!lib || !lib->b) return a; \
															return (lib->b)

//////////////////////////////////////////////////////////////////////////

Int32 XPEmitterObject::GetParticleCount() { XPLibCallR(0, xpemitGetParticleCount)(this); }
Int32 XPEmitterObject::GetAliveCount() { XPLibCallR(0, xpemitGetAliveCount)(this); }
Int32 XPEmitterObject::GetDeadCount() { XPLibCallR(0, xpemitGetDeadCount)(this); }
xparticles_lib::XParticle *XPEmitterObject::GetParticle(Int32 index) { XPLibCallR(NULL, xpemitGetParticle)(this, index); }
xparticles_lib::XParticle *XPEmitterObject::CreateParticle() { XPLibCallR(NULL, xpemitCreateParticle)(this); }
Bool XPEmitterObject::SetParticleCount(Int32 count) { XPLibCallR(FALSE, xpemitSetParticleCount)(this, count); }
Int32 XPEmitterObject::GetFlags() { XPLibCallR(0, xpemitGetFlags)(this); }
void XPEmitterObject::SetFlags(Int32 flags) { XPLibCall(xpemitSetFlags)(this, flags); }
xparticles_lib::XParticle *XPEmitterObject::GetFirstAlive() { XPLibCallR(NULL, xpemitGetFirstAlive)(this); }
xparticles_lib::XParticle *XPEmitterObject::GetLastAlive() { XPLibCallR(NULL, xpemitGetLastAlive)(this); }
Int32 XPEmitterObject::GetMaxCount() { XPLibCallR(0, xpemitGetMaxCount)(this); }
Bool XPEmitterObject::SetMaxCount(Int32 count) { XPLibCallR(FALSE, xpemitSetMaxCount)(this, count); }

void XPVideoPost::SkipRender()  { XPLibCall(xpvpSkipRender)(this); }

Vector xparticles_lib::XParticle::GetPosition() { XPLibCallR(Vector(), xppartGetPosition)(this); }
Vector xparticles_lib::XParticle::GetVelocity() { XPLibCallR(Vector(), xppartGetVelocity)(this); }
Float xparticles_lib::XParticle::GetTime() { XPLibCallR(0.0, xppartGetTime)(this); }
Float xparticles_lib::XParticle::GetLife() { XPLibCallR(0.0, xppartGetLife)(this); }
Vector xparticles_lib::XParticle::GetColor() { XPLibCallR(Vector(), xppartGetColor)(this); }
Float xparticles_lib::XParticle::GetRadius() { XPLibCallR(0.0, xppartGetRadius)(this); }
Float xparticles_lib::XParticle::GetMass() { XPLibCallR(0.0, xppartGetMass)(this); }
Float xparticles_lib::XParticle::GetSpeed() { XPLibCallR(0.0, xppartGetSpeed)(this); }
Int32 xparticles_lib::XParticle::GetGroupID() { XPLibCallR(0.0, xppartGetGroupID)(this); }
Int32 xparticles_lib::XParticle::GetID() { XPLibCallR(0.0, xppartGetID)(this); }
xparticles_lib::XPARTICLE_FLAGS xparticles_lib::XParticle::GetFlags() { XPLibCallR(xparticles_lib::XPARTICLE_FLAGS_0, xppartGetFlags)(this); }
Float xparticles_lib::XParticle::GetDensity() { XPLibCallR(0.0, xppartGetDensity)(this); }
Int32 xparticles_lib::XParticle::GetDisplay() { XPLibCallR(0.0, xppartGetDisplay)(this); }
xparticles_lib::XPARTICLE_BITS xparticles_lib::XParticle::GetBits() { XPLibCallR(xparticles_lib::XPARTICLE_BITS_0, xppartGetBits)(this); }
Matrix xparticles_lib::XParticle::GetMatrix() { XPLibCallR(Matrix(), xppartGetMatrix)(this); }
Vector xparticles_lib::XParticle::GetRotation() { XPLibCallR(Vector(), xppartGetRotation)(this); }
Float xparticles_lib::XParticle::GetDistanceTravelled() { XPLibCallR(0.0, xppartGetDistanceTravelled)(this); }
Vector xparticles_lib::XParticle::GetSpin() { XPLibCallR(Vector(), xppartGetSpin)(this); }
Bool xparticles_lib::XParticle::IsSpinEnabled() { XPLibCallR(FALSE, xppartIsSpinEnabled)(this); }
Float xparticles_lib::XParticle::GetTemperature() { XPLibCallR(0.0, xppartGetTemperature)(this); }
Float xparticles_lib::XParticle::GetFuel() { XPLibCallR(0.0, xppartGetFuel)(this); }
Float xparticles_lib::XParticle::GetFire() { XPLibCallR(0.0, xppartGetFire)(this); }
Float xparticles_lib::XParticle::GetSmoke() { XPLibCallR(0.0, xppartGetSmoke)(this); }
Float xparticles_lib::XParticle::GetExpansion() { XPLibCallR(0.0, xppartGetExpansion)(this); }
Vector xparticles_lib::XParticle::GetUVW() { XPLibCallR(Vector(), xppartGetUVW)(this); }

void xparticles_lib::XParticle::SetPosition(const Vector &p) { XPLibCall(xppartSetPosition)(this, p); }
void xparticles_lib::XParticle::SetVelocity(const Vector &v) { XPLibCall(xppartSetVelocity)(this, v); }
void xparticles_lib::XParticle::SetTime(Float time) { XPLibCall(xppartSetTime)(this, time); }
void xparticles_lib::XParticle::SetLife(Float life) { XPLibCall(xppartSetLife)(this, life); }
void xparticles_lib::XParticle::SetColor(const Vector &col) { XPLibCall(xppartSetColor)(this, col); }
void xparticles_lib::XParticle::SetRadius(Float r) { XPLibCall(xppartSetRadius)(this, r); }
void xparticles_lib::XParticle::SetMass(Float m) { XPLibCall(xppartSetMass)(this, m); }
void xparticles_lib::XParticle::SetSpeed(Float s) { XPLibCall(xppartSetSpeed)(this, s); }
void xparticles_lib::XParticle::SetGroupID(Int32 id) { XPLibCall(xppartSetGroupID)(this, id); }
void xparticles_lib::XParticle::SetID(Int32 id) { XPLibCall(xppartSetID)(this, id); }
void xparticles_lib::XParticle::SetFlags(xparticles_lib::XPARTICLE_FLAGS flags) { XPLibCall(xppartSetFlags)(this, flags); }
void xparticles_lib::XParticle::SetDensity(Float density) { XPLibCall(xppartSetDensity)(this, density); }
void xparticles_lib::XParticle::SetDisplay(Int32 type) { XPLibCall(xppartSetDisplay)(this, type); }
void xparticles_lib::XParticle::SetBits(XPARTICLE_BITS bits) { XPLibCall(xppartSetBits)(this, bits); }
void xparticles_lib::XParticle::SetMatrix(const Matrix &m) { XPLibCall(xppartSetMatrix)(this, m); }
void xparticles_lib::XParticle::SetRotation(const Vector &rot) { XPLibCall(xppartSetRotation)(this, rot); }
void xparticles_lib::XParticle::SetDistanceTravelled(Float dist) { XPLibCall(xppartSetDistanceTravelled)(this, dist); }
void xparticles_lib::XParticle::SetSpin(const Vector &spin) { XPLibCall(xppartSetSpin)(this, spin); }
void xparticles_lib::XParticle::SetSpinEnabled(Bool enable) { XPLibCall(xppartSetSpinEnabled)(this, enable); }
void xparticles_lib::XParticle::SetTemperature(Float temp) { XPLibCall(xppartSetTemperature)(this, temp); }
void xparticles_lib::XParticle::SetFuel(Float fuel) { XPLibCall(xppartSetFuel)(this, fuel); }
void xparticles_lib::XParticle::SetFire(Float fire) { XPLibCall(xppartSetFire)(this, fire); }
void xparticles_lib::XParticle::SetSmoke(Float smoke) { XPLibCall(xppartSetSmoke)(this, smoke); }
void xparticles_lib::XParticle::SetExpansion(Float expansion) { XPLibCall(xppartSetExpansion)(this, expansion); }
void xparticles_lib::XParticle::SetUVW(const Vector &uvw) { XPLibCall(xppartSetUVW)(this, uvw); }

Int32 xparticles_lib::XParticle::GetIndex() { XPLibCallR(0.0, xppartGetIndex)(this); }
xparticles_lib::XParticle *xparticles_lib::XParticle::GetNext() { XPLibCallR(NULL, xppartGetNext)(this); }

Int32 xparticles_lib::XParticle::AddCustomData(Int32 id, const String &name, const GeData &data) { XPLibCallR(NOTOK, xppartAddCustomData)(this, id, name, data); }
void xparticles_lib::XParticle::SetCustomData(Int32 index, const GeData &data) { XPLibCall(xppartSetCustomData)(this, index, data); }
GeData *xparticles_lib::XParticle::GetCustomData(Int32 index, Int32 *id, String *name) { XPLibCallR(NULL, xppartGetCustomData)(this, index, id, name); }
Int32 xparticles_lib::XParticle::FindCustomData(Int32 id, const String &name) { XPLibCallR(NOTOK, xppartFindCustomData)(this, id, name); }
Int32 xparticles_lib::XParticle::GetCustomDataCount() { XPLibCallR(0, xppartGetCustomDataCount)(this); }
Bool xparticles_lib::XParticle::RemoveCustomData(Int32 index) { XPLibCallR(FALSE, xppartRemoveCustomData)(this, index); }

Int32 xparticles_lib::XParticle::GetBirthConstraintsCount() { XPLibCallR(0, xppartGetBirthConstraintsCount)(this); }
Int32 xparticles_lib::XParticle::GetDistanceConstraintsCount() { XPLibCallR(0, xppartGetDistanceConstraintsCount)(this); }
Int32 xparticles_lib::XParticle::GetParticleConstraintsCount() { XPLibCallR(0, xppartGetParticleConstraintsCount)(this); }
Int32 xparticles_lib::XParticle::GetColliderConstraintsCount() { XPLibCallR(0, xppartGetColliderConstraintsCount)(this); }

xparticles_lib::XParticleConstraint *xparticles_lib::XParticle::GetBirthConstraint(Int32 index) { XPLibCallR(NULL, xppartGetBirthConstraint)(this, index); }
xparticles_lib::XParticleConstraint *xparticles_lib::XParticle::GetDistanceConstraint(Int32 index) { XPLibCallR(NULL, xppartGetDistanceConstraint)(this, index); }
xparticles_lib::XParticleConstraint *xparticles_lib::XParticle::GetParticleConstraint(Int32 index) { XPLibCallR(NULL, xppartGetParticleConstraint)(this, index); }
xparticles_lib::XParticleColliderConstraint *xparticles_lib::XParticle::GetColliderConstraint(Int32 index) { XPLibCallR(NULL, xppartGetColliderConstraint)(this, index); }

xparticles_lib::XParticleConstraint *xparticles_lib::XParticle::AddBirthConstraint() { XPLibCallR(NULL, xppartAddBirthConstraint)(this); }
xparticles_lib::XParticleConstraint *xparticles_lib::XParticle::AddDistanceConstraint() { XPLibCallR(NULL, xppartAddDistanceConstraint)(this); }
xparticles_lib::XParticleConstraint *xparticles_lib::XParticle::AddParticleConstraint() { XPLibCallR(NULL, xppartAddParticleConstraint)(this); }
xparticles_lib::XParticleConstraint *xparticles_lib::XParticle::AddColliderConstraint() { XPLibCallR(NULL, xppartAddColliderConstraint)(this); }

void xparticles_lib::XParticle::RemoveBirthConstraint(Int32 index) { XPLibCall(xppartRemoveBirthConstraint)(this, index); }
void xparticles_lib::XParticle::RemoveDistanceConstraint(Int32 index) { XPLibCall(xppartRemoveDistanceConstraint)(this, index); }
void xparticles_lib::XParticle::RemoveParticleConstraint(Int32 index) { XPLibCall(xppartRemoveParticleConstraint)(this, index); }
void xparticles_lib::XParticle::RemoveColliderConstraint(Int32 index) { XPLibCall(xppartRemoveColliderConstraint)(this, index); }

Float XPMaterial::SampleSize(xparticles_lib::XParticle *xpParticle, const Vector &p, VolumeData *vd, XPVideoPost *render) { XPLibCallR(0.0, xpvpSampleSize)(this, xpParticle, p, vd, render); }
Vector XPMaterial::SampleColor(xparticles_lib::XParticle *xpParticle, const Vector &p, VolumeData *vd, XPVideoPost *render, Float radius) { XPLibCallR(Vector(), xpvpSampleColor)(this, xpParticle, p, vd, render, radius); }
Float XPMaterial::SampleTrans(xparticles_lib::XParticle *xpParticle, const Vector &p, VolumeData *vd, XPVideoPost *render, Float radius) { XPLibCallR(0.0, xpvpSampleTrans)(this, xpParticle, p, vd, render, radius); }

String XPGetVersion()
{
	XPLibCallR(String(), xpGetVersion)();
}

Float xparticles_lib::XParticleConstraint::GetLength() { XPLibCallR(0.0, xpconstraintGetLength)(this); }
Int32 xparticles_lib::XParticleConstraint::GetIndex() { XPLibCallR(NOTOK, xpconstraintGetIndex)(this); }
Int32 xparticles_lib::XParticleConstraint::GetFlags() { XPLibCallR(0, xpconstraintGetFlags)(this); }
Int32 xparticles_lib::XParticleConstraint::GetID() { XPLibCallR(NOTOK, xpconstraintGetID)(this); }

void xparticles_lib::XParticleConstraint::SetLength(Float len) { XPLibCall(xpconstraintSetLength)(this, len); }
void xparticles_lib::XParticleConstraint::SetIndex(Int32 index) { XPLibCall(xpconstraintSetLength)(this, index); }
void xparticles_lib::XParticleConstraint::SetFlags(Int32 flags) { XPLibCall(xpconstraintSetLength)(this, flags); }
void xparticles_lib::XParticleConstraint::SetID(Int32 id) { XPLibCall(xpconstraintSetLength)(this, id); }

Float xparticles_lib::XParticleColliderConstraint::GetLength() { XPLibCallR(0.0, xpcollconstraintGetLength)(this); }
Int32 xparticles_lib::XParticleColliderConstraint::GetIndex() { XPLibCallR(NOTOK, xpcollconstraintGetIndex)(this); }
Int32 xparticles_lib::XParticleColliderConstraint::GetFlags() { XPLibCallR(0, xpcollconstraintGetFlags)(this); }
Int32 xparticles_lib::XParticleColliderConstraint::GetID() { XPLibCallR(NOTOK, xpcollconstraintGetID)(this); }
UInt64 xparticles_lib::XParticleColliderConstraint::GetColliderID() { XPLibCallR(0, xpcollconstraintGetColliderID)(this); }
void xparticles_lib::XParticleColliderConstraint::GetPositionRS(Float &r, Float &s) { XPLibCall(xpcollconstraintGetPositionRS)(this, r, s); }
Vector xparticles_lib::XParticleColliderConstraint::GetLastPosition() { XPLibCallR(Vector(), xpcollconstraintGetLastPosition)(this); }

void xparticles_lib::XParticleColliderConstraint::SetLength(Float len) { XPLibCall(xpcollconstraintSetLength)(this, len); }
void xparticles_lib::XParticleColliderConstraint::SetIndex(Int32 index) { XPLibCall(xpcollconstraintSetIndex)(this, index); }
void xparticles_lib::XParticleColliderConstraint::SetFlags(Int32 flags) { XPLibCall(xpcollconstraintSetFlags)(this, flags); }
void xparticles_lib::XParticleColliderConstraint::SetID(Int32 id) { XPLibCall(xpcollconstraintSetID)(this, id); }
void xparticles_lib::XParticleColliderConstraint::SetColliderID(UInt64 id) { XPLibCall(xpcollconstraintSetColliderID)(this, id); }
void xparticles_lib::XParticleColliderConstraint::SetPositionRS(Float r, Float s) { XPLibCall(xpcollconstraintSetPositionRS)(this, r, s); }
void xparticles_lib::XParticleColliderConstraint::SetLastPosition(const Vector &pos) { XPLibCall(xpcollconstraintSetLastPosition)(this, pos); }

Vector xparticles_lib::MixRS(Float r, Float s, Float ra, Float rb, Float rc, Float rd, Bool quad) { XPLibCallR(Vector(), xpMixRSreal)(r, s, ra, rb, rc, rd, quad); }
Vector xparticles_lib::MixRS(Float r, Float s, const Vector &va, const Vector &vb, const Vector &vc, const Vector &vd, Bool quad) { XPLibCallR(Vector(), xpMixRSvector)(r, s, va, vb, vc, vd, quad); }
void xparticles_lib::GetRS(Float &r, Float &s, const Vector &p, const Vector &va, const Vector &vb, const Vector &vc, const Vector &vd, Bool quad) { XPLibCall(xpGetRS)(r, s, p, va, vb, vc, vd, quad); }

XPEmitterObject *XPDomainObject::GetGasEmitter() { XPLibCallR(nullptr, xpdomainGetGasEmitter)(this); }
Int64 XPDomainObject::GetWidth() { XPLibCallR(0, xpdomainGetWidth)(this); }
Int64 XPDomainObject::GetHeight() { XPLibCallR(0, xpdomainGetHeight)(this); }
Int64 XPDomainObject::GetDepth() { XPLibCallR(0, xpdomainGetDepth)(this); }

void XPDomainObject::GetVoxelXYZ(const Vector &p, Int64 &x, Int64 &y, Int64 &z) { XPLibCall(xpdomainGetVoxelXYZ)(this, p, x, y, z); }
Vector XPDomainObject::GetVoxelCenter(Int64 x, Int64 y, Int64 z) { XPLibCallR(Vector(), xpdomainGetVoxelCenter)(this, x, y, z); }

Vector XPDomainObject::GetVelocity(const Vector &p) { XPLibCallR(Vector(), xpdomainGetVelocity)(this, p); }
Vector XPDomainObject::GetVelocity(Int64 x, Int64 y, Int64 z) { XPLibCallR(Vector(), xpdomainGetVelocityXYZ)(this, x, y, z); }
Float XPDomainObject::GetSmoke(const Vector &p) { XPLibCallR(0.0, xpdomainGetSmoke)(this, p); }
Float XPDomainObject::GetSmoke(Int64 x, Int64 y, Int64 z) { XPLibCallR(0.0, xpdomainGetSmokeXYZ)(this, x, y, z); }
Float XPDomainObject::GetFire(const Vector &p) { XPLibCallR(0.0, xpdomainGetFire)(this, p); }
Float XPDomainObject::GetFire(Int64 x, Int64 y, Int64 z) { XPLibCallR(0.0, xpdomainGetFireXYZ)(this, x, y, z); }
Float XPDomainObject::GetFuel(const Vector &p) { XPLibCallR(0.0, xpdomainGetFuel)(this, p); }
Float XPDomainObject::GetFuel(Int64 x, Int64 y, Int64 z) { XPLibCallR(0.0, xpdomainGetFuelXYZ)(this, x, y, z); }
Float XPDomainObject::GetTemperature(const Vector &p) { XPLibCallR(0.0, xpdomainGetTemperature)(this, p); }
Float XPDomainObject::GetTemperature(Int64 x, Int64 y, Int64 z) { XPLibCallR(0.0, xpdomainGetTemperatureXYZ)(this, x, y, z); }
Vector XPDomainObject::GetUVW(const Vector &p) { XPLibCallR(Vector(), xpdomainGetUVW)(this, p); }
Vector XPDomainObject::GetUVW(Int64 x, Int64 y, Int64 z) { XPLibCallR(Vector(), xpdomainGetUVWXYZ)(this, x, y, z); }
