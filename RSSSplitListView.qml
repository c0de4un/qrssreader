import QtQuick 2.13
import QtQuick.Controls 2.13 // SplitView
import QtQuick.Layouts 1.3 // Required for Layouts of SplitView

// RSS Channel & Channel' Items ListViews
Row {

    // Channels Container Width.
    property real channelsWidth: 240

    // Channel' Items Container Width.
    property real itemsWidth: 400

    // Height
    property real rssHeight: 480

    // Alias for Channels ListView Model.
    property alias channelsModel: channelsListView_id.model

    // Alias for Channel' Items ListView Model.
    property alias channelItemsModel: channelItemsListView_id.model

    // Alias for Channel' Items ListView current index.
    property alias itemsListIndex: channelItemsListView_id.currentIndex

    // Alias for Channels ListView current index.
    property alias channelsListIndex: channelsListView_id.currentIndex

    // Width
    width: channelsWidth + itemsWidth
    // Height
    height: rssHeight

    // Channels ListView Container
    Frame {

        // Width
        width: channelsWidth
        // Height
        height: rssHeight

        // Channels ListView
        ListView {

            // ID
            id: channelsListView_id
            anchors.fill: parent
            clip: true
            // Highlight
            highlight: Rectangle {
                color: "lightsteelblue"
                radius: 1
            }
            // Focus
            focus: true
            // Unselect
            currentIndex: -1

        } /// Channels ListView

    } /// Channels ListView Container

    // Channel' Items ListView Container
    Frame {

        // Width
        width: itemsWidth
        // Height
        height: rssHeight
        //background: Rectangle {
            //color: "#FF0000"
            //anchors.fill: parent
        //}

        // Channel' Items ListView
        ListView {

            // ID
            id: channelItemsListView_id
            anchors.fill: parent
            clip: true
            // Highlight
            highlight: Rectangle {
                color: "lightsteelblue"
                radius: 1
            }
            // Focus
            focus: true
            // Unselect
            currentIndex: -1

        }
        /// Channel' Items ListView

    } /// Channel' Items ListView Container

}
/// RSS Channel & Channel' Items ListViews
