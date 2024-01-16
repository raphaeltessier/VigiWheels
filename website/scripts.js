//Initialisation des variables pour orientation + vitesse
var reverse_car = false;
var steering_angle = 0;
var average_speed = 0;
const radius_wheel = 9.5;
const conversion_degree = 50;

// Function to move the arc gradually based on the specified angle
const arc = document.getElementById('arc');
arc.style.transformOrigin = "100px 100px"; // Set the rotation center of the arc

function moveArc(angle) {
    const arc = document.getElementById('arc');
    arc.style.transform = `rotate(${angle}deg)`; // Rotate the arc with the given angle offset
}

function changeBatteryLevel(BatteryLevel) {
    var batteryText = document.getElementById('batteryLevel');
    batteryText.innerText = `Battery level: ${BatteryLevel.toFixed(2)}`;
}

function changeSpeed(speedvalue, reverse) {
    const SpeedText = document.getElementById('speedvalue');
    if (speedvalue > 0) {
        if (reverse){
            SpeedText.innerText = `Reverse speed: ${-speedvalue.toFixed(4)} m/s`;
        }else{
            SpeedText.innerText = `Forward speed: ${speedvalue.toFixed(4)} m/s`;
        }   
    } else {
        SpeedText.innerText = "Car is currently stationary";
    }
}

function orientationCar(speed, steering_angle, reverse_car){
    var arrow_orientation_front = document.getElementById('arrow_direction_front');
    var arrow_orientation_rear = document.getElementById('arrow_direction_rear');

    if(speed>0){
        if (reverse_car){
            arrow_orientation_front.style.display = "none";
            arrow_orientation_rear.style.transform = `rotate(${-steering_angle}deg)`; 
            arrow_orientation_rear.style.display = "flex";
        }
        else{
            arrow_orientation_rear.style.display = "none";
            arrow_orientation_front.style.transform = `rotate(${steering_angle}deg)`; 
            arrow_orientation_front.style.display = "flex";
        }
    }else{
        arrow_orientation_front.style.display = "none";
        arrow_orientation_rear.style.display = "none";
    }

    
}

let Obst_detectedPositions = []; // Array to store detected obstacle positions

function toggleObstacle(position, enable) {
    const validPositions = ['tl', 'tm', 'tr', 'bl', 'bm', 'br']; // Valid obstacle positions
    if (validPositions.includes(position)) {
        const obstacle = document.getElementById(`obstacle_${position}`);

        if (enable === 1) {
            obstacle.style.display = "flex"; // Display the obstacle
            if (!Obst_detectedPositions.includes(position)) {
                Obst_detectedPositions.push(position); // Add the position if not already in the array
            }
        } else if (enable === 0) {
            obstacle.style.display = "none"; // Hide the obstacle
            const index = Obst_detectedPositions.indexOf(position);
            if (index !== -1) {
                Obst_detectedPositions.splice(index, 1); // Remove the position if in the array
            }
        }
    } else {
        console.log("Invalid position."); // Log if the position is not in the specified list
    }
    if (Obst_detectedPositions.length > 0) {
        // Call another function if at least one obstacle is still detected
        ObstacleDetected(1);
    } else {
        ObstacleDetected(0);
    }
}


// NOTIFICATIONS ON LEFT SIDE
let fireIntervalId = null;
let manometerIntervalId = null;
let obstacleIntervalId = null;

function fireDetected(isFireDetected) {
    const fireContainer = document.getElementById("fire_notif");

    if (isFireDetected === 1) {
        toggleDisplay(fireContainer, true); // Show fire notification
    } else if (isFireDetected === 0) {
        toggleDisplay(fireContainer, false); // Hide fire notification
    }
}

function ManometerDetected(isManometerDetected, value = 0) {
    const ManometerContainer = document.getElementById("manometer_notif");
    const manometerText = ManometerContainer.querySelector('.big-icon-text');

    if (isManometerDetected === 1) {
        if (value !== 0) {
            manometerText.innerText = "Manometer detected \n(value read: " + value + ")"; // Display value if available
        } else {
            manometerText.innerText = "Manometer detected \n(no value read)";
        }
        toggleDisplay(ManometerContainer, true); // Show manometer notification
    } else if (isManometerDetected === 0) {
        toggleDisplay(ManometerContainer, false); // Hide manometer notification
    }
}

function ObstacleDetected(isObstacleDetected) {
    const ObstacleContainer = document.getElementById("obstacle_notif");

    if (isObstacleDetected === 1) {
        toggleDisplay(ObstacleContainer, true); // Show obstacle notification
    } else if (isObstacleDetected === 0) {
        toggleDisplay(ObstacleContainer, false); // Hide obstacle notification
    }
}



// ICON APPARITIONS ON RIGHT SIDE
let Fire_detectedPositions = []; // Array to store detected fire positions

function togglefire(position, enable) {
    const validPositions = ['tl', 'tr', 'bl', 'br']; // Valid fire positions
    if (validPositions.includes(position)) {
        const fire = document.getElementById(`fire_${position}`);

        if (enable === 1) {
            fire.style.display = "flex"; // Display the fire
            if (!Fire_detectedPositions.includes(position)) {
                Fire_detectedPositions.push(position); // Add the position if not already in the array
            }
        } else if (enable === 0) {
            fire.style.display = "none"; // Hide the fire
            const index = Fire_detectedPositions.indexOf(position);
            if (index !== -1) {
                Fire_detectedPositions.splice(index, 1); // Remove the position if in the array
            }
        }
    } else {
        console.log("Invalid position."); // Log if the position is not in the specified list
    }
    if (Fire_detectedPositions.length > 0) {
        // Call another function if at least one obstacle is still detected
        fireDetected(1);
    } else {
        fireDetected(0);
    }
}

let intervalId = null;
const elementsToBlink = new Set();

function toggleDisplay(element, shouldDisplay) {
    if (shouldDisplay) {
        element.style.display = "flex"; // Set display to flex to show the element
    } else {
        element.style.display = "none"; // Hide the element
    }
}


// CONTROL USING KEY BOARD
let mano = 0;
let o1 = 0;
let o2 = 0;
let o3 = 0;
let o4 = 0;
let o5 = 0;
let o6 = 0;
let fire = 0;
/*
function waitFor(event) {
    // Handle key events for various functionalities
    if (event.key === 'm') {
        if (mano == 1) {
            ManometerDetected(0, 150);
            mano = 0;
        } else if (mano == 0) {
            ManometerDetected(1, 150);
            mano = 1;
        }
    }
    if (event.key === 'b') {
        changeBatteryLevel();
    }
    if (event.key === 'f') {
        if (fire == 0) {
            fireDetected(1);
            fire = 1;
        } else if (fire == 1) {
            fireDetected(0);
            fire = 0;
        }
    }
    // Toggle obstacles based on numeric keys
    if (event.key === '3') {
        if (o1 == 0) {
            toggleObstacle("tr", 1);
            o1 = 1;
        } else if (o1 == 1) {
            toggleObstacle("tr", 0);
            o1 = 0;
        }
    }
    if (event.key === '6') {
        if (o6 === 0) {
            toggleObstacle("bm", 1);
            o6 = 1;
        } else if (o6 === 1) {
            toggleObstacle("bm", 0);
            o6 = 0;
        }
    }

    if (event.key === '9') {
        if (o3 === 0) {
            toggleObstacle("tl", 1);
            o3 = 1;
        } else if (o3 === 1) {
            toggleObstacle("tl", 0);
            o3 = 0;
        }
    }
    if (event.key === '1') {
        if (o4 === 0) {
            toggleObstacle("br", 1);
            o4 = 1;
        } else if (o4 === 1) {
            toggleObstacle("br", 0);
            o4 = 0;
        }
    }
    if (event.key === '7') {
        if (o5 === 0) {
            toggleObstacle("bl", 1);
            o5 = 1;
        } else if (o5 === 1) {
            toggleObstacle("bl", 0);
            o5 = 0;
        }
    }
    if (event.key === '4') {
        if (o6 === 0) {
            toggleObstacle("bm", 1);
            o6 = 1;
        } else if (o6 === 1) {
            toggleObstacle("bm", 0);
            o6 = 0;
        }
    }
}
*/
document.addEventListener('keydown', waitFor);


// Website  redirection
function redirect(url) {
    window.location.href = url;
}


// Updater
function updateEmergencyAlert(message) {
    console.log(message)
    if (message.fire_detected == true) {
        fireDetected(1);
    } else {
        fireDetected(0);
    }
    /*
    if (message.ir_front_right == true) {
        togglefire("tr", 1);
    } else {
        togglefire("tr", 0);
    }
    if (message.ir_front_left == true) {
        togglefire("tl", 1);
    } else {
        togglefire("tl", 0);
    }
    if (message.ir_rear_left == true) {
        togglefire("bl", 1);
    } else {
        togglefire("bl", 0);
    }
    if (message.ir_rear_right == true) {
        togglefire("br", 1);
    } else {
        togglefire("br", 0);
    }*/

/*
    bool ir_front_right
    bool ir_front_left
    bool ir_rear_right
    bool ir_rear_left
    bool smoke_left
    bool smoke_right
    */
}
function updateGeneralData(message) {
    changeBatteryLevel(message.battery_level);
}

function updateCameraAngle(message) {
    new_angle = message.servo_cam_angle;
    moveArc(new_angle);
}

function updateObstacles(message) {
    if (message.rear_object) {
        toggleObstacle("tl", 1);
        toggleObstacle("tm", 1);
        toggleObstacle("tr", 1);
    } else {
        toggleObstacle("tl", 0);
        toggleObstacle("tm", 0);
        toggleObstacle("tr", 0);
    }

    if (message.front_object) {
        toggleObstacle("bl", 1);
        toggleObstacle("bm", 1);
        toggleObstacle("br", 1);
    } else {
        toggleObstacle("bl", 0);
        toggleObstacle("bm", 0);
        toggleObstacle("br", 0);
    }

}

function calculate_Speed_Orientation(message){

    // Calculate the speed of the car by average of right wheel speed and left wheel speed
    
    var speed_right = message.right_rear_speed;
    var speed_left = message.left_rear_speed;
    average_speed = (speed_left + speed_right)/2;
    average_speed = average_speed * radius_wheel * Math.pow(10, -2);   
    
    //Calculate steering angle of the car
    
    steering_angle = message.steering_angle;
    steering_angle = steering_angle * conversion_degree;  // [-1;1] for steering angle

    //Show the speed on the website
    changeSpeed(average_speed, reverse_car);

    //Positioning the arrow on basis of movement
    orientationCar(average_speed, steering_angle, reverse_car);

}

function identify_Reverse(message){

    // Identify if the car is going at reverse mode or not
    if (message.right_rear_pwm > 50){
        reverse_car = false;
    }    
    else{
        reverse_car = true;
    }
}


// ROS script initialization
var ros = new ROSLIB.Ros({
    url: 'ws://10.105.1.168:9090' // ROS websocket server URL
});

ros.on('connection', function () {
    console.log('Connected to ROS websocket server.');
});

ros.on('error', function (error) {
    console.log('Error connecting to ROS websocket server: ', error);
});

ros.on('close', function () {
    console.log('Connection to ROS websocket server closed.');
});


var l_servo_cam_angle = new ROSLIB.Topic({
    ros: ros,
    name: '/servo_cam_order',
    messageType: 'interfaces/msg/ServoCamOrder'
});
l_servo_cam_angle.subscribe(updateCameraAngle);

var l_general_data = new ROSLIB.Topic({
    ros: ros,
    name: '/general_data',
    messageType: 'interfaces/msg/GeneralData'
});
l_general_data.subscribe(updateGeneralData)

var l_emergency_alert = new ROSLIB.Topic({
    ros: ros,
    name: '/emergency_alert',
    messageType: 'interfaces/msg/EmergencyAlertFire'
});
l_emergency_alert.subscribe(updateEmergencyAlert)


var l_obstacles = new ROSLIB.Topic({
    ros: ros,
    name: '/obstacles_order',
    messageType: 'interfaces/msg/ObstaclesOrder'
});
l_obstacles.subscribe(updateObstacles)

var car_speed_listener = new ROSLIB.Topic({
    ros: ros,
    name: '/motors_feedback',
    messageType: 'interfaces/msg/MotorsFeedback'
});

car_speed_listener.subscribe(calculate_Speed_Orientation);

var motorOrder_listener = new ROSLIB.Topic({
    ros: ros,
    name: '/motors_order',
    messageType: 'interfaces/msg/MotorsOrder'
});

motorOrder_listener.subscribe(identify_Reverse);



// Timer for testing & demo & functions associated
function angleleft() {
    moveArc(-80);
    setTimeout(() => {
        angleright();
    }, 5000);
}

function angleright() {
    moveArc(80);
    setTimeout(() => {
        angleleft();
    }, 5000);
}
/*
setTimeout(() => {
    angleleft();
}, 3000);

setTimeout(() => {
    toggleObstacle("br", 1);
    toggleObstacle("tr", 1);

    ObstacleDetected(1);
    ManometerDetected(1);
}, 1000);

setTimeout(() => {
    toggleObstacle("br", 0);
    moveArc(30);
    ManometerDetected(0);
}, 10000);

*/