import bb.cascades 1.2
import bb.system 1.2
import QTimer 1.0
import "CustomElements"

Container {
    layout: DockLayout {}
    horizontalAlignment: HorizontalAlignment.Fill
    verticalAlignment: VerticalAlignment.Fill
    
    attachedObjects: [
        RenderFence {
            raised: true
            onReached: { fadeOutTransition.play() }
        }
    ]
    
    ScrollView {
        horizontalAlignment: HorizontalAlignment.Fill
        verticalAlignment: VerticalAlignment.Fill
        Container {
            layout: DockLayout {}
            horizontalAlignment: HorizontalAlignment.Fill
            verticalAlignment: VerticalAlignment.Fill
            topPadding: _ui.du(3)
            bottomPadding: topPadding
            Container {
                visible: !listViewParentContainer.visible
                horizontalAlignment: HorizontalAlignment.Center
                verticalAlignment: VerticalAlignment.Center
                
                Container {
                    SituationTemplate {
                        id: thisSituationTemplate
                        
                        property variant imageSourceList: ["asset:///images/unknown_colleague.png", "asset:///images/kid.png", "asset:///images/boss.png"]
                        property variant textList: []
                        property int iterator: -1
                        
                        onCreationCompleted: {
                            var tempList = new Array()
                            tempList[0] = qsTr("Can I borrow your phone to sneak... I mean to make a phone call?") + Retranslate.onLocaleOrLanguageChanged
                            tempList[1] = qsTr("Dad, can I play that race game on your phone, I won't download other paid games this time, I promise...") + Retranslate.onLocaleOrLanguageChanged
                            tempList[2] = qsTr("Today, you'll take your BlackBerry 10 device and demo our new application at the event. Remember all our internal documents are on there too, don't let users get out of our application, or you're fired!") + Retranslate.onLocaleOrLanguageChanged
                            textList = tempList
                        }
                        
                        attachedObjects: [
                            QTimer {
                                id: changeSituationTimer
                                interval: 1
                                singleShot: true
                                onTimeout: { fadeOutTransition.play() }
                            }
                        ]
                        animations: [
                            FadeTransition {
                                id: fadeOutTransition
                                fromOpacity: 1
                                toOpacity: 0
                                duration: 1000
                                onEnded: {
                                    thisSituationTemplate.iterator++
                                    
                                    if (thisSituationTemplate.iterator == thisSituationTemplate.textList.length)
                                        thisSituationTemplate.iterator = 0
                                    
                                    thisSituationTemplate.imageSource = thisSituationTemplate.imageSourceList[thisSituationTemplate.iterator]
                                    thisSituationTemplate.text = thisSituationTemplate.textList[thisSituationTemplate.iterator]
                                    
                                    changeSituationTimer.interval = thisSituationTemplate.textList[thisSituationTemplate.iterator].length * 40
                                    
                                    fadeInTransition.play()
                                }
                            },
                            FadeTransition {
                                id: fadeInTransition
                                fromOpacity: 0
                                toOpacity: 1
                                duration: 1000
                                onEnded: { changeSituationTimer.start() }
                            }
                        ]
                    }
                }
                
                Container {
                    topPadding: _ui.du(3)
                    horizontalAlignment: HorizontalAlignment.Center
                    Button {
                        text: qsTr("Lock to one application") + Retranslate.onLocaleOrLanguageChanged
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
    }
    
    Container {
        id: listViewParentContainer
        horizontalAlignment: HorizontalAlignment.Center
        verticalAlignment: VerticalAlignment.Center
        visible: false 
        ListViewContainer {}
    }
}
