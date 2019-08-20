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

// Include rss::SAXRSSHandler
#ifndef QRSS_READER_SAX_RSS_HANDLER_HPP
#include "../utils/SAXRSSHandler.hpp"
#endif // !QRSS_READER_SAX_RSS_HANDLER_HPP

#if defined( QT_DEBUG ) || defined( DEBUG ) // DEBUG

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
	  * Returns Channel, associated with a specific Row.
	  *
	  * @threadsafe - thread-lock used.
	  * @param pRow - Row.
	  * @returns - Channel instance, or null.
	  * @throw - no exceptions.
	**/
	rss::Channel * ChannelModel::getChannelByRow( const int pRow ) const noexcept
	{

#if defined( QT_DEBUG ) // DEBUG
		// Debug-message
		qDebug( ) << "ChannelModel::getChannelByRow - Row=" << QString::number( pRow );

		// Check Range.
		if ( pRow < 0 || pRow >= mChannels.size( ) )
		{

			// Error-message.
			qDebug( ) << "ChannelModel::getChannelByRow - Invalid Range: " << QString::number( pRow );

			// Return null.
			return( nullptr );

		} /// Check Range
#else // !DEBUG
		// Check Range.
		if ( pRow < 0 || pRow >= mChannels.size( ) )
			return( nullptr );
#endif // DEBUG

		// Thread-lock.
		QMutexLocker uLock( &mChannelsMutex );

		// Return Channel instance.
		return( mChannels.at( pRow ) );

	} /// ChannelModel::getChannelByRow

	/**
	  * Returns public-index of a Channel.
	  *
	  * @threadsafe - thread-lock used.
	  * @param pChannel - Channel.
	  * @throws - no exceptions.
	**/
	int ChannelModel::getChannelIndex( const rss::Channel *const pChannel ) const noexcept
	{

		// Thread-Lock
		QMutexLocker uLock( &mChannelsMutex );

		// Channels Count.
		const auto channelsCount_( mChannels.size( ) );

		// Channel.
		rss::Channel * channel_( nullptr );

		// Search Channel
		for( int i = 0; i < channelsCount_; i++ )
		{

			// Get Channel.
			channel_ = mChannels.at( i );

			// Compare.
			if ( channel_ == pChannel || channel_->id == pChannel->id )
				return( true );

		} /// Search Channel

		// Return -1 to use as Root.
		return( -1 );

	}

	/**
	  * Searches added Channel insatnce using Link Element as Key.
	  *
	  * (?) Used by RSS-parser to check if Channel with the same
	  * Link already added. Allows to update existing Channel,
	  * instead of dublication.
	  *
	  * @threadsafe - thread-lock used.
	  * @param pLink - Link Element Value (Url).
	  * @returns - Channel if found, null if not.
	  * @throws - no exceptions.
	**/
	ChannelModel::channel_ptr_t ChannelModel::getChannelByLink( const QUrl & pLink ) const noexcept
	{

		// Thread-Lock.
		QMutexLocker uLock( &mChannelsMutex );

		// Link Element.
		rss::Link * link_( nullptr );

		// Search Channel
		for( channel_ptr_t channel_ : mChannels )
		{

			// Get Channel Link Element.
			link_ = static_cast<rss::Link*>( channel_->getElement( rss::ElementType::LINK ) );

#if defined( QT_DEBUG ) || defined( DEBUG ) // DEBUG
			// Link - required ELement of every Channel.
			assert( link_ != nullptr && "ChannelModel::getChannelByLink - Link Element not found !" );
#else // !DEBUG
			// Cancel, if Link not found.
			if ( link_ == nullptr )
				continue;
#endif // DEBUG

			// Compare Links.
			if ( link_->mUrl == pLink )
				return( channel_ );

		} /// Search Channel

		// Return null.
		return( channel_ptr_t( nullptr ) );

	} /// ChannelModel::getChannelByLink

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

#if defined( QT_DEBUG ) || defined( DEBUG ) // DEBUG
			// Debug
			qDebug( ) << "ChannelModel::getChannelData - Image Url=" << *image->url;
#endif // DEBUG

			// Return Image Url
			return( *image->url );

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
			return( image->width > 0 ? image->width : QVariant( ) );

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
			return( image->height > 0 ? image->height : QVariant( ) );

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
	  * Called when Channel-class data created or updated.
	  *
	  * @threadsafe - thread-lock used.
	  * @param pChannel - Channel instance.
	  * @param pLock - 'true' to use thread-lock.
	  * @throws - no exceptions.
	**/
	rss::Channel * ChannelModel::addChannel( rss::Channel *const pChannel, const bool pLock ) noexcept
	{

		// Get Link Element.
		rss::Link *const newLink_( static_cast<rss::Link*>( pChannel->getElement( rss::ElementType::LINK ) ) );

		// Search Channel using Link.
		if ( newLink_ != nullptr )
		{

			// Get Channel.
			rss::Channel *const prevChannel( getChannelByLink( newLink_->mUrl ) );

			// Compare Channels & merge (move).
			if ( prevChannel != nullptr && prevChannel != pChannel && prevChannel->id != pChannel->id )
			{

				// Merge Channels (move Elements & Items from temp. to created).
				rss::Channel::merge( pChannel, prevChannel );

				// Return
				return( prevChannel );

			}

		} /// Search Channel using Link.

		// Lock
		if ( pLock )
		{

			// Lock
			QMutexLocker uLock( &mChannelsMutex );

			// Add Channel
			mChannels.push_back( pChannel );

		}
		else
			mChannels.push_back( pChannel ); // Add Channel

		// Return new Channel.
		return( pChannel );

	}

	/**
	  * Called after RSS parsing complete.
	  * Cause attach Views to Update.
	  *
	  * @threadsafe - not thread-safe.
	  * @throws - no exceptions.
	**/
	void ChannelModel::onChannelsUpdated( ) noexcept
	{

#if defined( QT_DEBUG ) || defined( DEBUG ) // DEBUG
		// Debug
		qDebug( ) << "ChannelModel::onChannelsUpdated";
#endif // DEBUG

		beginInsertRows( QModelIndex( ), 0, mChannels.size( ) - 1 );
		endInsertRows( );

	}

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

	/**
	  * Reads RSS-file.
	  *
	  * (?) If RSS-Channel with the same link found,
	  * and it's newer (pubDate, lastBuildDate), their data merged.
	  *
	  * @threadsafe - not thread-safe.
	  * @param pSrc - File-Path.
	  * @param pChannel - Channel-class to update from rss-document.
	  * @throws - no exceptions.
	**/
	void ChannelModel::readFile( const QString & pSrc, rss::Channel *const pChannel ) noexcept
	{

		// Create SAXRSSHandler instance.
		rss::SAXRSSHandler rssHandler( pChannel, this );

		// Create QFile.
		QFile rssFile( pSrc );

#if defined( QT_DEBUG ) // DEBUG
		// Debug
		qDebug( ) << "ChannelModel::readFile#" << pSrc;

		// Check FileExistance
		assert( rssFile.exists( ) && "ChannelModel::readFile - file not found !" );
#else // !DEBUG
		if ( !rssFile.exists( ) )
			return;
#endif // DEBUG

		// Create Xml-InputSource
		QXmlInputSource inputSource( &rssFile );

		// Create default Xml-Reader.
		QXmlSimpleReader xmlReader;

		// Set SAX-Handler for Xml-Reader.
		xmlReader.setContentHandler( &rssHandler );

		// Parse SAX Xml RSS-Document.
		xmlReader.parse( &inputSource );

		// Update
		onChannelsUpdated( );

	} /// ChannelModel::readFile

	/**
	  * Read RSS-file using QUrl.
	  *
	  * @threadsafe - thread-lock used, only if required.
	  * @param pUrl - URL from QML.
	  * @throws - no exceptions.
	**/
	void ChannelModel::parseRSSFile( const QUrl pUrl ) noexcept
	{ readFile( pUrl.toLocalFile( ), nullptr ); }

	// ===========================================================
	// OVERRIDE
	// ===========================================================

	Qt::ItemFlags ChannelModel::flags( const QModelIndex & pIndex ) const
	{

#if defined( QT_DEBUG ) || defined( DEBUG ) // DEBUG
		// Debug
		qDebug( ) << "ChannelModel::flags, index.row=" << pIndex.row( ) << "index.col=" << pIndex.column( ) << "index.pointer=" << QString( pIndex.internalPointer( ) != nullptr );
#endif // DEBUG

		// Return
		return( Qt::ItemFlags( Qt::ItemFlag::ItemIsEnabled | Qt::ItemFlag::ItemIsSelectable ) );

	}

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
		// Debug
		qDebug( ) << "ChannelModel::data, index.row=" << pIndex.row( ) << "index.col=" << pIndex.column( ) << "index.pointer=" << QString( pIndex.internalPointer( ) != nullptr );

		// Check Model-Index.
		assert( pIndex.isValid( ) && "ChannelModel::data - invalid Model-Index ! Root can't provide any data to display." );
#else // !DEBUG
		// Cancel, if invalid Model-Index.
		if ( !pIndex.isValid( ) )
			return( QVariant( ) );
#endif // DEBUG

		// Get rss::Element
		Element *const elementPtr( pIndex.internalPointer( ) != nullptr ? static_cast<Element*>( pIndex.internalPointer( ) ) : getChannelByIndex( pIndex.row( ) ) );

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

#if defined( QT_DEBUG ) // DEBUG
		// Debug
		qDebug( ) << "ChannelModel::index, index.row=" << pRow << "index.col=" << pCol;
#endif // DEBUG

		// Cancel, if trying to retrive index of root.
		if ( pRow < 0 || pCol < 0 )
			return( parentIndex );

		// Root
		if ( !parentIndex.isValid( ) )
		{

			// Return Model-Index for a Channel.
			return( createIndex( pRow, pCol, nullptr ) );

		} /// Root

		// Channel.
		if ( parentIndex.internalPointer( ) != nullptr )
		{

			// Get Element
			rss::Element *const element_( static_cast<rss::Element*>( parentIndex.internalPointer( ) ) );

			// Channel
			if ( element_->type == rss::ElementType::CHANNEL )
			{
				// Get Channel
				rss::Channel *const channel_( static_cast<rss::Channel*>( element_ ) );

				// Return Model-Index for Channel' Item.
				return( createIndex( pRow, pCol, channel_ ) );

			} /// Channel
			else if ( element_->type == rss::ElementType::ITEM )
			{ // Item

				// Get Item.
				rss::Item *const item_( static_cast<rss::Item*>( element_ ) );

				// Return Model-Index for a Item.
				return( createIndex( pRow, pCol, item_ ) );

			} /// Item

		} /// Channel

		// Return root.
		return( parentIndex );

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

#if defined( QT_DEBUG ) // DEBUG
		// Debug
		qDebug( ) << "ChannelModel::parent, index.row=" << pIndex.row( ) << "index.col=" << pIndex.column( ) << "index.pointer=" << QString( pIndex.internalPointer( ) != nullptr );
#endif // DEBUG

		// Return root if invalid.
		if ( !pIndex.isValid( ) || pIndex.internalPointer( ) == nullptr )
			return( QModelIndex( ) );

		// Get Element.
		rss::Element *const element( static_cast<rss::Element*>( pIndex.internalPointer( ) ) );

#if defined( QT_DEBUG ) || defined( DEBUG ) // DEBUG
		// Null-check.
		assert( element != nullptr && "ChannelModel::parent - Element is null ! Check ChannelModel::index() method." );
#endif // DEBUG

		// Cancel, if not Channel Item-Element.
		if ( element->type != ElementType::ITEM )
			return( QModelIndex( ) );

		// Get Item's Channel.
		rss::Channel *const channel( static_cast<rss::Channel*>( element->parent ) );

		// Generate Model-Index for Channel.
		return( createIndex( getChannelIndex( channel ), 0, nullptr ) );

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

#if defined( QT_DEBUG ) // DEBUG
		// Debug
		qDebug( ) << "ChannelModel::rowCount, index.row=" << parentIndex.row( ) << "index.col=" << parentIndex.column( ) << "index.pointer=" << QString( parentIndex.internalPointer( ) != nullptr );
#endif // DEBUG

		// Cancel, if bad-arguments.
		if ( parentIndex.column( ) > 0 )
			return( 0 );

		// roo-ModelIndex (invalid ModelIndex).
		if ( !parentIndex.isValid( ) )
			return( mChannels.size( ) );

		return( 0 );

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

#if defined( QT_DEBUG ) // DEBUG
		// Debug
		qDebug( ) << "ChannelModel::hasChildren, index.row=" << pIndex.row( ) << "index.col=" << pIndex.column( ) << "index.pointer=" << QString( pIndex.internalPointer( ) != nullptr );
#endif // DEBUG

		// Cancel, if Columns used.
		if ( pIndex.column( ) > 0 )
			return( false );

		// Root.
		if ( !pIndex.isValid( ) )
			return( true );

		// Channel.
		if ( pIndex.internalPointer( ) == nullptr )
		{

			// Get Channel.
			rss::Channel *const channel_( getChannelByIndex( pIndex.row( ) ) );

			// Return TRUE, if Channel have Items.
			return( channel_ != nullptr && !channel_->empty( ) );

		} /// Channel

		// Get Element.
		rss::Element *const element_( static_cast<rss::Element*>( pIndex.internalPointer( ) ) );

		// Get Item
		if ( element_->type == rss::ElementType::CHANNEL )
		{// Channel

			// Cast Element to Channel.
			rss::Channel *const channel_( static_cast<rss::Channel*>( element_ ) );

			// Return TRUE, if Item found.
			return( channel_->empty( ) );

		} /// Item
		else if ( element_->type == rss::ElementType::ITEM ) // Item' Element
		{

			// Do not expose Item Elements to Views.
			return( false );

		} /// Item' Element

#if defined( QT_DEBUG ) || defined( DEBUG ) // DEBUG
		// Debug
		qDebug( ) << "ChannelModel::hasChildren - bad logic, unreachable code.";
#endif // DEBUG

		// Return FALSE
		return( false );

	} /// ChannelModel::hasChildren

	/**
	  * Returns Role-Names used by this Model.
	  *
	  * @threadsafe - not required.
	  * @return - QHash for QML.
	  * @throws - no exceptions.
	**/
	QHash<int, QByteArray> ChannelModel::roleNames( ) const
	{

		// Create HashMap
		QHash<int, QByteArray> rolesMap;

		// Title
		rolesMap[rss::ChannelModel::Roles::RSS_TITLE_ELEMENT_ROLE] = "title";

		// Image Url.
		rolesMap[rss::ChannelModel::Roles::RSS_IMAGE_ELEMENT_ROLE] = "image";

		// Image Title.
		rolesMap[rss::ChannelModel::Roles::RSS_IMAGE_TITLE_ELEMENT_ROLE] = "image_title";

		// Image Link
		rolesMap[rss::ChannelModel::Roles::RSS_IMAGE_LINK_ELEMENT_ROLE] = "image_link";

		// Image Description
		rolesMap[rss::ChannelModel::Roles::RSS_IMAGE_DESCRIPTION_ELEMENT_ROLE] = "image_description";

		// Image Width
		rolesMap[rss::ChannelModel::Roles::RSS_IMAGE_WIDTH_ELEMENT_ROLE] = "image_width";

		// Image Height
		rolesMap[rss::ChannelModel::Roles::RSS_IMAGE_HEIGHT_ELEMENT_ROLE] = "image_height";

		// Language.
		rolesMap[rss::ChannelModel::Roles::RSS_LANGUAGE_ELEMENT_ROLE] = "language";

		// Copyright.
		rolesMap[rss::ChannelModel::Roles::RSS_COPYRIGHT_ELEMENT_ROLE] = "copyright";

		// Managing Editor.
		rolesMap[rss::ChannelModel::Roles::RSS_MANAGING_EDITOR_ELEMENT_ROLE] = "managingEditor";

		// Web-Master.
		rolesMap[rss::ChannelModel::Roles::RSS_WEB_MASTER_ELEMENT_ROLE] = "webMaster";

		// PubDate.
		rolesMap[rss::ChannelModel::Roles::RSS_PUB_DATE_ELEMENT_ROLE] = "pubDate";

		// Last Build Date.
		rolesMap[rss::ChannelModel::Roles::RSS_LAST_BUILD_DATE_ELEMENT_ROLE] = "lastBuildDate";

		// Category Text.
		rolesMap[rss::ChannelModel::Roles::RSS_CATEGORY_ELEMENT_TEXT_ROLE] = "category_text";

		// Category Domain.
		rolesMap[rss::ChannelModel::Roles::RSS_CATEGORY_ELEMENT_DOMAIN_ROLE] = "category_domain";

		// Generator.
		rolesMap[rss::ChannelModel::Roles::RSS_GENERATOR_ELEMENT_ROLE] = "generator";

		// Docs.
		rolesMap[rss::ChannelModel::Roles::RSS_DOCS_ELEMENT_ROLE] = "docs";

		// Cloud Domain.
		rolesMap[rss::ChannelModel::Roles::RSS_CLOUD_ELEMENT_DOMAIN_ROLE] = "cloud_domain";

		// Cloud Port.
		rolesMap[rss::ChannelModel::Roles::RSS_CLOUD_ELEMENT_PORT_ROLE] = "cloud_port";

		// Cloud Path.
		rolesMap[rss::ChannelModel::Roles::RSS_CLOUD_ELEMENT_PATH_ROLE] = "cloud_path";

		// Cloud Register-Procedure.
		rolesMap[rss::ChannelModel::Roles::RSS_CLOUD_ELEMENT_REGISTER_PROCEDURE_ROLE] = "cloud_registerProcedure";

		// Cloud Protocol.
		rolesMap[rss::ChannelModel::Roles::RSS_CLOUD_ELEMENT_PROTOCOL_ROLE] = "cloud_protocol";

		// TTL
		rolesMap[rss::ChannelModel::Roles::RSS_TTL_ELEMENT_ROLE] = "ttl";

		// Text-Input Title.
		rolesMap[rss::ChannelModel::Roles::RSS_TEXT_INPUT_ELEMENT_TITLE_ROLE] = "textInput_title";

		// Text-Input Description.
		rolesMap[rss::ChannelModel::Roles::RSS_TEXT_INPUT_ELEMENT_DESCRIPTION_ROLE] = "textInput_description";

		// Text-Input Name
		rolesMap[rss::ChannelModel::Roles::RSS_TEXT_INPUT_ELEMENT_NAME_ROLE] = "textInput_name";

		// Text-Input Link
		rolesMap[rss::ChannelModel::Roles::RSS_TEXT_INPUT_ELEMENT_LINK_ROLE] = "textInput_link";

		// Skip-Hours
		rolesMap[rss::ChannelModel::Roles::RSS_SKIP_HOURS_ELEMENT_ROLE] = "skipHours";

		// Skip-Days.
		rolesMap[rss::ChannelModel::Roles::RSS_SKIP_DAYS_ELEMENT_ROLE] = "skipDays";

		// Description.
		rolesMap[rss::ChannelModel::Roles::RSS_DESCRIPTION_ELEMENT_ROLE] = "description";

		// Link.
		rolesMap[rss::ChannelModel::Roles::RSS_LINK_ELEMENT_ROLE] = "link";

		// Author.
		rolesMap[rss::ChannelModel::Roles::RSS_AUTHOR_ELEMENT_ROLE] = "author";

		// Comments.
		rolesMap[rss::ChannelModel::Roles::RSS_COMMENTS_ELEMENT_ROLE] = "comments";

		// GUID.
		rolesMap[rss::ChannelModel::Roles::RSS_GUID_ELEMENT_ROLE] = "guid";

		// Source Text.
		rolesMap[rss::ChannelModel::Roles::RSS_SOURCE_ELEMENT_TEXT_ROLE] = "source_text";

		// Source Url.
		rolesMap[rss::ChannelModel::Roles::RSS_SOURCE_ELEMENT_URL_ROLE] = "source_url";

		// Enclosure Url.
		rolesMap[rss::ChannelModel::Roles::RSS_ENCLOSURE_ELEMENT_URL_ROLE] = "enclosure_url";

		// Enclosure Length.
		rolesMap[rss::ChannelModel::Roles::RSS_ENCLOSURE_ELEMENT_LENGTH_ROLE] = "enclosure_length";

		// Enclosure Mime-Type.
		rolesMap[rss::ChannelModel::Roles::RSS_ENCLOSURE_ELEMENT_TYPE_ROLE] = "enclosure_type";

		// Return Model-Roles.
		return( rolesMap );

	} /// ChannelModel::roleNames

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
