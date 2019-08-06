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

#ifndef QRSS_READER_TEXT_HPP
#define QRSS_READER_TEXT_HPP

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
// TEXT
// ===========================================================

namespace rss
{

	// -----------------------------------------------------------

	/**
	  * Text - RSS Text Element.
	  *
	  * @brief
	  * Text - alias for description, author, etc.
	  *
	  * @version 1.0
	  * @since 21.07.2019
	  * @authors Denis Z. (code4un@yandex.ru)
	**/
	struct Text final : public Element
	{

		// -----------------------------------------------------------

		// ===========================================================
		// CONSTANTS
		// ===========================================================

		/** Text. **/
		const QString mData;

		// ===========================================================
		// CONSTRUCTOR
		// ===========================================================

		/**
		  * Text constructor.
		  *
		  * @param pData - QString with Text-Data. (!) Value moved.
		  * @param parentElement - Parent-Element.
		  * @param pType - Emelent-Type (Description).
		  * @throws - no exceptions.
		**/
		explicit Text( const QString & pData, Element *const parentElement, const Element::Type pType = Element::Type::DESCRITION ) noexcept;

		// ===========================================================
		// DESTRUCTOR
		// ===========================================================

		/**
		  * Text destructor.
		  *
		  * @throws - no exceptions.
		**/
		virtual ~Text( ) noexcept final;

		// -----------------------------------------------------------

	private:

		// -----------------------------------------------------------

		// ===========================================================
		// DELETED CONSTRUCTORS & OPERATORS
		// ===========================================================

		/** @deleted Text const copy constructor. **/
		Text( const Text & ) noexcept = delete;

		/** @deleted Text copy-assignment operator. **/
		Text & operator=( const Text & ) noexcept = delete;

		/** @deleted Text move constructor. **/
		Text( Text && ) noexcept = delete;

		/** @deleted Text move assignment operator. **/
		Text & operator=( Text && ) noexcept = delete;

		// -----------------------------------------------------------

	}; // rss::Text

	// -----------------------------------------------------------

	// ===========================================================
	// Aliases
	// ===========================================================

	/** Description. **/
	using Description = Text;

	/** Web-Master. **/
	using WebMaster = Text;

	/** Managing-Editor. **/
	using ManagingEditor = Text;

	/** Title. **/
	using Title = Text;

	/** GUID **/
	using GUID = Text;

	/**  Language. **/
	using Language = Text;

	// -----------------------------------------------------------

} // rss

#define QRSS_READER_TEXT_DECL

// -----------------------------------------------------------


#endif // !QRSS_READER_TEXT_HPP
