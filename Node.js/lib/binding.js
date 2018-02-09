const addon = require('../../build/windows/Output/Node.js/Output/Debug/NodeJS_AlteryxYXDB');

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

    this.append_record = (record_data) => {
        return _addonInstance.append_record(record_data);
    }
}

function Field(field) {
    var _addonInstance = field;

    this.get_field_name = () => {
        return _addonInstance.get_field_name();
    }
    
    this.get_as_number = (record_data) => {
        return _addonInstance.get_as_number(record_data);
    }

    this.set_from_number = (record_creator, number) => {
        return _addonInstance.set_from_number(record_creator.get(), number);
    }
}

function RecordCreator(rec_cre) {
    var _addonInstance = rec_cre;

    this.reset = () => {
        return _addonInstance.reset();
    }

    this.finalize_record = () => {
        return _addonInstance.finalize_record();
    }

    this.get = () => {
        return _addonInstance.get();
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
        return new Field(_addonInstance.get_field(idx));
    }

    this.get_record_creator = () => {
        return new RecordCreator(_addonInstance.get_record_creator());
    }
}

module.exports = {
    AlteryxYXDB
    , Field
    , RecordCreator
    , RecordInfo
};
