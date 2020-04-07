import QtQuick 2.14
import QtQuick.Controls 2.14

ApplicationWindow {
   visible: true
   width: 640
   height: 480
   title: qsTr("Hello World")

   header: ToolBar {
      Label { anchors.centerIn: parent; text: "QtQuickApp" }
   }

   Drawer {
      id: drawer
      width: parent.width/2; height: parent.height
      ListView {
         anchors.fill: parent
         model: core.pluginController.pluginMetaData
         delegate: ItemDelegate {
            width: parent.width
            text: modelData.menuName
            onClicked: {
               stackView.pop(null)
               stackView.push(
                  (Qt.platform.os === "android") ?
                     "assets:/plugins/" + modelData.pluginName + "/" +
                       modelData.mainPage
                     :
                     "file://" + modelData.pluginName + "/" +
                       modelData.mainPage
                  )
               drawer.close()
            }
         }
      }
   }

   StackView {
      id: stackView
      anchors.fill: parent
      initialItem: Item {
         Label {
            anchors.centerIn: parent
            horizontalAlignment: Qt.AlignHCenter
            verticalAlignment: Qt.AlignVCenter
            text: "Hello from microkernel QtQuick application!"
         }
      }
   }
}
