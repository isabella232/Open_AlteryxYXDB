const addon = require('../../build/windows/Output/Node.js/Output/Debug/NodeJS_AlteryxYXDB');

function NApiSandbox(name) {
    var _addonInstance = new addon.NApiSandbox(name);
    
    this.greet = function(str) {
        return new Promise((resolve, reject) => {
            let rsv = (str) => {
                console.log("entered resolve on js side");
                resolve(str);
            }
            _addonInstance.greet(str, rsv, reject);
        });
    };
}

module.exports = NApiSandbox;
