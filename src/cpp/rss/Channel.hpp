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

#ifndef QRSS_READER_CHANNEL_HPP
#define QRSS_READER_CHANNEL_HPP

// -----------------------------------------------------------

// ===========================================================
// INCLUDES
// ===========================================================

// Include QString
#ifndef QSTRING_H
#include <QString>
#endif // !QSTRING_H

// Include QMap
#ifndef QMAP_H
#include <QMap>
#endif // !QMAP_H

// Include QVector
#ifndef QVECTOR_H
#include <QVector>
#endif // !QVECTOR_H

// Include QMutex & QMutexLocker
#ifndef QMUTEX_H
#include <QMutex>
#endif // !QMUTEX_H

// Include rss::Item
#ifndef QRSS_READER_ITEM_HPP
#include "Item.hpp"
#endif // !QRSS_READER_ITEM_HPP

// ===========================================================
// Channel
// ===========================================================

namespace rss
{

	// -----------------------------------------------------------

	/**
	  * Channel - class to store & manage RSS Channel data.
	  *
	  * @brief
	  * RSS Feed can have only one <channel>. Channel contains Elements (image, title,
	  * description, etc ) & Items (Publications/News).
	  * <br>
	  * (?) This class designed to be thread-safe, in case if data read (extracted) while
	  * updating.
	  * <br>
	  * (?) Designed to support RSS 2.0
	  *
	  * @version 1.0
	  * @since 21.07.2019
	  * @authors Denis Z. (code4un@yandex.ru)
	**/
	class Channel final
	{

	public:

		// -----------------------------------------------------------

		// ===========================================================
		// CONFIG
		// ===========================================================

		/** Alias for Item pointer. **/
		using item_ptr_t = Item*;

		/** Alias for Element pointer. **/
		using element_ptr_t = Element*;

		// -----------------------------------------------------------

	private:

		// -----------------------------------------------------------

		// ===========================================================
		// FIELDS
		// ===========================================================

		/** Elements. **/
		QMap<ElementType, element_ptr_t> mElements;

		/** Elements Thread-Lock. **/
		QMutex mElementsMutex;

		/** Items. **/
		QVector<item_ptr_t> mItems;

		/** Items Thread-Lock. **/
		QMutex mItemsMutex;

		// ===========================================================
		// DELETED CONSTRUCTORS & OPERATORS
		// ===========================================================

		/** @deleted Channel const copy constructor. **/
		Channel( const Channel & ) noexcept = delete;

		/** @deleted Channel copy-assignment operator. **/
		Channel & operator=( const Channel & ) noexcept = delete;

		/** @deleted Channel move constructor. **/
		Channel( Channel && ) noexcept = delete;

		/** @deleted Channel move assignment operator. **/
		Channel & operator=( Channel && ) noexcept = delete;

		// ===========================================================
		// METHODS
		// ===========================================================

		/**
		  * Searches for a Item with the specific GUID.
		  *
		  * @threadsafe - must be called only when thread-lock is active.
		  * @param pGUID - Item's GUID.
		  * @return - Item, or null.
		  * @throws - no exceptions.
		**/
		item_ptr_t searchItemByGUID( const QString & pGUID ) const noexcept;

		// -----------------------------------------------------------

	public:

		// -----------------------------------------------------------

		// ===========================================================
		// CONSTRUCTOR
		// ===========================================================

		/**
		  * Channel constructor.
		  *
		  * @throws - no exceptions.
		**/
		explicit Channel( ) noexcept;

		// ===========================================================
		// DESTRUCTOR
		// ===========================================================

		/**
		  * Channel destructor.
		  *
		  * @throws - no exceptions.
		**/
		~Channel( ) noexcept;

		// ===========================================================
		// GETTERS & SETTERS
		// ===========================================================

		/**
		  * Searches for a Element.
		  *
		  * @thread_safety - thread-lock used.
		  * @param pType - Element-Type.
		  * @return - Element, or null.
		  * @throws - no exceptions.
		**/
		element_ptr_t getElement( const ElementType pType ) noexcept;

		/**
		  * Returns 'true' if RSS Channel's Item with the given GUID found.
		  *
		  * @threadsafe - thread-lock used.
		  * @param pGUID - GUID.
		  * @return - 'true' if Item found, 'false' if not.
		  * @throws - no exceptions.
		**/
		bool hasItem( const QString & pGUID ) noexcept;

		/**
		  * Sets (add, insert) Element.
		  *
		  * @thread_safety - thread-lock used.
		  * @param pElement - Element.
		  * @return - 'true' if set, 'false' if same Element already set.
		  * @throws - no exceptions.
		**/
		bool setElement( element_ptr_t pElement ) noexcept;

		/**
		  * Returns 'true' if Channel have Element with a provided Element-Type.
		  *
		  * @threadsafe - thread-lock used.
		  * @param pType - Element-Type.
		  * @throws - no exceptions.
		**/
		bool hasElement( const ElementType pType ) noexcept;

		/**
		  * Search Item of Channel using GUID.
		  *
		  * (?) It is better to use GUID, in case if Items collection updated during request.
		  *
		  * @threadsafe - thread-lock used.
		  * @param pGUID - GUID of a Item.
		  * @return - Item, or null.
		  * @throws - no exceptions.
		**/
		item_ptr_t getItemByGUID( const QString & pGUID ) noexcept;

		/**
		  * Converts QString to Element-Type.
		  *
		  * @thread_safety - not required.
		  * @returns - Element-Type.
		  * @throws - no exceptions.
		**/
		static ElementType getElementTypeFromString( const QString pType ) noexcept;

		/**
		  * Converts int to Element-Type.
		  *
		  * @thread_safety - not required.
		  * @returns - Element-Type.
		  * @throws - no exceptions.
		**/
		static ElementType getElementTypeFromInt( const int pType ) noexcept;

		// ===========================================================
		// METHODS
		// ===========================================================

		/**
		  * Adds Item to Channel.
		  *
		  * (?) Used only by RSS parser.
		  *
		  * @threadsafe - thread-lock used.
		  * @param pItem - Item.
		  * @return - 'true' if added, 'false' if Item with the same GUID already added.</br>
		  * Use #hasItem(const QString&) method.
		  * @throws - no exceptions.
		**/
		bool addItem( item_ptr_t pItem ) noexcept;

		/**
		  * Removes all Items (delete).
		  *
		  * (?) Used only by destructor & RSS Parser (when data outdated).
		  *
		  * @threadsafe - thread-lock used.
		  * @throws - no exceptions.
		**/
		void releaseItems( ) noexcept;

		/**
		  * Removes all Elements (delete).
		  *
		  * (?) Used only by destructor & RSS Parser (when data outdated).
		  *
		  * @threadsafe - thread-lock used.
		  * @throws - no exceptions.
		**/
		void releaseElements( ) noexcept;

		// -----------------------------------------------------------

	}; // rss::Channel

	// -----------------------------------------------------------

} // rss

// -----------------------------------------------------------

#endif // !QRSS_READER_CHANNEL_HPP
