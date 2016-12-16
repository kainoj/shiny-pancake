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
        transparent: true,

        width:  500,
        height: 500,

        maxWidth:  500,
        maxHeight: 500
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
