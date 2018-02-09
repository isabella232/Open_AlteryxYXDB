import os, sys
sys.path.insert(0, 'W:/git/Open_AlteryxYXDB/build/windows/Output/Python/Output/Debug')
import Python_AlteryxYXDB as a


def EnglishNumber(int):
    return ''.join(['str(', str(int), ')'])


def WriteSampleFile(pFile):

	# // the RecordInfo structure defines a record for the YXDB file.
	# SRC::RecordInfo recordInfoOut;
    recordInfoOut = a.record_info()

	# // Before you can create a YXDB, you need to tell the RecordInfo what fields it will expect
	# // Use CreateFieldXML to properly format the XML that describes a field
	# recordInfoOut.AddField(SRC::RecordInfo::CreateFieldXml(L"Number", SRC::E_FT_Double));
    recordInfoOut.add_field("Number", a.FieldType.double)
	# recordInfoOut.AddField(SRC::RecordInfo::CreateFieldXml(L"English", SRC::E_FT_V_String, 256));
    recordInfoOut.add_field("English", a.FieldType.v_string, 256)

	# //Now that we have defined the fields, we can create the file.
	# Alteryx::OpenYXDB::Open_AlteryxYXDB fileOut;
    fileOut = a.AlteryxYXDB()

	# fileOut.Create(pFile, recordInfoOut.GetRecordXmlMetaData());
    fileOut.create(pFile, recordInfoOut.get_record_xml_meta_data())

    # // in order to add a record to the file, we need to create an empty record and then fill it in
    # SRC::SmartPointerRefObj<SRC::Record> pRec = recordInfoOut.CreateRecord();
    pRec = recordInfoOut.construct_record_creator()

    # create a bunch of records and populate values for the 2 columns
    for v in range(1000):
        pRec.reset()
        recordInfoOut[0].set_from_int32(pRec, v)
        recordInfoOut[1].set_from_string(pRec, EnglishNumber(v))
        fileOut.append_record(pRec.finalize_record())


def ReadSampleFile(pFile):
    pass

    fileIn = a.AlteryxYXDB()
    fileIn.open(pFile)







write_test = False
read_test  = True
write_filepath = 'w:/temp/test.yxdb'
read_filepath = write_filepath

if write_test:
    print('-- test: WriteSampleFile --')
    try:
        WriteSampleFile(write_filepath)
        print('test success!')
    except Exception as e:
        print('error: womp womp')
        print(e)

if read_test:
    print('-- test: ReadSampleFile --')
    try:
        ReadSampleFile(read_filepath)
        print('test success!')
    except Exception as e:
        print('error: womp womp')
        print(e)



# try:
#     file = a.AlteryxYXDB()
#     file.create(r'W:\temp\something.yxdb', r'<RecordInfo><Field name="Field1" size="3" source="TextInput:" type="String" /><Field name="Field2" source="TextInput:" type="Byte" /></RecordInfo>')
#
#     print('test success!')
# except:
#     print('error: womp womp')
