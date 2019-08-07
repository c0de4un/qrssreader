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

#ifndef QRSS_READER_SAX_RSS_HANDLER_HPP
#define QRSS_READER_SAX_RSS_HANDLER_HPP

// -----------------------------------------------------------

// ===========================================================
// INCLUDES
// ===========================================================

// Include QtXml
#include <QtXml> // QXmlDefaultHandler, QXmlContentHandler, etc.

// Include QString
#ifndef QSTRING_H
#include <qstring.h>
#endif // !QSTRING_H

// Include QMap
#ifndef QMAP_H
#include <qmap.h>
#endif // !QMAP_H

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

// Forward-declare rss::Text
#ifndef QRSS_READER_TEXT_DECL
#define QRSS_READER_TEXT_DECL
namespace rss
{
	struct Text;
	using Description = Text;
	using WebMaster = Text;
	using ManagingEditor = Text;
	using Title = Text;
	using GUID = Text;
	using Language = Text;
}
#endif // !QRSS_READER_TEXT_DECL

// Forward-declare rss::Source
#ifndef QRSS_READER_SOURCE_DECL
#define QRSS_READER_SOURCE_DECL
namespace rss
{
	struct Source;
	using Category = Source;
}
#endif // !QRSS_READER_SOURCE_DECL

// Forward-declare rss::Integer
#ifndef QRSS_READER_INTEGER_DECL
#define QRSS_READER_INTEGER_DECL
namespace rss
{
	struct Integer;
	using TTL = Integer;
	using SkipHours = Integer;
	using SkipDays = Integer;
}
#endif // !QRSS_READER_INTEGER_DECL

// Forward-declare rss::Enclosure
#ifndef QRSS_READER_ENCLOSURE_DECL
#define QRSS_READER_ENCLOSURE_DECL
namespace rss { struct Enclosure; }
#endif // !QRSS_READER_ENCLOSURE_DECL

// Forward-declare rss::Image
#ifndef QRSS_READER_IMAGE_DECL
#define QRSS_READER_IMAGE_DECL
namespace rss { struct Image; }
#endif // !QRSS_READER_IMAGE_DECL

// Forward-declare rss::Cloud
#ifndef QRSS_READER_CLOUD_DECL
#define QRSS_READER_CLOUD_DECL
namespace rss { struct Cloud; }
#endif // !QRSS_READER_CLOUD_DECL

// Forward-declare rss::Date
#ifndef QRSS_READER_DATE_DECL
#define QRSS_READER_DATE_DECL
namespace rss
{
	struct Date;
	using PubDate = Date;
	using LastBuildDate = Date;
}
#endif // !QRSS_READER_DATE_DECL

// Forward-declare rss:ChannelModel
#ifndef Q_RSS_READER_CHANNEL_MODEL_DECL
#define Q_RSS_READER_CHANNEL_MODEL_DECL
namespace rss{ class ChannelModel; }
#endif // !Q_RSS_READER_CHANNEL_MODEL_DECL

// ===========================================================
// rss::SAXRSSHandler
// ===========================================================

namespace rss
{

	// -----------------------------------------------------------

	/**
	  * SAXRSSHandler - handles SAX reading of RSS document (file).
	  *
	  * @brief
	  * SAX is the preferred XML reading-method due to stop (cancel, abort) action.
	  * For example, it is possible to read only specific part of RSS-document, avoiding
	  * full data downloading.
	  *
	  * @version 1.0
	  * @since 21.07.2019
	  * @authors Denis Z. (code4un@yandex.ru)
	**/
	class SAXRSSHandler : public QXmlDefaultHandler
	{// TODO SAXRSSHandler

	private:

		// -----------------------------------------------------------

		// ===========================================================
		// RSSPosition
		// ===========================================================

		/** RSS Parsing State. **/
		enum RSSPosition
		{

			/** Channel Element Parsing. **/
			RSS_CHANNEL_OPEN = 0,

			/** RSS Channel Title Element. **/
			RSS_CHANNEL_TITLE = 1,

			/**
			 * RSS Channel Link Element
			 * <channel>
			 * <link>www.site.org/rss/news.rss</link>
			 * </channel>
			**/
			RSS_CHANNEL_LINK = 2,

			/**
			  * RSS Channel Description Element.
			 * <channel>
			 * <description>News</description>
			 * </channel>
			**/
			RSS_CHANNEL_DESCRIPTION = 3,

			/**
			 * RSS Channel Language Element.
			 * <channel>
			 * <language>ru-RU</language>
			 * </channel>
			**/
			RSS_CHANNEL_LANGUAGE = 4,

			/**
			 * RSS Channel Ropyright Element.
			 * <channel>
			 * <copyright>someone@mail.com</copyright>
			 * </channel>
			**/
			RSS_CHANNEL_COPYRIGHT = 5,

			/**
			  * RSS Channel Managing Editor Element.
			  *
			 * <channel>
			 * <managingEditor>Vasya Pac</managingEditor>
			 * </channel>
			**/
			RSS_CHANNEL_MANAGING_EDITOR = 6,

			/**
			  * RSS Channel WebMaster Element.
			  *
			 * <channel>
			 * <webMaster />
			 * </channel>
			**/
			RSS_CHANNEL_WEB_MASTER = 7,

			/**
			  * RSS Channel PubDate Element.
			 * <channel>
			 * <pubDate />
			 * </channel>
			**/
			RSS_CHANNEL_PUB_DATE = 8,

			/** RSS Channel LastBuildDate Element. **/
			RSS_CHANNEL_LAST_BUILD_DATE = 9,

			/** RSS Channel Category Element. **/
			RSS_CHANNEL_CATEGORY = 10,

			/** RSS Generator Element. **/
			RSS_GENERATOR = 11,

			/** RSS Docs Element. **/
			RSS_DOCS = 12,

			/** Cloud Element. **/
			RSS_CLOUD = 13,

			/** TTL Element. **/
			RSS_CHANNEL_TTL = 14,

			/** RSS Channel Image. **/
			RSS_CHANNEL_IMAGE = 15,

			/** RSS Channel's Image Link **/
			RSS_CHANNEL_IMAGE_LINK = 16,

			/** RSS Channel's Image Title **/
			RSS_CHANNEL_IMAGE_TITLE = 17,

			/** RSS Channel's Image Description **/
			RSS_CHANNEL_IMAGE_DESCRIPTION = 18,

			/** RSS Channel's Image Url **/
			RSS_CHANNEL_IMAGE_URL = 19,

			/** RSS Channel's Image Width **/
			RSS_CHANNEL_IMAGE_WIDTH = 20,

			/** RSS Channel's Image Height **/
			RSS_CHANNEL_IMAGE_HEIGHT = 21,

			/** RSS Channel Text-Input Title. **/
			RSS_CHANNEL_TEXT_INPUT_TITLE = 22,

			/** RSS Channel Text-Input Description. **/
			RSS_CHANNEL_TEXT_INPUT_DESCRIPTION = 23,

			/** RSS Channel Text-Input Name. **/
			RSS_CHANNEL_TEXT_INPUT_NAME = 24,

			/** RSS Channel Text-Input Link. **/
			RSS_CHANNEL_TEXT_INPUT_LINK = 25,

			/** RSS Channel Text-Input. **/
			RSS_CHANNEL_TEXT_INPUT = 26,

			RSS_CHANNEL_SKIP_HOURS = 27,

			RSS_CHANNEL_SKIP_DAYS = 28,

			/** RSS Channel's Item Element. **/
			RSS_ITEM_OPEN,

			RSS_ITEM_LINK,

			RSS_ITEM_COMMENTS,

			RSS_ITEM_CATEGORY,

			RSS_ITEM_ENCLOSURE,

			RSS_ITEM_GUID,

			RSS_ITEM_PUB_DATE,

			RSS_ITEM_SOURCE,

			/** RSS Channel's Item Title Element. **/
			RSS_ITEM_TITLE,

			/** RSS Item Description. **/
			RSS_ITEM_DESCRIPTION

		}; // rss::SAXRSSHandler::RSSPosition

		// ===========================================================
		// FIELDS
		// ===========================================================

		/** RSS Channel class to Update/Merge. **/
		rss::Channel * mChannel;

		/** State. **/
		RSSPosition mCurrState;

		/** Previous State. Used to fallback neither to Channel or Item State-ID. **/
		RSSPosition mPrevState;

		/** Values Map. Used to avoid declaring sets of temp. variables. **/
		QMap<QString, QString> mValues;

		/** Item. **/
		rss::Item * mItem;

		/** ChannelModel. **/
		rss::ChannelModel *const mChannelModel;

		// ===========================================================
		// METHODS
		// ===========================================================

		/**
		  * Search Attribute.
		  *
		  * @threadsafe - not thread-safe.
		  * @param pName - Attribute-Name.
		  * @param pAttrs - Attributes.
		  * @return - Attribute Value in QString, or empty QString.
		  * @throws - no exceptions.
		**/
		static QString getAttribute( const QString & pName, const QXmlAttributes & pAttrs ) noexcept;

		/**
		  * Search tmp. value.
		  *
		  * @threadsafe - not thread-safe.
		  * @param pName - Value-Name ("url", "domain", "link", etc).
		  * @return - QString with value, or empty.
		  * @throws - no exceptions.
		**/
		QString getValue( const QString & pName ) const noexcept;

		// -----------------------------------------------------------

	public:

		// -----------------------------------------------------------

		// ===========================================================
		// CONSTRUCTOR
		// ===========================================================

		/**
		  * SAXRSSHandler constructor.
		  *
		  * @param pChannel - Channel-class to update directly.
		  * @param pModel - ChannelModel.
		  * @throws - no exceptions.
		**/
		explicit SAXRSSHandler( rss::Channel *const pChannel, rss::ChannelModel *const pModel ) noexcept;

		// ===========================================================
		// DESTRUCTOR
		// ===========================================================

		/**
		  * SAXRSSHandler destructor.
		  *
		  * @throws - no exceptions.
		**/
		virtual ~SAXRSSHandler( ) noexcept final;

		// ===========================================================
		// GETTERS
		// ===========================================================

		/**
		  * Returns RSS Channel-class instance.
		  *
		  * @threadsafe - not thread-safe.
		  * @return - Channel, or null if RSS document is invalid.
		  * @throws - no exceptions.
		**/
		rss::Channel * getChannel( ) noexcept;

		// ===========================================================
		// OVERRIDE: QXmlDefaultHandler
		// ===========================================================

		/**
		  * Called when root-Element reached (<rss>).
		  *
		  * @threadsafe - not thread-safe.
		  * @return - 'true' to continue, 'false' to stop further parsing.
		  * @throws - no exceptions.
		**/
		virtual bool startDocument( ) override;

		/**
		  * Called when element has been read.
		  *
		  * @threadsafe - not thread-safe.
		  * @param namespaceURI - Namespace.
		  * @param locaName - Element-Name with Namespace-prefix.
		  * @param qName - Element-Name (<rss>).
		  * @param pAttrs - Attributes.
		  * @return - 'true' to OK, 'false' if error.
		  * @throws - no exceptions.
		**/
		bool startElement( const QString& namespaceURI, const QString & localName, const QString & qName, const QXmlAttributes & pAttrs ) override;

		/**
		  * Called when end of Element reached (</rss>).
		  *
		  * @threadsafe - not thread-safe.
		  * @param namespaceURI - Namespace.
		  * @param locaName - Element-Name with Namespace-prefix.
		  * @param qName - Element-Name (<rss>).
		  * @return - 'true' to OK, 'false' if error.
		  * @throws - no exceptions.
		**/
		bool endElement(const QString& namespaceURI, const QString& localName, const QString& qName) override;

		/**
		  * Called when Text collected from Element
		  * (<link>https://some_site.ko.kr/news/q93ihfrq3h0.html</link>)
		  *
		  * @threadsafe - not thread-safe.
		  * @param pText - Characters.
		  * @throws - no exceptions.
		**/
		bool characters( const QString& pText ) override;

		/**
		  * Called when document-end reached (</rss>).
		  *
		  * @threadsafe - not thread-safe.
		  * @return - 'true' to OK, 'false' if error.
		  * @throws - no exceptions.
		**/
		virtual bool endDocument( ) override;

		/**
		  * Called when none-critical xml event occured.
		  *
		  * @threadsafe - not thread-safe.
		  * @param exception - exception details.
		  * @returns - 'false' to stop parsing, 'true' to ignore & continue.
		  * @throws - no exceptions.
		**/
		virtual bool warning(const QXmlParseException& exception) override;

		/**
		  * Called when xml error-event occured.
		  *
		  * @threadsafe - not thread-safe.
		  * @param exception - exception details.
		  * @returns - 'false' to stop parsing, 'true' to ignore & continue.
		  * @throws - no exceptions.
		**/
		virtual bool error(const QXmlParseException& exception) override;

		/**
		  * Called when critical (fatal) xml error occured.
		  *
		  * @threadsafe - not thread-safe.
		  * @param exception - exception details.
		  * @returns - 'false' to stop parsing, 'true' to ignore & continue.
		  * @throws - no exceptions.
		**/
		virtual bool fatalError(const QXmlParseException& exception) override;

		// -----------------------------------------------------------

	}; // rss::SAXRSSHandler

	// -----------------------------------------------------------

} // rss

// -----------------------------------------------------------

#endif // !QRSS_READER_SAX_RSS_HANDLER_HPP
