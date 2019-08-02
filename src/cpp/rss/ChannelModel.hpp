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

// Include rss::Item
#ifndef QRSS_READER_ITEM_HPP
#include "Item.hpp"
#endif // !QRSS_READER_ITEM_HPP

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

// ===========================================================
// ChannelModel
// ===========================================================

namespace rss
{

	/**
	  * ChannelModel - tree-model for RSS Channels.
	  *
	  * @brief
	  * Structure:
	  *  - Channel:
	  *    - Image (Logo, Icon);
	  *    - Name (Title);
	  *    - Url;
	  *    - Items (News):
	  *      -
	  *
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

			/** Image Role. Used to check if Image Element exists. **/
			CHANNEL_IMAGE_ROLE = Qt::DecorationRole,

			/** <title> **/
			CHANNEL_TITLE_ROLE = Qt::DisplayRole,

			/** <name> **/
			CHANNEL_NAME_ROLE = Qt::DisplayRole,

			/** <url> **/
			CHANNEL_URL_ROLE = Qt::UserRole + 1,

			/** <link> **/
			CHANNEL_LINK_ROLE = CHANNEL_URL_ROLE,
			ITEM_LINK_ROLE = CHANNEL_LINK_ROLE,
			LINK_ROLE = ITEM_LINK_ROLE,

			/** <description> **/
			CHANNEL_DESCRIPTION_ROLE = Qt::UserRole + 2,
			DESCRIPTION_ROLE = CHANNEL_DESCRIPTION_ROLE,
			ITEM_DESCRIPTION_ROLE = DESCRIPTION_ROLE,

			/** <text> **/
			CHANNEL_TEXT_ROLE = DESCRIPTION_ROLE,

			/** <language> **/
			CHANNEL_LANGUAGE_ROLE = Qt::UserRole + 3,

			/** <copyright> **/
			CHANNEL_COPYRIGHT_ROLE = Qt::UserRole + 4,

			/** <managingEditor> **/
			CHANNEL_EDITOR_ROLE = Qt::UserRole + 5,

			/** <webMaster> **/
			CHANNEL_WEB_MASTER_ROLE = Qt::UserRole + 6,

			/** <pubDate> **/
			CHANNEL_PUB_DATE_ROLE = Qt::UserRole + 7,

			/** <lastBuildDate> **/
			CHANNEL_LAST_BUILD_DATE_ROLE = Qt::UserRole + 8,

			/** <category> **/
			CHANNEL_CATEGORY_ROLE = Qt::UserRole + 9,

			/** <generator> **/
			CHANNEL_GENERATOR_ROLE = Qt::UserRole + 10,

			/** <docs> **/
			CHANNEL_DOCS_ROLE = Qt::UserRole + 11,

			/** <cloud> **/
			CHANNEL_CLOUD_ROLE = Qt::UserRole + 12,

			/** <ttl> **/
			CHANNEL_TTL_ROLE = Qt::UserRole + 13,

			/** <textInput> **/
			CHANNEL_TEXT_INPUT_ROLE = Qt::UserRole + 14,

			/** <skipHours> **/
			CHANNEL_SKIP_HOURS_ROLE = Qt::UserRole + 15,

			/** <skipDays> **/
			CHANNEL_SKIP_DAYS_ROLE = Qt::UserRole + 16,

			/** <image><url></image> **/
			CHANNEL_IMAGE_URL_ROLE = Qt::UserRole + 17,

			/** <image><title></image> **/
			IMAGE_TITLE_ROLE = Qt::UserRole + 18,

			/** <image><link></image> **/
			IMAGE_LINK_ROLE = Qt::UserRole + 19,

			/** <image><width></image> **/
			IMAGE_WIDTH_ROLE = Qt::UserRole + 20,

			/** <image><height></image> **/
			IMAGE_HEIGHT_ROLE = Qt::UserRole + 21,

			/** <image><description></image> **/
			IMAGE_DESCRIPTION_ROLE = Qt::UserRole + 22,

			/** <image><url></image> **/
			IMAGE_URL_ROLE = CHANNEL_IMAGE_URL_ROLE,

			/** Image check. **/
			IMAGE_EXISTS_ROLE = CHANNEL_IMAGE_ROLE,

			/** <title> **/
			ITEM_TITLE_ROLE = CHANNEL_TITLE_ROLE,
			TITLE_ROLE = CHANNEL_TITLE_ROLE,

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
		  * Returns 'true' if the given Model-Index has sub-Items.
		  *
		  * @threadsafe - thread-lock used.
		  * @param pIndex - Model-Index.
		  * @return - 'true' if contains sub-Items, 'false' if not.
		  * @throws - no exceptions.
		**/
		virtual bool hasChildren( const QModelIndex & pIndex = QModelIndex( ) ) const override;

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
		virtual QVariant headerData( int pSection, Qt::Orientation pOrientation, int pRole = Qt::DisplayRole ) const override;

		// -----------------------------------------------------------

	}; /// rss::ChannelModel

} // rss

// To avoid forward-declarations.
#define Q_RSS_READER_CHANNEL_MODEL_DECL

// -----------------------------------------------------------

#endif // !Q_RSS_READER_CHANNEL_MODEL_HPP
