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
#ifndef QRSS_READER_IMAGE_HPP
#include "Image.hpp"
#endif // !QRSS_READER_IMAGE_HPP

// ===========================================================
// Image
// ===========================================================

namespace rss
{

	// -----------------------------------------------------------

	// ===========================================================
	// CONSTRUCTOR
	// ===========================================================

	/**
	  * Image constructor.
	  *
	  * @param parentElement - Parent-Element.
	  * @param pUrl - URL
	  * @param pLink - Link-Url, null if not used.
	  * @param pTitle - Title, null if not used.
	  * @param pDescription - Description, null if not used.
	  * @param pWidth - Width, -1 if not used.
	  * @param pHeight - Height, -1 if not used.
	  * @throws - no exceptions.
	**/
	Image::Image( Element *const parentElement, const QUrl *const pUrl,
					const QUrl *const pLink, const QString *const pTitle,
					const QString *const pDescription, const int pWidth, const int pHeight ) noexcept
		: Element( ElementType::IMAGE, parentElement ),
		  url( new QUrl( *pUrl ) ),
		  link( pLink ? new QUrl( *pLink ) : nullptr ),
		  title( pTitle ? new QString( *pTitle ) : nullptr ),
		  description( pDescription ? new QString( *pDescription ) : nullptr ),
		  width( pWidth ),
		  height( pHeight )
	{
	}

	// ===========================================================
	// DESTRUCTOR
	// ===========================================================

	/**
	  * Image destructor.
	  *
	  * @throws - no exceptions.
	**/
	Image::~Image( ) noexcept
	{

		// Delete Url.
		delete url;

		// Delete Link.
		delete link;

		// Delete Title.
		delete title;

		// Delete Description.
		delete description;

	}

	// -----------------------------------------------------------

} // rss

// -----------------------------------------------------------
