#include "../../libraries.hpp"

class JSonConverter
{
public:
    JSonConverter() = default;
    ~JSonConverter() = default;

    std::string ToJson(std::vector<std::string> Row)
    {
        // JSON setup
        rapidjson::Document document;
        document.SetObject();
        rapidjson::Document::AllocatorType& allocator = document.GetAllocator();
        rapidjson::Value object(rapidjson::kObjectType);

        // JSON data insertion
        object.AddMember("ID",         rapidjson::Value(Row[0].c_str(), Row[0].size()), allocator);
        object.AddMember("first_name", rapidjson::Value(Row[1].c_str(), Row[1].size()), allocator);
        object.AddMember("last_name",  rapidjson::Value(Row[2].c_str(), Row[2].size()), allocator);
        object.AddMember("age",        rapidjson::Value(Row[3].c_str(), Row[3].size()), allocator);
        document.AddMember("User", object, allocator);

        // JSON to string
        rapidjson::StringBuffer strbuf;
        rapidjson::Writer<rapidjson::StringBuffer> writer(strbuf);
        document.Accept(writer);
        return strbuf.GetString();
    }

    std::string ToJson(std::vector<std::vector<std::string>> Table)
    {
        // JSON setup
        rapidjson::Document document;
        document.SetObject();
        rapidjson::Document::AllocatorType& allocator = document.GetAllocator();
        rapidjson::Value array(rapidjson::kArrayType);

        // JSON data insertion
        for (int i = 0; i < Table.size(); i++)
        {
            rapidjson::Value object(rapidjson::kObjectType);
            object.AddMember("ID",         rapidjson::Value(Table[i][0].c_str(), Table[i][0].size(), allocator), allocator);
            object.AddMember("first_name", rapidjson::Value(Table[i][1].c_str(), Table[i][1].size(), allocator), allocator);
            object.AddMember("last_name",  rapidjson::Value(Table[i][2].c_str(), Table[i][2].size(), allocator), allocator);
            object.AddMember("age",        rapidjson::Value(Table[i][3].c_str(), Table[i][3].size(), allocator), allocator);
            array.PushBack(object, allocator);
        }
        document.AddMember("Users", array, allocator);

        // JSON to string
        rapidjson::StringBuffer strbuf;
        rapidjson::Writer<rapidjson::StringBuffer> writer(strbuf);
        document.Accept(writer);
        return strbuf.GetString();
    }
};