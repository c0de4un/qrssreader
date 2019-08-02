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
	{// TODO ChannelModel::getChannelData

#if defined( QT_DEBUG ) || defined( DEBUG ) // DEBUG

		// Debug-flag, that data-role handled.
		bool roleHandled( false );

#endif // DEBUG

		// Handle Data-Role
		switch( pRole )
		{

		// ==================== Required elements. ====================

		// [<title>] Title (DisplayRole)
		case rss::ChannelModel::Roles::CHANNEL_TITLE_ROLE:
		{

			// Get Title-Element of Channel.
			rss::Title *const titleElement( static_cast<rss::Title*>( pChannel->getElement( rss::ElementType::TITLE ) ) );

#if defined( QT_DEBUG ) || defined( DEBUG ) // DEBUG
			// Null-Check
			assert( titleElement != nullptr && "ChannelModel::getChannelData - RSS Channel must have Title-Element !" );
#endif // DEBUG

			// Return Title
			return( QVariant( titleElement->mData ) );

		} /// Title [<title>]

		// Link [<link>]
		case rss::ChannelModel::Roles::CHANNEL_LINK_ROLE:
		{

			// Get Link-Element.
			rss::Link *const link( static_cast<rss::Link*>( pChannel->getElement( rss::ElementType::LINK ) ) );

#if defined( QT_DEBUG ) || defined( DEBUG ) // DEBUG
			// Null-Check
			assert( link != nullptr && "ChannelModel::getChannelData - RSS Channel must have Link-Element !" );
#endif // DEBUG

			// Return Link URL
			return( QVariant( link->mUrl ) );

		} /// Link [<link>]

		// Description [<description>]
		case rss::ChannelModel::Roles::CHANNEL_DESCRIPTION_ROLE:
		{

			// Get Link-Element.
			rss::Description *const desc( static_cast<rss::Description*>( pChannel->getElement( rss::ElementType::DESCRITION ) ) );

#if defined( QT_DEBUG ) || defined( DEBUG ) // DEBUG
			// Null-Check
			assert( desc != nullptr && "ChannelModel::getChannelData - RSS Channel must have Description-Element !" );
#endif // DEBUG

			// Return Link URL
			return( QVariant( desc->mData ) );

		} /// Description [<description>]

		// ==================== Not required elements. ====================

		// Language [<language>]
		case rss::ChannelModel::Roles::CHANNEL_LANGUAGE_ROLE:
		{

			// Get Language-Element.
			rss::Language *const language( static_cast<rss::Language*>( pChannel->getElement( rss::ElementType::LANGUAGE ) ) );

			// Return Language-Element value.
			return( QVariant( language->mData ) );

		} /// Language [<language>]

		// Image (checks if <image> element exists).
		case rss::ChannelModel::Roles::IMAGE_EXISTS_ROLE:
		{

			// Get Image Element
			rss::Image *const image_ptr( static_cast<rss::Image*>( pChannel->getElement( rss::ElementType::IMAGE ) ) );

			// Return TRUE if Image Element exists.
			return( QVariant( image_ptr != nullptr ) );

		}

		// Image Url <image><url></image>
		case rss::ChannelModel::Roles::IMAGE_URL_ROLE:
		{

			// Get Image Element
			rss::Image *const image_ptr( static_cast<rss::Image*>( pChannel->getElement( rss::ElementType::IMAGE ) ) );

#if defined( QT_DEBUG ) || defined( DEBUG ) // DEBUG
			// Null-Check
			assert( image_ptr != nullptr && "ChannelModel::getChannelData - Image-Element not found ! Use DecorationRole (or CHANNEL_IMAGE_ROLE, or IMAGE_EXISTS_ROLE) to get bool-flag !" );
#else // !DEBUG
			// Return null if Image Element not found.
			if ( image_ptr == nullptr )
				return( QVariant( QUrl( nullptr ) ) );
#endif // DEBUG

			// Get Image Url (Link) Element
			rss::Url *const url_ptr( static_cast<rss::Url*>( image_ptr->getElement( ElementType::URL ) ) );

#if defined( QT_DEBUG ) || defined( DEBUG ) // DEBUG
			// Null-Check
			assert( image_ptr != nullptr && "ChannelModel::getChannelData - Image Url Element not found !" );
#endif // DEBUG

			// Return Image.Url
			return( QVariant( url_ptr->mUrl ) );

		} /// Image Url <image><url></image>

		default:
		{

			// Return
			return( QVariant( QString( "error, unsupported data type." ) ) );

		}

		} /// Handle Data-Role

#if defined( QT_DEBUG ) || defined( DEBUG ) // DEBUG
		// Check if data-role handled.
		assert( roleHandled && "ChannelModel::getChannelData - Role not handled ! Data-type not supported ?" );
#endif // DEBUG

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
	{// TODO ChannelModel::getItemData

#if defined( QT_DEBUG ) || defined( DEBUG ) // DEBUG

		// Debug-flag, that data-role handled.
		bool roleHandled( false );

#endif // DEBUG

		// Handle Item Data-Role.
		switch( pRole )
		{

		// ======================= Required Elements =======================

		// <title>
		case rss::ChannelModel::Roles::TITLE_ROLE:
		{

			// Get Title Element.
			rss::Title *const title_ptr( static_cast<rss::Title*>( pItem->getElement( ElementType::TITLE ) ) );

#if defined( QT_DEBUG ) || defined( DEBUG ) // DEBUG
			// Null-check
			assert( title_ptr != nullptr && "ChannelModel::getItemData - title element not found !" );
#endif // DEBUG

			// Return Title.
			return( QVariant( title_ptr->mData ) );

		}

		// <link>
		case rss::ChannelModel::Roles::LINK_ROLE:
		{

			// Get Link Element.
			rss::Link *const link( static_cast<rss::Link*>( pItem->getElement( ElementType::LINK ) ) );

#if defined( QT_DEBUG ) || defined( DEBUG ) // DEBUG
			// Null-check
			assert( link != nullptr && "ChannelModel::getItemData - link element not found !" );
#endif // DEBUG

			// Return Link value.
			return( QVariant( link->mUrl ) );

		}

		// <description>
		case rss::ChannelModel::Roles::DESCRIPTION_ROLE:
		{

			// Get Description-Element.
			rss::Description *const description( static_cast<rss::Description*>( pItem->getElement( ElementType::DESCRITION ) ) );

#if defined( QT_DEBUG ) || defined( DEBUG ) // DEBUG
			// Null-check
			assert( description != nullptr && "ChannelModel::getItemData - description element not found !" );
#endif // DEBUG

			// Return Description.
			return( QVariant( description->mData ) );

		}

		// ======================= Additional (Optional) Elements =======================

		// Default
		default:
		{

			// Return error
			return( QVariant( QString( "error" ) ) );

		} /// Default

		} /// Handle Item Data-Role.

#if defined( QT_DEBUG ) || defined( DEBUG ) // DEBUG
		// Check if data-role handled.
		assert( roleHandled && "ChannelModel::getItemData - Role not handled ! Data-type not supported ?" );
#endif // DEBUG

		// Return empty
		return( QVariant( QString( "" ) ) ); // Unreachable

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

#if defined( QT_DEFINED ) || defined( DEBUG ) // DEBUG
		// Null-Check.
		assert( pIndex.internalPointer( ) != nullptr && "ChannelModel::data - invalid Model-Index data, it must contain an object, inherited from rss::Element !" );
#endif // DEBUG

		// Get rss::Element
		Element *const elementPtr( static_cast<Element*>( pIndex.internalPointer( ) ) );

		// Handle RSS Element-Type.
		switch( elementPtr->mType )
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

			// Stop
			break;

		} /// default
		} /// Handle RSS Element-Type.

		// Return Default
		return( QModelIndex( ) );

	} /// ChannelModel::data

	/**
	  * Search for Model-Index using col, row & parent-index.
	  *
	  * @threadsafe - thread-lock used.
	  * @param pRow - Row. Represents RSS Channel-class ID.
	  * @param pCol - Col, not used, alway 0.
	**/
	QModelIndex ChannelModel::index( int pRow, int pCol, const QModelIndex & parentIndex ) const
	{// TODO ChannelModel::index

		// Thread-Lock
		QMutexLocker uLock( &mChannelsMutex );

		// Get Channel using index.
		channel_ptr_t channel( getChannelByIndex( pCol ) );

#if defined( QT_DEBUG ) || defined( DEBUG ) // DEBUG
		// Check Channel pointer-value.
		assert( channel != nullptr && "ChannelModel::index - Channel is null !" ); // Unreachable, because indeices range checked already.
#endif // DEBUG

		//

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
	{// TODO ChannelModel::parent

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
	{// TODO ChannelModel::rowCount

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
	{// TODO ChannelModel::hasChildren

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
	QVariant ChannelModel::headerData( int pSection, Qt::Orientation pOrientation, int pRole ) const
	{// TODO ChannelModel::headerData

	} /// ChannelModel::headerData

	// -----------------------------------------------------------

} // rss

// -----------------------------------------------------------
