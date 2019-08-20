import QtQuick 2.13
import QtQuick.Dialogs 1.2 as QDialogs // Dialogs

// Dialog
QDialogs.Dialog {

    // ID
    id: aboutDialog_id
    // Width
    width: 240
    // Height
    height: 100
    // Title
    title: "About QRSSReader"

    // Content-Item
    contentItem: Rectangle {

        // Text
        Text {
            id: aboutTextView_id
            anchors.fill: parent
            font.italic: true
            font.bold: false
            wrapMode: Text.WrapAnywhere
            elide: Text.ElideLeft
            text: "QRSSReader - example applicaton to read RSS feed.

    Created with QT API (QtQuick, QML).

    Demonstrates usage of Data-Models with Proxies, ListViews."
        }

    } /// Content-Item

} /// Dialog
