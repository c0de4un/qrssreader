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

#ifndef QRSS_READER_LINK_HPP
#define QRSS_READER_LINK_HPP

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
// LINK
// ===========================================================

namespace rss
{

	/**
	  * Link - Link Element of RSS Channel & Item.
	  *
	  * @brief
	  * Link - Url.
	  *
	  * @version 1.0
	  * @since 21.07.2019
	  * @authors Denis Z. (code4un@yandex.ru)
	**/
	struct Link final : public Element
    {

		// -----------------------------------------------------------

		// ===========================================================
		// CONSTANTS
		// ===========================================================

		/** QUrl **/
		const QUrl mUrl;

		// ===========================================================
		// CONSTRUCTOR
		// ===========================================================

		/**
		  * Link constructor.
		  *
		  * @param pUrl - QString with Url.
		  * @param pType - Element-Type, default is Link.
		  * @throws - no exceptions.
		**/
		explicit Link( const QString & pUrl, const Element::Type pType = Element::Type::LINK ) noexcept;

		// ===========================================================
		// DESTRUCTOR
		// ===========================================================

		/**
		  * Link destructor.
		  *
		  * @throws - no exceptions.
		**/
		virtual ~Link( ) noexcept final;

		// -----------------------------------------------------------

	private:

		// -----------------------------------------------------------

		// ===========================================================
		// DELETED CONSTRUCTORS & OPERATORS
		// ===========================================================

		/** @deleted Link const copy constructor. **/
		Link( const Link & ) noexcept = delete;

		/** @deleted Link copy-assignment operator. **/
		Link & operator=( const Link & ) noexcept = delete;

		/** @deleted Link move constructor. **/
		Link( Link && ) noexcept = delete;

		/** @deleted Link move assignment operator. **/
		Link & operator=( Link && ) noexcept = delete;

		// -----------------------------------------------------------

    }; // rss::Link

} // rss

// -----------------------------------------------------------

#endif // !QRSS_READER_LINK_HPP
