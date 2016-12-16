const pancake = window.pancake = require('../build/Release/pancake');

const root = document.querySelector('#world');

requestAnimationFrame(function frame () {
    requestAnimationFrame(frame);
    draw(pancake.getData());
});

function draw (data) {
    data.forEach(unit => updateCell(findCell(unit), unit));
}

function findCell (unit) {
    const existing = document.getElementById(unit._id_);

    if (existing) {
        return existing;
    }

    const fresh = document.createElementNS('http://www.w3.org/2000/svg', 'circle');

    fresh.id = unit._id_;

    fresh.classList.add(unit.type);
    fresh.classList.add('team-' + unit.team);

    if (unit.type === 'Basic') {
        fresh.setAttribute('r', 10);
        fresh.classList.add('live');
    } else if (unit.type === 'Bullet') {
        fresh.setAttribute('r', 2);
    } else if (unit.type === 'Spawner') {
        fresh.setAttribute('r', 25);
        fresh.classList.add('live');
    }

    root.appendChild(fresh);

    return fresh;
}

function updateCell (cell, unit) {
    cell.setAttribute('cx', unit.posx);
    cell.setAttribute('cy', unit.posy);

    if (unit.type === 'Spawner') {
        cell.setAttribute('stroke-dashoffset', ~~(100 - unit._hp_ / 100 * (1000 - 844)));
    } else {
        cell.setAttribute('stroke-dashoffset', ~~(100 - unit._hp_ / 100 * (1000 - 937)));
    }
}
