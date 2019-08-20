import QtQuick 2.13
import QtQuick.Window 2.13 // ApplicationWindow
import QtQuick.Controls 2.13 // SplitView
import QtQuick.Layouts 1.3 // Required for Layouts of SplitView
import QtQuick.Dialogs 1.2 // Dialog
import QtQml.Models 2.12 // DelegateModel

import MainWindowLogic 1.0
import ChannelModel 1.0
import ProxyChannelModel 1.0

// Main Window
ApplicationWindow {

    // ------------------------------------------------------------------------

    // ID
    id: mainWindow_id
    // Visibility
    visible: true
    // Width
    width: 640
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
            urlInputDialog.open( );

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
        delegate: ChannelListItem {

            //
            channelViewWidth: rssListViews_id.channelsWidth - 16
            //
            channelViewHeight: channelViewWidth / 3
            //
            imageSource: image
            //
            channelTitle: title
            //
            channelDescription: description

            // Mouse-Area
            MouseArea {

                // ID
                id: rssChannelsView_MouseArea_id
                // Anchors
                anchors.fill: parent
                // OnClick
                onClicked: {

                    // Highlight Item.
                    rssListViews_id.channelsListIndex = index;

                    // Set Selected Channel.
                    proxyRssModel.setSelectedChannelIndex( link );

                } /// OnClick

            } /// Mouse-Area

        } /// Delegate

    } /// DelegateModel for Channels ListView

    // DelegateModel for Channel' Items ListView
    DelegateModel {

        // ID
        id: channelItemsListViewDelegateModel_id
        // Model
        model: proxyRssModel

        delegate: ChannelItemView {

            // Container View-Width
            width: rssListViews_id.itemsWidth
            // Container View-Height
            height: width / 4
            // Title
            titleValue: title
            // Description
            descriptionValue: description
            // Visibility
            visible: true

            // Mouse-Area
            MouseArea {

                // ID
                id: rssItemView_MouseArea_id
                // Anchors
                anchors.fill: parent
                // OnClick
                onClicked: {

                    // Highlight Item.
                    rssListViews_id.itemsListIndex = index;

                } /// OnClick

            } /// Mouse-Area

        } /// Delegate
    }
    /// DelegateModel for Channel' Items ListView

    // RSS View
    RSSSplitListView {

        // ID
        id: rssListViews_id
        // Channels Container Width
        channelsWidth: mainWindow_id.width / 3
        // Channel' Items Container Width
        itemsWidth: mainWindow_id.width - channelsWidth
        // Height
        rssHeight: mainWindow_id.height
        // Channels ListView Model
        channelsModel: channelsListViewDelegateModel_id
        // Channel' Items ListView Model
        channelItemsModel: channelItemsListViewDelegateModel_id

    }
    /// RSS View

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
    TextInputDialog {

        // Title
        title: "RSS"
        // ID
        id: urlInputDialog
        // Visibility
        visible: false
        // OK
        //onAccepted: {

        //} /// OK

    }
    /// Url Input Dialog

    // ------------------------------------------------------------------------

    // onCompleted
    onSceneGraphInitialized: mainWindowLogic.onReady( )

    // onClosing
    onClosing: Qt.quit( )

    // onDestruction
    Component.onDestruction: mainWindowLogic.onClose( )

} /// Main Window
