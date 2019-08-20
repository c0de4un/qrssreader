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
#ifndef QRSS_READER_PROXY_CHANNEL_MODEL_HPP
#include "ProxyChannelModel.hpp"
#endif // !QRSS_READER_PROXY_CHANNEL_MODEL_HPP

// Include rss::ChannelModel
#ifndef Q_RSS_READER_CHANNEL_MODEL_HPP
#include "ChannelModel.hpp"
#endif // !Q_RSS_READER_CHANNEL_MODEL_HPP

// Include QML
#ifndef QT_QTQML_MODULE_H
#include <QtQml> // qmlEngine( QObject * )
#endif // !QT_QTQML_MODULE_H

#if defined( QT_DEBUG ) || defined( DEBUG ) // DEBUG

// Include QDebug
#ifndef QDEBUG_H
#include <qdebug.h>
#endif // !QDEBUG_H

#endif // DEBUG

// ===========================================================
// rss::ProxyChannelModel
// ===========================================================

namespace rss
{

	// -----------------------------------------------------------

	// ===========================================================
	// CONSTRUCTOR
	// ===========================================================

	/**
	  * ProxyChannelModel constructor.
	  *
	  * @param qParent - Parent-QObject.
	  * @throws - no exceptions.
	**/
	ProxyChannelModel::ProxyChannelModel( QObject *const qParent ) noexcept
		: QSortFilterProxyModel( qParent ),
		  mSelectedChannel( nullptr ),
		  mSelectedChannelIndex( QModelIndex( ) ),
		  mRowsMap( ),
		  mItems( )
	{

#if defined( QT_DEBUG ) // DEBUG
		// Debug-info.
		qDebug( ) << "ProxyChannelModel::constructor";
#endif // DEBUG

	}

	// ===========================================================
	// DESTRUCTOR
	// ===========================================================

	/**
	  * ProxyChannelModel destructor.
	  *
	  * @throws - no exceptions.
	**/
	ProxyChannelModel::~ProxyChannelModel( ) noexcept
	{

#if defined( QT_DEBUG ) // DEBUG
		// Debug-info.
		qDebug( ) << "ProxyChannelModel::destructor";
#endif // DEBUG

	}

	// ===========================================================
	// METHODS
	// ===========================================================

	/**
	  * Searches for associated (mapped) Row Index.
	  *
	  * (?) Custom indexing used due to null-check in Qt QSortFilterProxyModel::index.
	  *
	  * @threadsafe - not thread-safe.
	  * @param pRow - Proxy-Row Index.
	  * @return - source-Row Index.
	  * @throws - no exceptions.
	**/
	int ProxyChannelModel::getSourceRow( const int pRow ) const noexcept
	{

		// Search Proxy-Row.
		auto rowPos_( mRowsMap.find( pRow ) );

		// Return source-Row if mapped.
		if ( rowPos_ != mRowsMap.cend( ) )
			return( rowPos_.value( ) );

		// No mapping, proxy Row Index = source Row Index.
		return( pRow );

	} /// ProxyChannelModel::getSourceRow

	/**
	  * Called to Update Channel' Items List.
	  *
	  * @brief
	  * (?) Called every time source-Model changed. Filters & sorts
	  * Items as Rows. Replaces Qt default-implementation, to reduce
	  * callback-time, by avoiding asking every channel' each item.
	  *
	  * @threadsafe - not thread-safe.
	  * @throws - no exceptions.
	**/
	void ProxyChannelModel::onUpdateItemsList( ) noexcept
	{

		// Reset Items List.
		mItems.clear( );

		// Count Channel' Items.
		const int itemsCount_( mSelectedChannel->countItems( ) );

		// Channel' Item.
		rss::Item * item_( nullptr );

		// Filter Items.
		for( int i = 0; i < itemsCount_; i++ )
		{

			// Get Item.
			item_ = mSelectedChannel->getItem( i );

			// Skip, if Item removed.
			if ( item_ == nullptr )
				continue;

			// Add Item to List.
			mItems.push_back( item_ );

		} /// Filter Items.

		// Sort Items.

	} /// ProxyChannelModel::onUpdateItemsList

	// ===========================================================
	// QML Methods
	// ===========================================================

	/**
	  * Called to set Channel-Index as root.
	  *
	  * (?) Cause Views to update state.
	  *
	  * @threadsafe - not thread-safe.
	  * @param pLink - Channel URL/Link.
	  * @throws - no exceptions.
	**/
	void ProxyChannelModel::setSelectedChannelIndex( const QUrl & pLink ) noexcept
	{

#if defined( QT_DEBUG ) // DEBUG
		// Debug-message.
		qDebug( ) << "ProxyChannelModel::setSelectedChannelIndex - Link=" << pLink;
#endif // DEBUG

		// Get ChannelModel instance.
		rss::ChannelModel *const channelModel_( static_cast<rss::ChannelModel*>( sourceModel( ) ) );

		// Get Channel using Link.
		rss::Channel *const channel_ ( channelModel_->getChannelByLink( pLink ) );

		// Cancel, if already selected.
		if ( mSelectedChannel == channel_ )
			return;

		// Set Selected Channel.
		mSelectedChannel = channel_;

		// Reset Rows-Map.
		mRowsMap.clear( );

		// Update Items List.
		onUpdateItemsList( );

		// Notify Views by emiting signal.
		beginInsertRows( QModelIndex( ), 0, mSelectedChannel->countItems( ) );
		endInsertRows( );

	} /// ProxyChannelModel::setSelectedChannelIndex


	// ===========================================================
	// OVERRIDE: QSortFilterProxyModel
	// ===========================================================

	/**
	  * Called to filter Rows.
	  *
	  * @threadsafe - not thread-safe.
	  * @param srcRow - Source-Model Row.
	  * @param srcIndex - Source-Model parent-Index.
	  * @return - 'true' to add Model-Index.
	  * @throws - no exceptions.
	**/
	bool ProxyChannelModel::filterAcceptsRow( int srcRow, const QModelIndex & srcIndex ) const
	{

		Q_UNUSED( srcIndex );
		Q_UNUSED( srcRow );

#if defined( QT_DEBUG ) // DEBUG
		// Debug-info.
		qDebug( ) << "ProxyChannelModel::filterAcceptsRow, Row=" + QString::number( srcRow );
#endif // DEBUG

		// This Proxy-Model stores only Channel' Items using manual (custom) sorting.
		return( false );

	} /// ProxyChannelModel::filterAcceptsRow

	/**
	  * Retrieves data (text, image, date, url, etc) using src-ModelIndex.
	  *
	  * @threadsafe - not thread-safe.
	  * @param srcIndex - ModelIndex.
	  * @param pRole = Role.
	  * @return - data, or invalid (empty) QVariant.
	  * @throws - no exceptions.
	**/
	QVariant ProxyChannelModel::data( const QModelIndex & pIndex, int pRole ) const
	{

		// Get ChannelModel
		rss::ChannelModel *const rssModel_( static_cast<rss::ChannelModel*>( sourceModel( ) ) );

		// Get Channel' Item.
		rss::Item *const item_( static_cast<rss::Item*>( pIndex.internalPointer( ) ) );

#if defined( QT_DEBUG ) // DEBUG
		// Debug-info.
		qDebug( ) << "ProxyChannelModel::data, Row=" << pIndex.row( ) << ", pointer=" << pIndex.internalPointer( );

		// Check Selected-Channel.
		assert( mSelectedChannel != nullptr && "ProxyChannelModel::data - can't provide data without Channel !" );

		// Check Source-Model.
		assert( rssModel_ != nullptr && "ProxyChannelModel::data - source-model is null !" );

		// Check Channel' Item.
		assert( item_ != nullptr && "ProxyChannelModel::data - Channel Item is null !" );
#else // !DEBUG
		// Cancel, if not Channel selected.
		if ( mSelectedChannel == nullptr || rssModel == nullptr || item_ == nullptr )
			return( QVariant( ) );
#endif // DEBUG

		// Get Channel' Item Data.
		return( rssModel_->getItemData( item_, pRole ) );

	} /// ProxyChannelModel::data

	/**
	  * Returns Role-Names used tp retrieve data with Model-Index.
	  *
	  * @threadsafe - not thread-safe.
	  * @returns - list of Roles.
	  * @throws - no exceptions.
	**/
	QHash<int,QByteArray> ProxyChannelModel::roleNames( ) const
	{

#if defined( QT_DEBUG ) // DEBUG
			// Debug-info.
			qDebug( ) << "ProxyChannelModel::roleNames";
#endif // DEBUG

		// Return Source-Model Roles.
		return( sourceModel( )->roleNames( ) );

	} /// ProxyChannelModel::roleNames

	/**
	  * Returns Rows count.
	  *
	  * @threadsafe - not thread-safe.
	  * @param parent - parent Model-Index.
	  * @return - number of rows.
	  * @throws - no exceptions.
	**/
	int ProxyChannelModel::rowCount( const QModelIndex & pIndex ) const
	{

#if defined( QT_DEBUG ) // DEBUG
			// Debug-info.
			qDebug( ) << "ProxyChannelModel::rowCount, Row=" << QString::number( pIndex.row( ) );
#endif // DEBUG

			// Return Channel' Items count.
			return( !pIndex.isValid( ) ? mItems.size( ) : 0 );

	} /// ProxyChannelModel::rowCount

	/**
	  * Returns 'true' of source-Index have children.
	  *
	  * @threadsafe - not thread-safe.
	  * @param parent - parent Model-Index.
	  * @return - 'true' if source-Index has children.
	  * @throws - no exceptions.
	**/
	bool ProxyChannelModel::hasChildren( const QModelIndex & pIndex ) const
	{

#if defined( QT_DEBUG ) // DEBUG
			// Debug-info.
			qDebug( ) << "ProxyChannelModel::hasChildren - row=" << QString::number( pIndex.row( ) ) << ", col=" << QString::number( pIndex.column( ) );
#endif // DEBUG

		// Return FALSE
		return( false );

	} /// ProxyChannelModel::hasChildren

	/**
	  * Returns parent-Index.
	  *
	  * @threadsafe - not thread-safe.
	  * @param parent - parent-Index.
	  * @return - Model-Index to parent, or invalid to root.
	  * @throws - no exceptions.
	**/
	QModelIndex ProxyChannelModel::parent( const QModelIndex & pIndex ) const
	{

#if defined( QT_DEBUG ) // DEBUG
			// Debug-info.
			qDebug( ) << "ProxyChannelModel::parent - row=" << QString::number( pIndex.row( ) ) << ", col=" << QString::number( pIndex.column( ) );
#endif // DEBUG

			// Return invalid-Index, since Proxy-Model for Channel' Items not suppose to support Tree-Model, only Items & Channel as root.
			return( QModelIndex( ) );

	} /// ProxyChannelModel::parent

	/**
	  * Returns Model-Index associated with the given row, col & parent.
	  *
	  * @threadsafe - not thread-safe.
	  * @param pRow - Row.
	  * @param pCol - Column, not used.
	  * @param parent - parent-Index.
	  * @return - Model-Index, or invalid (root) if none.
	  * @throws - no exceptions.
	**/
	QModelIndex ProxyChannelModel::index( int pRow, int pCol, const QModelIndex & pIndex ) const
	{

		Q_UNUSED( pCol )

#if defined( QT_DEBUG ) // DEBUG
		// Debug-info.
		qDebug( ) << "ProxyChannelModel::index - row=" << QString::number( pRow ) << ", col=" << QString::number( pCol );

		// Check parent-Index.
		assert( pIndex.internalPointer( ) == nullptr && "ProxyChannelModel::index - this Proxy-Model designed only for RSS Channel' Items." );

		// Check Items List.
		assert( !mItems.empty( ) && "ProxyChannelModel::index - No Items to display !" );
#else // !DEBUG
		// Cancel, if no Items.
		if ( mItems.isEmpty( ) )
			return( QModelIndex( ) );
#endif // DEBUG

		// Cancel, if invalid-Index, or Channel not set.
		if ( pRow < 0 || pCol < 0 || mSelectedChannel == nullptr )
			return( QModelIndex( ) );

		// Get Channel' Item using rows-mapping.
		rss::Item *const item_( mItems.at( pRow ) );

#if defined( QT_DEBUG ) // DEBUG
		// Check Channel' Item.
		assert( item_ != nullptr && "ProxyChannelModel::index - Channel\' Item not found ! Check #rowsCount method." );
#else // !DEBUG
		// Cancel, if Item not found.
		if ( item_ == nullptr )
			return( QModelIndex( ) );
#endif // DEBUG

		// Create Proxy-Model Index for Channel' Item.
		return( createIndex( pRow, pCol, item_ ) );

	} /// ProxyChannelModel::index

	/**
	  * Returns flags for Model-Index.
	  *
	  * @threadsafe - not thread-safe.
	  * @param pIndex - Model-Index.
	  * @throws - no exceptions.
	**/
	Qt::ItemFlags ProxyChannelModel::flags( const QModelIndex & pIndex ) const
	{

#if defined( QT_DEBUG ) // DEBUG
			// Debug-info.
			qDebug( ) << "ProxyChannelModel::flags - row=" << QString::number( pIndex.row( ) ) << ", col=" << QString::number( pIndex.column( ) );
#endif // DEBUG

		// Return same the flags as Source-Model has.
		return( sourceModel( )->flags( pIndex ) );

	} /// ProxyChannelModel::flags

	// -----------------------------------------------------------

} // rss

// -----------------------------------------------------------
