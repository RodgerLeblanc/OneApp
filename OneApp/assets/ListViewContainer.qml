import bb.cascades 1.2
import bb.system 1.2

Container {
    id: listViewContainer
    horizontalAlignment: HorizontalAlignment.Fill
    verticalAlignment: VerticalAlignment.Fill
    ListView {
        id: listView
        /*
        property variant luhData: luh.layoutFrame
        property variant itemShown: (scrollStateHandler.firstVisibleItem + 1) / dataModel.childCount(0)
        */
        
        dataModel: _app.dataModel
        onTriggered: {
            lockAppDialog.thisAppMap = dataModel.data(indexPath)
            lockAppDialog.show()
        }
        attachedObjects: [
            /*
            LayoutUpdateHandler {
                id: luh
            },
            ListScrollStateHandler {
                id: scrollStateHandler
            },*/
            SystemDialog {
                id: lockAppDialog
                property variant thisAppMap: {}
                title: qsTr("Lock one app") + Retranslate.onLocaleOrLanguageChanged
                body: qsTr("Would you like to lock your phone in ") + Retranslate.onLocaleOrLanguageChanged + thisAppMap.name + qsTr(" app?") + Retranslate.onLocaleOrLanguageChanged
                cancelButton.enabled: true
                confirmButton.enabled: true
                confirmButton.label: qsTr("Lock") + Retranslate.onLocaleOrLanguageChanged
                onFinished: {
                    if (buttonSelection() == confirmButton) {
                        setPasswordPrompt.show()
                    }
                    else {
                        listViewParentContainer.visible = false
                        listView.scrollToPosition(0, ScrollAnimation.None)
                    }
                }
            },
            SystemDialog {
                id: finalWarningDialog
                title: qsTr("Warning") + Retranslate.onLocaleOrLanguageChanged
                body: qsTr("Remember: To unlock the app, you have to hold VOLUME UP button until you're asked for a password.") + Retranslate.onLocaleOrLanguageChanged
                cancelButton.enabled: true
                cancelButton.label: qsTr("What?") + Retranslate.onLocaleOrLanguageChanged
                confirmButton.enabled: true
                confirmButton.label: qsTr("Got it!") + Retranslate.onLocaleOrLanguageChanged
                onFinished: {
                    if (buttonSelection() == confirmButton) 
                        _app.sendToHL("LOCK_THIS_APP", lockAppDialog.thisAppMap.packageName)
                    else 
                        finalWarningDialog.show()
                }
            },
            SystemPrompt {
                id: setPasswordPrompt
                title: qsTr("Set a password") + Retranslate.onLocaleOrLanguageChanged
                body: qsTr("Choose a password to unlock the app") + Retranslate.onLocaleOrLanguageChanged
                emoticonsEnabled: false
                onFinished: {
                    if (buttonSelection() == confirmButton) {
                        _settings.setValue("hashedPassword", _app.hashThis(inputFieldTextEntry()))
                        confirmPasswordPrompt.show()
                    }
                    else {
                        listViewParentContainer.visible = false
                        listView.scrollToPosition(0, ScrollAnimation.None)
                    }
                }
            },
            SystemPrompt {
                id: confirmPasswordPrompt
                title: qsTr("Confirm password") + Retranslate.onLocaleOrLanguageChanged
                body: qsTr("Enter password again to confirm") + Retranslate.onLocaleOrLanguageChanged
                emoticonsEnabled: false
                onFinished: {
                    if (buttonSelection() == confirmButton) {
                        if (_settings.value("hashedPassword", "") == _app.hashThis(inputFieldTextEntry())) {
                            finalWarningDialog.show()
                        }
                        else {
                            generalToast.body = qsTr("Password doesn't match")
                            generalToast.show()
                        }
                    }
                    listViewParentContainer.visible = false
                    listView.scrollToPosition(0, ScrollAnimation.None)
                }
            },
            SystemToast {
                id: generalToast
                button.label: qsTr("OK")
            }
        ]
        listItemComponents: [
            ListItemComponent {
                StandardListItem {
                    title: ListItemData.name
                    imageSource: ListItemData.icon
                }
                /*
                Container {
                    id: customListItem
                    property int deviceHeight: customListItem.ListItem.view.luhData.height
                    minWidth: customListItem.ListItem.view.luhData.width
                    attachedObjects: [
                        LayoutUpdateHandler { 
                            id: imageLuh 
                            onLayoutFrameChanged: {
                                var biggest = deviceHeight * customListItem.ListItem.view.itemShown
                                var percent = (layoutFrame.y / biggest) * 2
//                                console.log(layoutFrame.y + " " + biggest + " " + percent)
//                                imageView.minHeight = 96 * percent
                            }
                        }
                    ]
                    Container {
                        layout: StackLayout {
//                            orientation: LayoutOrientation.LeftToRight
                        }
                        horizontalAlignment: HorizontalAlignment.Center
                        ImageView {
                            id: imageView
                            imageSource: ListItemData.icon
                            scalingMethod: ScalingMethod.AspectFill
                            horizontalAlignment: HorizontalAlignment.Center
                            verticalAlignment: VerticalAlignment.Center
                            minHeight: 96
                            maxHeight: minHeight
                            minWidth: minHeight
                            maxWidth: minWidth
                        }
                        Label {
                            text: ListItemData.name
                            horizontalAlignment: HorizontalAlignment.Center
                            verticalAlignment: VerticalAlignment.Center
                        }
                    }
                }
*/
            } 
        ]
    }
}
