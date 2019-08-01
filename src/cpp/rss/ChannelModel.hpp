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

// Include QObject
#ifndef QOBJECT_H
#include <QObject>
#endif // !QOBJECT_H
//#include <QFileSystemModel>

// DEBUG
#if defined( QT_DEBUG ) || defined( DEBUG )

// Forward-declaration not required.
#define Q_RSS_READER_CHANNEL_MODEL_DECL

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

#endif
// DEBUG

// ===========================================================
// FORWARD-DECLARATIONS
// ===========================================================

// RELEASE
#if !defined( QT_DEBUG ) && !defined( DEBUG ) // RELEASE

#ifndef Q_RSS_READER_CHANNEL_MODEL_DECL
#define Q_RSS_READER_CHANNEL_MODEL_DECL

// Forward-Declare rss::Channel
namespace rss { class Channel; }

// Forward-Declare rss::Item
namespace rss { struct Item; }

// Forward-Declare rss::Element
namespace rss { struct Element; }

// Forward-Declare rss::Integer
namespace rss
{
	struct Integer;

	/** TTL **/
	using TTL = Integer;

	/** Skip Hours **/
	using SkipHours = Integer;

	/** Skip Days. **/
	using SkipDays = Integer;

}

// Forward-Declare rss::Enclosure
namespace rss { struct Enclosure; }

// Forward-Declare rss::Date
namespace rss
{
	struct Date;

	/** PubDate. **/
	using PubDate = Date;

	/** LastBuildDate. **/
	using LastBuildDate = Date;

}

// Forward-Declare rss::Cloud
namespace rss { struct Cloud; }

// Forward-Declare rss::Category
namespace rss { struct Category; }

// Forward-Declare rss::Text
namespace rss
{
	struct Text;

	/** Description. **/
	using Description = Text;

	/** Web-Master. **/
	using WebMaster = Text;

	/** Managing-Editor. **/
	using ManagingEditor = Text;

	/** Title. **/
	using Title = Text;
}

// Forward-Declare rss::Link
namespace rss { struct Link; }

#endif // !Q_RSS_READER_CHANNEL_MODEL_DECL

#endif
// RELEASE

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

		// -----------------------------------------------------------

	private:

		// -----------------------------------------------------------

		// ===========================================================
		// FIELDS
		// ===========================================================

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

			CHANNEL_LOGO_ROLE = Qt::DecorationRole,
			CHANNEL_NAME_ROLE = Qt::DisplayRole,
			CHANNEL_URL_ROLE = Qt::UserRole + 1

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

		// ===========================================================
		// OVERRIDE
		// ===========================================================

		/**
		  * Sets Item-Data.
		  *
		  * @thread_safety - thread-lock used & signals/slots.
		  * @param modelIndex - Item Model Index.
		  * @param pValue - value to set.
		  * @param pRole - Role.
		  * @return - 'true' if OK, 'false' data not set.
		  * @throws - no exceptions.
		**/
		virtual bool setData( const QModelIndex & modelIndex, const QVariant & pValue, const int pRole = Qt::EditRole ) override;

		// -----------------------------------------------------------

	}; /// rss::ChannelModel

} // rss

// To avoid forward-declarations.
#define Q_RSS_READER_CHANNEL_MODEL_DECL

// -----------------------------------------------------------

#endif // !Q_RSS_READER_CHANNEL_MODEL_HPP
