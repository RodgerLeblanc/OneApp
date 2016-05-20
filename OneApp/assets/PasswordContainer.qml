import bb.cascades 1.2
import bb.system 1.2

Container {
    id: passwordContainer
    
    layout: DockLayout {}
    horizontalAlignment: HorizontalAlignment.Fill
    verticalAlignment: VerticalAlignment.Fill
    
    attachedObjects: [
        LayoutUpdateHandler { id: luh }
    ]
    
    onCreationCompleted: {
        Application.fullscreen.connect(onFullscreen)
    }
    
    function onFullscreen() {
        if (passwordContainer.visible) {
            passwordTextField.requestFocus()
        }
    }
    
    Container {
        horizontalAlignment: HorizontalAlignment.Center
        verticalAlignment: VerticalAlignment.Center
        Label {
            text: qsTr("Enter password") + Retranslate.onLocaleOrLanguageChanged
            horizontalAlignment: HorizontalAlignment.Center
        }
        Container {
            horizontalAlignment: HorizontalAlignment.Center
            maxWidth: luh.layoutFrame.width * (2 / 3)
            TextField {
                id: passwordTextField
                hintText: qsTr("Password") + Retranslate.onLocaleOrLanguageChanged
                onTextChanging: { unlockButton.enabled = text.length > 0 }
            }
        }
        Container {
            topPadding: _ui.du(3)
            layout: StackLayout { orientation: LayoutOrientation.LeftToRight }
            horizontalAlignment: HorizontalAlignment.Center
            Button {
                text: qsTr("Cancel")
                verticalAlignment: VerticalAlignment.Center
                onClicked: {
                    _app.sendToHL("WRONG_PASSWORD")
                    passwordTextField.text = ""
                }
            }
            Button {
                id: unlockButton
                text: qsTr("Ok") + Retranslate.onLocaleOrLanguageChanged
                enabled: passwordTextField.text.length > 0
                verticalAlignment: VerticalAlignment.Center
                onClicked: {
                    var hashedPassword = _app.hashThis(passwordTextField.text)
                    unlockToast.unlockedSuccessfully = (hashedPassword == _settings.value("hashedPassword", _app.hashThis("CellNinja")))
                    if (unlockToast.unlockedSuccessfully) {
                        _app.stopLocking()
                    }
                    unlockToast.show()
                }
                attachedObjects: [
                    SystemToast {
                        id: unlockToast
                        property bool unlockedSuccessfully: false
                        body: unlockedSuccessfully ? qsTr("Unlocked successfully") + Retranslate.onLocaleOrLanguageChanged : qsTr("Password does not match, taking you back to locked app") + Retranslate.onLocaleOrLanguageChanged
                        button.label: qsTr("Ok") + Retranslate.onLocaleOrLanguageChanged
                        onFinished: {
                            if (!unlockedSuccessfully)
                                _app.sendToHL("WRONG_PASSWORD")
                            
                            passwordTextField.text = ""
                        }
                    }
                ]
            }
        }
    }
}
