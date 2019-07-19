import QtQuick 2.13
import QtQuick.Controls 2.13

ApplicationWindow {
   visible: true
   width: 640; height: 480
   title: qsTr("Simple Qt Quick Application")

   Label {
      anchors.centerIn: parent
      text: "Hello from Qt Quick!"
   }
}
