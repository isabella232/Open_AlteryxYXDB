const RecordInfo = require("../lib/binding.js").RecordInfo;

const demo = () => {
  const ri = new RecordInfo();
  ri.add_field("name", 5);

  console.log(ri.get_record_xml_meta_data());
};

demo();
