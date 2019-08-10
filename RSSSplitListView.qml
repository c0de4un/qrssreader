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
    //property alias channelsModel: itemsListView_id.model

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
            // Highlight
            highlight: Rectangle {
                color: "lightsteelblue"
                radius: 1
            }
            // Focus
            focus: true

        } /// Channels ListView

    } /// Channels ListView Container

    // Channel' Items ListView Container
    Frame {

        // Width
        width: itemsWidth
        // Height
        height: rssHeight

    } /// Channel' Items ListView Container

}
/// RSS Channel & Channel' Items ListViews
