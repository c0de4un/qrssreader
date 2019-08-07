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
#ifndef QRSS_READER_DATE_HPP
#include "Date.hpp"
#endif // !QRSS_READER_DATE_HPP

// ===========================================================
// Date
// ===========================================================

namespace rss
{

	// -----------------------------------------------------------

	// ===========================================================
	// CONSTRUCTOR
	// ===========================================================

	/**
	  * Date constructor.
	  *
	  * @param pDate - QString with Date.
	  * @param parentElement - Parent-Element.
	  * @param pType - Element-Type, default is PubDate.
	  * @throws - no exceptions.
	**/
	Date::Date( const QString & pDate, Element *const parentElement, const Element::Type pType ) noexcept
		: Element ( pType, parentElement ),
		  mStringDate( pDate )
	{
	}

	// ===========================================================
	// DESTRUCTOR
	// ===========================================================

	/**
	  * Date destructor.
	  *
	  * @throws - no exceptions.
	**/
	Date::~Date( ) noexcept = default;

	// ===========================================================
	// METHODS
	// ===========================================================

	/**
	  * Returns 'true' if src-Date is newer then dst-Date.
	  *
	  * @threadsafe - not thread-safe.
	  * @param srcDate - Date #1.
	  * @param dstDate - Date #2.
	  * @throws - no exceptions.
	**/
	bool Date::isNewer( const Date *const srcDate, const Date *const dstDate ) noexcept
	{

		// src-Date.
		QDate date_1( QDate::fromString( srcDate->mStringDate ) );

		// dst-Date.
		QDate date_2( QDate::fromString( dstDate->mStringDate ) );

		// Comapre.
		return( date_1 > date_2 );

	}

	// -----------------------------------------------------------

} // rss

// -----------------------------------------------------------
