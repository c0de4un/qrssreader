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
#ifndef QRSS_READER_SOURCE_HPP
#include "Source.hpp"
#endif // !QRSS_READER_SOURCE_HPP

// ===========================================================
// Source
// ===========================================================

namespace rss
{

	// -----------------------------------------------------------

	// ===========================================================
	// CONSTRUCTOR
	// ===========================================================

	/**
	  * Source constructor.
	  *
	  * @param pUrl - Url.
	  * @param pText - Text.
	  * @param parentElement - Parent-Element.
	  * @param elementType - Element-Type.
	  * @throws - no exceptions.
	**/
	Source::Source( const QString & pUrl, const QString & pText, Element *const parentElement, const ElementType elementType ) noexcept
		: Element( elementType, parentElement ),
		  url( pUrl ),
		  text( pText )
	{ }

	// ===========================================================
	// DESTRUCTOR
	// ===========================================================

	/**
	  * Source destructor.
	  *
	  * @throws - no exceptions.
	**/
	Source::~Source( ) noexcept = default;

	// -----------------------------------------------------------

} // rss

// -----------------------------------------------------------
