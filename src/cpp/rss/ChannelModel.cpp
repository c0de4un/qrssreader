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

// Debug-version includes those within header.
#if !defined( QT_DEBUG ) && !defined( DEBUG ) // RELEASE

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

#endif // RELEASE

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
		: QAbstractItemModel( qParent )
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
	ChannelModel::~ChannelModel( ) noexcept = default;

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
	bool ChannelModel::setData( const QModelIndex & modelIndex, const QVariant & pValue, const int pRole )
	{

#if defined( QT_DEBUG ) || defined( DEBUG ) // DEBUG
		//
#endif // DEBUG

		// Return FALSE
		return( false );

	}

	// -----------------------------------------------------------

} // rss

// -----------------------------------------------------------
