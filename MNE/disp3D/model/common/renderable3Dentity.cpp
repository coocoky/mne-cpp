//=============================================================================================================
/**
* @file     renderable3Dentity.cpp
* @author   Lorenz Esch <Lorenz.Esch@tu-ilmenau.de>;
*           Matti Hamalainen <msh@nmr.mgh.harvard.edu>
* @version  1.0
* @date     November, 2015
*
* @section  LICENSE
*
* Copyright (C) 2015, Lorenz Esch and Matti Hamalainen. All rights reserved.
*
* Redistribution and use in source and binary forms, with or without modification, are permitted provided that
* the following conditions are met:
*     * Redistributions of source code must retain the above copyright notice, this list of conditions and the
*       following disclaimer.
*     * Redistributions in binary form must reproduce the above copyright notice, this list of conditions and
*       the following disclaimer in the documentation and/or other materials provided with the distribution.
*     * Neither the name of MNE-CPP authors nor the names of its contributors may be used
*       to endorse or promote products derived from this software without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED
* WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
* PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
* INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
* PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
* HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
* NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
* POSSIBILITY OF SUCH DAMAGE.
*
*
* @brief    Renderable3DEntity class definition.
*
*/

//*************************************************************************************************************
//=============================================================================================================
// INCLUDES
//=============================================================================================================

#include "renderable3Dentity.h"
#include "shadermaterial.h"


//*************************************************************************************************************
//=============================================================================================================
// QT INCLUDES
//=============================================================================================================

#include <Qt3DCore/QTransform>


//*************************************************************************************************************
//=============================================================================================================
// Eigen INCLUDES
//=============================================================================================================


//*************************************************************************************************************
//=============================================================================================================
// QT INCLUDES
//=============================================================================================================

#include <QSharedPointer>

#include <Qt3DRender/QMaterial>
#include <Qt3DExtras/QPerVertexColorMaterial>
#include <Qt3DExtras/QPhongMaterial>
#include <Qt3DCore/QComponent>
#include <Qt3DRender/QEffect>
#include <Qt3DRender/QParameter>


//*************************************************************************************************************
//=============================================================================================================
// USED NAMESPACES
//=============================================================================================================

using namespace DISP3DLIB;
using namespace Eigen;
using namespace Qt3DCore;


//*************************************************************************************************************
//=============================================================================================================
// DEFINE MEMBER METHODS
//=============================================================================================================

Renderable3DEntity::Renderable3DEntity(Qt3DCore::QEntity* parent)
: Qt3DCore::QEntity(parent)
, m_pCustomMesh(new CustomMesh())
, m_pTransform(new Qt3DCore::QTransform())
, m_pMaterial(new ShaderMaterial())
, m_fAlpha(1.0f)
, m_fRotX(0.0f)
, m_fRotY(0.0f)
, m_fRotZ(0.0f)
, m_fTessInner(1.0f)
, m_fTessOuter(1.0f)
, m_fTriangleScale(1.0f)
{
    this->addComponent(m_pCustomMesh);
    this->addComponent(m_pTransform);
    this->addComponent(m_pMaterial);
}


//*************************************************************************************************************

Renderable3DEntity::Renderable3DEntity(const MatrixX3f& tMatVert, const MatrixX3f& tMatNorm, const MatrixX3i& tMatTris, Qt3DCore::QEntity* parent)
: Qt3DCore::QEntity(parent)
, m_pCustomMesh(new CustomMesh(tMatVert, tMatNorm, tMatTris))
, m_pTransform(new Qt3DCore::QTransform())
, m_pMaterial(new ShaderMaterial())
, m_fAlpha(1.0f)
, m_fRotX(0.0f)
, m_fRotY(0.0f)
, m_fRotZ(0.0f)
{
    this->addComponent(m_pCustomMesh);
    this->addComponent(m_pTransform);
    this->addComponent(m_pMaterial);
}


//*************************************************************************************************************

Renderable3DEntity::~Renderable3DEntity()
{
}


//*************************************************************************************************************

bool Renderable3DEntity::setVertColor(const QByteArray& tArrayColors)
{
    return m_pCustomMesh->setVertColor(tArrayColors);
}


//*************************************************************************************************************

bool Renderable3DEntity::setMeshData(const MatrixX3f& tMatVert,
                                     const MatrixX3f& tMatNorm,
                                     const MatrixXi& tMatTris,
                                     const QByteArray& tArrayColors,
                                     Qt3DRender::QGeometryRenderer::PrimitiveType primitiveType)
{
    if(!m_pCustomMesh.isNull()) {
        return m_pCustomMesh->setMeshData(tMatVert, tMatNorm, tMatTris, tArrayColors, primitiveType);
    }

    return false;
}


//*************************************************************************************************************

bool Renderable3DEntity::setTransform(QSharedPointer<Qt3DCore::QTransform> pTransform)
{
    if(!m_pTransform.isNull()) {
        m_pTransform = pTransform.data();
    }

    return true;
}


//*************************************************************************************************************

bool Renderable3DEntity::setMaterial(QSharedPointer<ShaderMaterial> pMaterial)
{
    if(!pMaterial.isNull()) {
        m_pMaterial = pMaterial.data();
    }

    return true;
}


//*************************************************************************************************************

bool Renderable3DEntity::setAlpha(float fAlpha)
{
    m_fAlpha = fAlpha;

    for(int i = 0; i < m_pMaterial->effect()->parameters().size(); i++) {
        if(m_pMaterial->effect()->parameters().at(i)->name() == "alpha") {
            m_pMaterial->effect()->parameters().at(i)->setValue(m_fAlpha);
            return true;
        }
    }

    return false;
}


//*************************************************************************************************************

bool Renderable3DEntity::setTessInner(float fTessInner)
{
    m_fTessInner = fTessInner;

    for(int i = 0; i < m_pMaterial->effect()->parameters().size(); i++) {
        if(m_pMaterial->effect()->parameters().at(i)->name() == "innerTess") {
            m_pMaterial->effect()->parameters().at(i)->setValue(m_fTessInner);
            return true;
        }
    }

    return false;
}


//*************************************************************************************************************

bool Renderable3DEntity::setTessOuter(float fTessOuter)
{
    m_fTessOuter = fTessOuter;

    for(int i = 0; i < m_pMaterial->effect()->parameters().size(); i++) {
        if(m_pMaterial->effect()->parameters().at(i)->name() == "outerTess") {
            m_pMaterial->effect()->parameters().at(i)->setValue(m_fTessOuter);
            return true;
        }
    }

    return false;
}


//*************************************************************************************************************

bool Renderable3DEntity::setTriangleScale(float fTriangleScale)
{
    m_fTriangleScale = fTriangleScale;

    for(int i = 0; i < m_pMaterial->effect()->parameters().size(); i++) {
        if(m_pMaterial->effect()->parameters().at(i)->name() == "triangleScale") {
            m_pMaterial->effect()->parameters().at(i)->setValue(m_fTriangleScale);
            return true;
        }
    }

    return false;
}


//*************************************************************************************************************

bool Renderable3DEntity::setShader(const QUrl& sShader)
{
    if(!m_pMaterial.isNull()) {
        m_pMaterial->setShader(sShader);

        return true;
    }

    return false;
}


//*************************************************************************************************************

float Renderable3DEntity::rotX() const
{
    return m_fRotX;
}


//*************************************************************************************************************

float Renderable3DEntity::rotY() const
{
    return m_fRotY;
}


//*************************************************************************************************************

float Renderable3DEntity::rotZ() const
{
    return m_fRotZ;
}


//*************************************************************************************************************

QVector3D Renderable3DEntity::position() const
{
    return m_position;
}


//*************************************************************************************************************

void Renderable3DEntity::setRotX(float rotX)
{
    if (m_fRotX == rotX)
        return;

    m_fRotX = rotX;
    emit rotXChanged(rotX);
    updateTransform();
}


//*************************************************************************************************************

void Renderable3DEntity::setRotY(float rotY)
{
    if (m_fRotY == rotY)
        return;

    m_fRotY = rotY;
    emit rotYChanged(rotY);
    updateTransform();
}


//*************************************************************************************************************

void Renderable3DEntity::setRotZ(float rotZ)
{
    if (m_fRotZ == rotZ)
        return;

    m_fRotZ = rotZ;
    emit rotZChanged(rotZ);
    updateTransform();
}


//*************************************************************************************************************

void Renderable3DEntity::setPosition(QVector3D position)
{
    if (m_position == position)
        return;

    m_position = position;
    emit positionChanged(position);
    updateTransform();
}


//*************************************************************************************************************

void Renderable3DEntity::updateTransform()
{
    QMatrix4x4 m;

    //Do the translation after rotating, otherwise rotation around the x,y,z axis would be screwed up
    m.translate(m_position);
    m.rotate(m_fRotX, QVector3D(1.0f, 0.0f, 0.0f));
    m.rotate(m_fRotY, QVector3D(0.0f, 1.0f, 0.0f));
    m.rotate(m_fRotZ, QVector3D(0.0f, 0.0f, 1.0f));

    m_pTransform->setMatrix(m);
}
