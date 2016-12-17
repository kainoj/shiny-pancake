const electron = require('electron');
const path     = require('path');
const url      = require('url');

let window;

electron.app.on('activate', function () {
    if (window === null) {
        createWindow();
    }
});

electron.app.on('ready', createWindow);

electron.app.on('window-all-closed', function () {
    if (process.platform !== 'darwin') {
        electron.app.quit();
    }
});

function createWindow () {
    window = new electron.BrowserWindow({
        frame: false,
        center: true,
        fullscreen: true,
        transparent: true,

        width:  1920,
        height: 1080,

        maxWidth:  1920,
        maxHeight: 1080,

        minWidth:  1920,
        minHeight: 1080
    });

    window.loadURL(url.format({
        pathname: path.join(__dirname, 'browser/index.html'),
        protocol: 'file:',
        slashes: true
    }));

    window.on('closed', function () {
        window = null;
    });
}
