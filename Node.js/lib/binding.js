const addon = require('../../build/windows/Output/Node.js/Output/Debug/NodeJS_AlteryxYXDB');

// function NApiSandbox(name) {
//     var _addonInstance = new addon.NApiSandbox(name);
    
//     this.greet = function(str) {
//         return new Promise((resolve, reject) => {
//             let rsv = (str) => {
//                 console.log("entered resolve on js side");
//                 resolve(str);
//             }
//             _addonInstance.greet(str, rsv, reject);
//         });
//     };
// }

function RecordInfo() {
    var _addonInstance = new addon.RecordInfo();

    this.add_field = (name, type) => {
        return _addonInstance.add_field(name, type);
    }

    this.get_record_xml_meta_data = () => {
        return _addonInstance.get_record_xml_meta_data();
    }

    this.get_field = (idx) => {
        return _addonInstance.get_field();
    }
}

// function AlteryxYXDB () {
//     var _addonInstance = new addon.AlteryxYXDB();

//     this.create = (file, xml) => {
//         return _addonInstance.create(file, xml);
//     }

//     this.close = () => {
//         return _addonInstance.close();
//     }
// }

module.exports = {
    // NApiSandbox
    // , 
    RecordInfo
};
