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
#ifndef QRSS_READER_IMAGE_HPP
#include "Image.hpp"
#endif // !QRSS_READER_IMAGE_HPP

// ===========================================================
// Image
// ===========================================================

namespace rss
{

	// -----------------------------------------------------------

	// ===========================================================
	// CONSTRUCTOR
	// ===========================================================

	/**
	  * Image constructor.
	  *
	  * @throws - no exceptions.
	**/
	Image::Image( ) noexcept
		: Element( ElementType::IMAGE ),
		  elements( )
	{ }

	// ===========================================================
	// DESTRUCTOR
	// ===========================================================

	/**
	  * Image destructor.
	  *
	  * @throws - no exceptions.
	**/
	Image::~Image( ) noexcept
	{

		// Release Elements.
		releaseElements( );

	}

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
	Image::element_ptr_t Image::getElement( const ElementType elementType ) const noexcept
	{

		// Search Element.
		const auto elementPos_ = elements.find( elementType );

		// Cancel, if Element not found.
		if ( elementPos_ == elements.cend( ) )
			return( element_ptr_t( nullptr ) );

		// Return Element.
		return( elementPos_.value( ) );

	} /// Image::getElement

	/**
	  * Sets (add, insert) Element.
	  *
	  * @threadsafe - not thread-safe.
	  * @param pElement - Element.
	  * @returns - 'true' if Element set, 'false' if not (other Element of the same type set, or invalid Element-Type).
	  * @throws - no exceptions.
	**/
	bool Image::setElement( Image::element_ptr_t pElement ) noexcept
	{

		// Search Element.
		const auto elementPos_ = elements.find( pElement->mType );

#if defined( QT_DEBUG ) || defined( DEBUG ) // DEBUG
		// Check Repeat.
		assert( elementPos_ == elements.cend( ) && "Image::setElement - Element already set !" );
#else
		// Cancel, if Element already set.
		if ( elementPos_ != elements.cend( ) )
			return( false );
#endif // DEBUG

		// Insert Element.
		elements.insert( pElement->mType, pElement );

		// Return TRUE
		return( true );

	} /// Image::setElement

	// ===========================================================
	// METHODS
	// ===========================================================

	/**
	  * Deletes Elements.
	  *
	  * @threadsafe - not thread-safe.
	  * @throws - no exceptions.
	**/
	void Image::releaseElements( ) noexcept
	{

		// Elements map iterator.
		auto elementsIter_ = elements.begin( );

		// Elements map end-iterator.
		const auto elementsEndIter_ = elements.cend( );

		// Delete Elements
		while( elementsIter_ != elementsEndIter_ )
		{

			// Delete Element.
			delete elementsIter_.value( );

			// Next Element
			elementsIter_++;

		} /// Delete Elements

		// Clear Elements map.
		elements.clear( );

	} /// Image::releaseElements

	// -----------------------------------------------------------

} // rss

// -----------------------------------------------------------
