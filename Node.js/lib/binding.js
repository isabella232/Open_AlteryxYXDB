const addon = require('../../build/windows/Output/Node.js/Output/Debug/NodeJS_AlteryxYXDB');

function Field() {
    var _addonInstance = new addon.Field();

    this.get_field_name = () => {
        return _addonInstance.get_field_name();
    }
    
    this.get_as_number = (record_data) => {
        return _addonInstance.get_as_number(record_data);
    }

    this.set_from_number = (record_creator, number) => {
        return _addonInstance.set_from_number(record_creator, number);
    }
}

function RecordCreator() {
    var _addonInstance = new addon.RecordCreator();

    this.reset = () => {
        return _addonInstance.reset();
    }

    this.finalize_record = () => {
        return _addonInstance.finalize_record();
    }
}

function RecordInfo() {
    var _addonInstance = new addon.RecordInfo();

    this.add_field = (name, type) => {
        return _addonInstance.add_field(name, type);
    }

    this.get_record_xml_meta_data = () => {
        return _addonInstance.get_record_xml_meta_data();
    }

    this.get_field = (idx) => {
        return _addonInstance.get_field(idx);
    }

    this.get_record_creator = () => {
        return _addonInstance.get_record_creator();
    }
}

function AlteryxYXDB () {
    var _addonInstance = new addon.AlteryxYXDB();

    this.close = () => {
        return _addonInstance.close();
    }

    this.open = (filename) => {
        return _addonInstance.open(filename);
    }

    this.create = (file, xml) => {
        return _addonInstance.create(file, xml);
    }
}

module.exports = {
    AlteryxYXDB
    , Field
    , RecordCreator
    , RecordInfo
};
