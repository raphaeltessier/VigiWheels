// Fonction pour déplacer l'arc progressivement en fonction de l'angle spécifié
const arc = document.getElementById('arc');
arc.style.transformOrigin = "100px 100px"; // Changement du centre de rotation


function deplacerArc(angle) {
    const arc = document.getElementById('arc');
    arc.style.transform = `rotate(${angle}deg)`;

}

let startAngle = 0;
function newCmdAngle(CMDangle) {
    const absCMDangle = Math.abs(CMDangle);
    const direction = CMDangle < startAngle ? -1 : 1;

    // Angle de départ
    const endAngle = CMDangle; // Angle final

    for (let i = startAngle; i !== endAngle; i += direction) {
        setTimeout(() => {
            deplacerArc(i);
        }, Math.abs(i - startAngle) * 20); // Déclenche l'animation à intervalles de 10 millisecondes
    }
    startAngle = endAngle;
}

let detectedPositions = []; // Tableau pour stocker les positions détectées

function toggleObstacle(position, enable) {
    const validPositions = ['tl', 'tm', 'tr', 'bl', 'bm', 'br'];

    if (validPositions.includes(position)) {
        const obstacle = document.getElementById(`obstacle_${position}`);

        if (enable === 1) {
            obstacle.style.display = "flex";
            if (!detectedPositions.includes(position)) {
                detectedPositions.push(position); // Ajoute la position si elle n'est pas déjà dans le tableau
            }
        } else if (enable === 0) {
            obstacle.style.display = "none";
            const index = detectedPositions.indexOf(position);
            if (index !== -1) {
                detectedPositions.splice(index, 1); // Enlève la position si elle est dans le tableau
            }
        }
    } else {
        console.log("Position non valide."); // Si la position n'est pas dans la liste spécifiée
    }
    if (detectedPositions.length > 0) {
        // Appeler une autre fonction si au moins un obstacle est encore détecté
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
        toggleDisplay(fireContainer, true);
    } else if (isFireDetected === 0) {
        toggleDisplay(fireContainer, false);
    }
}

function ManometerDetected(isManometerDetected, value = 0) {
    const ManometerContainer = document.getElementById("manometer_notif");
    const manometerText = ManometerContainer.querySelector('.big-icon-text');

    if (isManometerDetected === 1) {
        if (value !== 0) {
            manometerText.innerText = "Manometer detected \n(value read: " + value + ")";
        } else {
            manometerText.innerText = "Manometer detected \n(no value read)";
        }
        toggleDisplay(ManometerContainer, true);
    } else if (isManometerDetected === 0) {
        toggleDisplay(ManometerContainer, false);
    }
}

function ObstacleDetected(isObstacleDetected) {
    const ObstacleContainer = document.getElementById("obstacle_notif");

    if (isObstacleDetected === 1) {
        toggleDisplay(ObstacleContainer, true);
    } else if (isObstacleDetected === 0) {
        toggleDisplay(ObstacleContainer, false);
    }
}

let intervalId = null;
const elementsToBlink = new Set();


function toggleDisplay(element, shouldDisplay) {
    if (shouldDisplay) {
        element.style.display = "flex";
    } else {
        element.style.display = "none";
    }
}

function toggleBlinking(element, shouldBlink) {
    if (shouldBlink) {
        elementsToBlink.add(element);
    } else {
        elementsToBlink.delete(element);
        if (elementsToBlink.size === 0) {
            clearInterval(intervalId);
            intervalId = null;
        }
    }

    if (!intervalId) {
        intervalId = setInterval(() => {
            for (const el of elementsToBlink) {
                el.style.display = (el.style.display === 'none') ? 'flex' : 'none';
            }
        }, 800); // Alterne toutes les 1 seconde entre affichage et disparition (500ms de chaque côté)
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
    if (event.key === 'm') {
        if (mano == 1) {
            ManometerDetected(0,150);
            mano = 0;
        } else if (mano == 0) {
            ManometerDetected(1,150);
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
        if (o2 === 0) {
            toggleObstacle("tm", 1);
            o2 = 1;
        } else if (o2 === 1) {
            toggleObstacle("tm", 0);
            o2 = 0;
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

function angleleft() {
    newCmdAngle(-80);
    setTimeout(() => {
        angleright();
    }, 5000);
}
function angleright() {
    newCmdAngle(80);
    setTimeout(() => {
        angleleft();
    }, 5000);
}

setTimeout(() => {
    angleleft();
}, 3000);

/*
// Timer pour test & démo
setTimeout(() => {
    toggleObstacle("br",1);
    toggleObstacle("tr",1);

    ObstacleDetected(1);
    ManometerDetected(1);

}, 1000); 

setTimeout(() => {
    toggleObstacle("br",0);
    newCmdAngle(30);
    ManometerDetected(0);

}, 10000); 
*/
