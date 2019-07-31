import QtQuick 2.8

// Button root
Item {

    // Signals
    signal simpleButtonClicked

    // ID
    id: simpleButton_defaultID

    // Text
    property alias text: simpleButton_Label.text

    // Text Height
    property real textHeight: 32

    // Default Width
    width: 32
    // Default Height
    height: 32

    // Rectangular
    Rectangle {

        // ID
        id: backgroundRectangle_id
        // Width
        width: parent.width
        // Height
        height: parent.height
        // Color
        color: "#b0beca"
        border.width: 1
        border.color: "black"

    } /// Rectangular

    // Text
    Text {

        // ID
        id: simpleButton_Label
        // Text
        text: qsTr("Button")
        // Anchors
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        // Height
        height: textHeight
        // Alignment
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter

    } /// Text

    // Mouse Input
    MouseArea {
        id: simpleButton_mouseArea
        anchors.fill: parent
        onClicked: simpleButton_defaultID.simpleButtonClicked()
    } /// Mouse Input

} // Button root
