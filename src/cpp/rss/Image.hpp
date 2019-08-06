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

#ifndef QRSS_READER_IMAGE_HPP
#define QRSS_READER_IMAGE_HPP

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
// Image
// ===========================================================

namespace rss
{

	/**
	  * Image - struct to store Image RSS-Element data.
	  *
	  * @brief
	  * Image - sub-Element of a Channel, has url, title, description, link, width & height sub-Elements.
	  *
	  * @version 1.0
	  * @since 21.07.2019
	  * @authors Denis Z. (code4un@yandex.ru)
	**/
	struct Image final : public Element
	{

		// -----------------------------------------------------------

		// ===========================================================
		// CONSTANTS
		// ===========================================================

		/** Url. **/
		const QUrl *const url;

		/** Link. **/
		const QUrl *const link;

		/** Title. **/
		const QString *const title;

		/** Description. **/
		const QString *const description;

		/** Width. **/
		const int width;

		/** Height. **/
		const int height;

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
		explicit Image( Element *const parentElement, const QUrl *const pUrl,
						const QUrl *const pLink, const QString *const pTitle,
						const QString *const pDescription, const int pWidth, const int pHeight ) noexcept;

		// ===========================================================
		// DESTRUCTOR
		// ===========================================================

		/**
		  * Image destructor.
		  *
		  * @throws - no exceptions.
		**/
		virtual ~Image( ) noexcept final;

		// -----------------------------------------------------------

	private:

		// -----------------------------------------------------------

		// ===========================================================
		// DELETED CONSTRUCTORS & OPERATORS
		// ===========================================================

		/** @deleted Image const copy constructor. **/
		Image( const Image & ) noexcept = delete;

		/** @deleted Image copy-assignment operator. **/
		Image & operator=( const Image & ) noexcept = delete;

		/** @deleted Image move constructor. **/
		Image( Image && ) noexcept = delete;

		/** @deleted Image move assignment operator. **/
		Image & operator=( Image && ) noexcept = delete;

		// -----------------------------------------------------------

	}; // rss::Image

} // rss

#define QRSS_READER_IMAGE_DECL

// -----------------------------------------------------------

#endif // !QRSS_READER_IMAGE_HPP
