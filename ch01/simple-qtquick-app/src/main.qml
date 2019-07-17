import QtQuick 2.13
import QtQuick.Controls 2.13

ApplicationWindow {
    visible: true
    width: 640; height: 480
    title: qsTr("Simple QtQuick Application")

    menuBar: MenuBar {
      Menu {
         title: qsTr("&File")
         MenuItem {
            id: fileExitMenuItem
            text: qsTr("E&xit")
            icon {
               source: "qrc:/icons/application-exit.svg"
               color: "Indigo"
            }
            action: Action {
               shortcut: "Ctrl+Q"; onTriggered: Qt.quit()
            }
         }
      }
    }

   header: ToolBar {
      ToolButton {
         action: fileExitMenuItem.action
         icon {
            source: "qrc:/icons/application-exit.svg"; color: "white"
         }
      }
   }

   footer: Frame { Label { text: qsTr("Ready!") } }

   SplitView {
      anchors.fill: parent
      orientation: Qt.Horizontal
      ListView {
         id: listView
         SplitView.preferredWidth: 200
         SplitView.maximumWidth: 400
         model: [ qsTr("First item"),
                  qsTr("Second item"),
                  qsTr("Third item") ]
         clip: true
         delegate: ItemDelegate {
            width: parent.width
            text: modelData
            icon {
               source: "qrc:/icons/qtlogo.svg"; color: "transparent"
            }
            highlighted: ListView.isCurrentItem
            onClicked: listView.currentIndex = index
         }
      }
      Label {
         id: label
         SplitView.fillWidth: true
         horizontalAlignment: Text.AlignHCenter
         verticalAlignment: Text.AlignVCenter
         text: listView.currentItem.text
      }
   }
}
