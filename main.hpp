// -----------------------------------------------------------

// ===========================================================
// INCLUDES
// ===========================================================

// QT
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QWindow>
#include <QStandardPaths>
#include <QDir>
#include <QStringList>
#include <QSettings>

// MainWindowLogic
#ifndef QT_RSS_READER_MAIN_WINDOW_LOGIC_HPP
#include "src/cpp/ui/MainWindowLogic.hpp"
#endif // !QT_RSS_READER_MAIN_WINDOW_LOGIC_HPP

// UrlDialog
#ifndef QT_RSS_READER_URL_INPUT_DIALOG_HPP
//#include "src/cpp/ui/UrlInputDialog.hpp"
#endif // !QT_RSS_READER_URL_INPUT_DIALOG_HPP

/**
  * Returns path to dir where app can store private-files.
  *
  * @thread_safety - not required.
  * @return - string with path to a dir.
  * @throws - no exceptions.
**/
static QString getPrivateDataDir( ) noexcept;

// -----------------------------------------------------------
