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
#ifndef QRSS_READER_INTEGER_HPP
#include "Integer.hpp"
#endif // !QRSS_READER_INTEGER_HPP

// ===========================================================
// Integer
// ===========================================================

namespace rss
{

	// -----------------------------------------------------------

	// ===========================================================
	// CONSTRUCTORS
	// ===========================================================

	/**
	  * Integer constructor.
	  *
	  * @param strValue - QString with int-value. Value not modified.
	  * @param parentElement - Parent-Element.
	  * @param pType - Element-Type (ttl, skipHours, skipDays).
	  * @throws - no exceptions.
	**/
	Integer::Integer( const QString & strValue, Element *const parentElement, const Element::Type pType ) noexcept
		: Element ( pType, parentElement ),
		  mValue( strValue.toInt( ) )
	{ }

	/**
	  * Integer constructor.
	  *
	  * @param pValue - int-value, value copied.
	  * @param parentElement - Parent-Element.
	  * @param pType - Element-Type (ttl, skipHours, skipDays).
	  * @throws - no exceptions.
	**/
	Integer::Integer( const int pValue, Element *const parentElement, const Element::Type pType ) noexcept
		: Element ( pType, parentElement ),
		  mValue( pValue )
	{ }

	// ===========================================================
	// DESTRUCTOR
	// ===========================================================

	/**
	  * Integer destructor.
	  *
	  * @throws - no exceptions.
	**/
	Integer::~Integer( ) noexcept = default;

	// -----------------------------------------------------------

} // rss

// -----------------------------------------------------------
