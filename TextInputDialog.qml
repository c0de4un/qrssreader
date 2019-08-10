import QtQuick 2.13
import QtQuick.Dialogs 1.2 as QDialogs // Dialogs

// Dialog
QDialogs.Dialog {

    // Alias for TextEdit Text
    property alias textValue: textInputDialog_TextEdit.text

    // Text Height
    property real textHeight: 12

    // ID
    id: textInputDialog_id
    // Width
    width: 180
    // Height
    height: 60
    // Title
    title: "No Title"

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
        width: textInputDialog_id.width
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

} /// Dialog
