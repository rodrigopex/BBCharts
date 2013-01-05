// Default empty project template
import bb.cascades 1.0

// creates one page with a label
Page {
    Container {
        Label {
            text: "Image loaded:"
            textStyle.base: SystemDefaults.TextStyles.PrimaryText
        }
        Button {
            text: "change graph!"
            onClicked: {
                _controller.changePicture()
                }
        }
        ImageView {
            objectName: "myImage";
            id: myImage
            image: _controller.image
        }
    }
//    onCreationCompleted: {
//        //console.log("foi!")
//    }
}

