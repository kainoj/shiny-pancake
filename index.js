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
        fullscreen: true,
        transparent: true,

        width:  1920,
        height: 1080
    });

    window.setIgnoreMouseEvents(true);
    window.loadURL(url.format({
        pathname: path.join(__dirname, 'browser/index.html'),
        protocol: 'file:',
        slashes: true
    }));

    window.on('closed', function () {
        window = null;
    });
}
