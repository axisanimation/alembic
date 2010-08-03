//-*****************************************************************************
//
// Copyright (c) 2009-2010, Industrial Light & Magic,
//   a division of Lucasfilm Entertainment Company Ltd.
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
// *       Neither the name of Industrial Light & Magic nor the names of
// its contributors may be used to endorse or promote products derived
// from this software without specific prior written permission.
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

#include <Alembic/Asset/Body/IAssetBody.h>

namespace Alembic {
namespace Asset {

//-*****************************************************************************
IAssetBody::IAssetBody( const std::string &fname )
  : m_fileName( fname )
{
    // Open the file
    m_file.open( m_fileName );

    // Get the comments off.
    m_comments = m_file.comment();

    // Open the root group, and then the "Alembic" group right after that
    H5G root( m_file, "/", Alembic::HDF5::kOpen );

    // init parent body
    parentInit( root, "Alembic" );
}

//-*****************************************************************************
//-*****************************************************************************
IAssetBody::~IAssetBody() throw()
{
    // These could throw.
    if ( m_file.valid() )
    {
        try
        {
            this->close();
            assert( !m_file.valid() );
        }
        catch ( std::exception &exc )
        {
            std::cerr << "ERROR: IAssetBody::~IAssetBody() "
                      << "Exception: " << exc.what() << std::endl;
        }
        catch ( ... )
        {
            std::cerr << "ERROR: IAssetBody::~IAssetBody() "
                      << "UNKNOWN EXCEPTION" << std::endl;
        }
    }
}

//-*****************************************************************************
void IAssetBody::close()
{
    if ( m_file.valid() )
    {
        m_file.close();
    }
    IParentBody::close();
}

} // End namespace Asset
} // End namespace Alembic
