//
//  conversion.hpp
//  myplugins
//
//  Created by HermenB on 20-09-17.
//  Copyright © 2017 MAXON Computer GmbH. All rights reserved.
//

#ifndef conversion_h
#define conversion_h

#include "conversion.h"

#include "c4d.h"
#include "Python.h"
#include "numpy/arrayobject.h"
#include "c4d_libs/lib_py.h"
#include "lib_xp.h"

enum xpProperties
{
    POSITION = 1,
    VELOCITY = 2,
    TIME = 1 << 2,
    LIFE = 1 << 3,
    COLOR = 1 << 4,
    RADIUS = 1 << 5,
    MASS = 1 << 6,
    SPEED = 1 << 7,
    GROUPID = 1 << 8,
    ID = 1 << 9,
    DENSITY = 1 << 10,
    DISPLAY = 1 << 11,
    MATRIX = 1 << 12,
    ROTATION = 1 << 13,
    DISTANCE = 1 << 14,
    SPIN = 1 << 15,
    //SPINENABLED = 1 << 16,
    TEMPERATURE = 1 << 16,
    FUEL = 1 << 17,
    FIRE = 1 << 18,
    SMOKE = 1 << 19,
    EXPANSION = 1 << 20,
    UVW = 1 << 21
}ENUM_END_FLAGS(xpProperties);

bool testNumpy();

class ParticleArray
{
public:
    Float* vPosition = nullptr;
    Float* vVelocity = nullptr;
    Float* fTime = nullptr;
    Float* fLife = nullptr;
    Float* vColor = nullptr;
    Float* fRadius = nullptr;
    Float* fMass = nullptr;
    Float* fSpeed = nullptr;
    Int32* iGroupID = nullptr;
    Int32* iID = nullptr;
    Float* fDensity = nullptr;
    Int32* iDisplay = nullptr;
    Float* mMatrix = nullptr;
    Float* vRotation = nullptr;	// HPB
    Float* fDistance = nullptr;
    Float* vSpin = nullptr;
    //Bool* bSpinEnabled = nullptr;
    Float* fTemperature = nullptr;
    Float* fFuel = nullptr;
    Float* fFire = nullptr;
    Float* fSmoke = nullptr;
    Float* fExpansion = nullptr;
    Float* vUVW = nullptr;
    
    Float* op_Mg = nullptr;
    
    Int32 msize;
    Int32 mPROPERTIES;
    
    ParticleArray() {};
    ParticleArray(XPEmitterObject *emitter, Int32 PROPERTIES=3) {
        xparticles_lib::XParticle *xp = emitter->GetFirstAlive();
        msize = emitter->GetParticleCount();
        mPROPERTIES = PROPERTIES;
        Init(xp);
    }
    ParticleArray(xparticles_lib::XParticle *xp, Int32 size, Int32 PROPERTIES=3) {
        msize = size;
        mPROPERTIES = PROPERTIES;
        Init(xp);
    }
    // c4d particles ctor
    ParticleArray(Particle *pp, Int32 pcnt) {
        msize = pcnt;
        mPROPERTIES = POSITION|VELOCITY;
        Init(pp);
    }
    
    ~ParticleArray(){Free();};
    
    void Init(Particle *pp);
    void Init(xparticles_lib::XParticle *xp);
    void SetMg(BaseObject* op);
    void Set(Particle* pp, BaseParticle* ss);
    void Set(XPEmitterObject *emitter);
    void Free();
};


class NumpyArray : public ParticleArray
{
public:
    PyObject* vPositionNP = nullptr;
    PyObject* vVelocityNP = nullptr;
    PyObject* fTimeNP = nullptr;
    PyObject* fLifeNP = nullptr;
    PyObject* vColorNP = nullptr;
    PyObject* fRadiusNP = nullptr;
    PyObject* fMassNP = nullptr;
    PyObject* fSpeedNP = nullptr;
    PyObject* iGroupIDNP = nullptr;
    PyObject* iIDNP = nullptr;
    PyObject* fDensityNP = nullptr;
    PyObject* iDisplayNP = nullptr;
    PyObject* mMatrixNP = nullptr;
    PyObject* vRotationNP = nullptr; // HPB
    PyObject* fDistanceNP = nullptr;
    PyObject* vSpinNP = nullptr;
    //PyObject* bSpinEnabledNP = nullptr; //nb
    PyObject* fTemperatureNP = nullptr;
    PyObject* fFuelNP = nullptr;
    PyObject* fFireNP = nullptr;
    PyObject* fSmokeNP = nullptr;
    PyObject* fExpansionNP = nullptr;
    PyObject* vUVWNP = nullptr;
    
    PyObject* op_MgNP = nullptr;
    
    NumpyArray(XPEmitterObject *emitter, Int32 PROPERTIES=3) {
        xparticles_lib::XParticle *xp = emitter->GetFirstAlive();
        msize = emitter->GetParticleCount();
        mPROPERTIES = PROPERTIES;
        Init(xp);
    }
    NumpyArray(xparticles_lib::XParticle *xp, Int32 size, Int32 PROPERTIES=3) {
        msize = size;
        mPROPERTIES = PROPERTIES;
        Init(xp);
    }
    NumpyArray(Particle *pp, Int32 pcnt) {
        msize = pcnt;
        mPROPERTIES = POSITION|VELOCITY;
        Init(pp);
    }
    
    /*
     ~NumpyArray() {
        FreeNP();
        Free();
    }
    */
    
    void addNumpyArrays(PythonLibrary pylib, PythonBase *pybase);
    void FreeNP();
};


#endif /* conversion_h */
