// -----------------------------------------------------------

// ===========================================================
// INCLUDES
// ===========================================================

// HEADER
#include "main.hpp"

#if defined( Q_DEBUG ) || defined( DEBUG ) // DEBUG
#include <QDebug>
#endif // DEBUG

// ===========================================================
// METHODS
// ===========================================================

QString getPrivateDataDir( ) noexcept
{

    // Get Paths to Home-Dir.
    const auto pathList = QStandardPaths::standardLocations( QStandardPaths::HomeLocation );

    // Extract first available path.
    const QString homeDirPath = pathList.first( ).split( QDir::separator( ) ).last( );

#if defined( QT_DEBUG ) || defined( DEBUG ) // DEBUG
    // Print path to a Debug-Output.
    qDebug( ) << "HomeDir=" << homeDirPath ;
#endif // DEBUG

    // Return Path to a Home-Dir.
    return( homeDirPath );

}

int main(int argc, char *argv[])
{

    // Enable DPI Scaling
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    // Set Organization Name
    QCoreApplication::setOrganizationName( "C0DE4UN INC." );

    // Set Application Name
    QCoreApplication::setApplicationName( "QRSSReader" );

    // Set Home-Dir.
    MainWindowLogic::mHomeDir = getPrivateDataDir( );

    // Set Version
    QCoreApplication::setApplicationVersion( "1.0" );

    // Create GUI Application
    QGuiApplication app(argc, argv);

    // Register MainWindowLogic.
    qmlRegisterType<MainWindowLogic>( "MainWindowLogic", 1, 0, "MainWindowLogic" );

	//
	qmlRegisterType<rss::ChannelModel>( "ChannelModel", 1, 0, "ChannelModel" );

    // Create QML Application Enigne
    QQmlApplicationEngine engine;

	// Create ChannelsModel.
	rss::ChannelModel *const channelModel( new rss::ChannelModel( ) );

	// Get root-Context.
	QQmlContext *const rootContext( engine.rootContext( ) );

	// Make ChannelMode available for all Views.
	rootContext->setContextProperty( "rssModel", channelModel );

    // QML
    const QUrl url(QStringLiteral("qrc:/main.qml"));

    // Connect Engine & Application
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);

    // Load QML
    engine.load(url);

    //QWindow
    QWindow *const rootWindow( qobject_cast<QWindow*>( engine.rootObjects( ).first( ) ) );

#if defined( Q_DEBUG ) || defined( DEBUG ) // DEBUG

    //qDebug( rootWindow-> );
    const QVariant windowName = rootWindow->property( "name" );

    // Check root-Window
    assert( windowName.toString( ) == "mainWindow" && "main.hpp - root Window missmatch !" );

#endif // DEBUG

    // Set root-Window
    MainWindowLogic::mMainWindowLogicInstance->mMainWindow = rootWindow;

    // Set Engine
    MainWindowLogic::mMainWindowLogicInstance->mQQmlApplicationEngine = &engine;

	const auto returnCode( app.exec( ) );

	// Delete ChannelModel.
	delete channelModel;

    // Execute QT Application
	return( returnCode );

}

// -----------------------------------------------------------
