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
#ifndef QRSS_READER_TEXT_INPUT_HPP
#include "TextInput.hpp"
#endif // !QRSS_READER_TEXT_INPUT_HPP

// ===========================================================
// TextInput
// ===========================================================

namespace rss
{

	// -----------------------------------------------------------

	// ===========================================================
	// CONSTRUCTOR
	// ===========================================================

	/**
	  * TextInput constructor.
	  *
	  * @param pElement - Parent-Element.
	  * @param pTitle - Title.
	  * @param pDescription - Description.
	  * @param pName - Name.
	  * @param pLink - Link.
	  * @throws - no exceptions.
	**/
	TextInput::TextInput( rss::Element *const pElement, const QString & pTitle, const QString & pDescription, const QString & pName, const QString & pLink ) noexcept
		: Element( rss::ElementType::TEXT_INPUT, pElement ),
		  mTitle( pTitle.isEmpty( ) ? nullptr : new QString( pTitle ) ),
		  mDescription( pDescription.isEmpty( ) ? nullptr : new QString( pDescription ) ),
		  mName( pName.isEmpty( ) ? nullptr : new QString( pName ) ),
		  mLink( pLink.isEmpty( ) ? nullptr : new QUrl( pLink ) )
	{ }

	// ===========================================================
	// DESTRUCTOR
	// ===========================================================

	/**
	  * TextInput destructor.
	  *
	  * @throws - no exceptions.
	**/
	TextInput::~TextInput( ) noexcept
	{

		// Delete Title
		delete mTitle;

		// Delete Description
		delete mDescription;

		// Delete Name
		delete mName;

		// Delete Link
		delete mLink;

	}

	// -----------------------------------------------------------

} // rss

// -----------------------------------------------------------
