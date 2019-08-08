import QtQuick 2.13
import QtQuick.Window 2.13 // ApplicationWindow
import QtQuick.Controls 2.5 // Views & Widgets
import QtQuick.Dialogs 1.2 // Dialog
import QtQml.Models 2.12 // DelegateModel

import MainWindowLogic 1.0
import ChannelModel 1.0

// Main Window
ApplicationWindow {

    // ------------------------------------------------------------------------

    // ID
    id: mainWindow_id
    // Visibility
    visible: true
    // Width
    width: 320
    // Height
    height: 480
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

    } /// showUrlDialog

    /**
      * Shows Open-FileDialog to RSS file.
      *
      * If file exists, pass it to ChannelModel,
      * which parse it & update data.
    **/
    function showOpenFileRSSDialog( )
    {

        // Show File-Dialog for RSS-File
        if ( !openFSSFileDialog_id.visible )
            openFSSFileDialog_id.open( );

    } /// showOpenFileRSSDialog

    /**
      * Tries to open RSS-File using ChannelModel.
      * If RSS data has been read, ChannelModel updates.
    **/
    function openRSSFile( rssFileUrl )
    {

        // Parse RSS File.
        rssModel.parseRSSFile( rssFileUrl );

        // Show ChannelsListView
        channelsListView_id.visible = true;
        channelsListView_id.enabled = true;

    } /// openRSSFile

    /**
      * Shows AboutAppDialog.
    **/
    function showAboutAppDialog( )
    {

        // Show AboutAppDialog
        if ( !about_DialogID.visible )
            about_DialogID.open( );

    } /// showAboutAppDialog

    // ------------------------------------------------------------------------

    // DelegateModel for Channels ListView
    DelegateModel {

        // ID
        id: channelsListViewDelegateModel_id
        // Model
        model: rssModel
        // Delegate
        delegate: Rectangle {

            // Width
            width: parent.width
            // Height
            height: 80

            // Image
            Image {

                // ID
                id: channelImage_id
                // Source = Url of ChannelModel' Channel-Object using "image" as Role.
                source: image
                // Visibility
                visible: true
                // Width [Min. Width of RSS Image]
                width: 88
                // Height [Min. Height of RSS Image]
                height: 31

            } /// Image

            // Text
            Text {
                anchors.left: channelImage_id.right
                text: title
            }

        } /// Delegate

    } /// DelegateModel for Channels ListView

    // Channels ListView
    ListView {

        // ID
        id: channelsListView_id
        // Anchors
        //anchors.fill: parent
        // Width
        width: 400
        // Height
        height: 400
        // Visibility
        visible: false
        // Enabled
        enabled: false
        // Model & Delegate
        model: channelsListViewDelegateModel_id

    } /// Channels ListView

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
                text: "Open URL"
                onTriggered: showUrlDialog( )
            }
            Action {
                text: "Open File"
                onTriggered: showOpenFileRSSDialog( )
            }
            Action {
                text: "About"
                onTriggered: showAboutAppDialog( )
            }
            Action {
                text: "Quit"
                onTriggered: Qt.quit( );
            }
        } /// Application
    }
    /// Menu

    // ------------------------------------------------------------------------

    // AboutAppDialog
    AboutAppDialog {

        // ID
        id: about_DialogID
        // Visibility
        visible: false
        // X
        x: ( parent.width / 2 ) - ( width / 2 )
        // Y
        y: ( parent.height / 2 ) - ( height / 2 )

    } /// AboutAppDialog

    // ------------------------------------------------------------------------

    // Open FileDialog for RSS
    FileDialog {

        // ID
        id: openFSSFileDialog_id
        // Title
        title: "Open RSS"
        // Default Path
        folder: shortcuts.home
        // Filters
        nameFilters: [ "RSS (*.rss *.xml)" ]
        // Modality
        modality: Qt.Dialog
        // Visibility
        visible: false
        // Multi-Selection
        selectMultiple: false
        // Select Exisitin
        selectExisting: true
        // File-Only
        selectFolder: false

        // OnAccepted
        onAccepted: openRSSFile( openFSSFileDialog_id.fileUrl )
        // OnRejected
        //onRejected: openFSSFileDialog_id.close( )

    } /// Open FileDialog for RSS

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
