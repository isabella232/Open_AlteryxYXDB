const Field = require('../lib/binding.js').Field;
const RecordCreator = require('../lib/binding.js').RecordCreator;
const RecordInfo = require("../lib/binding.js").RecordInfo;
const YXDB = require('../lib/binding.js').AlteryxYXDB;

const demo = () => {
  const ri = new RecordInfo();
  ri.add_field("name", 5);
  console.log(ri.get_record_xml_meta_data());

  console.log('getting a field');
  const f = ri.get_field(0);
  console.log("got a field; it's name is: ");
  console.log(f.get_field_name());

  const record_creator = ri.get_record_creator();

  const filename = 'D:\\Dev\\InnovationDays\\Open_AlteryxYXDB\\filename.yxdb';
  const file = new YXDB();
  console.log('constructed a YXDB object');
  file.create(filename, ri.get_record_xml_meta_data());
  console.log('created YXDB file');
  file.close();
  console.log('closed YXDB file');
  console.log('finished demo!');
};

demo();
