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

#ifndef QT_RSS_READER_MAIN_WINDOW_LOGIC_HPP
#define QT_RSS_READER_MAIN_WINDOW_LOGIC_HPP

// -----------------------------------------------------------

// ===========================================================
// INCLUDES
// ===========================================================

// Include QT API
#include <QString>
#include <QObject>

// ===========================================================
// FORWARD-DECLARATIONS
// ===========================================================

// QWindow
#if !defined( QWINDOW_H ) && !defined( QWINDOW_DECL ) // !QWINDOW_H
#define QWINDOW_DECL
class QWindow;
#endif // !QWINDOW_H

// QQmlApplicationEngine
#if !defined( QQMLAPPLICATIONENGINE_H ) && !defined( QQMLAPPLICATIONENGINE_DECL )
#define QQMLAPPLICATIONENGINE_DECL
class QQmlApplicationEngine;
#endif

// QQuickView
#if !defined( QQUICKVIEW_H ) && !defined( QQUICKVIEW_DECL )
#define QQUICKVIEW_DECL
class QQuickView;
#endif

// ===========================================================
// TYPES
// ===========================================================

/**
  * MainWindowLogic - handle RSS Reader Main-Window logic.
  *
  * @version 1.0
  * @since 23.07.2019
  * @authors Denis Z. (code4un@yandex.ru)
**/
class MainWindowLogic : public QObject
{

    // -----------------------------------------------------------

    // ===========================================================
    // QT MACROS
    // ===========================================================

    Q_OBJECT

    // -----------------------------------------------------------

private:

    // -----------------------------------------------------------

    // ===========================================================
    // FIELDS
    // ===========================================================

    /** Main Window Initialized flag. **/
    bool mInitialized;

    /** RSS Feeds Count. **/
    int mFeedsCount;

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
    bool loadSettings( ) noexcept;

    /**
      *
    **/
    //void readSettings( ) noexcept;

    // -----------------------------------------------------------

public:

    // -----------------------------------------------------------

    // ===========================================================
    // CONSTANTS
    // ===========================================================

    /** Settings File Path & Name. **/
    static const QString SETTINGS_FILE_SRC;

    // ===========================================================
    // FIELDS
    // ===========================================================

    /** MainWindowLogic instance. **/
    static MainWindowLogic * mMainWindowLogicInstance;

    /** Home Dir. **/
    static QString mHomeDir;

    /** QQmlApplicationEngine **/
    QQmlApplicationEngine * mQQmlApplicationEngine;

    /** Main Window. **/
    QWindow * mMainWindow;

    /** RSS Feed Dialog **/
    QQuickView * mRSSFeedView;

    // ===========================================================
    // CONSTRUCTOR
    // ===========================================================

    /**
      * MainWindowLogic constructor.
      *
      * @throws - no exceptions.
    **/
    explicit MainWindowLogic( ) noexcept;

    // ===========================================================
    // DESTRUCTOR
    // ===========================================================

    /**
      * MainWindowLogic destructor.
      *
      * @throws - no exceptions.
    **/
    virtual ~MainWindowLogic( ) noexcept;

    // ===========================================================
    // METHODS
    // ===========================================================

    /**
      * Called when MainWindow created & loaded.
      *
      * @thread_safety - not thread-safe.
      * @throws - no exceptions.
    **/
    Q_INVOKABLE void onReady( ) noexcept;

    /**
      * Called when MainWindow closed.
      *
      * @thread_safety - not thread-safe.
      * @throws - no exceptions.
    **/
    Q_INVOKABLE void onClose( ) noexcept;

    /**
      * Called when GUI requests to add new RSS Feed from Url.
      *
      * @thread_safety - not required.
      * @param pUrl - RSS Url (rss://my_feed.xml || https://rss.mysite.com/news.xml).
      * @return - 'true' if Url is valid & RSS Feed added, 'false' if not (same url already added, Url is invalid).
      * @throws - no exceptions.
    **/
    Q_INVOKABLE bool AddRSSFeed( const QString pUrl ) noexcept;

    // -----------------------------------------------------------

}; /// MainWindowLogic

// -----------------------------------------------------------

#endif // !QT_RSS_READER_MAIN_WINDOW_LOGIC_HPP
