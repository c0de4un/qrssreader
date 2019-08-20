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

#ifndef Q_RSS_READER_CHANNEL_MODEL_HPP
#define Q_RSS_READER_CHANNEL_MODEL_HPP

// -----------------------------------------------------------

// ===========================================================
// INCLUDES
// ===========================================================

// Include QAbstractItemModel
#ifndef QABSTRACTITEMMODEL_H
#include <QAbstractItemModel>
#endif // !QABSTRACTITEMMODEL_H

// Include QMap
#ifndef QMAP_H
#include <qmap.h>
#endif // !QMAP_H

// Include QVector
#ifndef QVECTOR_H
#include <qvector.h>
#endif // !QVECTOR_H

// Include QMutex
#ifndef QMUTEX_H
#include <qmutex.h>
#endif // !QMUTEX_H

// Include QObject
#ifndef QOBJECT_H
#include <QObject>
#endif // !QOBJECT_H

// Include rss::Channel
#ifndef QRSS_READER_CHANNEL_HPP
#include "Channel.hpp"
#endif // !QRSS_READER_CHANNEL_HPP

// Include rss::Category
#ifndef QRSS_READER_SOURCE_HPP
#include "Source.hpp"
#endif // !QRSS_READER_SOURCE_HPP

// Include rss::Cloud
#ifndef QRSS_READER_CLOUD_HPP
#include "Cloud.hpp"
#endif // !QRSS_READER_CLOUD_HPP

// Include rss::Date
#ifndef QRSS_READER_DATE_HPP
#include "Date.hpp"
#endif // !QRSS_READER_DATE_HPP

// Include rss::Enclosure
#ifndef QRSS_READER_ENCLOSURE_HPP
#include "Enclosure.hpp"
#endif // !QRSS_READER_ENCLOSURE_HPP

// Include rss::Integer
#ifndef QRSS_READER_INTEGER_HPP
#include "Integer.hpp"
#endif // !QRSS_READER_INTEGER_HPP

// Include rss::Image
#ifndef QRSS_READER_IMAGE_HPP
#include "Image.hpp"
#endif // !QRSS_READER_IMAGE_HPP

// Include rss::Link
#ifndef QRSS_READER_LINK_HPP
#include "Link.hpp"
#endif // !QRSS_READER_LINK_HPP

// Include rss::Text
#ifndef QRSS_READER_TEXT_HPP
#include "Text.hpp"
#endif // !QRSS_READER_TEXT_HPP

// Include rss::TextInput
#ifndef QRSS_READER_TEXT_INPUT_HPP
#include "TextInput.hpp"
#endif // !QRSS_READER_TEXT_INPUT_HPP

// ===========================================================
// ChannelModel
// ===========================================================

namespace rss
{

	/**
	  * ChannelModel - tree-model for RSS Channels.
	  * <br/>
	  *
	  * @brief<br/>
	  * Columns not used, so that param is alway 0.
	  * Row #0 used to get Model-Index for root, means
	  * its rows count = Channels count.
	  * <br/>
	  *
	  * <br/>
	  * @version 0.1
	  * @since 21.07.2019
	  * @authors Denis Z. (code4un@yandex.ru)
	**/
	class ChannelModel : public QAbstractItemModel
	{

		// -----------------------------------------------------------

		// ===========================================================
		// QT MACROS
		// ===========================================================

		Q_OBJECT

		// ===========================================================
		// SIGNALS
		// ===========================================================


		// ===========================================================
		// CONFIG
		// ===========================================================

		/** Alias for Channel pointer. **/
		using channel_ptr_t = rss::Channel*;

		// -----------------------------------------------------------

	private:

		// -----------------------------------------------------------

		// ===========================================================
		// FIELDS
		// ===========================================================

		/** Channels Mutex. **/
		mutable QMutex mChannelsMutex;

		/** RSS Channels collection (container). Collection is private (inner), so no sorting are made. **/
		QVector<channel_ptr_t> mChannels;

		// -----------------------------------------------------------

	public:

		// -----------------------------------------------------------

		// ===========================================================
		// TYPES
		// ===========================================================

		/**
		  * Roles - ChannelModel unique Roles.
		**/
		enum Roles
		{

			// TEST-CODE
			/**
			  * By default, Channel & Item returns Title as
			  * DisplayRole. Use RSS_ELEMENT_DESCRIPTION_ROLE
			  * to retrieve the Description.
			**/
			RSS_TITLE_ELEMENT_ROLE = Qt::DisplayRole,

			/**
			  * <image><url /></image>
			  * Used to return Url of an Image.
			  * Use same value as DecorationRole.
			  * If returned value is valid (QUrl), try using
			  * RSS_IMAGE_WIDTH, RSS_IMAGE_HEIGHT, RSS_IMAGE_TITLE,
			  * RSS_IMAGE_LINK, RSS_IMAGE_DESCRIPTION to retrieve
			  * optional (additional) data.
			  * If Image-Element not found,
			  * invalid QVariant returned.
			**/
			RSS_IMAGE_ELEMENT_ROLE = Qt::DecorationRole,

			/** <image><title /></image>. @see RSS_IMAGE_ELEMENT_ROLE.
			 * If <width> not found, invalid QVariant returned. **/
			RSS_IMAGE_TITLE_ELEMENT_ROLE = Qt::UserRole + 1,

			/** <image><description /></image>. @see RSS_IMAGE_ELEMENT_ROLE.
			 * If <height> not found, invalid QVariant returned. **/
			RSS_IMAGE_DESCRIPTION_ELEMENT_ROLE = Qt::UserRole + 2,

			/** <image><width /></image>. @see RSS_IMAGE_ELEMENT_ROLE.
			 * If <width> not found, invalid QVariant returned. **/
			RSS_IMAGE_WIDTH_ELEMENT_ROLE = Qt::UserRole + 3,

			/** <image><height /></image>. @see RSS_IMAGE_ELEMENT_ROLE.
			 * If <width> not found, invalid QVariant returned. **/
			RSS_IMAGE_HEIGHT_ELEMENT_ROLE = Qt::UserRole + 4,

			/** <image><link /></image>. @see RSS_IMAGE_ELEMENT_ROLE.
			 * If <width> not found, invalid QVariant returned. **/
			RSS_IMAGE_LINK_ELEMENT_ROLE = Qt::UserRole + 5,

			/**
			  * Language.
			  * <language>ru-RU</language>
			  * Returns language-id.
			  * If not found, invalid QVariant returned.
			**/
			RSS_LANGUAGE_ELEMENT_ROLE = Qt::UserRole + 6,

			/** <copyright>. If Element not found, returns invalid QVariant. **/
			RSS_COPYRIGHT_ELEMENT_ROLE = Qt::UserRole + 7,

			/** <managingEditor>. If Element not found, returns invalid QVariant. **/
			RSS_MANAGING_EDITOR_ELEMENT_ROLE = Qt::UserRole + 8,

			/** <webMaster>. If Element not found, returns invalid QVariant. **/
			RSS_WEB_MASTER_ELEMENT_ROLE = Qt::UserRole + 9,

			/** <pubDate>. If Element not found, returns invalid QVariant. **/
			RSS_PUB_DATE_ELEMENT_ROLE = Qt::UserRole + 10,

			/** <lastBuildDate>. If Element not found, returns invalid QVariant. **/
			RSS_LAST_BUILD_DATE_ELEMENT_ROLE = Qt::UserRole + 11,

			/** <category>TEXT</category>. If Element not found, returns invalid QVariant. **/
			RSS_CATEGORY_ELEMENT_TEXT_ROLE = Qt::UserRole + 12,

			/** <category domain="URL">. If Element not found, returns invalid QVariant. **/
			RSS_CATEGORY_ELEMENT_DOMAIN_ROLE = Qt::UserRole + 13,

			/** <generator>. If Element not found, returns invalid QVariant. **/
			RSS_GENERATOR_ELEMENT_ROLE = Qt::UserRole + 14,

			/** <docs>. If Element not found, returns invalid QVariant. **/
			RSS_DOCS_ELEMENT_ROLE = Qt::UserRole + 15,

			/** <cloud domain="URL">. If Element not found, returns invalid QVariant. **/
			RSS_CLOUD_ELEMENT_DOMAIN_ROLE = Qt::UserRole + 16,

			/** <cloud port="80">. If Element not found, returns invalid QVariant. **/
			RSS_CLOUD_ELEMENT_PORT_ROLE = Qt::UserRole + 17,

			/** <cloud path="/RPC">. If Element not found, returns invalid QVariant. **/
			RSS_CLOUD_ELEMENT_PATH_ROLE = Qt::UserRole + 18,

			/** <cloud registerProcedure="xmlStorageSystem.rssPleaseNotify">. If Element not found, returns invalid QVariant. **/
			RSS_CLOUD_ELEMENT_REGISTER_PROCEDURE_ROLE = Qt::UserRole + 19,

			/** <cloud protocol="xml-rpc">. If Element not found, returns invalid QVariant. **/
			RSS_CLOUD_ELEMENT_PROTOCOL_ROLE = Qt::UserRole + 20,

			/** <ttl>int</ttl>. If Element not found, returns invalid QVariant. **/
			RSS_TTL_ELEMENT_ROLE = Qt::UserRole + 21,

			/** <textInput><title></textInput>. If Element not found, returns invalid QVariant. **/
			RSS_TEXT_INPUT_ELEMENT_TITLE_ROLE = Qt::UserRole + 22,

			/** <textInput><description></textInput>. If Element not found, returns invalid QVariant. **/
			RSS_TEXT_INPUT_ELEMENT_DESCRIPTION_ROLE = Qt::UserRole + 23,

			/** <textInput><name></textInput>. If Element not found, returns invalid QVariant. **/
			RSS_TEXT_INPUT_ELEMENT_NAME_ROLE = Qt::UserRole + 24,

			/** <textInput><link></textInput>. If Element not found, returns invalid QVariant. **/
			RSS_TEXT_INPUT_ELEMENT_LINK_ROLE = Qt::UserRole + 25,

			/** <skipHours>. If Element not found, returns invalid QVariant. **/
			RSS_SKIP_HOURS_ELEMENT_ROLE = Qt::UserRole + 26,

			/** <skipDays>. If Element not found, returns invalid QVariant. **/
			RSS_SKIP_DAYS_ELEMENT_ROLE = Qt::UserRole + 27,

			/** <description>. If Element not found, returns invalid QVariant. **/
			RSS_DESCRIPTION_ELEMENT_ROLE = Qt::UserRole + 28,

			/** <link>. If Element not found, returns invalid QVariant. **/
			RSS_LINK_ELEMENT_ROLE = Qt::UserRole + 29,

			/** <author>some_email@mail.org</author>. If Element not found, returns invalid QVariant. **/
			RSS_AUTHOR_ELEMENT_ROLE = Qt::UserRole + 30,

			/** <comments>. If Element not found, returns invalid QVariant. **/
			RSS_COMMENTS_ELEMENT_ROLE = Qt::UserRole + 31,

			/** <guid>. If Element not found, returns invalid QVariant. **/
			RSS_GUID_ELEMENT_ROLE = Qt::UserRole + 32,

			/** <source>TEXT</source>. If Element not found, returns invalid QVariant. **/
			RSS_SOURCE_ELEMENT_TEXT_ROLE = Qt::UserRole + 33,

			/** <source url="URL">. If Element not found, returns invalid QVariant. **/
			RSS_SOURCE_ELEMENT_URL_ROLE = Qt::UserRole + 34,

			/**
			  * <enclosure url="URL">
			  * If Element not found, returns invalid QVariant.
			**/
			RSS_ENCLOSURE_ELEMENT_URL_ROLE = Qt::UserRole + 35,

			/**
			  * <enclosure length="0">
			  * If Element not found, returns invalid QVariant.
			**/
			RSS_ENCLOSURE_ELEMENT_LENGTH_ROLE = Qt::UserRole + 36,

			/**
			  * <enclosure type="mime/type">
			  * If Element not found, returns invalid QVariant.
			**/
			RSS_ENCLOSURE_ELEMENT_TYPE_ROLE = Qt::UserRole + 37

		}; // Roles

		// ===========================================================
		// CONSTRUCTOR
		// ===========================================================

		/**
		  * ChannelModel constructor.
		  *
		  * @param qParent - Parent-Object. default is null.
		  * @throws - no exceptions.
		**/
		explicit ChannelModel( QObject *const qParent = nullptr ) noexcept;

		// ===========================================================
		// DESTRUCTOR
		// ===========================================================

		/**
		  * ChannelModel destructor.
		  *
		  * @throws - no exceptions.
		**/
		virtual ~ChannelModel( ) noexcept override;

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
		channel_ptr_t getChannelByIndex( const int pIndex ) const noexcept;

		/**
		  * Returns public-index of a Channel.
		  *
		  * @threadsafe - thread-lock used.
		  * @param pChannel - Channel.
		  * @throws - no exceptions.
		**/
		int getChannelIndex( const rss::Channel *const pChannel ) const noexcept;

		/**
		  * Returns Channel, associated with a specific Row.
		  *
		  * @threadsafe - thread-lock used.
		  * @param pRow - Row.
		  * @returns - Channel instance, or null.
		  * @throw - no exceptions.
		**/
		rss::Channel * getChannelByRow( const int pRow ) const noexcept;

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
		channel_ptr_t getChannelByLink( const QUrl & pLink ) const noexcept;

		/**
		  * Returns RSS Channel-class data (title, description, image, etc).
		  *
		  * @threadsafe - must be called only while thread-lock locked.
		  * @param pChannel - RSS Channel-class.
		  * @param pRole - Role (image, text, etc).
		  * @return - QVariant with data.
		  * @throws - no exceptions.
		**/
		QVariant getChannelData( rss::Channel *const pChannel, const int pRole ) const noexcept;

		/**
		  * Returns RSS Channel's Item data (date, form, text).
		  *
		  * @threadsafe - must be called only while thread-lock locked.
		  * @param pChannel - RSS Channel-class.
		  * @param pRole - Role (image, text, etc).
		  * @return - QVariant with data.
		  * @throws - no exceptions.
		**/
		QVariant getItemData( rss::Item *const pItem, const int pRole ) const noexcept;

		/**
		  * Deletes all Channels.
		  *
		  * @brief
		  * (?) Used by destructor or RSS-parser.
		  *
		  * @threadsafe - thread-lock used.
		  * @throws - no exceptions.
		**/
		void clearChannels( ) noexcept;

		/**
		  * Called when Channel-class data created or updated.
		  *
		  * @threadsafe - thread-lock used.
		  * @param pChannel - Channel instance.
		  * @param pLock - 'true' to use thread-lock.
		  * @throws - no exceptions.
		**/
		rss::Channel * addChannel( rss::Channel *const pChannel, const bool pLock ) noexcept;

		/**
		  * Called after RSS parsing complete.
		  * Cause attach Views to Update.
		  *
		  * @threadsafe - not thread-safe.
		  * @throws - no exceptions.
		**/
		void onChannelsUpdated( ) noexcept;

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
		void readFile( const QString & pSrc, rss::Channel *const pChannel ) noexcept;

		/**
		  * Read RSS-file using QUrl.
		  *
		  * @threadsafe - thread-lock used, only if required.
		  * @param pUrl - URL from QML.
		  * @throws - no exceptions.
		**/
		Q_INVOKABLE void parseRSSFile( const QUrl pUrl ) noexcept;

		Q_INVOKABLE QModelIndex getInvalidIndex( ) noexcept
		{
			return( QModelIndex( ) );
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
		virtual QVariant data( const QModelIndex & pIndex, int pRole = Qt::DisplayRole ) const override;

		/**
		  *
		**/
		//virtual bool canFetchMore( const QModelIndex & pIndex ) const override;

		/**
		  *
		**/
		virtual Qt::ItemFlags flags( const QModelIndex & pIndex ) const override;

		/**
		  * Search for Model-Index using col, row & parent-index.
		  *
		  * @threadsafe - thread-lock used.
		  * @param pRow - Row. Represents RSS Channel-class ID.
		  * @param pCol - Col, not used, alway 0.
		**/
		virtual QModelIndex index( int pRow, int pCol, const QModelIndex & parentIndex = QModelIndex( ) ) const override;

		/**
		  * Searches Model-Item Parent.
		  *
		  * @threadsafe - thread-lock used.
		  * @param pIndex - Model's Item Index.
		  * @return - Model-Index.
		  * @throws - no excepions.
		**/
		virtual QModelIndex parent( const QModelIndex & pIndex ) const override;

		/**
		  * Count Rows of the given Model-Item (RSS Channel || Item).
		  *
		  * @threadsafe - thread-lock used.
		  * @param parentIndex - Item to investigate.
		  * @returns - Rows Count.
		  * @throws - no exceptions.
		**/
		virtual int rowCount( const QModelIndex & parentIndex = QModelIndex( ) ) const override;

		/**
		  * Counts Columns for a Model-Index.
		  *
		  * Not used in Tree-Models.
		  *
		  * @threadsafe - thread-lock used.
		  * @param pIndex - Model-Index.
		  * @returns - Columns count.
		  * @throws - no exceptions.
		**/
		virtual int columnCount( const QModelIndex & pIndex = QModelIndex( ) ) const override
		{
			Q_UNUSED( pIndex )
			return( 0 );
		}

		/**
		  * Returns 'true' if the given Model-Index has sub-Items.
		  *
		  * @threadsafe - thread-lock used.
		  * @param pIndex - Model-Index.
		  * @return - 'true' if contains sub-Items, 'false' if not.
		  * @throws - no exceptions.
		**/
		virtual bool hasChildren( const QModelIndex & pIndex = QModelIndex( ) ) const override;

		/**
		  * Returns Role-Names used by this Model.
		  *
		  * @threadsafe - not required.
		  * @return - QHash for QML.
		  * @throws - no exceptions.
		**/
		virtual QHash<int, QByteArray> roleNames( ) const override;

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
		//virtual QVariant headerData( int pSection, Qt::Orientation pOrientation, int pRole = Qt::DisplayRole ) const override;

		// -----------------------------------------------------------

	}; /// rss::ChannelModel

} // rss

// To avoid forward-declarations.
#define Q_RSS_READER_CHANNEL_MODEL_DECL

// -----------------------------------------------------------

#endif // !Q_RSS_READER_CHANNEL_MODEL_HPP
