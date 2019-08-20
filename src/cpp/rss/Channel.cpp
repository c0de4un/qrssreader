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
#ifndef QRSS_READER_CHANNEL_HPP
#include "Channel.hpp"
#endif // !QRSS_READER_CHANNEL_HPP

// Include rss::Text
#ifndef QRSS_READER_TEXT_HPP
#include "Text.hpp"
#endif // !QRSS_READER_TEXT_HPP

#if defined( QT_DEBUG ) || defined( DEBUG ) // DEBUG

// Include QDebug
#ifndef QDEBUG_H
#include <qdebug.h>
#endif // !QDEBUG_H

#endif // DEBUG

// ===========================================================
// Channel
// ===========================================================

namespace rss
{

	// -----------------------------------------------------------

	// ===========================================================
	// CONSTRUCTOR
	// ===========================================================

	/**
	  * Channel constructor.
	  *
	  * @param rssVersion - RSS-Version.
	  * @throws - no exceptions.
	**/
	Channel::Channel( const QString & rssVersion ) noexcept
		: Element( ElementType::CHANNEL, nullptr ),
		  mRSSVersion( rssVersion ),
		  mElements( ),
		  mElementsMutex( ),
		  mItems( ),
		  mItemsMutex( )
	{

#if defined( QT_DEBUG ) || defined( DEBUG ) // DEBUG
		// Debug
		qDebug( ) << "Channel#" << id << "::constructor";
#endif // DEBUG

	}

	// ===========================================================
	// DESTRUCTOR
	// ===========================================================

	/**
	  * Channel destructor.
	  *
	  * @throws - no exceptions.
	**/
	Channel::~Channel( ) noexcept
	{

#if defined( QT_DEBUG ) || defined( DEBUG ) // DEBUG
		// Debug
		qDebug( ) << "Channel#" << QString::number( id ) << "::destructor";
#endif // DEBUG

		// Release Elements
		releaseElements( );

		// Release Items
		releaseItems( );

	}

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
	Channel::element_ptr_t Channel::getElement( const ElementType pType ) noexcept
	{

#if defined( QT_DEBUG ) || defined( DEBUG ) // DEBUG
		// Debug
		qDebug( ) << "Channel#" << QString::number( id ) << "::getElement";
#endif // DEBUG

		// Thread-Lock
		QMutexLocker threadLock( &mElementsMutex );

		// Search Element
		const auto elementPos = mElements.find( pType );

		// Cancel, if Element not found.
		if ( elementPos == mElements.cend( ) )
			return( element_ptr_t( nullptr ) );

		// Return Element
		return( elementPos.value( ) );

	} /// Channel::getElement

	/**
	  * Count Items.
	  *
	  * @threadsafe - thread-lock used.
	  * @return - Items coun.
	  * @throws - no exceptions.
	**/
	int Channel::countItems( ) const noexcept
	{

#if defined( QT_DEBUG ) || defined( DEBUG ) // DEBUG
		// Debug
		qDebug( ) << "Channel#" << QString::number( id ) << "::countItems";
#endif // DEBUG

		// Thread-Lock
		QMutexLocker uLock( &mItemsMutex );

		// Count Items
		return( mItems.size( ) );

	} /// Channel::countItems

	/**
	  * Searches for a Item.
	  *
	  * @threadsafe - thread-lock used.
	  * @param pIndex - Item index.
	  * @returns - Item, or null.
	  * @throws - no exceptions.
	**/
	Channel::item_ptr_t Channel::getItem( const int pIndex ) const noexcept
	{

#if defined( QT_DEBUG ) || defined( DEBUG ) // DEBUG
		// Debug
		qDebug( ) << "Channel#" << QString::number( id ) << "::getItem";
#endif // DEBUG

		// Thread-Lock.
		QMutexLocker uLock( &mItemsMutex );

		// Cancel, if out-of-range.
		if ( pIndex < 0 || pIndex > mItems.size( ) - 1 )
			return( nullptr );

		// Return Item.
		return( mItems.at( pIndex ) );

	} /// Channel::getItem

	/**
	  * Returns 'true' if RSS Channel's Item with the given GUID found.
	  *
	  * @threadsafe - thread-lock used.
	  * @param pGUID - GUID.
	  * @return - 'true' if Item found, 'false' if not.
	  * @throws - no exceptions.
	**/
	bool Channel::hasItemGUID( const QString & pGUID ) noexcept
	{

#if defined( QT_DEBUG ) || defined( DEBUG ) // DEBUG
		// Debug
		qDebug( ) << "Channel#" << QString::number( id ) << "::hasItemGUID";
#endif // DEBUG

		// Search Item
		return( getItemByGUID( pGUID ) != nullptr );

	}

	/**
	  * Returns 'true' if Channel have Element with a provided Element-Type.
	  *
	  * @threadsafe - thread-lock used.
	  * @param pType - Element-Type.
	  * @throws - no exceptions.
	**/
	bool Channel::hasElement( const ElementType pType ) noexcept
	{

#if defined( QT_DEBUG ) || defined( DEBUG ) // DEBUG
		// Debug
		qDebug( ) << "Channel#" << QString::number( id ) << "::hasElement";
#endif // DEBUG

		// Search Element.
		return( getElement( pType ) != nullptr );

	} /// Channel::hasElement

	/**
	  * Sets (add, insert) Element.
	  *
	  * @thread_safety - thread-lock used.
	  * @param pElement - Element.
	  * @param pReplace - 'true' to replace already set Element. Used for merging (moveing, updating).
	  * @return - 'true' if set, 'false' if same Element already set.
	  * @throws - no exceptions.
	**/
	bool Channel::setElement( Channel::element_ptr_t pElement, const bool pReplace ) noexcept
	{

#if defined( QT_DEBUG ) || defined( DEBUG ) // DEBUG
		// Debug
		qDebug( ) << "Channel#" << QString::number( id ) << "::setElement";
#endif // DEBUG

		// Thread-Lock.
		QMutexLocker uniqueLock( &mElementsMutex );

		// Search Element.
		const auto elementPos_ = mElements.find( pElement->type );

#if defined( QT_DEBUG ) || defined( DEBUG ) // DEBUG
		// Check Element Repeat.
		if ( !pReplace )
			assert( elementPos_ == mElements.cend( ) && "Channel::setElement - Channel already have such Element ! RSS data corrupt ?" );
#else // !DEBUG
		// Cancel, if Element already stored.
		if ( !pReplace && elementPos_ != mElements.cend( ) )
			return( false );
#endif // DEBUG

		// Delete previous Element.
		if ( elementPos_ != mElements.cend( ) )
			delete elementPos_.value( );

		// Set Element.
		mElements[pElement->type] = pElement;

		// Remove Element.
		//mElements.erase( elementPos_ );

		// Add new Element.
		//mElements.insert( pElement->type, pElement );

		// Return TRUE
		return( true );

	} /// Channel::setElement

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
	Channel::item_ptr_t Channel::getItemByGUID( const QString & pGUID ) noexcept
	{

#if defined( QT_DEBUG ) || defined( DEBUG ) // DEBUG
		// Debug
		qDebug( ) << "Channel#" << QString::number( id ) << "::getItemGUID";
#endif // DEBUG

		// Thread-Lock.
		QMutexLocker uLock( &mItemsMutex );

		// Search & Return Item.
		return( searchItemByGUID( pGUID ) );

	}

	/**
	  * Converts QString to Element-Type.
	  *
	  * @thread_safety - not required.
	  * @returns - Element-Type.
	  * @throws - no exceptions.
	**/
	ElementType Channel::getElementTypeFromString( const QString pType ) noexcept
	{

		// link
		if ( pType == "link" )
			return( ElementType::LINK );
		else if ( pType == "description" )
			return( ElementType::DESCRITION );
		else if ( pType == "title" )
			return( ElementType::TITLE );
		else if ( pType == "ttl" )
			return( ElementType::TTL );
		else if ( pType == "pubDate" )
			return( ElementType::PUB_DATE );
		else if ( pType == "docs" )
			return( ElementType::DOCS );
		else if ( pType == "guid" )
			return( ElementType::GUID );
		else if ( pType == "image" )
			return( ElementType::IMAGE );
		else if ( pType == "category" )
			return( ElementType::CATEGORY );
		else if ( pType == "language" )
			return( ElementType::LANGUAGE );
		else if ( pType == "copyright" )
			return( ElementType::COPYRIGHT );
		else if ( pType == "managingEditor" )
			return( ElementType::MANAGING_EDITOR );
		else if ( pType == "lastBuildDate" )
			return( ElementType::LAST_BUILD_DATE );
		else if ( pType == "webMaster" )
			return( ElementType::WEB_MASTER );
		else if ( pType == "textInput" )
			return( ElementType::TEXT_INPUT );
		else if ( pType == "skipHours" )
			return( ElementType::SKIP_HOURS );
		else if ( pType == "skipDays" )
			return( ElementType::SKIP_DAYS );
		else if ( pType == "generator" )
			return( ElementType::GENERATOR );
		else if ( pType == "cloud" )
			return( ElementType::CLOUD );
		else if ( pType == "enclosure" )
			return( ElementType::ENCLOSURE );
		else if ( pType == "author" )
			return( ElementType::AUTHOR );
		else if ( pType == "comments" )
			return( ElementType::COMMENTS );
		else if ( pType == "source" )
			return( ElementType::SOURCE );

#if defined( QT_DEBUG ) || defined( DEBUG ) // DEBUG
		// Assertion
		static_assert( "", "Channel::getElementTypeFromString" );
#endif // DEBUG

		// Default
		return( ElementType::DESCRITION );

	} /// Channel::getElementTypeFromString

	/**
	  * Converts int to Element-Type.
	  *
	  * @thread_safety - not required.
	  * @returns - Element-Type.
	  * @throws - no exceptions.
	**/
	ElementType Channel::getElementTypeFromInt( const int pType ) noexcept
	{ return( static_cast<ElementType>( pType ) ); }

	// ===========================================================
	// METHODS
	// ===========================================================

	/**
	  * Returns 'true' if this Element don't have sub-Elements.
	  *
	  * @threadsafe - not thread-safe.
	  * @return - 'true' if Empty, 'false' if have sub-Elements.
	  * @throws - no exceptions.
	**/
	bool Channel::empty( ) const noexcept
	{ return( mElements.empty( ) || mItems.empty( ) ); }

	/**
	  * Merge (move Elements from source to a destination Channel).
	  *
	  * (?) All replaced Elements automatically deleted.
	  *
	  * @threadsafe - thread-lock used.
	  * @param srcChannel - Channel to move Elements from.
	  * @param dstChannel - Channel to move Elements to.
	  * @throws - no exceptions.
	**/
	void Channel::merge( rss::Channel *const srcChannel, rss::Channel *const dstChannel ) noexcept
	{

#if defined( QT_DEBUG ) || defined( DEBUG ) // DEBUG
		// Debug
		qDebug( ) << "Channel#" << dstChannel->id << "::merge";
#endif // DEBUG

		// Move Elements
		for( rss::Element * srcElement : srcChannel->mElements )
		{

			// Set Element (override/replace if required).
			if ( !dstChannel->setElement( srcElement, true ) )
			{// Element wasn't added.

				// Delete Element.
				delete srcElement;

			} /// Set Element

		} /// Move Elements

		// Clear Elements collection to move.
		srcChannel->mElements.clear( );

		// Move Items
		for( rss::Item * srcItem : srcChannel->mItems )
		{

			// Move Item
			if ( !dstChannel->addItem( srcItem ) )
			{// Item not added.

				// Delete Item.
				delete srcItem;

			} /// Move Item

		} // Move Items.

		// Clear Items to Move.
		srcChannel->mItems.clear( );

	} /// Channel::merge

	/**
	  * Count sub-Elements.
	  *
	  * @threadsafe - not thread-safe.
	  * @return - number of sub-Elements.
	  * @throws - no exceptions.
	**/
	int Channel::count( ) const noexcept
	{ return( mItems.size( ) ); }

	/**
	  * Searches for a Item with the specific GUID.
	  *
	  * @threadsafe - must be called only when thread-lock is active.
	  * @param pGUID - Item's GUID.
	  * @return - Item, or null.
	  * @throws - no exceptions.
	**/
	Channel::item_ptr_t Channel::searchItemByGUID( const QString & pGUID ) const noexcept
	{

#if defined( QT_DEBUG ) || defined( DEBUG ) // DEBUG
		// Debug
		qDebug( ) << "Channel#" << QString::number( id ) << "::searchItemByGUID";
#endif // DEBUG

		// Search Item
		for( item_ptr_t item_ : mItems )
		{

			// Comparison
			if ( static_cast<rss::GUID*>( item_->getElement( ElementType::GUID ) )->mData == pGUID )
				return( item_ );

		} /// Search Item

		// Return null.
		return( item_ptr_t( nullptr ) );

	} /// Channel::searchItemByGUID

	/**
	  * Adds Item to Channel.
	  *
	  * (?) Used only by RSS parser.
	  *
	  * @threadsafe - thread-lock used.
	  * @param pItem - Item.
	  * @return - 'true' if added, 'false' if Item with the same GUID already added.</br>
	  * Use #hasItemGUID(const QString&) method.
	  * @throws - no exceptions.
	**/
	bool Channel::addItem( Channel::item_ptr_t pItem ) noexcept
	{

#if defined( QT_DEBUG ) || defined( DEBUG ) // DEBUG
		// Debug
		qDebug( ) << "Channel#" << QString::number( id ) << "::addItem";
#endif // DEBUG

		// Get GUID
		const rss::GUID *const guid_ptr( static_cast<rss::GUID*>( pItem->getElement( ElementType::GUID ) ) );

		// Get Item.
		rss::Item *const prevItem_( guid_ptr != nullptr ? getItemByGUID( guid_ptr->mData ) : nullptr );

		// GUID-Check.
		if ( prevItem_ != nullptr && !rss::Item::isNewer( pItem, prevItem_ ) )
			return( false );

		// Thread-Lock
		QMutexLocker threadLock( &mItemsMutex );

		// Add Item.
		mItems.push_back( pItem );

		// Return TRUE
		return( true );

	} /// Channel::addItem

	/**
	  * Removes all Items (delete).
	  *
	  * (?) Used only by destructor & RSS Parser (when data outdated).
	  *
	  * @threadsafe - thread-lock used.
	  * @throws - no exceptions.
	**/
	void Channel::releaseItems( ) noexcept
	{

#if defined( QT_DEBUG ) || defined( DEBUG ) // DEBUG
		// Debug
		qDebug( ) << "Channel#" << QString::number( id ) << "::releaseItems";
#endif // DEBUG

		// Thread-Lock
		QMutexLocker threadLock( &mItemsMutex );

		// Cancel, if Items collection (container) is empty.
		if ( mItems.empty( ) )
			return;

		// Items map Iterator.
		auto itemsIter_ = mItems.begin( );

		// Items map End-Iterator.
		const auto itemsEndIter_ = mItems.cend( );

		// Item
		item_ptr_t item_ptr( nullptr );

		// Remove Items
		while( itemsIter_ != itemsEndIter_ )
		{

			// Get Item.
			item_ptr = *itemsIter_;

#if defined( QT_DEBUG ) || defined( DEBUG ) // DEBUG

			// Null-Check
			assert( item_ptr != nullptr && "Channel::releaseItems - Item is null !" );

#endif // DEBUG

			// Delete Item
			delete item_ptr;

			// Next Item
			itemsIter_++;

		} /// Remove Items

		// Clear Items Collection (container).
		mItems.clear( );

	} ///Channel::releaseItems

	/**
	  * Removes all Elements (delete).
	  *
	  * (?) Used only by destructor & RSS Parser (when data outdated).
	  *
	  * @threadsafe - thread-lock used.
	  * @throws - no exceptions.
	**/
	void Channel::releaseElements( ) noexcept
	{

#if defined( QT_DEBUG ) || defined( DEBUG ) // DEBUG
		// Debug
		qDebug( ) << "Channel#" << QString::number( id ) << "::releaseElements";
#endif // DEBUG

		// Thread-Lock
		QMutexLocker threadLock( &mElementsMutex );

		// Cancel, if Elements collection (container) is empty.
		if ( mElements.empty( ) )
			return;

		// Elements map Iterator.
		auto elementsIter_ = mElements.begin( );

		// Elements map End-Iterator.
		const auto elementsEndIter_ = mElements.cend( );

		// Element
		element_ptr_t element_ptr( nullptr );

		// Remove Elements
		while( elementsIter_ != elementsEndIter_ )
		{

			// Get Item.
			element_ptr = elementsIter_.value( );

#if defined( QT_DEBUG ) || defined( DEBUG ) // DEBUG

			// Null-Check
			assert( element_ptr != nullptr && "Channel::releaseElements - Element is null !" );

			// Delete Item
			delete element_ptr;

#endif // DEBUG

			// Next Item
			elementsIter_++;

		} /// Remove Elements

		// Clear Elements Collection (container).
		mElements.clear( );

	} ///Channel::releaseElements

	// -----------------------------------------------------------

} // rss

// -----------------------------------------------------------
