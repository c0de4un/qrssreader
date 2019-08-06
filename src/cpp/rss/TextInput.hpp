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

#ifndef QRSS_READER_TEXT_INPUT_HPP
#define QRSS_READER_TEXT_INPUT_HPP

// -----------------------------------------------------------

// ===========================================================
// INCLUDES
// ===========================================================

// Include rss::Element
#ifndef QRSS_READER_ELEMENT_HPP
#include "Element.hpp"
#endif // !QRSS_READER_ELEMENT_HPP

// Include QUrl
#ifndef QURL_H
#include <QUrl>
#endif // !QURL_H

// ===========================================================
// TextInput
// ===========================================================

namespace rss
{

	// -----------------------------------------------------------

	/**
	  * TextInput - <textInput> Element class.
	  *
	  * @version 1.0
	  * @since 21.07.2019
	  * @authors Denis Z. (code4un@yandex.ru)
	**/
	struct TextInput final : public rss::Element
	{

		// -----------------------------------------------------------

		// ===========================================================
		// CONSTANTS
		// ===========================================================

		/** Title **/
		const QString *const mTitle;

		/** Description **/
		const QString *const mDescription;

		/** Name **/
		const QString *const mName;

		/** Link **/
		const QUrl *const mLink;

		// ===========================================================
		// CONSTRUCTOR
		// ===========================================================

		/**
		  * TextInput constructor.
		  *
		  * @param pElement - Parent-Element.
		  * @param pTitle - Title.
		  * @param pDescription - Description.
		  * @param pName - Name.
		  * @param pLink - Link.
		  * @throws - no exceptions.
		**/
		explicit TextInput( rss::Element *const pElement, const QString & pTitle, const QString & pDescription, const QString & pName, const QString & pLink ) noexcept;

		// ===========================================================
		// DESTRUCTOR
		// ===========================================================

		/**
		  * TextInput destructor.
		  *
		  * @throws - no exceptions.
		**/
		virtual ~TextInput( ) noexcept final;

		// -----------------------------------------------------------

	private:

		// -----------------------------------------------------------

		// ===========================================================
		// DELETED CONSTRUCTORS & OPERATORS
		// ===========================================================

		/** @deleted TextInput const copy constructor. **/
		TextInput( const TextInput & ) noexcept = delete;

		/** @deleted TextInput copy-assignment operator. **/
		TextInput & operator=( const TextInput & ) noexcept = delete;

		/** @deleted TextInput move constructor. **/
		TextInput( TextInput && ) noexcept = delete;

		/** @deleted TextInput move assignment operator. **/
		TextInput & operator=( TextInput && ) noexcept = delete;

		// -----------------------------------------------------------

	}; // rss::TextInput

	// -----------------------------------------------------------

} // rss

// -----------------------------------------------------------

#endif // !QRSS_READER_TEXT_INPUT_HPP
