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
#ifndef QRSS_READER_ITEM_HPP
#include "Item.hpp"
#endif // !QRSS_READER_ITEM_HPP

// Include rss::Date
#ifndef QRSS_READER_DATE_HPP
#include "Date.hpp" // PubDate
#endif // !QRSS_READER_DATE_HPP

// ===========================================================
// Item
// ===========================================================

namespace rss
{

	// -----------------------------------------------------------

	// ===========================================================
	// CONSTRUCTOR
	// ===========================================================

	/**
	  * Item constructor.
	  *
	  * @param parentElement - Parent-Element.
	  * @throws - no exceptions.
	**/
	Item::Item( Element *const parentElement ) noexcept
		: Element( ElementType::CHANNEL_ITEM, parentElement )
	{ }

	// ===========================================================
	// DESTRUCTOR
	// ===========================================================

	/**
	  * Item destructor.
	  *
	  * @throws - no exceptions.
	**/
	Item::~Item( ) noexcept
	{

		// Release Elements
		releaseElements( );

	}

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
	Item::element_ptr_t Item::getElement( const ElementType pType ) const noexcept
	{

		// Search Element.
		auto elementPos_ = elements.find( pType );

		// Cancel, if Element not found.
		if ( elementPos_ == elements.cend( ) )
			return( element_ptr_t( nullptr ) );

		// Return Element.
		return( elementPos_.value( ) );

	} /// Item::getElement

	/**
	  * Sets Item's Element.
	  *
	  * @threadsafe - not thread-safe.
	  * @param pElement - Element to add.
	  * @return - 'true' if set, 'false' if not (Element with the same type already set), or Item can't store this type.
	  * @throws - no exceptions.
	**/
	bool Item::setElement( Item::element_ptr_t pElement ) noexcept
	{

		// Search Element.
		auto elementPos_ = elements.find( pElement->type );

#if defined( QT_DEBUG ) || defined( DEBUG ) // DEBUG
		// Element Position Assertion.
		assert( elementPos_ == elements.cend( ) && "Item::setElement - Element already added !" );
#else // !DEBUG
		// Cancel, if Element found.
		if ( elementPos_ != elements.cend( ) )
			return( false );
#endif // DEBUG

		// Add Element.
		elements.insert( pElement->type, pElement );

		// Return TRUE
		return( true );

	} /// Item::setElement

	/**
	  * Checks if Item have newer date.
	  *
	  * @threadsafe - not thread-safe.
	  * @param newItem - New-Item.
	  * @param oldItem - Old-Item.
	  * @returns - 'true' if new Item has newer date, or date-Elements not found.
	  * @throws - no exceptions.
	**/
	bool Item::isNewer( const rss::Item *const newItem, const rss::Item *const oldItem ) noexcept
	{

		// Get new-PubDate Element.
		const rss::PubDate *const pubDate_1( static_cast<rss::PubDate*>( newItem->getElement( rss::ElementType::PUB_DATE ) ) );

		// Get old-PubDate Element.
		const rss::PubDate *const pubDate_2( static_cast<rss::PubDate*>( oldItem->getElement( rss::ElementType::PUB_DATE ) ) );

		// Return TRUE, if pubDate Element not found.
		if ( pubDate_1 == nullptr && pubDate_2 == nullptr )
			return( true );

		// Compare Dates.
		return( rss::PubDate::isNewer( pubDate_1, pubDate_2 ) );

	} /// Item::isNewer

	// ===========================================================
	// METHODS
	// ===========================================================

	/**
	  * Deletes all Item's Elements.
	  *
	  * @threadsafe - not thread-safe.
	  * @throws - no exceptions.
	**/
	void Item::releaseElements( ) noexcept
	{

		// Elements map Iterator.
		auto elementsIter_ = elements.begin( );

		// Elements map end-Iterator.
		const auto elementsEndIter_ = elements.cend( );

		// Element
		element_ptr_t elementPtr( nullptr );

		// Delete Elements
		while( elementsIter_ != elementsEndIter_ )
		{

			// Element
			elementPtr = elementsIter_.value( );

#if defined( QT_DEBUG ) || defined( DEBUG ) // DEBUG
			// Null-Check
			Q_ASSERT( elementPtr != nullptr );
#endif // DEBUG

			// Delete Element
			delete elementPtr;

			// Next Element
			elementsIter_++;

		} // Delete Elements

		// Clear Elements collection (container).
		elements.clear( );

	} /// Item::releaseElements

	/**
	  * Returns 'true' if this Element don't have sub-Elements.
	  *
	  * @threadsafe - not thread-safe.
	  * @return - 'true' if Empty, 'false' if have sub-Elements.
	  * @throws - no exceptions.
	**/
	bool Item::empty( ) const noexcept
	{ return( elements.empty( ) ); }

	/**
	  * Count sub-Elements.
	  *
	  * @threadsafe - not thread-safe.
	  * @return - number of sub-Elements.
	  * @throws - no exceptions.
	**/
	int Item::count( ) const noexcept
	{ return( elements.size( ) ); }

	// -----------------------------------------------------------

} // rss

// -----------------------------------------------------------
