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

#ifndef QRSS_READER_ELEMENT_HPP
#define QRSS_READER_ELEMENT_HPP

// -----------------------------------------------------------

// ===========================================================
// INCLUDES
// ===========================================================

// ===========================================================
// FORWARD-DECLARATIONS
// ===========================================================

// ===========================================================
// ELEMENT
// ===========================================================

namespace rss
{

    // -----------------------------------------------------------

    /**
      * Element - RSS Channel Element structure.
      *
      * @brief
      * Element - stores RSS Channel data, like Url, Image, Date, Input-Form, Media, etc.
      *
      * @version 1.0
      * @since 21.07.2019
      * @authors Denis Z. (code4un@yandex.ru)
    **/
    struct Element
    {

        // -----------------------------------------------------------

        // ===========================================================
        // TYPE
        // ===========================================================

        /**
          * Element::Type - enumeration (list) of Elements-Types.
          *
          * @brief
          * Element can store static data, like Date (MM::DD::YY, etc), Text (Plain-Text, Rich-Text, or even HTML),
          * & dynamic (Media, Forms, Timers). To support such variety, base (abstract)
          * structure Element used.
          * </br>
          *
          * @version 1.0
          * @since 21.07.2019
          * @authors Denis Z. (code4un@yandex.ru)
        **/
        enum Type : unsigned char
        {

            // -----------------------------------------------------------

            /** Url/Link **/
			URL = 0,

            /** Link Element **/
			LINK = 1,

            /** Title-Element (<title>Title</title>) **/
            TITLE = 2,

            /** Description-Element (<description><b>Text</b></description>) **/
            DESCRITION = 3,

            /** Language-Element (<language>ru-RU</language>) **/
            LANGUAGE = 4,

            /** Copyright-Element. **/
            COPYRIGHT = 5,

            /** Managing Editor. **/
            MANAGING_EDITOR = 6,

            /** Web-Master. **/
            WEB_MASTER = 7,

            /** Publication Date. **/
            PUB_DATE = 8,

            /** RSS Data Changed (Updated) Date. **/
            LAST_BUILD_DATE = 9,

            /** Category **/
            CATEGORY = 10,

            /** RSS Generator. **/
            GENERATOR = 11,

            /** RSS Standard Documentation Url. **/
            DOCS = 12,

            /** Cloud. **/
            CLOUD = 13,

            /** Time RSS Channel Stays Actual, in minutes. **/
            TTL = 14,

            /** Channel Image (Logo, Icon). **/
            IMAGE = 15,

            /** Text-Input Form. **/
            TEXT_INPUT = 16,

            /** Delay RSS Updating Hours. **/
            SKIP_HOURS = 17,

            /** Delay RSS Updating Days. **/
			SKIP_DAYS = 18,

			/** Enclosure. **/
			ENCLOSURE = 19,

			/** Channel's Item. **/
			CHANNEL_ITEM = 20,

			/** GUID **/
			GUID = 21,

			/** Author. **/
			AUTHOR = 22,

			/** Source. **/
			SOURCE = 23,

			/** Comments. **/
			COMMENTS = 24

            // -----------------------------------------------------------

        }; // Element::Type

        // ===========================================================
        // CONSTANTS
        // ===========================================================

        /** Type. **/
        const Element::Type mType;

        // ===========================================================
        // CONSTRUCTOR
        // ===========================================================

        /**
          * Element constructor.
          *
          * @param pType - Element-Type.
          * @throws - no exceptions.
        **/
        explicit Element( const Element::Type pType ) noexcept;

        // ===========================================================
        // DESTRUCTOR
        // ===========================================================

        /**
          * Element destructor.
          *
          * @throws - no exceptions.
        **/
        virtual ~Element( ) noexcept;

        // ===========================================================
        // METHODS
        // ===========================================================

        /**
          * Wrapper-mehod to cast Element to specific type.
          *
          * @thread_safety - not required.
          * @param pElement - Element to cast.
          * @return - T.
          * @throws - no exceptions.
        **/
        template <typename T>
        static T* castTo( Element *const pElement ) noexcept;

        // -----------------------------------------------------------

    private:

        // -----------------------------------------------------------

        // ===========================================================
        // DELETED CONSTRUCTORS & OPERATORS
        // ===========================================================

        /** @deleted Element const copy constructor. **/
        Element( const Element & ) noexcept = delete;

        /** @deleted Element copy-assignment operator. **/
        Element & operator=( const Element & ) noexcept = delete;

        /** @deleted Element move constructor. **/
        Element( Element && ) noexcept = delete;

        /** @deleted Element move assignment operator. **/
        Element & operator=( Element && ) noexcept = delete;

        // -----------------------------------------------------------

    }; // Element

	/** Alias for Element::Type **/
	using ElementType = Element::Type;

    // -----------------------------------------------------------

} // rss

// -----------------------------------------------------------

#endif // !QRSS_READER_ELEMENT_HPP
