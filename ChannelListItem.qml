import QtQuick 2.13

// Channel View Layout for ListView
Item {

    // Elements Border Size
    property real borderSize: 2

    // Alias for Container Width
    property alias channelViewWidth: channelView_id.width

    // Alias for Container Height
    property alias channelViewHeight: channelView_id.height

    // Alias for Channel' Image Width
    property alias channelImageWidth: channelImage_id.width

    // Alias for Channel' Image Height
    property alias channelImageHeight: channelImage_id.height

    // Alias for Channel' Image Source
    property alias imageSource: channelImage_id.source

    // Alias for Channel' Title.
    property alias channelTitle: channelTitle_id.text

    // Alias for Channel' Description
    property alias channelDescription: channelDescription_id.text

    // Min. Image Width
    property real minImageWidth: 88
    // Min. Image Height
    property real minImageHeight: 31
    // Max. Image Width
    // Max. Image Height

    // ID
    id: channelView_id
    // Width
    width: 200
    // Height
    height: 80
    // Color = Transparent

    // Channel' Image
    Image {

        // ID
        id: channelImage_id
        // Initial Width
        width: minImageWidth
        // Initial Height
        height: minImageHeight
        // X-Offset
        x: 0
        // Y-Offset
        y: borderSize

    } /// Channel' Image

    // Channel' Title
    Text {
        // ID
        id: channelTitle_id
        // Anchors
        //anchors.left: channelImage_id.right
        //
        x: ( channelImage_id.x + channelImage_id.width ) + 0
        //
        y: ( channelImage_id.y + channelImage_id.height ) / 2
        // Text
        text: "No Title"
        // Style
        font.bold: true
        wrapMode: Text.WrapAnywhere
        // Elide
        elide: Text.ElideRight
        // Width
        width: channelView_id.width - ( x + (borderSize * 6) )
        // Height
        height: channelView_id.height - ( y + (borderSize * 6) )
        // Visibility
        visible: true

    } /// Channel' Title

    // Channel' Description
    Text {

        // ID
        id: channelDescription_id
        // Text
        text: "No Description"
        // X-Offset
        x: 0
        // Y
        y: borderSize
        // Anchors
        anchors.top: channelImage_id.bottom
        // Width
        width: channelView_id.width - ( x + ( borderSize * 6 ) )
        // Height
        height: channelView_id.height - ( y + ( borderSize * 6 ) )
        // Visibility
        visible: true
        // Style
        font.bold: false
        font.italic: true
        // Wrap-Mode
        wrapMode: Text.WrapAnywhere
        // Elide
        elide: Text.ElideRight

    }

    /// Channel' Description

}
/// Channel View Layout for ListView
