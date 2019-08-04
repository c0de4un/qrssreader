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
#ifndef QRSS_READER_CLOUD_HPP
#include "Cloud.hpp"
#endif // !QRSS_READER_CLOUD_HPP

// ===========================================================
// CLOUD
// ===========================================================

namespace rss
{

	// -----------------------------------------------------------

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
	Cloud::Cloud( const QString & pDomain_, Element *const parentElement, const int pPort_, const QString & pPath_, const QString registerProcedure_, const QString pProtocol_ ) noexcept
		: Element ( Element::Type::CLOUD, parentElement ),
		  domain( pDomain_ ),
		  port( pPort_ ),
		  path( pPath_ ),
		  registerProcedure( registerProcedure_ ),
		  protocol( pProtocol_ )
	{ }

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
	Cloud::Cloud( const QUrl & pDomain_, Element *const parentElement, const int pPort_, const QString & pPath_, const QString registerProcedure_, const QString pProtocol_ ) noexcept
		: Element ( Element::Type::CLOUD, parentElement ),
		  domain( pDomain_ ),
		  port( pPort_ ),
		  path( pPath_ ),
		  registerProcedure( registerProcedure_ ),
		  protocol( pProtocol_ )
	{ }

	// ===========================================================
	// DESTRUCTOR
	// ===========================================================

	/**
	  * Cloud destructor.
	  *
	  * @throws - no exceptions.
	**/
	Cloud::~Cloud( ) noexcept = default;

	// -----------------------------------------------------------

} // rss

// -----------------------------------------------------------
