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

#ifndef QRSS_READER_PROXY_CHANNEL_MODEL_HPP
#define QRSS_READER_PROXY_CHANNEL_MODEL_HPP

// -----------------------------------------------------------

// ===========================================================
// INCLUDES
// ===========================================================

// Include QSortFilterProxyModel
#ifndef QSORTFILTERPROXYMODEL_H
#include <QSortFilterProxyModel>
#endif // !QSORTFILTERPROXYMODEL_H

// Include QMap
#ifndef QMAP_H
#include <QMap>
#endif // !QMAP_H

// Include QVector
#include <QVector>

// ===========================================================
// FORWARD-DECLARATIONS
// ===========================================================

// Forward-declare rss::Channel
#ifndef QRSS_READER_CHANNEL_DECL
namespace rss { struct Channel; }
#define QRSS_READER_CHANNEL_DECL
#endif // !QRSS_READER_CHANNEL_DECL

// Forward-declare rss::Item
#ifndef QRSS_READER_ITEM_DECL
#define QRSS_READER_ITEM_DECL
namespace rss { struct Item; }
#endif // !QRSS_READER_ITEM_DECL

// ===========================================================
// rss::ProxyChannelModel
// ===========================================================

namespace rss
{

	// -----------------------------------------------------------

	/**
	  * ProxyChannelModel - Proxy-Model for ChannelModel.
	  *
	  * @brief
	  * ProxyChannelModel allows to sort Channels or Channel' Items,
	  * by pubDate, Read-Status, Channel.
	  *
	  * @version 1.0
	  * @since 21.09.2019
	  * @authors Denis Z. (code4un@yandex.ru)
	**/
	class ProxyChannelModel : public QSortFilterProxyModel
	{

		// -----------------------------------------------------------

		// ===========================================================
		// META
		// ===========================================================

		Q_OBJECT

		// ===========================================================
		// QML Methods
		// ===========================================================

		// -----------------------------------------------------------

	signals:

		// -----------------------------------------------------------

		// ===========================================================
		// SIGNALS
		// ===========================================================

		// -----------------------------------------------------------

	private:

		// -----------------------------------------------------------

		// ===========================================================
		// FIELDS
		// ===========================================================

		/** Selected Channel. **/
		rss::Channel * mSelectedChannel;

		/** Source Model Index for Selected Channel. **/
		QModelIndex mSelectedChannelIndex;

		/**
		  * Map to store association with source-rows.
		  * Used instead of storing indices within data-structs.
		  * Key - Proxy-Row Index.
		  * Value - Source-Row Index.
		**/
		QMap<int, int> mRowsMap;

		/**
		  * Filtered & sorted Channel' Items List (vector).
		**/
		QVector<rss::Item*> mItems;

		// -----------------------------------------------------------

	public:

		// -----------------------------------------------------------

		// ===========================================================
		// rss::ProxyChannelModel::FilterSyntax
		// ===========================================================

		/** Filter syntax enum. **/
		enum FilterSyntax
		{

			// -----------------------------------------------------------

			// ===========================================================
			// CONSTANTS
			// ===========================================================

			RegExp,
			WildCard,
			FixedString

			// -----------------------------------------------------------

		}; // rss::ProxyChannelModel::FilterSyntax

		// ===========================================================
		// CONSTRUCTOR
		// ===========================================================

		/**
		  * ProxyChannelModel constructor.
		  *
		  * @param qParent - Parent-QObject.
		  * @throws - no exceptions.
		**/
		explicit ProxyChannelModel( QObject *const qParent = nullptr ) noexcept;

		// ===========================================================
		// DESTRUCTOR
		// ===========================================================

		/**
		  * ProxyChannelModel destructor.
		  *
		  * @throws - no exceptions.
		**/
		virtual ~ProxyChannelModel( ) noexcept override;

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
		Q_INVOKABLE void setSelectedChannelIndex( const QUrl & pLink ) noexcept;

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
		int getSourceRow( const int pRow ) const noexcept;

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
		void onUpdateItemsList( ) noexcept;

		// ===========================================================
		// OVERRIDE: QSortFilterProxyModel
		// ===========================================================

		/**
		  * Called to filter Rows.
		  *
		  * @threadsafe - not thread-safe.
		  * @param srcRow - Model Row.
		  * @param srcIndex - Model parent-Index.
		  * @return - 'true' to add Model-Index.
		  * @throws - no exceptions.
		**/
		bool filterAcceptsRow( int srcRow, const QModelIndex & srcIndex ) const override;

		/**
		  * Retrieves data (text, image, date, url, etc) using src-ModelIndex.
		  *
		  * @threadsafe - not thread-safe.
		  * @param srcIndex - ModelIndex.
		  * @param pRole = Role.
		  * @return - data, or invalid (empty) QVariant.
		  * @throws - no exceptions.
		**/
		virtual QVariant data( const QModelIndex & pIndex, int role = Qt::DisplayRole ) const override;

		/**
		  * Returns Role-Names used tp retrieve data with Model-Index.
		  *
		  * @threadsafe - not thread-safe.
		  * @returns - list of Roles.
		  * @throws - no exceptions.
		**/
		virtual QHash<int,QByteArray> roleNames( ) const override;

		/**
		  * Returns Rows count.
		  *
		  * @threadsafe - not thread-safe.
		  * @param parent - parent Model-Index.
		  * @return - number of rows.
		  * @throws - no exceptions.
		**/
		virtual int rowCount( const QModelIndex & pIndex = QModelIndex( ) ) const override;

		/**
		  * Returns 'true' of Index have children.
		  *
		  * @threadsafe - not thread-safe.
		  * @param parent - parent Model-Index.
		  * @return - 'true' if Index has children.
		  * @throws - no exceptions.
		**/
		virtual bool hasChildren( const QModelIndex & pIndex = QModelIndex( ) ) const override;

		/**
		  * Returns parent-Index.
		  *
		  * @threadsafe - not thread-safe.
		  * @param parent - parent-Index.
		  * @return - Model-Index to parent, or invalid to root.
		  * @throws - no exceptions.
		**/
		virtual QModelIndex parent( const QModelIndex & pIndex = QModelIndex( ) ) const override;

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
		virtual QModelIndex index( int pRow, int pCol, const QModelIndex & pIndex = QModelIndex( ) ) const override;

		/**
		  * Returns flags for Model-Index.
		  *
		  * @threadsafe - not thread-safe.
		  * @param pIndex - Model-Index.
		  * @throws - no exceptions.
		**/
		virtual Qt::ItemFlags flags( const QModelIndex & pIndex = QModelIndex( ) ) const override;

		// -----------------------------------------------------------

	}; // rss::ProxyChannelModel

	// -----------------------------------------------------------

} // rss

#define QRSS_READER_PROXY_CHANNEL_MODEL_DECL

// -----------------------------------------------------------

#endif // !QRSS_READER_PROXY_CHANNEL_MODEL_HPP
