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

#ifndef QRSS_READER_IMAGE_HPP
#define QRSS_READER_IMAGE_HPP

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

// Include QMap
#ifndef QMAP_H
#include <QMap>
#endif // !QMAP_H

// ===========================================================
// Image
// ===========================================================

namespace rss
{

	/**
	  * Image - struct to store Image RSS-Element data.
	  *
	  * @brief
	  * Image - sub-Element of a Channel, has url, title, description, link, width & height sub-Elements.
	  *
	  * @version 1.0
	  * @since 21.07.2019
	  * @authors Denis Z. (code4un@yandex.ru)
	**/
	struct Image final : public Element
	{

		// -----------------------------------------------------------

		// ===========================================================
		// CONFIG
		// ===========================================================

		/** Alias for Element pointer. **/
		using element_ptr_t = Element*;

		// ===========================================================
		// CONSTRUCTOR
		// ===========================================================

		/**
		  * Image constructor.
		  *
		  * @throws - no exceptions.
		**/
		explicit Image( ) noexcept;

		// ===========================================================
		// DESTRUCTOR
		// ===========================================================

		/**
		  * Image destructor.
		  *
		  * @throws - no exceptions.
		**/
		virtual ~Image( ) noexcept final;

		// ===========================================================
		// GETTERS & SETTERS
		// ===========================================================

		/**
		  * Searches for a Element matching the given Element-Type.
		  *
		  * @threadsafe - not thread-safe.
		  * @param elementType - Element-Type.
		  * @return - Element, or null.
		  * @throws - no exceptions.
		**/
		element_ptr_t getElement( const ElementType elementType ) const noexcept;

		/**
		  * Sets (add, insert) Element.
		  *
		  * @threadsafe - not thread-safe.
		  * @param pElement - Element.
		  * @returns - 'true' if Element set, 'false' if not (other Element of the same type set, or invalid Element-Type).
		  * @throws - no exceptions.
		**/
		bool setElement( element_ptr_t pElement ) noexcept;

		// -----------------------------------------------------------

	private:

		// -----------------------------------------------------------

		// ===========================================================
		// FIELDS
		// ===========================================================

		/** Elements. **/
		QMap<ElementType, element_ptr_t> elements;

		// ===========================================================
		// DELETED CONSTRUCTORS & OPERATORS
		// ===========================================================

		/** @deleted Image const copy constructor. **/
		Image( const Image & ) noexcept = delete;

		/** @deleted Image copy-assignment operator. **/
		Image & operator=( const Image & ) noexcept = delete;

		/** @deleted Image move constructor. **/
		Image( Image && ) noexcept = delete;

		/** @deleted Image move assignment operator. **/
		Image & operator=( Image && ) noexcept = delete;

		// ===========================================================
		// METHODS
		// ===========================================================

		/**
		  * Deletes Elements.
		  *
		  * @threadsafe - not thread-safe.
		  * @throws - no exceptions.
		**/
		void releaseElements( ) noexcept;

		// -----------------------------------------------------------

	}; // rss::Image

} // rss

// -----------------------------------------------------------

#endif // !QRSS_READER_IMAGE_HPP
