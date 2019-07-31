import QtQuick 2.13
import QtQuick.Window 2.13
import QtQuick.Controls 2.5
import QtQuick.Dialogs 1.2
import MainWindowLogic 1.0

// Main Window
ApplicationWindow {

    // ------------------------------------------------------------------------

    // ID
    id: mainWindow_id
    // Visibility
    visible: true
    // Width
    width: 1280
    // Height
    height: 720
    // Title
    title: qsTr("Q-RSSReader")

    // Name (used due to id can't be used as string).
    property string name: "mainWindow"

    // ------------------------------------------------------------------------

    // Logic
    MainWindowLogic {
        // ID
        id: mainWindowLogic
    } /// Logic

    // ------------------------------------------------------------------------

    // Show UrlDialog
    function showUrlDialog( )
    {
        if ( !urlInputDialog.visible )
            urlInputDialog.show( );
    }

    // ------------------------------------------------------------------------

    // Menu [QtQuickControls 2.5]
    menuBar: MenuBar {

        // ID
        id: menuBar_id
        // Visibility
        visible: true
        // Application
        Menu {
            // ID
            id: menuBar_applicationMenu_id
            // Title
            title: "App"
            Action {
                text: "+RSS"
                onTriggered: showUrlDialog( )
            }
            Action {
                text: "About"
            }
            Action {
                text: "Quit"
                onTriggered: Qt.quit( );
            }
        } /// Application
    }
    /// Menu

    // ------------------------------------------------------------------------

    // Url Input Dialog
    UrlDialog {

        // ID
        id: urlInputDialog
        // Name
        objectName: "urlInputDialog"
        // Width
        width: 200
        // Height
        height: 80
        // Visibility
        visible: false
        // Title
        title: "Url"
        // EditText.Text
        label: "https://qt.io"
        // X
        x: mainWindow_id.x + ( ( mainWindow_id.width / 2 ) - width / 2 )
        // Y
        y: mainWindow_id.y + ( ( mainWindow_id.height / 2 ) - height / 2 )

        // onDialogWindowOK
        onDialogWindowOK: {
            urlInputDialog.hide( );
        } /// onDialogWindowOK

        // onDialogWindowDiscard
        onDialogWindowDiscard: {
            urlInputDialog.hide( );
        } /// onDialogWindowDiscard

    } /// Url Input Dialog

    // ------------------------------------------------------------------------

    // onCompleted
    onSceneGraphInitialized: mainWindowLogic.onReady( )

    // onClosing
    onClosing: Qt.quit( )

    // onDestruction
    Component.onDestruction: mainWindowLogic.onClose( )

} /// Main Window
