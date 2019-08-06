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
#ifndef QRSS_READER_SAX_RSS_HANDLER_HPP
#include "SAXRSSHandler.hpp"
#endif // !QRSS_READER_SAX_RSS_HANDLER_HPP

// Include rss::Channel
#ifndef QRSS_READER_CHANNEL_HPP
#include "../rss/Channel.hpp"
#endif // !QRSS_READER_CHANNEL_HPP

// Include rss::Category
#ifndef QRSS_READER_SOURCE_HPP
#include "../rss/Source.hpp"
#endif // !QRSS_READER_SOURCE_HPP

// Include rss::Cloud
#ifndef QRSS_READER_CLOUD_HPP
#include "../rss/Cloud.hpp"
#endif // !QRSS_READER_CLOUD_HPP

// Include rss::Date
#ifndef QRSS_READER_DATE_HPP
#include "../rss/Date.hpp"
#endif // !QRSS_READER_DATE_HPP

// Include rss::Enclosure
#ifndef QRSS_READER_ENCLOSURE_HPP
#include "../rss/Enclosure.hpp"
#endif // !QRSS_READER_ENCLOSURE_HPP

// Include rss::Integer
#ifndef QRSS_READER_INTEGER_HPP
#include "../rss/Integer.hpp"
#endif // !QRSS_READER_INTEGER_HPP

// Include rss::Item
#ifndef QRSS_READER_ITEM_HPP
#include "../rss/Item.hpp"
#endif // !QRSS_READER_ITEM_HPP

// Include rss::Image
#ifndef QRSS_READER_IMAGE_HPP
#include "../rss/Image.hpp"
#endif // !QRSS_READER_IMAGE_HPP

// Include rss::Link
#ifndef QRSS_READER_LINK_HPP
#include "../rss/Link.hpp"
#endif // !QRSS_READER_LINK_HPP

// Include rss::Text
#ifndef QRSS_READER_TEXT_HPP
#include "../rss/Text.hpp"
#endif // !QRSS_READER_TEXT_HPP

// Include rss::TextInput
#ifndef QRSS_READER_TEXT_INPUT_HPP
#include "../rss/TextInput.hpp"
#endif // !QRSS_READER_TEXT_INPUT_HPP

#if defined( QT_DEBUG ) // DEBUG
#include <QDebug>
#endif // DEBUG

// ===========================================================
// rss::SAXRSSHandler
// ===========================================================

namespace rss
{

	// -----------------------------------------------------------

	// ===========================================================
	// CONSTRUCTOR
	// ===========================================================

	/**
	  * SAXRSSHandler constructor.
	  *
	  * @param pChannel - Channel-class to update directly.
	  * @throws - no exceptions.
	**/
	SAXRSSHandler::SAXRSSHandler( rss::Channel *const pChannel ) noexcept
		: mChannel( pChannel ),
		  mCurrState( SAXRSSHandler::RSSPosition::RSS_CHANNEL_OPEN ),
		  mPrevState( SAXRSSHandler::RSSPosition::RSS_CHANNEL_OPEN ),
		  mValues( ),
		  mItem( )
	{ }

	// ===========================================================
	// DESTRUCTOR
	// ===========================================================

	/**
	  * SAXRSSHandler destructor.
	  *
	  * @throws - no exceptions.
	**/
	SAXRSSHandler::~SAXRSSHandler( ) noexcept
	{

		// Delete Channel Instance.
		if ( mChannel != nullptr )
			delete mChannel;

	}

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
	rss::Channel * SAXRSSHandler::getChannel( ) noexcept
	{
		// Copy-pointer-value.
		rss::Channel *const result_( mChannel );

		// Reset Channel-pointer.
		mChannel = nullptr;

		// Return RSS Channel-class Instance.
		return( result_ );
	}

	/**
	  * Search Attribute.
	  *
	  * @threadsafe - not thread-safe.
	  * @param pName - Attribute-Name.
	  * @param pAttrs - Attributes.
	  * @return - Attribute Value in QString, or empty QString.
	  * @throws - no exceptions.
	**/
	QString SAXRSSHandler::getAttribute( const QString & pName, const QXmlAttributes & pAttrs ) noexcept
	{

		// Attributes count.
		const auto attrsCount( pAttrs.count( ) );

		// Search Attribute.
		for( auto i = 0; i < attrsCount; i++ )
		{

			// Compare Attribute-Name
			if ( pAttrs.localName( i ) == pName )
				return( pAttrs.value( i ) );

		} /// Search Attribute

		// Return empty.
		return( QString( ) );

	} /// SAXRSSHandler::getAttribute

	/**
	  * Search tmp. value.
	  *
	  * @threadsafe - not thread-safe.
	  * @param pName - Value-Name ("url", "domain", "link", etc).
	  * @return - QString with value, or empty.
	  * @throws - no exceptions.
	**/
	QString SAXRSSHandler::getValue( const QString & pName ) const noexcept
	{

		// Search value.
		auto valuePos_ = mValues.find( pName );

		// Return
		return( valuePos_ != mValues.cend( ) ? valuePos_.value( ) : QString( ) );

	} /// SAXRSSHandler::getValue

	// ===========================================================
	// OVERRIDE: QXmlDefaultHandler
	// ===========================================================

	/**
	  * Called when none-critical xml event occured.
	  *
	  * @threadsafe - not thread-safe.
	  * @param exception - exception details.
	  * @returns - 'false' to stop parsing, 'true' to ignore & continue.
	  * @throws - no exceptions.
	**/
	bool SAXRSSHandler::warning( const QXmlParseException& exception )
	{

#if defined( QT_DEBUG ) // DEBUG
		// Debug
		qDebug( ) << "SAXRSSHandler::warning=" << exception.message( );
#endif // DEBUG

		return( true );

	}

	/**
	  * Called when xml error-event occured.
	  *
	  * @threadsafe - not thread-safe.
	  * @param exception - exception details.
	  * @returns - 'false' to stop parsing, 'true' to ignore & continue.
	  * @throws - no exceptions.
	**/
	bool SAXRSSHandler::error( const QXmlParseException& exception )
	{

#if defined( QT_DEBUG ) // DEBUG
		// Debug
		qDebug( ) << "SAXRSSHandler::error=" << exception.message( );
#endif // DEBUG

		return( false );
	}

	/**
	  * Called when critical (fatal) xml error occured.
	  *
	  * @threadsafe - not thread-safe.
	  * @param exception - exception details.
	  * @returns - 'false' to stop parsing, 'true' to ignore & continue.
	  * @throws - no exceptions.
	**/
	bool SAXRSSHandler::fatalError( const QXmlParseException& exception )
	{
#if defined( QT_DEBUG ) // DEBUG
		// Debug
		qDebug( ) << "SAXRSSHandler::fatalError=" << exception.message( );
#endif // DEBUG

		return( false );
	}

	/**
	  * Called when root-Element reached (<rss>).
	  *
	  * @threadsafe - not thread-safe.
	  * @return - 'true' to continue, 'false' to stop further parsing.
	  * @throws - no exceptions.
	**/
	bool SAXRSSHandler::startDocument( )
	{

#if defined( QT_DEBUG ) // DEBUG
		// Debug
		qDebug( ) << "SAXRSSHandler::startDocument";
#endif // DEBUG

		// Return TRUE
		return( true );

	} /// SAXRSSHandler::startDocument

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
	bool SAXRSSHandler::startElement( const QString& namespaceURI, const QString & localName, const QString & qName, const QXmlAttributes & pAttrs )
	{

		Q_UNUSED( namespaceURI )
		Q_UNUSED( localName )

#if defined( QT_DEBUG ) // DEBUG
		// Debug
		qDebug( ) << "SAXRSSHandler::startElement: " << qName;
#endif // DEBUG

		// <channel>
		if ( qName == "channel" )
		{

			// Create new Channel.
			if ( mChannel == nullptr )
				mChannel = new rss::Channel( );

			// Set State.
			mCurrState = RSSPosition::RSS_CHANNEL_OPEN;

			// Stop
			return( true );

		} /// <channel>

		// <width>
		if ( qName == "width" )
		{

			// State
			if ( mCurrState == RSS_CHANNEL_IMAGE )
				mCurrState = RSS_CHANNEL_IMAGE_WIDTH;

			// Stop
			return( true );

		} /// <width>

		// <height>
		if ( qName == "height" )
		{

			// State
			if ( mCurrState == RSS_CHANNEL_IMAGE )
				mCurrState = RSS_CHANNEL_IMAGE_HEIGHT;

			// Stop
			return( true );

		} /// <height>

		// <item>
		if ( qName == "item" )
		{

			// Set State
			mCurrState = RSSPosition::RSS_ITEM_OPEN;

			// Create Item.
			mItem = new rss::Item( mChannel );

			// Stop
			return( true );

		} /// <item>

		// <source>
		if ( qName == "source" )
		{

			// Item
			if ( mCurrState == RSS_ITEM_OPEN )
			{

				// Get domain.
				mValues["url"] = getAttribute( "url", pAttrs );

				// Set State.
				mCurrState = RSS_ITEM_SOURCE;

				// Stop
				return( true );

			} /// Item

		} /// <source>

		// <lastBuildDate>
		if ( qName == "lastBuildDate" )
		{

			// State
			if ( mCurrState == RSS_CHANNEL_OPEN )
				mCurrState = RSS_CHANNEL_LAST_BUILD_DATE;

		} /// <lastBuildDate>

		// <guid>
		if ( qName == "guid" )
		{

			// Item
			if ( mCurrState == RSS_ITEM_OPEN )
				mCurrState = RSS_ITEM_GUID;

			// Stop
			return( true );

		} /// <guid>

		// <pubDate>
		if ( qName == "pubDate" )
		{

			// Item
			if ( mCurrState == RSS_ITEM_OPEN )
				mCurrState = RSS_ITEM_PUB_DATE;

			// Stop
			return( true );

		} /// <pubDate>

		// <comments>
		if ( qName == "comments" )
		{

			// Item
			if ( mCurrState == RSS_ITEM_OPEN )
				mCurrState = RSS_ITEM_COMMENTS;

			// Stop
			return( true );

		} /// <comments>

		// <enclosure>
		if ( qName == "enclosure" && mCurrState == RSS_ITEM_OPEN )
		{

			// Url
			const QString url_( getAttribute( "url", pAttrs ) );

			// Length
			const QString length_( getAttribute( "length", pAttrs ) );

			// Type
			const QString type_( getAttribute( "type", pAttrs ) );

			// Add Enclosure Element to a Item.
			if ( !url_.isEmpty( ) )
				mItem->setElement( new rss::Enclosure( url_, mItem, length_, type_ ) );

			// Stop
			return( true );

		} /// <enclosure>

		// <category>
		if ( qName == "category" )
		{

			// Get domain.
			mValues["domain"] = getAttribute( "domain", pAttrs );

			// Set State.
			if ( mCurrState == RSS_CHANNEL_OPEN )
				mCurrState = RSS_CHANNEL_CATEGORY;
			else if ( mCurrState == RSS_ITEM_OPEN )
				mCurrState = RSS_ITEM_CATEGORY;

			// Stop
			return( true );

		} /// <category>

		// <name>
		if ( qName == "name" )
		{

			// Channel TextInput
			if ( mCurrState == RSS_CHANNEL_TEXT_INPUT )
				mCurrState = RSS_CHANNEL_TEXT_INPUT_NAME;

			// Stop
			return( true );

		} /// <name>

		// <image>
		if ( qName == "image" )
		{

			// State
			if ( mCurrState == RSS_CHANNEL_OPEN )
				mCurrState = RSS_CHANNEL_IMAGE;

			// Stop
			return( true );

		} /// <image>

		// <title>
		if ( qName == "title" )
		{

			// Channel
			if ( mCurrState == RSSPosition::RSS_CHANNEL_OPEN )
				mCurrState = RSSPosition::RSS_CHANNEL_TITLE; // Set State.
			else if ( mCurrState == RSSPosition::RSS_ITEM_OPEN ) // Item
				mCurrState = RSSPosition::RSS_ITEM_TITLE; // Set State.
			else if ( mCurrState == RSSPosition::RSS_CHANNEL_TEXT_INPUT )
				mCurrState = RSSPosition::RSS_CHANNEL_TEXT_INPUT_TITLE;

			// Stop
			return( true );

		} /// Title

		// <cloud>
		if ( qName == "cloud" )
		{

			// Channel
			if ( mCurrState == RSSPosition::RSS_CHANNEL_OPEN )
			{

				// domain
				const QString domain_( getAttribute( "domain", pAttrs ) );

				// Cancel, if domain not set.
				if ( domain_.isEmpty( ) )
					return( true );

				// port
				const QString attrValue_( getAttribute( "port", pAttrs ) );

				// port
				const int port_( attrValue_.isEmpty( ) ? 80 : attrValue_.toInt( ) );

				// path
				const QString path_( getAttribute( "path", pAttrs ) );

				// registerProcedure
				const QString registerProcedure_( getAttribute( "registerProcedure", pAttrs ) );

				// protocol
				const QString protocol_( getAttribute( "protocol", pAttrs ) );

				// Create Cloud-Element class instance.
				rss::Cloud *const cloud_( new rss::Cloud( domain_, mChannel, port_, path_, registerProcedure_, protocol_ ) );

				// Add Cloud-Element to a Channel.
				mChannel->setElement( cloud_ );

			} /// Channel

			// Stop
			return( true );

		} /// <cloud>

		// <ttl>
		if ( qName == "ttl" )
		{

			// Set State.
			mCurrState = RSSPosition::RSS_CHANNEL_TTL;

		} /// <ttl>

		// <description>
		if ( qName == "description" )
		{

			// Channel
			if ( mCurrState == RSSPosition::RSS_CHANNEL_OPEN )
				mCurrState = RSSPosition::RSS_CHANNEL_DESCRIPTION;
			else if ( mCurrState == RSSPosition::RSS_ITEM_OPEN ) // Item
				mCurrState = RSSPosition::RSS_ITEM_DESCRIPTION;
			else if ( mCurrState == RSSPosition::RSS_CHANNEL_TEXT_INPUT )
				mCurrState = RSSPosition::RSS_CHANNEL_TEXT_INPUT_DESCRIPTION;
			else if ( mCurrState == RSSPosition::RSS_CHANNEL_IMAGE )
				mCurrState = RSSPosition::RSS_CHANNEL_IMAGE_DESCRIPTION;

			// Stop
			return( true );

		} /// <description>

		// <textInput>
		if ( qName == "textInput" )
		{

			// Set State
			if ( mCurrState == RSSPosition::RSS_CHANNEL_OPEN )
				mCurrState = RSSPosition::RSS_CHANNEL_TEXT_INPUT;

			// Stop
			return( true );

		} /// <textInput>

		// <skipHours>
		if ( qName == "skipHours" )
		{

			// Set State.
			if ( mCurrState == RSS_CHANNEL_OPEN )
				mCurrState = RSS_CHANNEL_SKIP_HOURS;

			// Stop
			return( true );

		} /// <skipHours>

		// <link>
		if ( qName == "link" )
		{

			// Channel
			if ( mCurrState == RSSPosition::RSS_CHANNEL_OPEN )
				mCurrState = RSSPosition::RSS_CHANNEL_LINK;
			else if ( mCurrState == RSSPosition::RSS_ITEM_OPEN ) // Item
				mCurrState = RSSPosition::RSS_ITEM_LINK;
			else if ( mCurrState == RSSPosition::RSS_CHANNEL_IMAGE )
				mCurrState = RSSPosition::RSS_CHANNEL_IMAGE_LINK;

			// Stop
			return( true );

		} /// <link>

		// <skipDays>
		if ( qName == "skipDays" )
		{

			// Set State.
			if ( mCurrState == RSS_CHANNEL_OPEN )
				mCurrState = RSS_CHANNEL_SKIP_DAYS;

			// Stop
			return( true );

		} /// <skipDays>

		// <url>
		if ( qName == "url" )
		{

			// State
			if ( mCurrState == RSS_CHANNEL_IMAGE )
				mCurrState = RSS_CHANNEL_IMAGE_URL;

		} /// <url>

		// Return TRUE
		return( true );

	} /// SAXRSSHandler::startElement

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
	bool SAXRSSHandler::endElement( const QString& namespaceURI, const QString& localName, const QString& qName )
	{

		Q_UNUSED( namespaceURI )
		Q_UNUSED( localName )
		Q_UNUSED( qName )

#if defined( QT_DEBUG ) // DEBUG
		// Debug
		qDebug( ) << "SAXRSSHandler::endElement: " << qName;
#endif // DEBUG

		// <textInput>
		if ( qName == "textInput" )
		{

			// Channel
			if ( mCurrState == RSSPosition::RSS_CHANNEL_TEXT_INPUT )
			{

				// <title>
				const QString title_( getValue( "title" ) );

				// <description>
				const QString description_( getValue( "description" ) );

				// <name>
				const QString name_( getValue( "name" ) );

				// <link>
				const QString link_( getValue( "link" ) );

				// Create TextInput Element instance.
				rss::TextInput *const textInput_( new rss::TextInput( mChannel, title_, description_, name_, link_ ) );

				// Add TextInput to Channel.
				mChannel->setElement( textInput_ );

				// Clear temp. Values.
				mValues.clear( );

				// Set State.
				mCurrState = RSS_CHANNEL_OPEN;

			} /// Channel

		} /// <textInput>

		// <image>
		if ( qName == "image" )
		{

			// Channel
			if ( mCurrState == RSSPosition::RSS_CHANNEL_IMAGE )
			{

				// Url
				const QUrl url_( getValue( "url" ) );

				// Link
				const QUrl link_( getValue( "link" ) );

				// Title-value.
				const QString title_( getValue( "title" ) );

				// Description
				const QString description_( getValue( "description" ) );

				// Width
				QString value_( getValue( "width" ) );
				const int width_( value_.isEmpty( ) ? 88 : value_.toInt( ) );

				// Height
				value_ = getValue( "height" );
				const int height_( value_.isEmpty( ) ? 31 : value_.toInt( ) );

				// Create Image Element class instance.
				rss::Image *const image_( new rss::Image( mChannel, &url_, link_.isEmpty( ) ? nullptr : &link_, title_.isEmpty( ) ? nullptr : &title_, description_.isEmpty( ) ? nullptr : &description_, width_, height_ ) );

				// Attach Image to a Channel.
				mChannel->setElement( image_ );

				// Clear values.
				mValues.clear( );

				// Set State.
				mCurrState = RSS_CHANNEL_OPEN;

			} /// Channel

		} /// <image>

		// </item>
		if ( qName == "item" && mItem != nullptr )
		{

			// Add Item to a Channel.
			mChannel->addItem( mItem );

			// Reset
			mItem = nullptr;

			// State
			mCurrState = RSS_CHANNEL_OPEN;

		} /// </item>

		// Return TRUE
		return( true );

	} /// SAXRSSHandler::endElement

	/**
	  * Called when Text collected from Element
	  * (<link>https://some_site.ko.kr/news/q93ihfrq3h0.html</link>)
	  *
	  * @threadsafe - not thread-safe.
	  * @param pText - Characters.
	  * @throws - no exceptions.
	**/
	bool SAXRSSHandler::characters( const QString& pText )
	{

#if defined( QT_DEBUG ) // DEBUG
		// Debug
		qDebug( ) << "SAXRSSHandler::characters: " << pText;
#endif // DEBUG

		// Handle RSS-Document Parsing State (Position).
		switch( mCurrState )
		{

		// skipHours
		case RSS_CHANNEL_SKIP_HOURS:
		{

			// Add Element to a Channel.
			mChannel->setElement( new rss::SkipHours( pText, mChannel, rss::ElementType::SKIP_HOURS ) );

			// Set State.
			mCurrState = RSS_CHANNEL_OPEN;

			// Stop
			break;

		} /// skipHours

		// skipDays
		case RSS_CHANNEL_SKIP_DAYS:
		{

			// Add Element to a Channel.
			mChannel->setElement( new rss::SkipDays( pText, mChannel, rss::ElementType::SKIP_DAYS ) );

			// Set State.
			mCurrState = RSS_CHANNEL_OPEN;

			// Stop
			break;

		} /// skipDays

		// Channel Build Date.
		case RSS_CHANNEL_LAST_BUILD_DATE:
		{

			// Get current Build-Date Element.
			rss::LastBuildDate *const buildDate_element( static_cast<rss::LastBuildDate*>( mChannel->getElement( rss::ElementType::LAST_BUILD_DATE ) ) );

			// Compare Build-Dates.
			if ( buildDate_element != nullptr && buildDate_element->mStringDate != pText )
				mChannel->setElement( new rss::LastBuildDate( pText, mChannel, rss::ElementType::LAST_BUILD_DATE ) );

			// Set State.
			mCurrState = RSS_CHANNEL_OPEN;

			// Stop
			break;

		} /// Channel Build Date.

		// Channel Title
		case RSS_CHANNEL_TITLE:
		{

			// Add Title Element to a Channel.
			mChannel->setElement( new rss::Title( pText, mChannel, rss::ElementType::TITLE ) );

			// Set State.
			mCurrState = RSS_CHANNEL_OPEN;

			// Stop
			break;

		} /// Channel Title

		// Item Title.
		case RSS_ITEM_TITLE:
		{

			// Add Title Element to a Item.
			mItem->setElement( new rss::Title( pText, mItem, rss::ElementType::TITLE ) );

			// Set State.
			mCurrState = RSS_ITEM_OPEN;

			// Stop
			break;

		} /// Item Title.

		// Item Link.
		case RSS_ITEM_LINK:
		{

			// Add Element to a Item.
			mItem->setElement( new rss::Link( pText, mItem, rss::ElementType::LINK ) );

			// Set State.
			mCurrState = RSS_ITEM_OPEN;

			// Stop
			break;

		} /// Item Link.

		// RSS Item Comments
		case RSS_ITEM_COMMENTS:
		{

			// Add Element to a Item.
			mItem->setElement( new rss::Comments( pText, mItem, rss::ElementType::COMMENTS ) );

			// Set State.
			mCurrState = RSS_ITEM_OPEN;

			// Stop
			break;

		} /// RSS Item Comments

		// Item Category
		case RSS_ITEM_CATEGORY:
		{

			// Get Category Domain.
			const QString domain_( getValue( "domain" ) );

			// Create Category Element intsance.
			rss::Category *const category( new rss::Category( domain_, pText, mItem, rss::ElementType::CATEGORY ) );

			// Attach Category Element to a Item.
			mItem->setElement( category );

			// Set State
			mCurrState = RSS_ITEM_OPEN;

			// Clear Values.
			mValues.clear( );

			// Stop
			break;

		} /// Item Category

		// Item pubDate.
		case RSS_ITEM_PUB_DATE:
		{

			// Add Element.
			mItem->setElement( new rss::PubDate( pText, mItem, rss::ElementType::PUB_DATE ) );

			// Set State
			mCurrState = RSS_ITEM_OPEN;

			// Stop
			break;

		} /// Item pubDate

		// Item Source.
		case RSS_ITEM_SOURCE:
		{

			// Add Element.
			mItem->setElement( new rss::Source( getValue( "url" ), pText, mItem, rss::ElementType::SOURCE ) );

			// Set State
			mCurrState = RSS_ITEM_OPEN;

			// Clear Values.
			mValues.clear( );

			// Stop
			break;

		} /// Item Source

		// Item GUID
		case RSS_ITEM_GUID:
		{

			// Add Element.
			mItem->setElement( new rss::GUID( pText, mItem, rss::ElementType::GUID ) );

			// Set State
			mCurrState = RSS_ITEM_OPEN;

			// Stop.
			break;

		} /// Item GUID

		// Channel Description.
		case RSS_CHANNEL_DESCRIPTION:
		{

			// Add Description Element to a Channel.
			mChannel->setElement( new rss::Description( pText, mChannel, rss::ElementType::DESCRITION ) );

			// Set State.
			mCurrState = RSS_CHANNEL_OPEN;

			// Stop
			break;

		} /// Channel Description.

		// Item Description.
		case RSS_ITEM_DESCRIPTION:
		{

			// Add Description Element to a Item.
			mItem->setElement( new rss::Description( pText, mItem, rss::ElementType::DESCRITION ) );

			// Set State.
			mCurrState = RSS_ITEM_OPEN;

			// Stop
			break;

		} /// Item Description.

		// Channel TTL.
		case RSS_CHANNEL_TTL:
		{

			// Get Integer-value.
			const int ttl_( pText.toInt( ) );

			// Add TTL Element
			mChannel->setElement( new rss::TTL( ttl_, mChannel, rss::ElementType::TTL ) );

			// Set State.
			mCurrState = RSS_CHANNEL_OPEN;

			// Stop
			break;

		} /// Channel TTL.

		// Channel Image Link
		case RSS_CHANNEL_IMAGE_LINK:
		{

			// Cache value.
			mValues.insert( "link", pText );

			// Set State.
			mCurrState = RSS_CHANNEL_IMAGE;

			// Stop
			break;

		} /// Channel Image Link

		// Channel Image Description
		case RSS_CHANNEL_IMAGE_DESCRIPTION:
		{

			// Cache value.
			mValues.insert( "description", pText );

			// Set State.
			mCurrState = RSS_CHANNEL_IMAGE;

			// Stop
			break;

		} /// Channel Image Description

		// Image Url
		case RSS_CHANNEL_IMAGE_URL:
		{

			// Cache value.
			mValues["url"] = pText;

			// Set State.
			mCurrState = RSS_CHANNEL_IMAGE;

			// Stop
			break;

		} /// Channel Image Url

		// Channel Image Width
		case RSS_CHANNEL_IMAGE_WIDTH:
		{

			// Cache value.
			mValues.insert( "width", pText );

			// Set State.
			mCurrState = RSS_CHANNEL_IMAGE;

			// Stop
			break;

		} /// Channel Image Width

		// Channel Image Height
		case RSS_CHANNEL_IMAGE_HEIGHT:
		{

			// Cache value.
			mValues.insert( "height", pText );

			// Set State.
			mCurrState = RSS_CHANNEL_IMAGE;

			// Stop
			break;

		} /// Channel Image Height

		// TextInput Title
		case RSS_CHANNEL_TEXT_INPUT_TITLE:
		{

			// Cache value.
			mValues.insert( "title", pText );

			// Set State.
			mCurrState = RSS_CHANNEL_TEXT_INPUT;

			// Stop
			break;

		} /// TextInput Title

		// Channel Link.
		case RSS_CHANNEL_LINK:
		{

			// Add Link Element.
			mChannel->setElement( new rss::Link( pText, mChannel, rss::ElementType::LINK ) );

			// Set State
			mCurrState = RSS_CHANNEL_OPEN;

			// Stop
			break;

		}

		// TextInput Name
		case RSS_CHANNEL_TEXT_INPUT_NAME:
		{

			// Cache value.
			mValues.insert( "name", pText );

			// Set State.
			mCurrState = RSS_CHANNEL_TEXT_INPUT;

			// Stop
			break;

		} /// TextInput Name

		// TextInput Description
		case RSS_CHANNEL_TEXT_INPUT_DESCRIPTION:
		{

			// Cache value.
			mValues.insert( "description", pText );

			// Set State.
			mCurrState = RSS_CHANNEL_TEXT_INPUT;

			// Stop
			break;

		} /// TextInput Description

		// TextInput Link
		case RSS_CHANNEL_TEXT_INPUT_LINK:
		{

			// Cache value.
			mValues.insert( "link", pText );

			// Set State.
			mCurrState = RSS_CHANNEL_TEXT_INPUT;

			// Stop
			break;

		} /// TextInput Link


		// Default
		default:
			break;

		} /// Handle RSS-Document Parsing State (Position).

		// Return TRUE
		return( true );

	} /// SAXRSSHandler::characters

	/**
	  * Called when document-end reached (</rss>).
	  *
	  * @threadsafe - not thread-safe.
	  * @return - 'true' to OK, 'false' if error.
	  * @throws - no exceptions.
	**/
	bool SAXRSSHandler::endDocument( )
	{

#if defined( QT_DEBUG ) // DEBUG
		// Debug
		qDebug( ) << "SAXRSSHandler::endDocument";
#endif // DEBUG

		// Return TRUE
		return( true );

	} /// SAXRSSHandler::endDocument

	// -----------------------------------------------------------

} // rss

// -----------------------------------------------------------
