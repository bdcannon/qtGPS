import QtQuick 1.1

Rectangle {
    width: 360
    height: 360

    MouseArea {
        anchors.fill: parent
        onClicked: {
            Qt.quit();
        }
    }

    Rectangle{
        anchors.centerIn:parent
        color:"blue"
        height:180
        width:180
        NumberAnimation on rotation{
            from:0
            to : 360
            loops:NumberAnimation.Infinite
            duration:3000
        }
    }
}
