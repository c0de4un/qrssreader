import QtQuick 2.13

// Channel' Item View for ListView Item
Item {

    // Elements Border Size
    property real borderSize: 8

    // Title value.
    property alias titleValue: itemTitle_id.text

    // Description value.
    property alias descriptionValue: itemDescription_id.text

    // ID
    id: itemView_id

    // Default Width
    width: 100
    // Default Height
    height: 50

    // Title
    Text {
        // ID
        id: itemTitle_id
        // X
        x: borderSize
        // Y
        y: borderSize
        // Text
        text: "No Title"
        // Style
        font.bold: true
        wrapMode: Text.WrapAnywhere
        // Elide
        elide: Text.ElideRight
        // Width
        width: itemView_id.width - ( x + borderSize )
        // Visibility
        visible: true
    } /// Title

    // Description
    Text {

        // ID
        id: itemDescription_id
        // Text
        text: "No Description"
        // Style
        font.bold: false
        wrapMode: Text.WrapAnywhere
        // Elide
        elide: Text.ElideRight
        // X
        x: borderSize
        // Y
        y: itemTitle_id.y + ( itemTitle_id.contentHeight + ( borderSize ) )
        // Width
        width: itemView_id.width - ( x + borderSize )
        // Height
        height: itemView_id.height - ( borderSize + y )
        // Visibility
        visible: true

    }
    /// Description

}
/// Channel' Item View for ListView Item
