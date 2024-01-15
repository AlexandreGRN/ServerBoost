#include "../libraries.hpp"

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
        object.AddMember("User", rapidjson::Value(Row[0].c_str(), Row[0].size()), document.GetAllocator());
        object.AddMember("first_name", rapidjson::Value(Row[1].c_str(), Row[1].size()), document.GetAllocator());
        object.AddMember("last_name", rapidjson::Value(Row[2].c_str(), Row[2].size()), document.GetAllocator());
        document.AddMember("User", object, document.GetAllocator());

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
            object.AddMember("ID", rapidjson::Value(Table[i][0].c_str(), Table[i][0].size(), allocator), document.GetAllocator());
            object.AddMember("first_name", rapidjson::Value(Table[i][1].c_str(), Table[i][1].size(), allocator), document.GetAllocator());
            object.AddMember("last_name", rapidjson::Value(Table[i][2].c_str(), Table[i][2].size(), allocator), document.GetAllocator());
            array.PushBack(object, document.GetAllocator());
        }
        document.AddMember("Users", array, document.GetAllocator());

        // JSON to string
        rapidjson::StringBuffer strbuf;
        rapidjson::Writer<rapidjson::StringBuffer> writer(strbuf);
        document.Accept(writer);
        return strbuf.GetString();
    }
};