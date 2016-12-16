const pancake = require('../build/Release/pancake');

const root = document.querySelector('#world');
const teams = {
    1: 'red',
    2: 'blue'
};

alert(pancake ? ':)' : ':(');

requestAnimationFrame(function frame () {
    requestAnimationFrame(frame);
    draw(data());
});

function data () {
    // TODO: C++
    return [{
        _id_: 0,
        posx: 20,
        posy: 30,
        type: 'dummy',
        team: 1
    }, {
        _id_: 1,
        posx: 200,
        posy: 300,
        type: 'dummy',
        team: 2
    }];
}

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
