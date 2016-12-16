const context = createCanvas({width: 300, height: 300});

requestAnimationFrame(function frame () {
    requestAnimationFrame(frame);
    draw(data());
});

function createCanvas (options) {
    const canvas  = document.querySelector('canvas');
    const context = canvas.getContext('2d');

    canvas.width  = options.width;
    canvas.height = options.height;

    return context;
}

function data () {
    // TODO: C++
}

function draw (data) {
    // TODO: Everything!
}
