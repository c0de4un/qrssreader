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
#ifndef QRSS_READER_ENCLOSURE_HPP
#include "Enclosure.hpp"
#endif // !QRSS_READER_ENCLOSURE_HPP

// ===========================================================
// Enclosure
// ===========================================================

namespace rss
{

	// -----------------------------------------------------------

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
	Enclosure::Enclosure( const QString & pUrl, Element *const parentElement, const QString & pLength, const QString & mimeType ) noexcept
		: Element( Element::Type::ENCLOSURE, parentElement ),
		  url( pUrl ),
		  length( pLength.toLongLong( ) ),
		  mimeType( getMimeTypeFromString( mimeType ) )
	{ }

	// ===========================================================
	// DESTRUCTOR
	// ===========================================================

	/**
	  * Enclosure destructor.
	  *
	  * @throws - no exceptions.
	**/
	Enclosure::~Enclosure( ) noexcept = default;

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
	QMimeType Enclosure::getMimeTypeFromString( const QString & mimeType ) noexcept
	{

		// Get QMimeDatabase
		QMimeDatabase mimeDB;

		// Convert QString to QMimeType
		return( mimeDB.mimeTypeForName( mimeType ) );

	}

	// -----------------------------------------------------------

} // rss

// -----------------------------------------------------------
