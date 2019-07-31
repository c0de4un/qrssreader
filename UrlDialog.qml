import QtQuick 2.8 // QT 5.8
import QtQuick.Window 2.0

// Dialog-Window
Window {

    // Signals
    signal dialogWindowOK
    signal dialogWindowDiscard

    // Text Height
    property real textHeight: 12

    // Text-Field
    property alias label: textInputDialog_TextEdit.text

    // ID
    id: textInputDialog_Window
    // Name
    objectName: "textInputDialog_Window"
    // Width
    width: 180
    // Height
    height: 60
    // Min. Width
    minimumWidth: width
    // Min. Height
    minimumHeight: height
    // Max. Width
    maximumWidth: width
    // Max. Height
    maximumHeight: height
    // Modality
    modality: Qt.WindowModal
    // Flags
    flags: Qt.Dialog || Qt.WindowStaysOnTopHint

    // Title
    title: "Text Input"

    // Text-Field
    TextEdit {

        // ID
        id: textInputDialog_TextEdit
        // X
        x: 0
        // Y
        y: 0
        // Text
        text: "rss://qt.io"
        // Width
        width: textInputDialog_Window.width
        // Height
        height: textHeight + 2
        // Wrap-Mode
        wrapMode: TextEdit.NoWrap
        // Flags
        inputMethodHints: Qt.ImhUrlCharactersOnly || Qt.ImhNoAutoUppercase || Qt.ImhNoPredictiveText
        // Alignment
        verticalAlignment: TextEdit.AlignVCenter
        horizontalAlignment: TextEdit.AlignLeft

    } /// Text-Field

    // Cancel Button
    SimpleButton {

        // ID
        id: btn_cancel
        // Text
        text: "Cancel"
        // Width
        width: 80
        // Height
        height: 40
        // Anchors
        anchors.top: textInputDialog_TextEdit.bottom
        anchors.left: textInputDialog_TextEdit.left

        /// OnClick
        onSimpleButtonClicked: {
            dialogWindowDiscard( );
            hide( );
        }

    } /// Cancel Button

    // OK Button
    SimpleButton {

        // ID
        id: btn_ok
        // Text
        text: "OK"
        // Width
        width: 80
        // Height
        height: 40
        // Anchors
        anchors.top: textInputDialog_TextEdit.bottom
        anchors.right: textInputDialog_TextEdit.right

        // OnClick
        onSimpleButtonClicked: {
            dialogWindowOK( );
            close( );
        } /// OnClick

    } /// OK Button

    // onDestroyed
    Component.onDestruction: dialogWindowDiscard( )

} /// Dialog-Window
