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

#ifndef QRSS_READER_ITEM_HPP
#define QRSS_READER_ITEM_HPP

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

// Include QMap
#ifndef QMAP_H
#include <QMap>
#endif // !QMAP_H

// ===========================================================
// Item
// ===========================================================

namespace rss
{

	/**
	  * Item - struct to store & manage RSS Channel's Item-Element data.
	  *
	  * @brief
	  * Item contains sub-Elements, like <description>, <enclosure>, <guid>, etc.
	  *
	  * @version 1.0
	  * @since 21.07.2019
	  * @authors Denis Z. (code4un@yandex.ru)
	**/
	struct Item final : public Element
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
		  * Item constructor.
		  *
		  * @param parentElement - Parent-Element.
		  * @throws - no exceptions.
		**/
		explicit Item( Element *const parentElement ) noexcept;

		// ===========================================================
		// DESTRUCTOR
		// ===========================================================

		/**
		  * Item destructor.
		  *
		  * @throws - no exceptions.
		**/
		virtual ~Item( ) noexcept final;

		// ===========================================================
		// GETTERS & SETTERS
		// ===========================================================

		/**
		  * Searches for a Element of Item.<br/>
		  *
		  * (?) To Convert QString || int to Element-Type, use Channel-class
		  * or Element::Type directly.<br/>
		  *
		  * @threadsafe - not thread-safe.
		  * @param pType - Element-Type.
		  * @return - Element, or null.
		  * @throws - no exceptions.
		**/
		element_ptr_t getElement( const ElementType pType ) const noexcept;

		/**
		  * Sets Item's Element.
		  *
		  * @threadsafe - not thread-safe.
		  * @param pElement - Element to add.
		  * @return - 'true' if set, 'false' if not (Element with the same type already set), or Item can't store this type.
		  * @throws - no exceptions.
		**/
		bool setElement( element_ptr_t pElement ) noexcept;

		// ===========================================================
		// METHODS
		// ===========================================================

		/**
		  * Deletes all Item's Elements.
		  *
		  * @threadsafe - not thread-safe.
		  * @throws - no exceptions.
		**/
		void releaseElements( ) noexcept;

		/**
		  * Returns 'true' if this Element don't have sub-Elements.
		  *
		  * @threadsafe - not thread-safe.
		  * @return - 'true' if Empty, 'false' if have sub-Elements.
		  * @throws - no exceptions.
		**/
		virtual bool empty( ) const noexcept final;

		/**
		  * Count sub-Elements.
		  *
		  * @threadsafe - not thread-safe.
		  * @return - number of sub-Elements.
		  * @throws - no exceptions.
		**/
		virtual int count( ) const noexcept final;

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

		/** @deleted Item const copy constructor. **/
		Item( const Item & ) noexcept = delete;

		/** @deleted Item copy-assignment operator. **/
		Item & operator=( const Item & ) noexcept = delete;

		/** @deleted Item move constructor. **/
		Item( Item && ) noexcept = delete;

		/** @deleted Item move assignment operator. **/
		Item & operator=( Item && ) noexcept = delete;

		// -----------------------------------------------------------

	}; // rss::Item

} // rss

// -----------------------------------------------------------

#endif // !QRSS_READER_ITEM_HPP
