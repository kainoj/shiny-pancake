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
        if (unit._hp_ <= 0) {
            root.removeChild(existing);
            return null;
        }

        return existing;
    }

    if (unit._hp_ <= 0) {
        return null;
    }

    const fresh = document.createElementNS('http://www.w3.org/2000/svg', 'g');
    const range = document.createElementNS('http://www.w3.org/2000/svg', 'circle');
    const unit1 = document.createElementNS('http://www.w3.org/2000/svg', 'circle');
    const unit2 = document.createElementNS('http://www.w3.org/2000/svg', 'circle');

    fresh.id = unit._id_;

    fresh.classList.add(unit.type);
    fresh.classList.add('team-' + unit.team);

    unit1.classList.add('cell');
    unit2.classList.add('back');

    if (unit.type === 'Basic') {
        unit1.setAttribute('r', 10);
        range.classList.add('range');
        fresh.classList.add('live');
        fresh.appendChild(unit2);
        fresh.appendChild(range);
    } else if (unit.type === 'Bullet') {
        unit1.setAttribute('r', 2);
    } else if (unit.type === 'Spawner') {
        unit1.setAttribute('r', 25);
        fresh.classList.add('live');
        fresh.appendChild(unit2);
    } else if (unit.type === 'Tank') {
        unit1.setAttribute('r', 15);
        range.classList.add('range');
        fresh.classList.add('live');
        fresh.appendChild(unit2);
        fresh.appendChild(range);
    }

    fresh.appendChild(unit1);
    root.appendChild(fresh);

    return fresh;
}

function updateCell (cell, unit) {
    if (cell === null) {
        return;
    }

    cell.setAttribute('transform', `translate(${unit.posx}, ${unit.posy})`);

    if (unit.type === 'Basic') {
        cell.querySelector('.cell').setAttribute('stroke-dashoffset', ~~(1000 - unit._hp_ / 100 * (1000 - 937)));
    } else if (unit.type === 'Spawner') {
        cell.querySelector('.cell').setAttribute('stroke-dashoffset', ~~(1000 - unit._hp_ / 100 * (1000 - 844)));
    } else if (unit.type === 'Tank') {
        cell.querySelector('.cell').setAttribute('stroke-dashoffset', ~~(1000 - unit._hp_ / 100 * (1000 - 906)));
    }
}
