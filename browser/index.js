const pancake = window.pancake = require('../build/Release/pancake');

const root = document.querySelector('#world');

let prev = performance.now();
let mult = 1;

requestAnimationFrame(function frame(now) {
  requestAnimationFrame(frame);
  draw(pancake.getData(mult / (now - prev) / 2));
  prev = now;
});

document.addEventListener('click',       event => (event.preventDefault(), ++mult));
document.addEventListener('contextmenu', event => (event.preventDefault(), --mult));
document.addEventListener('keydown',     event => (event.preventDefault(), document.body.classList.toggle('debug')));

function draw(data) {
  data.forEach(unit => updateCell(findCell(unit), unit));
}

function findCell(unit) {
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

  if (unit.type === 'Stats') {
    const stats = document.createElement('div');

    stats.id = unit._id_;
    stats.classList.add('stats');

    document.body.appendChild(stats);

    return stats;
  }

  const fresh = document.createElementNS('http://www.w3.org/2000/svg', 'g');
  const range =
      document.createElementNS('http://www.w3.org/2000/svg', 'circle');
  const unit1 =
      document.createElementNS('http://www.w3.org/2000/svg', 'circle');
  const unit2 =
      document.createElementNS('http://www.w3.org/2000/svg', 'circle');

  fresh.id = unit._id_;

  fresh.classList.add('team-' + unit.team);
  fresh.classList.add(unit.type);
  range.classList.add('range');
  unit1.classList.add('cell');
  unit2.classList.add('back');

  if (unit.type !== 'Bullet') {
    fresh.appendChild(unit2);
    fresh.classList.add('live');

    if (unit.type !== 'Spawner') {
      fresh.appendChild(range);
    }
  }

  fresh.appendChild(unit1);
  root.appendChild(fresh);

  return fresh;
}

function updateCell(cell, unit) {
  if (cell === null) {
    return;
  }

  if (unit.type === 'Stats') {
    cell.style.background = `-webkit-linear-gradient(left,
      rgb(20, 200, 200),
      rgb(20, 200, 200) ${unit.stats.team1 * 100 - 0.25}%,
      rgb(200, 200, 20) ${unit.stats.team1 * 100 + 0.25}%,
      rgb(200, 200, 20) ${(unit.stats.team1 + unit.stats.team2) * 100 - 0.25}%,
      rgb(200, 20, 200) ${(unit.stats.team1 + unit.stats.team2) * 100 + 0.25}%,
      rgb(200, 20, 200) ${(unit.stats.team1 + unit.stats.team2 + unit.stats.team3) * 100 - 0.25}%,
      rgb(100, 200, 20) ${(unit.stats.team1 + unit.stats.team2 + unit.stats.team3) * 100 + 0.25}%,
      rgb(100, 200, 20)
    )`;
    return;
  }

  cell.setAttribute('transform', `translate(${unit.posx}, ${unit.posy})`);

  if (unit.type === 'Basic') {
    cell.querySelector('.cell').setAttribute(
        'stroke-dashoffset', ~~(1000 - unit._hp_ / 100 * (1000 - 937)));
  } else if (unit.type === 'Spawner') {
    cell.querySelector('.cell').setAttribute(
        'stroke-dashoffset', ~~(1000 - unit._hp_ / 100 * (1000 - 844)));
  } else if (unit.type === 'Sniper') {
    cell.querySelector('.cell').setAttribute(
        'stroke-dashoffset', ~~(1000 - unit._hp_ / 100 * (1000 - 969)));
  } else if (unit.type === 'Tank') {
    cell.querySelector('.cell').setAttribute(
        'stroke-dashoffset', ~~(1000 - unit._hp_ / 100 * (1000 - 906)));
  }
}
