import bb.cascades 1.2
import QTimer 1.0

Container {
    id: changelogContainer
    property alias changelogText: changelogLabel.text
    property int remainingSeconds: 10
    
    onCreationCompleted: { enableOkButtonTimer.start() }
    layout: DockLayout {}
    horizontalAlignment: HorizontalAlignment.Fill
    verticalAlignment: VerticalAlignment.Fill
    
    attachedObjects: [
        QTimer {
            id: enableOkButtonTimer
            interval: 1000
            onTimeout: { 
                remainingSeconds-- 
                if (remainingSeconds == 0) {
                    enableOkButtonTimer.stop()
                }
            }
        }
    ]

    Container {
        layout: DockLayout {}
        horizontalAlignment: HorizontalAlignment.Fill
        verticalAlignment: VerticalAlignment.Fill
        background: backgroundImage.imagePaint
        opacity: 0.4
        attachedObjects: [
            ImagePaintDefinition {
                id: backgroundImage
                repeatPattern: RepeatPattern.XY
                imageSource: "asset:///images/appIcon96_sketch.amd"
            }
        ]
    }
    Container {
        layout: DockLayout {}
        horizontalAlignment: HorizontalAlignment.Fill
        verticalAlignment: VerticalAlignment.Fill
        ScrollView {
            id: changelogScrollview
            horizontalAlignment: HorizontalAlignment.Fill
            verticalAlignment: VerticalAlignment.Fill
            Container {
                layout: DockLayout {}
                horizontalAlignment: HorizontalAlignment.Fill
                verticalAlignment: VerticalAlignment.Fill
                Container {
                    horizontalAlignment: HorizontalAlignment.Center
                    verticalAlignment: VerticalAlignment.Center
                    topPadding: 100
                    bottomPadding: topPadding
                    leftPadding: topPadding
                    rightPadding: topPadding
                    Label {
                        id: changelogLabel
                        multiline: true
                        horizontalAlignment: HorizontalAlignment.Center
                    }
                    Button {
                        text: ((remainingSeconds > 0) ? remainingSeconds : qsTr("Ok"))
                        enabled: (remainingSeconds <= 0)
                        horizontalAlignment: HorizontalAlignment.Center
                        onClicked: {
                            changelogContainer.visible = false
                            changelogScrollview.scrollToPoint(0, 0)
                        }
                    }
                }
            }
        }
    }
}
