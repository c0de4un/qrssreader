/**
* Copyright © Denis Z. (code4un@yandex.ru) All rights reserved.
* Authors: Denis Z. (code4un@yandex.ru)
* All rights reserved.
* Language: C++
* License: see LICENSE
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS ``AS
* IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
* THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
* PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL COPYRIGHT HOLDERS OR CONTRIBUTORS
* BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
* CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
* SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
* INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
* CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
* ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
* POSSIBILITY OF SUCH DAMAGE.
**/

// -----------------------------------------------------------

// ===========================================================
// INCLUDES
// ===========================================================

// HEADER
#ifndef QRSS_READER_ELEMENT_HPP
#include "Element.hpp"
#endif // !QRSS_READER_ELEMENT_HPP

// ===========================================================
// ELEMENT
// ===========================================================

namespace rss
{

    // -----------------------------------------------------------

    // ===========================================================
    // CONSTRUCTOR
    // ===========================================================

    /**
      * Element constructor.
      *
      * @param pType - Element-Type.
      * @throws - no exceptions.
    **/
    Element::Element( const Element::Type pType ) noexcept
        : mType( pType )
    {
    }

    // ===========================================================
    // DESTRUCTOR
    // ===========================================================

    /**
      * Element destructor.
      *
      * @throws - no exceptions.
    **/
    Element::~Element( ) noexcept = default;

    // ===========================================================
    // METHODS
    // ===========================================================

    /**
      * Wrapper-mehod to cast Element to specific type.
      *
      * @thread_safety - not required.
      * @param pElement - Element to cast.
      * @return - T.
      * @throws - no exceptions.
    **/
    template <typename T>
    T* Element::castTo( Element *const pElement ) noexcept
    { return( static_cast<T*>( pElement ) ); }

    // -----------------------------------------------------------

} // rss

// -----------------------------------------------------------
