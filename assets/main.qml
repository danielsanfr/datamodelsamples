/*
 * Copyright (c) 2011-2013 BlackBerry Limited.
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

import bb.system 1.0
import bb.cascades 1.0
import model.custom 1.0

Page {
    attachedObjects: [
        SystemToast {
            id: sysTst
        },
        ComponentDefinition {
            id: optDefinition
            Option {
            }
        }
    ]
    Container {
        verticalAlignment: VerticalAlignment.Fill
        horizontalAlignment: HorizontalAlignment.Fill
        layout: StackLayout {
            orientation: LayoutOrientation.LeftToRight
        }
        ListView {
            id: lstVwItems
            layoutProperties: StackLayoutProperties {
                spaceQuota: 10
            }
            dataModel: FilteredListDataModel {
                id: dtModel
                filterBy: "name"
            }
            listItemComponents: [
                ListItemComponent {
                    StandardListItem {
                        title: ListItemData.name
                    }
                }
            ]
            onCreationCompleted: {
                dtModel.appendList([ {"name": 1}, {"name": 2}, {"name": 3}, {"name": 4}, {"name": 5} ])
                for (var i = 0; i < 5; ++ i) {
                    var option1 = optDefinition.createObject(), option2 = optDefinition.createObject()
                    option1.setText(i)
                    option2.setText(i)
                    ddRemove.add(option1)
                    ddSwap.add(option2)
                }
            }
        }
        Container {
            background: Color.LightGray
            verticalAlignment: VerticalAlignment.Fill
            horizontalAlignment: HorizontalAlignment.Fill
            layoutProperties: StackLayoutProperties {
                spaceQuota: 0.1
            }
        }
        ScrollView {
            verticalAlignment: VerticalAlignment.Fill
            horizontalAlignment: HorizontalAlignment.Fill
            layoutProperties: StackLayoutProperties {
                spaceQuota: 10
            }
            Container {
                topPadding: 20
                leftPadding: 20
                rightPadding: 20
                bottomPadding: 20
                verticalAlignment: VerticalAlignment.Fill
                horizontalAlignment: HorizontalAlignment.Fill
                Container {
                    layout: StackLayout {
                        orientation: LayoutOrientation.LeftToRight
                    }
                    Label {
                        text: qsTr("Search") + ":" + Retranslate.onLocaleOrLanguageChanged
                        verticalAlignment: VerticalAlignment.Center
                    }
                    TextField {
                        hintText: ""
                        inputMode: TextFieldInputMode.EmailAddress
                        onTextChanging: {
                            dtModel.setFilter(text)
                        }
                    }
                }
                Container {
                    topMargin: 20
                    layout: StackLayout {
                        orientation: LayoutOrientation.LeftToRight
                    }
                    Label {
                        text: qsTr("Item") + ":" + Retranslate.onLocaleOrLanguageChanged
                        verticalAlignment: VerticalAlignment.Center
                    }
                    TextField {
                        id: txtFldItem
                        hintText: ""
                        inputMode: TextFieldInputMode.EmailAddress
                    }
                }
                Button {
                    text: qsTr("Append item") + Retranslate.onLocaleOrLanguageChanged
                    horizontalAlignment: HorizontalAlignment.Fill
                    onClicked: {
                        dtModel.append({"name":txtFldItem.text})
                        var option = optDefinition.createObject(), option2 = optDefinition.createObject()
                        option.setText(dtModel.size() - 1)
                        option2.setText(dtModel.size() - 1)
                        ddRemove.add(option)
                        ddSwap.add(option2)
                    }
                }
                Button {
                    text: qsTr("Prepend item") + Retranslate.onLocaleOrLanguageChanged
                    horizontalAlignment: HorizontalAlignment.Fill
                    onClicked: {
                        dtModel.prepend({"name":txtFldItem.text})
                        var option = optDefinition.createObject(), option2 = optDefinition.createObject()
                        option.setText(dtModel.size() - 1)
                        option2.setText(dtModel.size() - 1)
                        ddRemove.add(option)
                        ddSwap.add(option2)
                    }
                }
                Divider {
                }
                DropDown {
                    id: ddRemove
                    title: qsTr("Position") + Retranslate.onLocaleOrLanguageChanged
                }
                Button {
                    text: qsTr("Remove item")
                    horizontalAlignment: HorizontalAlignment.Fill
                    onClicked: {
                        dtModel.removeAt(ddRemove.selectedOption.text)
                        ddRemove.remove(ddRemove.at(ddRemove.count() - 1))
                        ddSwap.remove(ddSwap.at(ddSwap.count() - 1))
                    }
                }
                Container {
                    layout: StackLayout {
                        orientation: LayoutOrientation.LeftToRight
                    }
                    Label {
                        text: qsTr("New item") + ":" + Retranslate.onLocaleOrLanguageChanged
                        verticalAlignment: VerticalAlignment.Center
                    }
                    TextField {
                        id: txtFldNewItem
                        hintText: ""
                        inputMode: TextFieldInputMode.EmailAddress
                    }
                }
                Button {
                    text: qsTr("Update item")
                    horizontalAlignment: HorizontalAlignment.Fill
                    onClicked: {
                        dtModel.replace(ddRemove.selectedOption.text, {"name": txtFldNewItem.text})
                    }
                }
                DropDown {
                    id: ddSwap
                    title: qsTr("Position") + Retranslate.onLocaleOrLanguageChanged
                }
                Button {
                    text: qsTr("Swap items")
                    horizontalAlignment: HorizontalAlignment.Fill
                    onClicked: {
                        dtModel.swap(ddRemove.selectedOption.text, ddSwap.selectedOption.text)
                    }
                }
                Container {
                    layout: StackLayout {
                        orientation: LayoutOrientation.LeftToRight
                    }
                    Button {
                        text: qsTr("RF") + Retranslate.onLocaleOrLanguageChanged
                        onClicked: {
                            dtModel.removeFirst()
                            ddRemove.remove(ddRemove.at(ddRemove.count() - 1))
                            ddSwap.remove(ddSwap.at(ddSwap.count() - 1))
                        }
                    }
                    Button {
                        text: qsTr("RL") + Retranslate.onLocaleOrLanguageChanged
                        onClicked: {
                            dtModel.removeLast()
                            ddRemove.remove(ddRemove.at(ddRemove.count() - 1))
                            ddSwap.remove(ddSwap.at(ddSwap.count() - 1))
                        }
                    }
                    Button {
                        text: qsTr("CT") + Retranslate.onLocaleOrLanguageChanged
                        onClicked: {
                            sysTst.body = dtModel.size()
                            sysTst.show()
                        }
                    }
                    Button {
                        text: qsTr("IE") + Retranslate.onLocaleOrLanguageChanged
                        onClicked: {
                            sysTst.body = dtModel.isEmpty()
                            sysTst.show()
                        }
                    }
                }
                Button {
                    text: qsTr("Clear list") + Retranslate.onLocaleOrLanguageChanged
                    horizontalAlignment: HorizontalAlignment.Fill
                    onClicked: {
                        dtModel.clear()
                        ddRemove.removeAll()
                        ddSwap.removeAll()
                    }
                }
            }
        }
    }
}