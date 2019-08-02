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

#ifndef QRSS_READER_ID_STORAGE_HPP
#define QRSS_READER_ID_STORAGE_HPP

// -----------------------------------------------------------

// ===========================================================
// INCLUDES
// ===========================================================

// Include QMap
#ifndef QMAP_H
#include <qmap.h>
#endif // !QMAP_H

// Include QMutex
#ifndef QMUTEX_H
#include <qmutex.h>
#endif // !QMUTEX_H

// Include C++ limits.
#include <limits>

// ===========================================================
// IDStorage
// ===========================================================

namespace rss
{

	// -----------------------------------------------------------

	/**
	  * IDStorage - utility-class to store & manage generated IDs (number values).
	  *
	  * @brief
	  * IDStorage generates numerical IDs, adds them to map. To manage (reserve & release)
	  * ids map-container of bool-values used (obviously because bit-set requires static size).
	  *
	  * @version 1.0
	  * @since 21.07.2019
	  * @authors - Denis Z. (code4un@yandex.ru).
	**/
	template <typename T = unsigned int>
	class IDStorage final
	{

	private:

		// -----------------------------------------------------------

		// ===========================================================
		// FIELDS
		// ===========================================================

		/** IDs. **/
		QMap<T, bool> mIDs;

		/** Mutex. **/
		QMutex mIDsMutex;

		// ===========================================================
		// DELETED CONSTRUCTORS & OPERATORS
		// ===========================================================

		/** @deleted IDStorage const copy constructor. **/
		IDStorage( const IDStorage & ) noexcept = delete;

		/** @deleted IDStorage copy-assignment operator. **/
		IDStorage & operator=( const IDStorage & ) noexcept = delete;

		/** @deleted IDStorage move constructor. **/
		IDStorage( IDStorage && ) noexcept = delete;

		/** @deleted IDStorage move assignment operator. **/
		IDStorage & operator=( IDStorage && ) noexcept = delete;

		// -----------------------------------------------------------

	public:

		// -----------------------------------------------------------

		// ===========================================================
		// CONSTRUCTOR
		// ===========================================================

		/**
		  * IDStorage constructor.
		  *
		  * @throws - no exceptions.
		**/
		explicit IDStorage( ) noexcept
			: mIDs( ),
			  mIDsMutex( )
		{
		}

		// ===========================================================
		// DESTRUCTOR
		// ===========================================================

		/**
		  * IDStorage destructor.
		  *
		  * @throws - no exceptions.
		**/
		~IDStorage( ) noexcept = default;

		// ===========================================================
		// METHODS
		// ===========================================================

		/**
		  * Searches for available ID.
		  *
		  * (!) Always use #releaseID(T) when ID no loner used.
		  *
		  * @threadsafe - thread-lock used.
		  * @returns - ID, or INVALID_ID if out of limits.
		  * @throws - no exceptions.
		**/
		T generateID( ) noexcept
		{

			// Thread-Lock
			QMutexLocker qLock( &mIDsMutex );

			// IDs map iterator.
			auto iter_ = mIDs.begin( );

			// IDs map end-iterator.
			const auto endIter_ = mIDs.cend( );

			// Search available ID.
			while( iter_ != endIter_ )
			{

				// Check ID state.
				if ( iter_.value( ) == false )
				{

					// Reserve ID
					iter_.value( ) = true;

					// Return ID
					return( iter_.key( ) );

				} /// Check ID state.

				// Next ID
				iter_++;

			} /// Search available ID.

			// Limit
			if ( mIDs.size( ) <= std::numeric_limits<T>::max( ) - 1 )
				return( std::numeric_limits<T>::max( ) - 1 );

			// New ID
			const T id_( mIDs.size( ) );

			// Reserve ID
			mIDs.insert( id_, true );

			// Return ID
			return( id_ );

		} /// generateID

		/**
		  * Release ID making it available.
		  *
		  * @threadsafe - thread-lock used.
		  * @throws - no exceptions.
		**/
		void releaseID( const T & pID ) noexcept
		{

			// Lock
			QMutexLocker lock_( &mIDsMutex );

			// Search ID
			auto idPos_ = mIDs.find( pID );

			// Cancel, if ID not found.
			if ( idPos_ == mIDs.cend( ) )
				return;

			// Mark ID as available.
			idPos_.value( ) = true;

		} /// releaseID

		// -----------------------------------------------------------

	}; // rss::IDStorage

	// -----------------------------------------------------------

} // rss

// -----------------------------------------------------------

#endif // !QRSS_READER_ID_STORAGE_HPP
