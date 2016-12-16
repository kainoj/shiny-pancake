const pancake = window.pancake = require('../build/Release/pancake');

const root = document.querySelector('#world');
const teams = {
    1: 'red',
    2: 'blue'
};

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
    fresh.setAttribute('r', 10);

    root.appendChild(fresh);

    return fresh;
}

function updateCell (cell, unit) {
    cell.setAttribute('cx', unit.posx);
    cell.setAttribute('cy', unit.posy);
    cell.setAttribute('fill', teams[unit.team]);
}
