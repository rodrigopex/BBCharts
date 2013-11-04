import bb.cascades 1.0

Page {
    Container {
        Label {
            text: "Image loaded:"
            textStyle.base: SystemDefaults.TextStyles.PrimaryText
        }
        Button {
            text: "change graph!"
            onClicked: {
                _chartManager.drawChart()
            }
        }
        ImageView {
            id: myImage
            image: _chartManager.image
            horizontalAlignment: HorizontalAlignment.Fill
            implicitLayoutAnimationsEnabled: false
        }

    }
}
