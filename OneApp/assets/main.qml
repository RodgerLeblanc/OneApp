/*
 * Copyright (c) 2013-2015 BlackBerry Limited.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

import bb.cascades 1.2
import "Changelog"
import "Sheets"

Page {
    id: mainPage
    property bool lockModeEnabled: _settings.allSettings.lockModeEnabled
    
    Menu.definition: MenuDefinition {
        id: menuDefinition
        actions: [
            ActionItem {
                title: qsTr("About") + Retranslate.onLanguageChanged
                imageSource: "asset:///images/ic_info.png"
                onTriggered: { aboutSheet.open() }
            }
        ] 
    }
    
    onCreationCompleted: {
        Application.menuEnabled = !mainPage.lockModeEnabled
        
        // Creates a MultiCover or SceneCover depending on asset selection
        Application.setCover(activeFrame)

        _app.newChangelog.connect(onNewChangelog)
    }
    
    function onNewChangelog(newChangelogForThisUser) {
        changelogContainer.changelogText = "Changelog:\n" + newChangelogForThisUser
        changelogContainer.visible = true
    }
    
    onLockModeEnabledChanged: {
        Application.menuEnabled = !mainPage.lockModeEnabled
    }
    
    attachedObjects: [
        AboutSheet { id: aboutSheet },
        AppCover { id: activeFrame }
    ]

    Container {
        layout: DockLayout {}
        horizontalAlignment: HorizontalAlignment.Fill
        verticalAlignment: VerticalAlignment.Fill
        
        leftPadding: 30
        rightPadding: leftPadding
        
        ChangelogContainer { id: changelogContainer; visible: false; }
        Container {
            layout: DockLayout {}
            horizontalAlignment: HorizontalAlignment.Fill
            verticalAlignment: VerticalAlignment.Fill
            visible: !changelogContainer.visible
            
            NormalUiContainer { visible: !mainPage.lockModeEnabled }
            PasswordContainer { visible: mainPage.lockModeEnabled }
        }
    }
}
