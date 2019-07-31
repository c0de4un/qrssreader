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
#ifndef QT_RSS_READER_MAIN_WINDOW_LOGIC_HPP
#include "MainWindowLogic.hpp"
#endif // !QT_RSS_READER_MAIN_WINDOW_LOGIC_HPP

// Include QWindow
#include <QWindow>

// Include QQuickView
#include <QQuickView>

// Include QFile
#include <QFile> // QFile, exists, open

// Include QDir
#include <QDir> // separator

// Include QTextStream
#include <QTextStream> // readLine

// Include QQmlApplicationEngine
#include <QQmlApplicationEngine>

// DEBUG
#ifdef DEBUG

// Include C++ assert (QT-C assert ?)
#include <assert.h>

#endif
// DEBUG

// ===========================================================
// CONSTANTS
// ===========================================================

/** Settings File Path & Name. **/
const QString MainWindowLogic::SETTINGS_FILE_SRC( "cache/settings.ini" );

// ===========================================================
// FIELDS
// ===========================================================

/** MainWindowLogic instance. **/
MainWindowLogic * MainWindowLogic::mMainWindowLogicInstance( nullptr );

/** Home Dir. **/
QString MainWindowLogic::mHomeDir( "" );

// ===========================================================
// CONSTRUCTOR
// ===========================================================

/**
  * MainWindowLogic constructor.
  *
  * @throws - no exceptions.
**/
MainWindowLogic::MainWindowLogic( ) noexcept
    : QObject( ),
      mInitialized( false ),
      mFeedsCount( 0 ),
      mQQmlApplicationEngine( nullptr ),
      mMainWindow( nullptr ),
      mRSSFeedView( nullptr )
{

    // Set STATIC instance.
    mMainWindowLogicInstance = this;

}

// ===========================================================
// DESTRUCTOR
// ===========================================================

/**
  * MainWindowLogic destructor.
  *
  * @throws - no exceptions.
**/
MainWindowLogic::~MainWindowLogic( ) noexcept
{

    // Reset STATIC instance.
    mMainWindowLogicInstance = nullptr;

}

// ===========================================================
// METHODS
// ===========================================================

/**
  * Loads cached-data (settings) including RSS-Feeds.
  *
  * @thread_safety - main-thread (ui) only.
  * @return - 'true' if data loaded, 'false' if not.
  * @throws - no exceptions.
**/
bool MainWindowLogic::loadSettings( ) noexcept
{// TODO MainWindowLogic::loadSettings

    // Settings File Name.
    QString settingsFileName( mHomeDir );
    settingsFileName += QDir::separator( );
    settingsFileName += "code4un/QtRSSReader/settings.ini";

    // Create File.
    QFile settingsFile( settingsFileName );

    // Return FALSE, if settings not created.
    if ( !settingsFile.exists( ) )
        return( false );

    // Open Settings-File
    if ( !settingsFile.open( QIODevice::ReadOnly | QIODevice::Text ) )
        return( false );

    // Create TextStream to cast Bytes to Text
    QTextStream inputStream( &settingsFile );

    // Line #0: "RSS"
    // RSS Feeds Count
    QString inputString( inputStream.readLine( ) );

    // Set RSS Feeds Count.
    mFeedsCount = inputString.toInt( );

#if defined( QT_DEBUG ) || defined( DEBUG ) // DEBUG
    qDebug( ) << "RSS Feeds Count=" << inputString;
#endif // DEBUG

    // Read Urls
    for( int i = 0; i < mFeedsCount; i++ )
    {

        //

    } /// Read Urls

    // Return FALSE
    return( true );

}

/**
  * Called when GUI requests to add new RSS Feed from Url.
  *
  * @thread_safety - not required.
  * @param pUrl - RSS Url (rss://my_feed.xml || https://rss.mysite.com/news.xml).
  * @return - 'true' if Url is valid & RSS Feed added, 'false' if not (same url already added, Url is invalid).
  * @throws - no exceptions.
**/
bool MainWindowLogic::AddRSSFeed( const QString pUrl ) noexcept
{

    //

    // Return FALSE
    return( false );

}

/**
  * Called when MainWindow created & loaded.
  *
  * @thread_safety - not thread-safe.
  * @throws - no exceptions.
**/
void MainWindowLogic::onReady( ) noexcept
{// TODO MainWindowLogic::onReady

    // Cancel, if already initialized.
    if ( mInitialized )
        return;

#if defined( QT_DEBUG ) || defined( DEBUG ) // DEBUG
    // Print Debug-message.
    qDebug( "MainWindowLogic::onReady" );

    // Check MainWindow
    assert( mMainWindow != nullptr && "MainWindowLogic::onReady - pointer to the MainWindow not set ! Its suppose to be set in main !" );

    // Check QQmlApplicationEngine
    assert( mQQmlApplicationEngine != nullptr && "MainWindowLogic::onReady - pointer to the QQmlApplicationEngine not set ! Its suppose to be set in main !" );
#endif // DEBUG

    // Set Initialized flag.
    mInitialized = true;

    // Load Settings (Custom format used).
    if ( !loadSettings( ) )
    {// Clean-Launch

        // Create QQuickView
        //if ( mRSSFeedView == nullptr )
            //mRSSFeedView = new QQuickView( mQQmlApplicationEngine, mMainWindow );

        // QML File
        //const QUrl qmlFile( QStringLiteral( "qrc:/feed_editor_dialog.qml" ) );

        // Load QML using current Thread
        //mRSSFeedView->setSource( qmlFile );

        // Show Window
        //mRSSFeedView->show( );

    } /// Load Settings (Custom format used).

}

/**
  * Called when MainWindow closed.
  *
  * @thread_safety - not thread-safe.
  * @throws - no exceptions.
**/
void MainWindowLogic::onClose( ) noexcept
{

    // Cancel, if not initialized.
    if ( !mInitialized )
        return;

#if defined( QT_DEBUG ) || defined( DEBUG ) // DEBUG
    // Print Debug-message.
    qDebug( "MainWindowLogic::onClose" );
#endif // DEBUG

    // Close Application
    mQQmlApplicationEngine->exit( 0 );

    // Reset Initialized-flag.
    mInitialized = false;

    // Reset MainWindow instance.
    mMainWindow = nullptr;

    // Reset QQmlApplicationEngine
    mQQmlApplicationEngine = nullptr;

    //
    mRSSFeedView = nullptr;

}

// -----------------------------------------------------------
