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
    const endAngle =  CMDangle; // Angle final

    for (let i = startAngle; i !== endAngle; i += direction) {
        setTimeout(() => {
            deplacerArc(i);
        }, Math.abs(i - startAngle) * 20); // Déclenche l'animation à intervalles de 10 millisecondes
    }
    startAngle = endAngle;
}
newCmdAngle(-50);
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

