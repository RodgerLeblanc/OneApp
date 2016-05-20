import bb.cascades 1.2
import bb.system 1.2
import "CustomElements"

Container {
    layout: DockLayout {}
    horizontalAlignment: HorizontalAlignment.Fill
    verticalAlignment: VerticalAlignment.Fill

    ScrollView {
        horizontalAlignment: HorizontalAlignment.Fill
        verticalAlignment: VerticalAlignment.Fill
        Container {
            layout: DockLayout {}
            horizontalAlignment: HorizontalAlignment.Fill
            verticalAlignment: VerticalAlignment.Fill
            Container {
                visible: !listViewParentContainer.visible
                horizontalAlignment: HorizontalAlignment.Center
                verticalAlignment: VerticalAlignment.Center
                Container {
                    topPadding: _ui.du(3)
                    bottomPadding: topPadding
                    
                    SituationTemplate {
                        imageSource: "asset:///images/unknown_colleague.png"
                        text: qsTr("Can I borrow your phone to sneak... I mean to make a phone call?") + Retranslate.onLocaleOrLanguageChanged
                    }
                    SituationTemplate {
                        imageSource: "asset:///images/kid.png"
                        text: qsTr("Dad, can I play that race game on your phone, I won't download other paid games this time, I promise...") + Retranslate.onLocaleOrLanguageChanged
                    }
                    SituationTemplate {
                        imageSource: "asset:///images/boss.png"
                        text: qsTr("Today, you'll take your BlackBerry 10 device and demo our new app at the event. Don't let users get out of our app, or you're fired.") + Retranslate.onLocaleOrLanguageChanged
                    }
                }
                
                Button {
                    text: qsTr("Lock") + Retranslate.onLocaleOrLanguageChanged
                    horizontalAlignment: HorizontalAlignment.Center
                    onClicked: {
                        listViewParentContainer.visible = true
                    }
                }
                
                Label {
                    text: qsTr("Limitations") + Retranslate.onLocaleOrLanguageChanged
                    horizontalAlignment: HorizontalAlignment.Center
                    textStyle.textAlign: TextAlign.Justify
                    textStyle.fontSize: FontSize.XSmall
                    textStyle.color: Color.Blue
                    multiline: true
                    gestureHandlers: [ TapHandler { onTapped: { limitationsToast.show() } } ]
                    attachedObjects: [
                        SystemToast {
                            id: limitationsToast
                            body: qsTr("1) Cards can't be blocked. For instance, if a user is locked inside Browser app, he would be able to select text, hit the share icon and a list of available cards would be accessible to him, like BBM, emails, SMS, etc. Keep that in mind when choosing an app to lock.\n\n2) Quick Settings menu is accessible by a two finger swipe down gesture.") + Retranslate.onLocaleOrLanguageChanged
                            button.label: qsTr("OK") + Retranslate.onLocaleOrLanguageChanged
                        }
                    ]
                }
            }
        }
    }
    
    Container {
        id: listViewParentContainer
        horizontalAlignment: HorizontalAlignment.Center
        verticalAlignment: VerticalAlignment.Center
        visible: false 
        ListViewContainer {}
    }
}
