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

/*
function toggleObstacle(position, enable) {
    const obstacle = document.getElementById(`obstacle_${position}`); // Sélection de tous les éléments avec la classe 'obstacle'
    if (enable == 1){
        obstacle.style.display = "flex";
    } else if (enable == 0){
        obstacle.style.display = "none";
    }


}*/

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
        toggleBlinking(fireContainer, true);
    } else if (isFireDetected === 0) {
        toggleBlinking(fireContainer, false);
    }
}

function ManometerDetected(isManometerDetected) {
    const ManometerContainer = document.getElementById("manometer_notif");

    if (isManometerDetected === 1) {
        toggleBlinking(ManometerContainer, true);
    } else if (isManometerDetected === 0) {
        toggleBlinking(ManometerContainer, false);
    }
}

function ObstacleDetected(isObstacleDetected) {
    const ObstacleContainer = document.getElementById("obstacle_notif");

    if (isObstacleDetected === 1) {
        toggleBlinking(ObstacleContainer, true);
    } else if (isObstacleDetected === 0) {
        toggleBlinking(ObstacleContainer, false);
    }
}

let intervalId = null;
const elementsToBlink = new Set();

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
function waitForO(event) {
    if (event.key === 'o') {
        // L'action que vous voulez exécuter une fois que 'o' est pressé
        alert("La touche 'o' a été pressée !");
        // Autre action que vous souhaitez réaliser ici
    }
    if (event.key === 'm') {
        // L'action que vous voulez exécuter une fois que 'o' est pressé
        if (mano == 1) {
            ManometerDetected(0);
            mano = 0;
        } else if (mano == 0) {
            ManometerDetected(1);
            mano = 1;
        }
        // Autre action que vous souhaitez réaliser ici
    }
    if (event.key === 'b') {
        // L'action que vous voulez exécuter une fois que 'o' est pressé
        changeBatteryLevel();
        // Autre action que vous souhaitez réaliser ici
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

function changeBatteryLevel() {
    var batteryText = document.getElementById('batteryLevel');
    if (batteryText.innerText.includes('High')) {
        batteryText.innerText = batteryText.innerText.replace('High', 'Low');
    } else if (batteryText.innerText.includes('Low')) {
        batteryText.innerText = batteryText.innerText.replace('Low', 'Medium');
    } else if (batteryText.innerText.includes('Medium')) {
        batteryText.innerText = batteryText.innerText.replace('Medium', 'High');
    }
}

document.addEventListener('keydown', waitForO);

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
