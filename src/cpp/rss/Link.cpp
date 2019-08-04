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
#ifndef QRSS_READER_LINK_HPP
#include "Link.hpp"
#endif // !QRSS_READER_LINK_HPP

// ===========================================================
// LINK
// ===========================================================

namespace rss
{

	// -----------------------------------------------------------

	// ===========================================================
	// CONSTRUCTOR
	// ===========================================================

	/**
	  * Link constructor.
	  *
	  * @param pUrl - QString with Url.
	  * @param parentElement - Parent-Element.
	  * @param pType - Element-Type, default is Link.
	  * @throws - no exceptions.
	**/
	Link::Link( const QString & pUrl, Element *const parentElement, const Element::Type pType ) noexcept
		: Element( pType, parentElement ),
		  mUrl( pUrl )
	{
	}

	// ===========================================================
	// DESTRUCTOR
	// ===========================================================

	/**
	  * Link destructor.
	  *
	  * @throws - no exceptions.
	**/
	Link::~Link( ) noexcept = default;

	// -----------------------------------------------------------

} // rss

// -----------------------------------------------------------
