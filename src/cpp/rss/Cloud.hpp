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

#ifndef QRSS_READER_CLOUD_HPP
#define QRSS_READER_CLOUD_HPP

// -----------------------------------------------------------

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

// ===========================================================
// CLOUD
// ===========================================================

namespace rss
{

	// -----------------------------------------------------------

	struct Cloud final : public Element
	{

		// -----------------------------------------------------------

		// ===========================================================
		// CONSTANTS
		// ===========================================================

		/** Domain. **/
		const QUrl domain;

		/** Port. **/
		const int port;

		/** Path. **/
		const QString path;

		/** Register-Procedure. **/
		const QString registerProcedure;

		/** Protocol. **/
		const QString protocol;

		// ===========================================================
		// CONSTRUCTOR
		// ===========================================================

		/**
		  * Cloud constructor.
		  *
		  * @param pDomain - Url to RSS-Cloud Web-Service (HTTP-POST, XML-RPC or SOAP 1.1).
		  * @param parentElement - Parent-Element.
		  * @param pPort - Port.
		  * @param pPath - Path.
		  * @param registerProcedure - Register Procedure Name.
		  * @param pProtocol - Protocol (xml-rpc, soap, etc).
		  * @throws - no exceptions.
		**/
		explicit Cloud( const QString & pDomain_, Element *const parentElement, const int pPort_, const QString & pPath_, const QString registerProcedure_, const QString pProtocol_ ) noexcept;

		/**
		  * Cloud constructor.
		  *
		  * @param pDomain - Url to RSS-Cloud Web-Service (HTTP-POST, XML-RPC or SOAP 1.1).
		  * @param parentElement - Parent-Element.
		  * @param pPort - Port.
		  * @param pPath - Path.
		  * @param registerProcedure - Register Procedure Name.
		  * @param pProtocol - Protocol (xml-rpc, soap, etc).
		  * @throws - no exceptions.
		**/
		explicit Cloud( const QUrl & pDomain_, Element *const parentElement, const int pPort_, const QString & pPath_, const QString registerProcedure_, const QString pProtocol_ ) noexcept;

		// ===========================================================
		// DESTRUCTOR
		// ===========================================================

		/**
		  * Cloud destructor.
		  *
		  * @throws - no exceptions.
		**/
		virtual ~Cloud( ) noexcept final;

		// -----------------------------------------------------------

	private:

		// -----------------------------------------------------------

		// ===========================================================
		// DELETED CONSTRUCTORS & OPERATORS
		// ===========================================================

		/** @deleted Cloud const copy constructor. **/
		Cloud( const Cloud & ) noexcept = delete;

		/** @deleted Cloud copy-assignment operator. **/
		Cloud & operator=( const Cloud & ) noexcept = delete;

		/** @deleted Cloud move constructor. **/
		Cloud( Cloud && ) noexcept = delete;

		/** @deleted Cloud move assignment operator. **/
		Cloud & operator=( Cloud && ) noexcept = delete;

		// -----------------------------------------------------------

	}; // rss::Cloud

	// -----------------------------------------------------------

} // rss

#define QRSS_READER_CLOUD_DECL

// -----------------------------------------------------------

#endif // !QRSS_READER_CLOUD_HPP
