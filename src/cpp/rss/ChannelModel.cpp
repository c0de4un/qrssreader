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
#ifndef Q_RSS_READER_CHANNEL_MODEL_HPP
#include "ChannelModel.hpp"
#endif // !Q_RSS_READER_CHANNEL_MODEL_HPP

#if defined( QT_DEFINED ) || defined( DEBUG ) // DEBUG

// Include QDebug
#ifndef QDEBUG_H
#include <qdebug.h>
#endif // !QDEBUG_H

#endif // DEBUG

// ===========================================================
// ChannelModel
// ===========================================================

namespace rss
{

	// -----------------------------------------------------------

	// ===========================================================
	// CONSTRUCTOR
	// ===========================================================

	/**
	  * ChannelModel constructor.
	  *
	  * @param qParent - Parent-Object. default is null.
	  * @throws - no exceptions.
	**/
	ChannelModel::ChannelModel( QObject *const qParent ) noexcept
		: QAbstractItemModel( qParent ),
		  mChannelsMutex( ),
		  mChannels( )
	{
	}

	// ===========================================================
	// DESTRUCTOR
	// ===========================================================

	/**
	  * ChannelModel destructor.
	  *
	  * @throws - no exceptions.
	**/
	ChannelModel::~ChannelModel( ) noexcept
	{

		// Delete Channels.
		clearChannels( );

	}

	// ===========================================================
	// METHODS
	// ===========================================================

	/**
	  * Search Channel using Model-private index.
	  *
	  * @threadsafe - thread-lock used.
	  * @param pIndex - Channel index.
	  * @returns - Channel, or null.
	  * @throws - no exceptions.
	**/
	ChannelModel::channel_ptr_t ChannelModel::getChannelByIndex( const int pIndex ) const noexcept
	{

		// Thread-Lock
		QMutexLocker uLock( &mChannelsMutex );

#if defined( QT_DEBUG ) || defined( DEBUG ) // DEBUG
		// Check range.
		assert( pIndex <= mChannels.size( ) && "ChannelModel::getChannelByIndex - index out of bounds !" );
#endif // DEBUG

		// Return Channel.
		return( mChannels.at( pIndex ) );

	} /// ChannelModel::getChannelByIndex

	/**
	  * Returns RSS Channel-class data (title, description, image, etc).
	  *
	  * @threadsafe - must be called only while thread-lock locked.
	  * @param pChannel - RSS Channel-class.
	  * @param pRole - Role (image, text, etc).
	  * @return - QVariant with data.
	  * @throws - no exceptions.
	**/
	QVariant ChannelModel::getChannelData( rss::Channel *const pChannel, const int pRole ) const noexcept
	{

		// Handle Data-Role
		switch( pRole )
		{

		// ==================== Required elements. ====================

		// [<title>] Title (DisplayRole)
		case rss::ChannelModel::Roles::RSS_TITLE_ELEMENT_ROLE:
		{

			// Get Title-Element of Channel.
			rss::Title *const titleElement( static_cast<rss::Title*>( pChannel->getElement( rss::ElementType::TITLE ) ) );

#if defined( QT_DEBUG ) || defined( DEBUG ) // DEBUG
			// Null-Check
			assert( titleElement != nullptr && "ChannelModel::getChannelData - RSS Channel must have Title-Element !" );
#else // !DEBUG
			// Return invalid QVariant
			if ( titleElement == nullptr )
				return( QVariant( ) );
#endif // DEBUG

			// Return Title
			return( QVariant( titleElement->mData ) );

		} /// Title [<title>]

		// Link [<link>]
		case rss::ChannelModel::Roles::RSS_LINK_ELEMENT_ROLE:
		{

			// Get Link-Element.
			rss::Link *const link( static_cast<rss::Link*>( pChannel->getElement( rss::ElementType::LINK ) ) );

#if defined( QT_DEBUG ) || defined( DEBUG ) // DEBUG
			// Null-Check
			assert( link != nullptr && "ChannelModel::getChannelData - RSS Channel must have Link-Element !" );
#else // !DEBUG
			// Return invalid QVariant
			if ( link == nullptr )
				return( QVariant( ) );
#endif // DEBUG

			// Return Link URL
			return( QVariant( link->mUrl ) );

		} /// Link [<link>]

		// Description [<description>]
		case rss::ChannelModel::Roles::RSS_DESCRIPTION_ELEMENT_ROLE:
		{

			// Get Link-Element.
			rss::Description *const desc( static_cast<rss::Description*>( pChannel->getElement( rss::ElementType::DESCRITION ) ) );

#if defined( QT_DEBUG ) || defined( DEBUG ) // DEBUG
			// Null-Check
			assert( desc != nullptr && "ChannelModel::getChannelData - RSS Channel must have Description-Element !" );
#else // !DEBUG
			// Return invalid QVariant
			if ( desc == nullptr )
				return( QVariant( ) );
#endif // DEBUG

			// Return Link URL
			return( QVariant( desc->mData ) );

		} /// Description [<description>]

		// ==================== Not required elements. ====================

		// Language [<language>]
		case rss::ChannelModel::Roles::RSS_LANGUAGE_ELEMENT_ROLE:
		{

			// Get Language-Element.
			rss::Language *const language( static_cast<rss::Language*>( pChannel->getElement( rss::ElementType::LANGUAGE ) ) );

			// Return invalid QVariant
			if ( language == nullptr )
				return( QVariant( ) );

			// Return Language-Element value.
			return( QVariant( language->mData ) );

		} /// Language [<language>]

		// [<image url="">] Image Url
		case rss::ChannelModel::Roles::RSS_IMAGE_ELEMENT_ROLE:
		{

			// Get Image-Element.
			rss::Image *const image( static_cast<rss::Image*>( pChannel->getElement( rss::ElementType::IMAGE ) ) );

			// Return invalid QVariant, if Image Element not found.
			if ( image == nullptr )
				return( QVariant( ) );

			// Return Image Url
			return( QVariant( image->url ) );

		} /// [<image url="">] Image Url

		// [<image><width /></image>] Image Width
		case rss::ChannelModel::Roles::RSS_IMAGE_WIDTH_ELEMENT_ROLE:
		{

			// Get Image-Element.
			rss::Image *const image( static_cast<rss::Image*>( pChannel->getElement( rss::ElementType::IMAGE ) ) );

			// Return invalid QVariant, if Image Element not found.
			if ( image == nullptr )
				return( QVariant( ) );

			// Return Image Width, or invalid QVariant if not set.
			return( image->width > 0 ? QVariant( image->width ) : QVariant( ) );

		} /// [<image><width /></image>] Image Width

		// [<image><height /></image>] Image Height
		case rss::ChannelModel::Roles::RSS_IMAGE_HEIGHT_ELEMENT_ROLE:
		{

			// Get Image-Element.
			rss::Image *const image( static_cast<rss::Image*>( pChannel->getElement( rss::ElementType::IMAGE ) ) );

			// Return invalid QVariant, if Image Element not found.
			if ( image == nullptr )
				return( QVariant( ) );

			// Return Image Height, or invalid QVariant if not set.
			return( image->height > 0 ? QVariant( image->height ) : QVariant( ) );

		} /// [<image><height /></image>] Image Height

		// [<image><link /></image>] Image Link
		case rss::ChannelModel::Roles::RSS_IMAGE_LINK_ELEMENT_ROLE:
		{

			// Get Image-Element.
			rss::Image *const image( static_cast<rss::Image*>( pChannel->getElement( rss::ElementType::IMAGE ) ) );

			// Return invalid QVariant, if Image Element not found.
			if ( image == nullptr || image->link == nullptr )
				return( QVariant( ) );

			// Return Image Link.
			return( QVariant( *image->link ) );

		} /// [<image><link /></image>] Image Link

		// [<image><description /></image>] Image Description
		case rss::ChannelModel::Roles::RSS_IMAGE_DESCRIPTION_ELEMENT_ROLE:
		{

			// Get Image-Element.
			rss::Image *const image( static_cast<rss::Image*>( pChannel->getElement( rss::ElementType::IMAGE ) ) );

			// Return invalid QVariant, if Image Element not found.
			if ( image == nullptr || image->description == nullptr )
				return( QVariant( ) );

			// Return Description.
			return( QVariant( *image->description ) );

		} /// [<image><description /></image>] Image Description

		// [<lastBuildDate>] Last Build Date.
		case rss::ChannelModel::Roles::RSS_LAST_BUILD_DATE_ELEMENT_ROLE:
		{

			// Get LastBuildDate Element.
			rss::LastBuildDate *const buildDate( static_cast<rss::LastBuildDate*>( pChannel->getElement( rss::ElementType::LAST_BUILD_DATE ) ) );

			// Return invalid QVariant if element not found.
			if ( buildDate == nullptr )
				return( QVariant( ) );

			// Return Channel Last Build Date as QString.
			return( QVariant( buildDate->mStringDate ) );

		} /// [<lastBuildDate>] Last Build Date.

		// []

		// Default
		default:
		{

			// Return invalid QVariant.
			return( QVariant( ) );

		} /// Default

		} /// Handle Data-Role

	} /// ChannelModel::getChannelData

	/**
	  * Returns RSS Channel's Item data (date, form, text).
	  *
	  * @threadsafe - must be called only while thread-lock locked.
	  * @param pChannel - RSS Channel-class.
	  * @param pRole - Role (image, text, etc).
	  * @return - QVariant with data.
	  * @throws - no exceptions.
	**/
	QVariant ChannelModel::getItemData( rss::Item *const pItem, const int pRole ) const noexcept
	{

		// Handle Item Data-Role.
		switch( pRole )
		{

		// ======================= Required Elements =======================

		// [<title>] Title
		case rss::ChannelModel::Roles::RSS_TITLE_ELEMENT_ROLE:
		{

			// Get Title Element.
			rss::Title *const title( static_cast<rss::Title*>( pItem->getElement( rss::ElementType::TITLE ) ) );

#if defined( QT_DEBUG ) || defined( DEBUG ) // DEBUG
			// Check Title.
			assert( title != nullptr && "ChannelModel::getItemData - Title Element not found !" );
#endif // DEBUG

			// Return invalid QVariant, if element not found.
			if ( title == nullptr )
				return( QVariant( ) );

			// Return Title.
			return( QVariant( title->mData ) );

		} /// [<title>] Title

		// [<description>] Description
		case rss::ChannelModel::Roles::RSS_DESCRIPTION_ELEMENT_ROLE:
		{

			// Get Description Element.
			rss::Description *const description( static_cast<rss::Description*>( pItem->getElement( rss::ElementType::DESCRITION ) ) );

#if defined( QT_DEBUG ) || defined( DEBUG ) // DEBUG
			// Check Description.
			assert( description != nullptr && "ChannelModel::getItemData - Description Element not found !" );
#endif // DEBUG

			// Return invalid QVariant, if element not found.
			if ( description == nullptr )
				return( QVariant( ) );

			// Return Description.
			return( QVariant( description->mData ) );

		} /// [<description>] Description

		// [<link>] Link
		case rss::ChannelModel::Roles::RSS_LINK_ELEMENT_ROLE:
		{

			// Get Link Element.
			rss::Link *const link( static_cast<rss::Link*>( pItem->getElement( rss::ElementType::LINK ) ) );

#if defined( QT_DEBUG ) || defined( DEBUG ) // DEBUG
			// Check Description.
			assert( link != nullptr && "ChannelModel::getItemData - Link Element not found !" );
#endif // DEBUG

			// Return invalid QVariant, if element not found.
			if ( link == nullptr )
				return( QVariant( ) );

			// Return Link.
			return( QVariant( link->mUrl ) );

		} /// [<link>] Link

		// ======================= Additional (Optional) Elements =======================

		// [<pubDate>] Publication Date.
		case rss::ChannelModel::Roles::RSS_PUB_DATE_ELEMENT_ROLE:
		{

			// Get PubDate Element.
			rss::PubDate *const pubDate( static_cast<rss::PubDate*>( pItem->getElement( rss::ElementType::PUB_DATE ) ) );

			// Reutrn invalid QVariant, if element not found.
			if ( pubDate == nullptr )
				return( QVariant( ) );

			// Return PubDate Element value.
			return( QVariant( pubDate->mStringDate ) );

		} /// [<pubDate>] Publication Date.

		// [<guid>] GUID
		case rss::ChannelModel::Roles::RSS_GUID_ELEMENT_ROLE:
		{

			// Get GUID Element.
			rss::GUID *const guid( static_cast<rss::GUID*>( pItem->getElement( rss::ElementType::GUID ) ) );

			// Reutrn invalid QVariant, if element not found.
			if ( guid == nullptr )
				return( QVariant( ) );

			// Return GUID Element value.
			return( QVariant( guid->mData ) );

		} /// [<guid>] GUID

		// Default
		default:
		{

			// Return invalid QVariant.
			return( QVariant( ) );

		} /// Default

		} /// Handle Item Data-Role.

	} /// ChannelModel::getItemData

	/**
	  * Deletes all Channels.
	  *
	  * @brief
	  * (?) Used by destructor or RSS-parser.
	  *
	  * @threadsafe - thread-lock used.
	  * @throws - no exceptions.
	**/
	void ChannelModel::clearChannels( ) noexcept
	{

		// Thread-Lock
		QMutexLocker uLock( &mChannelsMutex );

		// Delete Channels.
		for( channel_ptr_t channel : mChannels )
		{

			// Delete Channel.
			delete channel;

		} /// Delete Channels

		// Clear Channels Collection (container, map).
		mChannels.clear( );

	}

	// ===========================================================
	// OVERRIDE
	// ===========================================================

	/**
	  * Extract specific data using index.
	  *
	  * @threadsafe - thread-lock used.
	  * @param pIndex - Model-Index, contains inner-data (RSS Channel || Item).
	  * @param pRole - Model-Item Role, default is DisplayRole (Text).
	  * @return - QVariant with data.
	  * @throws - no exceptions.
	**/
	QVariant ChannelModel::data( const QModelIndex & pIndex, int pRole ) const
	{

#if defined( QT_DEBUG ) || defined( DEBUG ) // DEBUG
		// Check Model-Index.
		assert( pIndex.isValid( ) && "ChannelModel::data - invalid Model-Index ! Root can't provide any data to display." );
#else // !DEBUG
		// Cancel, if invalid Model-Index.
		if ( !pIndex.isValid( ) )
			return( QVariant( ) );
#endif // DEBUG

		// Get rss::Element
		Element *const elementPtr( static_cast<Element*>( pIndex.internalPointer( ) ) );

		// Cancel, if root.
		if ( elementPtr == nullptr )
			return( QVariant( ) );

		// Handle RSS Element-Type.
		switch( elementPtr->type )
		{

		// RSS Channel
		case ElementType::CHANNEL:
		{

			// Get Channel
			rss::Channel *const channel_ptr( static_cast<rss::Channel*>( elementPtr ) );

			// Return Channel data.
			return( getChannelData( channel_ptr, pRole ) );

		}

		// RSS Channel's Item
		case ElementType::ITEM:
		{

			// Get Item.
			rss::Item *const item_ptr( static_cast<rss::Item*>( elementPtr ) );

			// Return Item data.
			return( getItemData( item_ptr, pRole ) );

		}

		default: // default
		{

#if defined( QT_DEFINED ) || defined( DEBUG ) // DEBUG
			// ERROR-message
			qDebug( ) << "ChannelModel::data - invalid Element-Type !";
#endif // DEBUG

			// Return invalid QVariant.
			return( QVariant( ) );


		} /// default
		} /// Handle RSS Element-Type.

	} /// ChannelModel::data

	/**
	  * Search for Model-Index using col, row & parent-index.
	  *
	  * @threadsafe - thread-lock used.
	  * @param pRow - Row. Represents RSS Channel-class ID.
	  * @param pCol - Col, not used, alway 0.
	**/
	QModelIndex ChannelModel::index( int pRow, int pCol, const QModelIndex & parentIndex ) const
	{

		// Return root, if Model-Index is invalid.
		if ( pRow < 0 || pCol < 0 || !parentIndex.isValid( ) )
			return( createIndex( 0, 0, nullptr ) );

		// Thread-Lock
		QMutexLocker uLock( &mChannelsMutex );

		// Return Channel.
		if ( parentIndex.internalPointer( ) == nullptr )
		{ // Root

			// Channel.
			rss::Channel *const channel( getChannelByIndex( pRow ) );

			// Return Model-Index for a Channel.
			return( createIndex( pRow, pCol, channel ) );

		} /// Root
		else // sub-Element
		{

			// Get Element.
			rss::Element *const element( static_cast<rss::Element*>( parentIndex.internalPointer( ) ) );

			// Handle Element-Type.
			switch( element->type )
			{

			// Channel
			case rss::ElementType::CHANNEL:
			{

				// Get Channel from Model-Index.
				rss::Channel *const channel( static_cast<rss::Channel*>( parentIndex.internalPointer( ) ) );

				// Get Item.
				rss::Item *const item( static_cast<rss::Item*>( channel->getItem( pRow ) ) );

#if defined( QT_DEBUG ) || defined( DEBUG ) // DEBUG
				// Null-check.
				assert( item != nullptr && "ChannelModel::index - Item is null ! Check rowsCount method logic." );
#endif /// DEBUG

				// Return Model-Index for a Item.
				return( createIndex( 0, 0, item ) );

			} /// Channel

			// Channel Item
			case rss::ElementType::ITEM:
			{

				// Do not provide any Model-Indices for Item sub-Elements.
				return( QModelIndex( ) );


			} /// Channel Item

			// Default
			default:
				return( QModelIndex( ) ); // Return invalid-index.

			}

		} /// sub-Element.

	} /// ChannelModel::index

	/**
	  * Searches Model-Item Parent.
	  *
	  * @threadsafe - thread-lock used.
	  * @param pIndex - Model's Item Index.
	  * @return - Model-Index.
	  * @throws - no excepions.
	**/
	QModelIndex ChannelModel::parent( const QModelIndex & pIndex ) const
	{

		// Cancel, if root || invalid.
		if ( !pIndex.isValid( ) || pIndex.internalPointer( ) == nullptr )
			return( QModelIndex( ) );

		// Get Element.
		rss::Element *const element( static_cast<rss::Element*>( pIndex.internalPointer( ) ) );

#if defined( QT_DEBUG ) || defined( DEBUG ) // DEBUG
		// Null-check.
		assert( element != nullptr && "ChannelModel::parent - Element is null ! Check ChannelModel::index() method." );
#endif // DEBUG

		// Channel has no parent Model-Index.
		if ( element->type == ElementType::CHANNEL )
			return( QModelIndex( ) );

		// Cancel, if not Channel Item-Element.
		if ( element->type != ElementType::ITEM )
			return( QModelIndex( ) );

		// Get Item's Channel.
		rss::Channel *const channel( static_cast<rss::Channel*>( element->parent ) );

		// Generate Model-Index for Channel.
		return( createIndex( 1, 0, channel ) );

	} /// ChannelModel::parent

	/**
	  * Count Rows of the given Model-Item (RSS Channel || Item).
	  *
	  * @threadsafe - thread-lock used.
	  * @param parentIndex - Item to investigate.
	  * @returns - Rows Count.
	  * @throws - no exceptions.
	**/
	int ChannelModel::rowCount( const QModelIndex & parentIndex ) const
	{

		// Invalid Model-Index.
		if ( !parentIndex.isValid( ) )
			return( -1 );

		// root Model-Index.
		if ( parentIndex.row( ) == 0 && parentIndex.internalPointer( ) == nullptr )
			return( mChannels.size( ) );

		// Get Element.
		rss::Element *const element( static_cast<rss::Element*>( parentIndex.internalPointer( ) ) );

#if defined( QT_DEBUG ) || defined( DEBUG ) // DEBUG
		// Check Element.
		assert( element != nullptr && "ChannelModel::rowCount - Element is null ! None root-Index must have Element !" );
#endif // DEBUG

		// Return Element size.
		return( element->count( ) );

	} /// ChannelModel::rowCount

	/**
	  * Returns 'true' if the given Model-Index has sub-Items.
	  *
	  * @threadsafe - thread-lock used.
	  * @param pIndex - Model-Index.
	  * @return - 'true' if contains sub-Items, 'false' if not.
	  * @throws - no exceptions.
	**/
	bool ChannelModel::hasChildren( const QModelIndex & pIndex ) const
	{

		// Invalid Model-Index == root.
		if ( !pIndex.isValid( ) || pIndex.internalPointer( ) == nullptr )
			return( mChannels.size( ) );

		// Element.
		rss::Element *const element( static_cast<rss::Element*>( pIndex.internalPointer( ) ) );

		// Channel
		if ( element->type == rss::ElementType::CHANNEL )
		{

			// Return Channel Items-Count.
			return( element->count( ) );

		} /// Channel

		// Items & their sub-Element no counted.
		return( 0 );

	} /// ChannelModel::hasChildren

	/**
	  * Returns data to display as View-Header.
	  *
	  * @threadsafe - thread-lock used.
	  * @param pSection - section.
	  * @param pOrientation - View-Orientation.
	  * @param pRole - Data Role (Text, Image, etc).
	  * @return - QVariant with View's data.
	  * @throws - no exceptions.
	**/
	//QVariant ChannelModel::headerData( int pSection, Qt::Orientation pOrientation, int pRole ) const
	//{

		// Return RSS
		//return( QVariant( QString( "RSS" ) ) );

	//} /// ChannelModel::headerData

	// -----------------------------------------------------------

} // rss

// -----------------------------------------------------------
