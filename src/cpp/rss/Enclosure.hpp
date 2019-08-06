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

#ifndef QRSS_READER_ENCLOSURE_HPP
#define QRSS_READER_ENCLOSURE_HPP

// -----------------------------------------------------------

// Include QTGlobal
#ifndef QGLOBAL_H
#include <QtGlobal> // QT_VERSION_CHECK
#endif // !QGLOBAL_H

// QT 5+ Required
#if ( QT_VERSION < QT_VERSION_CHECK( 5, 0, 0 ) )
#error "Enclosure.hpp - QT 5+ required !"
#endif // QT 5-

// ===========================================================
// INCLUDES
// ===========================================================

// Include rss::Element
#ifndef QRSS_READER_ELEMENT_HPP
#include "Element.hpp"
#endif // !QRSS_READER_ELEMENT_HPP

// Include QString
#ifndef QSTRING_H
#include <QString>
#endif // !QSTRING_H

// Include QUrl
#ifndef QURL_H
#include <QUrl>
#endif // !QURL_H

// Include QMimeType
#ifndef QMIMETYPE_H
#include <QMimeType>
#endif // !QMIMETYPE_H

// Include QMimeDatabase
#ifndef QMIMEDATABASE_H
#include <QMimeDatabase>
#endif // !QMIMEDATABASE_H

// ===========================================================
// Enclosure
// ===========================================================

namespace rss
{

	// -----------------------------------------------------------

	/**
	  * Enclosure - Enclosure Element of RSS Channel's Item.
	  *
	  * @brief
	  * Enclosure - contains media.
	  *
	  * @version 1.0
	  * @since 21.07.2019
	  * @authors Denis Z. (code4un@yandex.ru)
	**/
	struct Enclosure final : public Element
	{

		// -----------------------------------------------------------

		// ===========================================================
		// CONSTANTS
		// ===========================================================

		/** Url. **/
		const QUrl url;

		/** Length in Bytes. **/
		const qlonglong length;

		/** MIME-Type. **/
		const QMimeType mimeType;

		// ===========================================================
		// CONSTRUCTOR
		// ===========================================================

		/**
		  * Enclosure constructor.
		  *
		  * @param pUrl - Url to a data.
		  * @param parentElement - Parent-Element.
		  * @param pLength - data length in bytes.
		  * @param mimeType - MIME-Type.
		  * @throws - no exceptions.
		**/
		explicit Enclosure( const QString & pUrl, Element *const parentElement, const QString & pLength, const QString & mimeType ) noexcept;

		// ===========================================================
		// DESTRUCTOR
		// ===========================================================

		/**
		  * Enclosure destructor.
		  *
		  * @throws - no exceptions.
		**/
		virtual ~Enclosure( ) noexcept final;

		// ===========================================================
		// GETTERS & SETTERS
		// ===========================================================

		/**
		  * Converts (casts) QString of MIME-TYPE Name to a QMimeType.
		  *
		  * @thread_safety - not required.
		  * @param mimeType - QString with a Name of QMimeType.
		  * @returns - QMimeType.
		  * @throws - no exceptions.
		**/
		static QMimeType getMimeTypeFromString( const QString & mimeType ) noexcept;

		// -----------------------------------------------------------

	private:

		// -----------------------------------------------------------

		// ===========================================================
		// DELETED CONSTRUCTORS & OPERATORS
		// ===========================================================

		/** @deleted Enclosure const copy constructor. **/
		Enclosure( const Enclosure & ) noexcept = delete;

		/** @deleted Enclosure copy-assignment operator. **/
		Enclosure & operator=( const Enclosure & ) noexcept = delete;

		/** @deleted Enclosure move constructor. **/
		Enclosure( Enclosure && ) noexcept = delete;

		/** @deleted Enclosure move assignment operator. **/
		Enclosure & operator=( Enclosure && ) noexcept = delete;

		// -----------------------------------------------------------

	}; // rss::Enclosure

	// -----------------------------------------------------------

} // rss

#define QRSS_READER_ENCLOSURE_DECL

// -----------------------------------------------------------

#endif // !QRSS_READER_ENCLOSURE_HPP
