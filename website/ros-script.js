// ros-script.js

var ros = new ROSLIB.Ros({
    url: 'ws://10.105.1.168:9090'
});

ros.on('connection', function () {
    console.log('Connecté au serveur websocket ROS.');
});

ros.on('error', function (error) {
    console.log('Erreur de connexion au serveur websocket ROS: ', error);
});

ros.on('close', function () {
    console.log('Connexion au serveur websocket ROS fermée.');
});

var modePublisher = new ROSLIB.Topic({
    ros: ros,
    name: '/web_mode',
    messageType: 'interfaces/msg/WebMode'
});


var generalDataListener = new ROSLIB.Topic({
    ros: ros,
    name: '/general_data', 
    messageType: 'interfaces/msg/GeneralData'
});


function updateBatteryDisplay(message) {

    if (message.battery_level !== undefined) {

        document.getElementById('batteryDisplay').innerHTML = 'Battery Level: ' + message.battery_level;
    }
}

generalDataListener.subscribe(updateBatteryDisplay);
