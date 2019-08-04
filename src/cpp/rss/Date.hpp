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

#ifndef QRSS_READER_DATE_HPP
#define QRSS_READER_DATE_HPP

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
// Date
// ===========================================================

namespace rss
{

	// -----------------------------------------------------------

	/**
	  * Date - Date Element of RSS Channel & Item.
	  *
	  * @brief
	  * Date - used by pubDate & lastBuildDate Elements.
	  * Data stored with QString for easier cast (transformation).
	  *
	  * @version 1.0
	  * @since 21.07.2019
	  * @authors Denis Z. (code4un@yandex.ru)
	**/
	struct Date final : public Element
	{

		// -----------------------------------------------------------

		// ===========================================================
		// CONSTANTS
		// ===========================================================

		/** Date in QString format. **/
		const QString mStringDate;

		// ===========================================================
		// CONSTRUCTOR
		// ===========================================================

		/**
		  * Date constructor.
		  *
		  * @param pDate - QString with Date.
		  * @param parentElement - Parent-Element.
		  * @param pType - Element-Type, default is PubDate.
		  * @throws - no exceptions.
		**/
		explicit Date( const QString & pDate, Element *const parentElement, const Element::Type pType = Element::Type::PUB_DATE ) noexcept;

		// ===========================================================
		// DESTRUCTOR
		// ===========================================================

		/**
		  * Date destructor.
		  *
		  * @throws - no exceptions.
		**/
		virtual ~Date( ) noexcept final;

		// -----------------------------------------------------------

	private:

		// -----------------------------------------------------------

		// ===========================================================
		// DELETED CONSTRUCTORS & OPERATORS
		// ===========================================================

		/** @deleted Date const copy constructor. **/
		Date( const Date & ) noexcept = delete;

		/** @deleted Date copy-assignment operator. **/
		Date & operator=( const Date & ) noexcept = delete;

		/** @deleted Date move constructor. **/
		Date( Date && ) noexcept = delete;

		/** @deleted Date move assignment operator. **/
		Date & operator=( Date && ) noexcept = delete;

		// -----------------------------------------------------------

	}; // rss::Date

	// -----------------------------------------------------------

	// ===========================================================
	// Aliases
	// ===========================================================

	/** PubDate. **/
	using PubDate = Date;

	/** LastBuildDate. **/
	using LastBuildDate = Date;

	// -----------------------------------------------------------

} // rss

// -----------------------------------------------------------

#endif // !QRSS_READER_DATE_HPP
