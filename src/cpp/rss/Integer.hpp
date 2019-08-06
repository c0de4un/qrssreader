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

#ifndef QRSS_READER_INTEGER_HPP
#define QRSS_READER_INTEGER_HPP

// -----------------------------------------------------------

// ===========================================================
// INCLUDES
// ===========================================================

// Include rss::Element
#ifndef QRSS_READER_ELEMENT_HPP
#include "Element.hpp"
#endif // !QRSS_READER_ELEMENT_HPP

// Include QString
#ifndef QSTRING_H
#include <QString>
#endif // !QSTRING_H

// ===========================================================
// Integer
// ===========================================================

namespace rss
{

	// -----------------------------------------------------------

	/**
	  * Integer - RSS Channel Element with integer value.
	  *
	  * @brief
	  * Integer RSS Element used for ttl, skipHours, skipDays.
	**/
	struct Integer final : public Element
	{

		// -----------------------------------------------------------

		// ===========================================================
		// CONSTANTS
		// ===========================================================

		/** Int-value. **/
		const int mValue;

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
		explicit Integer( const QString & strValue, Element *const parentElement, const Element::Type pType = Element::Type::TTL ) noexcept;

		/**
		  * Integer constructor.
		  *
		  * @param pValue - int-value, value copied.
		  * parentElement
		  * @param pType - Element-Type (ttl, skipHours, skipDays).
		  * @throws - no exceptions.
		**/
		explicit Integer( const int pValue, Element *const parentElement, const Element::Type pType = Element::Type::TTL ) noexcept;

		// ===========================================================
		// DESTRUCTOR
		// ===========================================================

		/**
		  * Integer destructor.
		  *
		  * @throws - no exceptions.
		**/
		virtual ~Integer( ) noexcept final;

		// -----------------------------------------------------------

	private:

		// -----------------------------------------------------------

		// ===========================================================
		// DELETED CONSTRUCTORS & OPERATORS
		// ===========================================================

		/** @deleted Integer const copy constructor. **/
		Integer( const Integer & ) noexcept = delete;

		/** @deleted Integer copy-assignment operator. **/
		Integer & operator=( const Integer & ) noexcept = delete;

		/** @deleted Integer move constructor. **/
		Integer( Integer && ) noexcept = delete;

		/** @deleted Integer move assignment operator. **/
		Integer & operator=( Integer && ) noexcept = delete;

		// -----------------------------------------------------------

	}; // rss::Integer

	// -----------------------------------------------------------

	// ===========================================================
	// Aliases
	// ===========================================================

	/** TTL **/
	using TTL = Integer;

	/** Skip Hours **/
	using SkipHours = Integer;

	/** Skip Days. **/
	using SkipDays = Integer;

	// -----------------------------------------------------------

} // rss

#define QRSS_READER_INTEGER_DECL

// -----------------------------------------------------------

#endif // !QRSS_READER_INTEGER_HPP
