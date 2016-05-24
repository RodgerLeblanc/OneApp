import bb.cascades 1.2

Container {
    property alias imageSource: imageView.imageSource
    property alias text: label.text
    
    topMargin: _ui.du(4)
    bottomMargin: topMargin
    visible: label.text != ""
    
    CustomDivider {}
    
    Container {
        layout: StackLayout { orientation: LayoutOrientation.LeftToRight }
        horizontalAlignment: HorizontalAlignment.Center
        
        ImageView {
            id: imageView
            verticalAlignment: VerticalAlignment.Center
            maxHeight: _ui.du(20)
            minHeight: maxHeight
            minWidth: maxHeight
            scalingMethod: ScalingMethod.AspectFit
        }
        Container {
            layout: DockLayout {}
            verticalAlignment: VerticalAlignment.Center
            ImageView {
                imageSource: "asset:///images/border_bubble.amd"
                verticalAlignment: VerticalAlignment.Fill
                horizontalAlignment: HorizontalAlignment.Fill
            }
            Container {
                topPadding: 15
                bottomPadding: topPadding
                rightPadding: topPadding
                leftPadding: 55
                Label {
                    id: label
                    multiline: true
                    textStyle.textAlign: TextAlign.Justify
                    textStyle.fontSize: FontSize.Large
                    textStyle.color: Color.create("#640D38")
                    textStyle.fontFamily: "Comic Sans MS"
                }
            }
        }
    
    }
    
    CustomDivider {}
}
