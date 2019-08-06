import QtQuick 2.13

// root-View for ChannelsListView Item.
Item
{

    // This function configures
    // Image-View (channelImageView_id)
    // Not all RSS-Channels have <image>,
    // so Image-View can stay empty.
    function loadImage( )
    {

        //



    } // loadImage

    // Width
    width: 240
    // Height
    height: 180

    // Image
    Image {

        // ID
        id: channelImageView_id
        // Default-Width [min=88, max=144]
        width: 88
        // Default-Height [min=31, max=400]
        height: 31
        // Data Loaded Asynchronously using default QT API behavior.


    } /// Image

}
