

// Function to move the arc gradually based on the specified angle
const arc = document.getElementById('arc');
arc.style.transformOrigin = "100px 100px"; // Set the rotation center of the arc

function moveArc(angle) {
    const arc = document.getElementById('arc');
    arc.style.transform = `rotate(${angle + 90}deg)`; // Rotate the arc with the given angle offset
}

let detectedPositions = []; // Array to store detected obstacle positions

function toggleObstacle(position, enable) {
    const validPositions = ['tl', 'tm', 'tr', 'bl', 'bm', 'br']; // Valid obstacle positions
    if (validPositions.includes(position)) {
        const obstacle = document.getElementById(`obstacle_${position}`);

        if (enable === 1) {
            obstacle.style.display = "flex"; // Display the obstacle
            if (!detectedPositions.includes(position)) {
                detectedPositions.push(position); // Add the position if not already in the array
            }
        } else if (enable === 0) {
            obstacle.style.display = "none"; // Hide the obstacle
            const index = detectedPositions.indexOf(position);
            if (index !== -1) {
                detectedPositions.splice(index, 1); // Remove the position if in the array
            }
        }
    } else {
        console.log("Invalid position."); // Log if the position is not in the specified list
    }
    if (detectedPositions.length > 0) {
        // Call another function if at least one obstacle is still detected
        ObstacleDetected(1);
    } else {
        ObstacleDetected(0);
    }
}

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

let intervalId = null;
const elementsToBlink = new Set();

function toggleDisplay(element, shouldDisplay) {
    if (shouldDisplay) {
        element.style.display = "flex"; // Set display to flex to show the element
    } else {
        element.style.display = "none"; // Hide the element
    }
}

let mano = 0;
let o1 = 0;
let o2 = 0;
let o3 = 0;
let o4 = 0;
let o5 = 0;
let o6 = 0;
let fire = 0;

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


function redirect(url) {
    window.location.href = url;
}

function changeBatteryLevel(BatteryLevel = "None") {
    var batteryText = document.getElementById('batteryLevel');
    batteryText.innerText = `Battery level: ${BatteryLevel}`;
}

function changeSpeed(speedvalue) {
    const SpeedText = document.getElementById('speedvalue');
    if (speedvalue > 0) {
        SpeedText.innerText = `Forward speed: ${speedvalue} rpm`;
    } else if (speedvalue < 0) {
        SpeedText.innerText = `Reverse speed: ${-speedvalue} rpm`;
    } else {
        SpeedText.innerText = "Car is currently stationary";
    }
}

document.addEventListener('keydown', waitFor);

// Function to move the arc left and right in intervals
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

setTimeout(() => {
    angleleft();
}, 3000);

// Timer for testing & demo
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

// ROS topic listener
var listener = new ROSLIB.Topic({
    ros: ros,
    name: '/motors_order',
    messageType: 'interfaces/msg/MotorsOrder'
});

// Subscribe to ROS topic and call the test function
listener.subscribe(test);

function test(message) {
    console.log('Message:', message.right_rear_pwm);
}