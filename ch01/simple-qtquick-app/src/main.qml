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
            text: qsTr("E&xit")
            action: Action {
               id: fileExitAction
               icon {
                  source: "qrc:/icons/application-exit.svg"
                  color: "Indigo"
               }
               shortcut: "Ctrl+Q"; onTriggered: Qt.quit()
            }
         }
      }
   }

   header: ToolBar { ToolButton { action: fileExitAction } }

   footer: Frame { Label { text: qsTr("Ready!") } }

   SplitView {
      anchors.fill: parent
      orientation: Qt.Horizontal // default value
      ListView {
         id: listView
         SplitView.preferredWidth: 200
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
         horizontalAlignment: Text.AlignHCenter
         verticalAlignment: Text.AlignVCenter
         text: listView.currentItem.text
      }
   }
}
