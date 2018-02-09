const Field = require('../lib/binding.js').Field;
const RecordCreator = require('../lib/binding.js').RecordCreator;
const RecordInfo = require("../lib/binding.js").RecordInfo;
const YXDB = require('../lib/binding.js').AlteryxYXDB;

const demo = () => {
  const record_info = new RecordInfo();
  record_info.add_field("count", 5);

  const count_field = record_info.get_field(0);

  const filename = 'D:\\Dev\\InnovationDays\\Open_AlteryxYXDB\\filename.yxdb';
  const file = new YXDB();
  file.create(filename, record_info.get_record_xml_meta_data());

  const record_creator = record_info.get_record_creator();

  for(let i = 0; i < 10; ++i)
  {
    record_creator.reset();
    count_field.set_from_number(record_creator, i);
    file.append_record(record_creator.finalize_record());
  }

  file.close();
};

demo();
