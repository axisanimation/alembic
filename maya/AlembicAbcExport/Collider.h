//-*****************************************************************************
//
// Copyright (c) 2009-2010,
//  Sony Pictures Imageworks Inc. and
//  Industrial Light & Magic, a division of Lucasfilm Entertainment Company Ltd.
//
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
// *       Redistributions of source code must retain the above copyright
// notice, this list of conditions and the following disclaimer.
// *       Redistributions in binary form must reproduce the above
// copyright notice, this list of conditions and the following disclaimer
// in the documentation and/or other materials provided with the
// distribution.
// *       Neither the name of Sony Pictures Imageworks, nor
// Industrial Light & Magic, nor the names of their contributors may be used
// to endorse or promote products derived from this software without specific
// prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
//-*****************************************************************************

#ifndef _AlembicAbcExport_Collider_h_
#define _AlembicAbcExport_Collider_h_

#include "Foundation.h"
#include "SimpleNull.h"

namespace AlembicAbcExport {

//-*****************************************************************************
class Collider : public BaseSimpleNull<Atg::OSimpleNull>
{
public:
    typedef Collider this_type;
    
    enum ShapeType
    {
        kSphere,
        kCube,
        kCylinder,
        kCone,
        kPlane,
        kUnknown
    };

    Collider( Exportable &parent,
              MDagPath &dagPath,
              MObject &nde,
              const std::string &nme,
              const Abc::TimeSamplingInfo &tinfo,
              ShapeType shapeType );

    virtual void close()
    {
        std::cout << "Closing collider: " << alembicParentObject().name()
                  << std::endl;
        BaseSimpleNull<Atg::OSimpleNull>::close();
    }

protected:
    virtual Abc::Box3d internalWriteSample( const Abc::Time &sampTime,
                                            const Abc::Box3d &childBounds );

    Abc::OCharProperty m_shapeTypeProp;

    ShapeType m_shapeType;

    // Rest bounds
    Abc::Box3d m_restBounds;
};

//-*****************************************************************************
Collider::ShapeType GetColliderShapeType( MDagPath &dp );

} // End namespace AlembicAbcExport

#endif
