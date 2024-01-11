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


var listener = new ROSLIB.Topic({
    ros: ros,
    name: '/motors_order',
    messageType: 'interfaces/msg/MotorsOrder'
});

listener.subscribe(test);

function test(message){

    console.log('mess',message.right_rear_pwm);

}