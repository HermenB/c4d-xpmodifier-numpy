//
//  conversion.cpp
//  myplugins
//
//  Created by HermenB on 20-09-17.
//  Copyright © 2017 MAXON Computer GmbH. All rights reserved.
//

#include "conversion.h"

bool testNumpy() {
    PythonLibrary pylib;
    PythonGIL *pyGIL = pylib.AllocGIL();
    
    //run pythoncode
    bool result = pylib.Execute("import numpy\n");
    if (!result) {
        pylib.ErrPrint();
        GeConsoleOut("Numpy could not be imported.\nPlease install Numpy in your '/packages' directory.\n");
    }
    pylib.FreeGIL(pyGIL);
    return result;
}


void ParticleArray::Init(Particle *pp) {
    vPosition = new Float[3*msize];
    vVelocity = new Float[3*msize];
    Int32 FLAGS = PARTICLEFLAGS_VISIBLE|PARTICLEFLAGS_ALIVE;
    Int32 j = 0;
    for (Int32 i=0; i<msize; i++) {
        Particle &particle = pp[i];
        
        // Skip unwanted particles
        if (!(particle.bits&FLAGS))
            continue;
        
        vPosition[j] = particle.off.x;
        vVelocity[j++] = particle.v3.x;
        
        vPosition[j] = particle.off.y;
        vVelocity[j++] = particle.v3.y;
        
        vPosition[j] = particle.off.z;
        vVelocity[j++] = particle.v3.z;
    }
    msize = j/3;
}
    
void ParticleArray::Init(xparticles_lib::XParticle *xp)
{
    if (mPROPERTIES & POSITION) {
        vPosition = new Float[3*msize];
        if (vPosition == nullptr) mPROPERTIES -= POSITION;
    }
    if (mPROPERTIES & VELOCITY) {
        vVelocity = new Float[3*msize];
        if (vVelocity == nullptr) mPROPERTIES -= VELOCITY;
    }
    if (mPROPERTIES & TIME) {
        fTime = new Float[msize];
        if (fTime == nullptr) mPROPERTIES -= TIME;
    }
    if (mPROPERTIES & LIFE) {
        fLife = new Float[msize];
        if (fLife == nullptr) mPROPERTIES -= LIFE;
    }
    if (mPROPERTIES & COLOR) {
        vColor = new Float[3*msize];
        if (vColor == nullptr) mPROPERTIES -= COLOR;
    }
    if (mPROPERTIES & RADIUS) {
        fRadius = new Float[msize];
        if (fRadius == nullptr) mPROPERTIES -= RADIUS;
    }
    if (mPROPERTIES & MASS) {
        fMass = new Float[msize];
        if (fMass == nullptr) mPROPERTIES -= MASS;
    }
    if (mPROPERTIES & SPEED) {
        fSpeed = new Float[msize];
        if (fSpeed == nullptr) mPROPERTIES -= SPEED;
    }
    if (mPROPERTIES & GROUPID) {
        iGroupID = new Int32[msize];
        if (iGroupID == nullptr) mPROPERTIES -= GROUPID;
    }
    if (mPROPERTIES & ID) {
        iID = new Int32[msize];
        if (iID == nullptr) mPROPERTIES -= ID;
    }
    if (mPROPERTIES & DENSITY) {
        fDensity = new Float[msize];
        if (fDensity == nullptr) mPROPERTIES -= DENSITY;
    }
    if (mPROPERTIES & DISPLAY) {
        iDisplay = new Int32[msize];
        if (iDisplay == nullptr) mPROPERTIES -= DISPLAY;
    }
    if (mPROPERTIES & MATRIX) {
        mMatrix = new Float[12*msize];
        if (mMatrix == nullptr) mPROPERTIES -= MATRIX;
    }
    if (mPROPERTIES & ROTATION) {
        vRotation = new Float[3*msize];
        if (vRotation == nullptr) mPROPERTIES -= ROTATION;
    }
    if (mPROPERTIES & DISTANCE) {
        fDistance = new Float[msize];
        if (fDistance == nullptr) mPROPERTIES -= DISTANCE;
    }
    if (mPROPERTIES & SPIN) {
        vSpin = new Float[3*msize];
        if (vSpin == nullptr) mPROPERTIES -= SPIN;
    }
    if (mPROPERTIES & TEMPERATURE) {
        fTemperature = new Float[msize];
        if (fTemperature == nullptr) mPROPERTIES -= TEMPERATURE;
    }
    if (mPROPERTIES & FUEL) {
        fFuel = new Float[msize];
        if (fFuel == nullptr) mPROPERTIES -= FUEL;
    }
    if (mPROPERTIES & FIRE) {
        fFire = new Float[msize];
        if (fFire == nullptr) mPROPERTIES -= FIRE;
    }
    if (mPROPERTIES & SMOKE) {
        fSmoke = new Float[msize];
        if (fSmoke == nullptr) mPROPERTIES -= SMOKE;
    }
    if (mPROPERTIES & EXPANSION) {
        fExpansion = new Float[msize];
        if (fExpansion == nullptr) mPROPERTIES -= EXPANSION;
    }
    if (mPROPERTIES & UVW) {
        vUVW = new Float[3*msize];
        if (vUVW == nullptr) mPROPERTIES -= UVW;
    }
    
    Int32 i = 0, j = 0, k = 0;
    Vector v(DC);
    Matrix m(DC);
    
    while (xp != nullptr) {
        j = 3*i;
        if (mPROPERTIES & POSITION) {
            v = xp->GetPosition();
            vPosition[j]   = v.x;
            vPosition[j+1] = v.y;
            vPosition[j+2] = v.z;
        }
        if (mPROPERTIES & VELOCITY) {
            v = xp->GetVelocity();
            vVelocity[j]   = v.x;
            vVelocity[j+1] = v.y;
            vVelocity[j+2] = v.z;
        }
        if (mPROPERTIES & TIME) fTime[i] = xp->GetTime();
        if (mPROPERTIES & LIFE) fLife[i] = xp->GetLife();
        if (mPROPERTIES & COLOR) {
            v = xp->GetColor();
            vColor[j] = v.x;
            vColor[j+1] = v.y;
            vColor[j+2] = v.z;
        }
        if (mPROPERTIES & RADIUS) fRadius[i] = xp->GetRadius();
        if (mPROPERTIES & MASS) fMass[i] = xp->GetMass();
        if (mPROPERTIES & SPEED) fSpeed[i] = xp->GetSpeed();
        if (mPROPERTIES & GROUPID) iGroupID[i] = xp->GetGroupID();
        if (mPROPERTIES & ID) iID[i] = xp->GetID();
        if (mPROPERTIES & DENSITY) fDensity[i] = xp->GetDensity();
        if (mPROPERTIES & DISPLAY) iDisplay[i] = xp->GetDisplay();
        if (mPROPERTIES & MATRIX) {
            k = 12*i;
            m = xp->GetMatrix();
            mMatrix[k] = m.off.x;
            mMatrix[k+1] = m.off.y;
            mMatrix[k+2] = m.off.z;
            mMatrix[k+3] = m.v1.x;
            mMatrix[k+4] = m.v1.y;
            mMatrix[k+5] = m.v1.z;
            mMatrix[k+6] = m.v2.x;
            mMatrix[k+7] = m.v2.y;
            mMatrix[k+8] = m.v2.z;
            mMatrix[k+9] = m.v3.x;
            mMatrix[k+10] = m.v3.y;
            mMatrix[k+11] = m.v3.z;
        }
        if (mPROPERTIES & ROTATION) {
            v = xp->GetRotation();
            vRotation[j] = v.x;
            vRotation[j+1] = v.y;
            vRotation[j+2] = v.z;
        }
        if (mPROPERTIES & DISTANCE) fDistance[i] = xp->GetDistanceTravelled();
        if (mPROPERTIES & SPIN) {
            v = xp->GetSpin();
            vSpin[j] = v.x;
            vSpin[j+1] = v.y;
            vSpin[j+2] = v.z;
        }
        if (mPROPERTIES & TEMPERATURE) fTemperature[i] = xp->GetTemperature();
        if (mPROPERTIES & FUEL) fFuel[i] = xp->GetFuel();
        if (mPROPERTIES & FIRE) fFire[i] = xp->GetFire();
        if (mPROPERTIES & SMOKE) fSmoke[i] = xp->GetSmoke();
        if (mPROPERTIES & EXPANSION) fExpansion[i] = xp->GetExpansion();
        if (mPROPERTIES & UVW) {
            v = xp->GetUVW();
            vUVW[j] = v.x;
            vUVW[j+1] = v.y;
            vUVW[j+2] = v.z;
        }
        xp = xp->GetNext();
        i++;
    }
    msize = i;
}

void ParticleArray::SetMg(BaseObject* op) {
    Matrix m = op->GetMg();
    op_Mg = new double[12] {m.off.x, m.off.y, m.off.z,
                            m.v1.x, m.v1.y, m.v1.z,
                            m.v2.x, m.v2.y, m.v2.z,
                            m.v3.x, m.v3.y, m.v3.z};
}

void ParticleArray::Set(Particle *pp, BaseParticle* ss) {
    Int32 FLAGS = PARTICLEFLAGS_VISIBLE|PARTICLEFLAGS_ALIVE;
    Int32 j = 0;
    for (Int32 i=0; i<msize; i++) {
        Particle &particle = pp[i];
        
        // Skip unwanted particles
        if (!(particle.bits&FLAGS))
            continue;
        
        particle.off = Vector(vPosition[j], vPosition[j+1], vPosition[j+2]);
        //particle.v3 = Vector(vVelocity[j], vVelocity[j+1], vVelocity[j+2]);
        
        // Add resulting velocity
        BaseParticle &baseParticle = ss[i];
        baseParticle.count++;
        baseParticle.v += Vector(vVelocity[j], vVelocity[j+1], vVelocity[j+2]);
        
        j += 3;
    }
}


void ParticleArray::Set(XPEmitterObject *emitter) {
    Int32 i = 0, j = 0, k = 0;
    Vector v(DC);
    Matrix m(DC);
    
    xparticles_lib::XParticle *xp = emitter->GetFirstAlive();
    
    while (xp != nullptr) {
        j = 3*i;
        if (mPROPERTIES & POSITION) {
            v.x = vPosition[j];
            v.y = vPosition[j+1];
            v.z = vPosition[j+2];
            xp->SetPosition(v);
                        }
        if (mPROPERTIES & VELOCITY) {
            v.x = vVelocity[j];
            v.y = vVelocity[j+1];
            v.z = vVelocity[j+2];
            xp->SetVelocity(v);
        }
        if (mPROPERTIES & TIME) xp->SetTime(fTime[i]);              //
        if (mPROPERTIES & LIFE) xp->SetLife(fLife[i]);              //
        if (mPROPERTIES & COLOR) {
            v.x = vColor[j];
            v.y = vColor[j+1];
            v.z = vColor[j+2];
            xp->SetColor(v);
        }
        if (mPROPERTIES & RADIUS) xp->SetRadius(fRadius[i]);
        if (mPROPERTIES & MASS) xp->SetMass(fMass[i]);
        if (mPROPERTIES & SPEED) xp->SetSpeed(fSpeed[i]);           //
        if (mPROPERTIES & GROUPID) xp->SetGroupID(iGroupID[i]);
        if (mPROPERTIES & ID) xp->SetID(iID[i]);                    //
        if (mPROPERTIES & DENSITY) xp->SetDensity(fDensity[i]);
        if (mPROPERTIES & DISPLAY) xp->SetDisplay( iDisplay[i]);
        if (mPROPERTIES & MATRIX) {
            k = 12*i;
            m.off.x = mMatrix[k];
            m.off.y = mMatrix[k+1];
            m.off.z = mMatrix[k+2];
            m.v1.x = mMatrix[k+3];
            m.v1.y = mMatrix[k+4];
            m.v1.z = mMatrix[k+5];
            m.v2.x = mMatrix[k+6];
            m.v2.y = mMatrix[k+7];
            m.v2.z = mMatrix[k+8];
            m.v3.x = mMatrix[k+9];
            m.v3.y = mMatrix[k+10];
            m.v3.z = mMatrix[k+11];
            xp->SetMatrix(m);
        }
        if (mPROPERTIES & ROTATION) {
            v.x = vRotation[j];
            v.y = vRotation[j+1];
            v.z = vRotation[j+2];
            xp->SetRotation(v);
        }
        if (mPROPERTIES & DISTANCE) xp->SetDistanceTravelled(fDistance[i]);     //
        if (mPROPERTIES & SPIN) {
            v.x = vSpin[j];
            v.y = vSpin[j+1];
            v.z = vSpin[j+2];
            xp->SetSpin(v);
        }
        if (mPROPERTIES & TEMPERATURE) xp->SetTemperature(fTemperature[i]);
        if (mPROPERTIES & FUEL) xp->SetFuel(fFuel[i]);
        if (mPROPERTIES & FIRE) xp->SetFire(fFire[i]);
        if (mPROPERTIES & SMOKE) xp->SetSmoke(fSmoke[i]);
        if (mPROPERTIES & EXPANSION) xp->SetExpansion(fExpansion[i]);
        if (mPROPERTIES & UVW) {
            v.x = vUVW[j];
            v.y = vUVW[j+1];
            v.z = vUVW[j+2];
            xp->SetUVW(v);
        }
        xp = xp->GetNext();
        i++;
    }

}
    
void ParticleArray::Free() {
    if (op_Mg != nullptr) delete[] op_Mg;
    if (mPROPERTIES & POSITION) delete[] vPosition;
    if (mPROPERTIES & VELOCITY) delete[] vVelocity;
    if (mPROPERTIES & TIME) delete[] fTime;
    if (mPROPERTIES & LIFE) delete[] fLife;
    if (mPROPERTIES & COLOR) delete[] vColor;
    if (mPROPERTIES & RADIUS) delete[] fRadius;
    if (mPROPERTIES & MASS) delete[] fMass;
    if (mPROPERTIES & SPEED) delete[] fSpeed;
    if (mPROPERTIES & GROUPID) delete[] iGroupID;
    if (mPROPERTIES & ID) delete[] iID;
    if (mPROPERTIES & DENSITY) delete[] fDensity;
    if (mPROPERTIES & DISPLAY) delete[] iDisplay;
    if (mPROPERTIES & MATRIX) delete[] mMatrix;
    if (mPROPERTIES & ROTATION) delete[] vRotation;
    if (mPROPERTIES & DISTANCE) delete[] fDistance;
    if (mPROPERTIES & SPIN) delete[] vSpin;
    if (mPROPERTIES & TEMPERATURE) delete[] fTemperature;
    if (mPROPERTIES & FUEL) delete[] fFuel;
    if (mPROPERTIES & FIRE) delete[] fFire;
    if (mPROPERTIES & SMOKE) delete[] fSmoke;
    if (mPROPERTIES & EXPANSION) delete[] fExpansion;
    if (mPROPERTIES & UVW) delete[] vUVW;
}



static void addArray(PythonLibrary pylib, PythonBase *pybase, Int32 ND, npy_intp *dims, PyObject* NParray, int NPTYPE, void* arr, String pyname) {
    NParray = PyArray_SimpleNewFromData(ND, dims, NPTYPE, arr);
    pylib.SetPyObject(pybase, pyname, (_PyObject*)NParray);
}
    
void NumpyArray::addNumpyArrays(PythonLibrary pylib, PythonBase *pybase) {
    
    _import_array();
    
    if (op_Mg != nullptr) {
        npy_intp mdims[2] {4, 3};
        addArray(pylib, pybase, 2, mdims, op_MgNP, NPY_DOUBLE, op_Mg, "m");
    }
    
    npy_intp dims[2] {msize, 3};
    if (mPROPERTIES & POSITION) {
        addArray(pylib, pybase, 2, dims, vPositionNP, NPY_DOUBLE, vPosition, "Position");
    }
    if (mPROPERTIES & VELOCITY) {
        addArray(pylib, pybase, 2, dims, vVelocityNP, NPY_DOUBLE, vVelocity, "Velocity");
    }
    if (mPROPERTIES & TIME) {
        addArray(pylib, pybase, 1, dims, fTimeNP, NPY_DOUBLE, fTime, "Time");
    }
    if (mPROPERTIES & LIFE) {
        addArray(pylib, pybase, 1, dims, fLifeNP, NPY_DOUBLE, fLife, "Life");
    }
    if (mPROPERTIES & COLOR) {
        addArray(pylib, pybase, 2, dims, vColorNP, NPY_DOUBLE, vColor, "Color");
    }
    if (mPROPERTIES & RADIUS) {
        addArray(pylib, pybase, 1, dims, fRadiusNP, NPY_DOUBLE, fRadius, "Radius");
    }
    if (mPROPERTIES & MASS) {
        addArray(pylib, pybase, 1, dims, fMassNP, NPY_DOUBLE, fMass, "Mass");
    }
    if (mPROPERTIES & SPEED) {
        addArray(pylib, pybase, 1, dims, fSpeedNP, NPY_DOUBLE, fSpeed, "Speed");
    }
    if (mPROPERTIES & GROUPID) {
        addArray(pylib, pybase, 1, dims, iGroupIDNP, NPY_INT32, iGroupID, "GroupID");
    }
    if (mPROPERTIES & ID) {
        addArray(pylib, pybase, 1, dims, iIDNP, NPY_INT32, iID, "ID");
    }
    if (mPROPERTIES & DENSITY) {
        addArray(pylib, pybase, 1, dims, fDensityNP, NPY_DOUBLE, fDensity, "Density");
    }
    if (mPROPERTIES & DISPLAY) {
        addArray(pylib, pybase, 1, dims, iDisplayNP, NPY_INT32, iDisplay, "Display");
    }
    if (mPROPERTIES & MATRIX) {
        npy_intp dimm[3] {msize, 4, 3};
        addArray(pylib, pybase, 3, dimm, mMatrixNP, NPY_DOUBLE, mMatrix, "Matrix");
    }
    if (mPROPERTIES & ROTATION) {
        addArray(pylib, pybase, 2, dims, vRotationNP, NPY_DOUBLE, vRotation, "Rotation");
    }
    if (mPROPERTIES & DISTANCE) {
        addArray(pylib, pybase, 1, dims, fDistanceNP, NPY_DOUBLE, fDistance, "Distance");
    }
    if (mPROPERTIES & SPIN) {
        addArray(pylib, pybase, 2, dims, vSpinNP, NPY_DOUBLE, vSpin, "Spin");
    }
    if (mPROPERTIES & TEMPERATURE) {
        addArray(pylib, pybase, 1, dims, fTemperatureNP, NPY_DOUBLE, fTemperature, "Temperature");
    }
    if (mPROPERTIES & FUEL) {
        addArray(pylib, pybase, 1, dims, fFuelNP, NPY_DOUBLE, fFuel, "Fuel");
    }
    if (mPROPERTIES & FIRE) {
        addArray(pylib, pybase, 1, dims, fFireNP, NPY_DOUBLE, fFire, "Fire");
    }
    if (mPROPERTIES & SMOKE) {
        addArray(pylib, pybase, 1, dims, fSmokeNP, NPY_DOUBLE, fSmoke, "Smoke");
    }
    if (mPROPERTIES & EXPANSION) {
        addArray(pylib, pybase, 1, dims, fExpansionNP, NPY_DOUBLE, fExpansion, "Expansion");
    }
    if (mPROPERTIES & UVW) {
        addArray(pylib, pybase, 2, dims, vUVWNP, NPY_DOUBLE, vUVW, "UVW");
    }
    
}
    
void NumpyArray::FreeNP() {
    // Not called
    if (mPROPERTIES & POSITION) Py_DECREF (vPositionNP);
    if (mPROPERTIES & VELOCITY) Py_DECREF (vVelocityNP);
    if (mPROPERTIES & TIME) Py_DECREF (fTimeNP);
    if (mPROPERTIES & LIFE) Py_DECREF (fLifeNP);
    if (mPROPERTIES & COLOR) Py_DECREF (vColorNP);
    if (mPROPERTIES & RADIUS) Py_DECREF (fRadiusNP);
    if (mPROPERTIES & MASS) Py_DECREF (fMassNP);
    if (mPROPERTIES & SPEED) Py_DECREF (fSpeedNP);
    if (mPROPERTIES & GROUPID) Py_DECREF (iGroupIDNP);
    if (mPROPERTIES & ID) Py_DECREF (iIDNP);
    if (mPROPERTIES & DENSITY) Py_DECREF (fDensityNP);
    if (mPROPERTIES & DISPLAY) Py_DECREF (iDisplayNP);
    if (mPROPERTIES & MATRIX) Py_DECREF (mMatrixNP);
    if (mPROPERTIES & ROTATION) Py_DECREF (vRotationNP);
    if (mPROPERTIES & DISTANCE) Py_DECREF (fDistanceNP);
    if (mPROPERTIES & SPIN) Py_DECREF (vSpinNP);
    if (mPROPERTIES & TEMPERATURE) Py_DECREF (fTemperatureNP);
    if (mPROPERTIES & FUEL) Py_DECREF (fFuelNP);
    if (mPROPERTIES & FIRE) Py_DECREF (fFireNP);
    if (mPROPERTIES & SMOKE) Py_DECREF (fSmokeNP);
    if (mPROPERTIES & EXPANSION) Py_DECREF (fExpansionNP);
    if (mPROPERTIES & UVW) Py_DECREF (vUVWNP);
}
