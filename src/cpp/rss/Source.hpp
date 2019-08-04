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

#ifndef QRSS_READER_SOURCE_HPP
#define QRSS_READER_SOURCE_HPP

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

// Include QUrl
#ifndef QURL_H
#include <QUrl>
#endif // !QURL_H

// ===========================================================
// Source
// ===========================================================

namespace rss
{

	// -----------------------------------------------------------

	/**
	  * Source - Source Element of RSS Channel & Item.
	  *
	  * @brief
	  * Source - contains text & url. Same type as <category> element.
	  *
	  * @version 1.0
	  * @since 21.07.2019
	  * @authors Denis Z. (code4un@yandex.ru)
	**/
	struct Source final : public Element
	{

		// -----------------------------------------------------------

		// ===========================================================
		// CONSTANTS
		// ===========================================================

		/** Url. **/
		const QUrl url;

		/** Text. **/
		const QString text;

		// ===========================================================
		// CONSTRUCTOR
		// ===========================================================

		/**
		  * Source constructor.
		  *
		  * @param pUrl - Url.
		  * @param pText - Text.
		  * @param parentElement - Parent-Element.
		  * @param elementType - Element-Type.
		  * @throws - no exceptions.
		**/
		explicit Source( const QString & pUrl, const QString & pText, Element *const parentElement, const ElementType elementType = ElementType::SOURCE ) noexcept;

		// ===========================================================
		// DESTRUCTOR
		// ===========================================================

		/**
		  * Source destructor.
		  *
		  * @throws - no exceptions.
		**/
		virtual ~Source( ) noexcept final;

		// -----------------------------------------------------------

	private:

		// -----------------------------------------------------------

		// ===========================================================
		// DELETED CONSTRUCTORS & OPERATORS
		// ===========================================================

		/** @deleted Source const copy constructor. **/
		Source( const Source & ) noexcept = delete;

		/** @deleted Source copy-assignment operator. **/
		Source & operator=( const Source & ) noexcept = delete;

		/** @deleted Source move constructor. **/
		Source( Source && ) noexcept = delete;

		/** @deleted Source move assignment operator. **/
		Source & operator=( Source && ) noexcept = delete;

		// -----------------------------------------------------------

	}; // rss::Source

	// -----------------------------------------------------------

	// ===========================================================
	// ALIASES
	// ===========================================================

	/** Category. **/
	using Category = Source;

	// -----------------------------------------------------------

} // rss

// -----------------------------------------------------------

#endif // !QRSS_READER_SOURCE_HPP
