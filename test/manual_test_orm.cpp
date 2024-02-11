#include <iostream>
#include <string>
#include <cstdarg>
#include <vector>

enum class TableType
{
    User
};

enum class ColumnType
{
    Id,
    FirstName,
    LastName,
    Age,
    Building,
    Genre
};

enum OperatorType
{
    And,
    Or
};

class Table
{
public:
    std::string getTable(const TableType& tableType) const
    {
        if (tableType == TableType::User)
            return "user";
        return "";
    }
};

template <typename... Args>
class Select_ {
public:

    Select_(const TableType& tableType, Args... args)
    {
        SelectString = "SELECT * from " + Table{}.getTable(tableType) + " WHERE ";
        processArgs(args...);
    }
    ~Select_() = default;

    const std::string& retrieveSelectString()
    {
        return SelectString;
    }

private:
    template <typename T>
    void makeFilterBody(const T& arg)
    {
        if (isFirstCondition)
            isFirstCondition = false;
        else
            SelectString += arg.retrieveOperator();
        SelectString += arg.retrieveConditionString();
    }

    // Create the vector of argument strings
    void processArgs(Args... args) {processSingleArg(args...);}
    template <typename T>
    void processSingleArg(const T& arg) {
        makeFilterBody(arg);
    }

    template <typename T, typename... Rest>
    void processSingleArg(const T& arg, Rest... rest) {
        makeFilterBody(arg);
        processSingleArg(rest...);
    }

    std::string SelectString = "";
    bool isFirstCondition = true;
};

template <typename... Args>
class Filter_
{
public:
    // Multiple conditions constructor
    Filter_(Args... args)
    {
        // Make minor filter
        if (sizeof...(args) == 1)
        {
            processArgs(args...);
        }
        // Make major filter
        else
        {
            processArgs(args...);
        }
    }
    ~Filter_() = default;

    std::string retrieveConditionString() const
    {
        return "(" + filterString + ")";
    }

    std::string retrieveOperator() const
    {
        if (operator_ == OperatorType::And)
            return " AND ";
        else
            return " OR ";
    }

private:

    // minor filter
    void makeGroupConditionString(const std::string& arg)
    {
        filterString += arg;
    }

    template<typename T>
    void makeGroupConditionString(const T& arg)
    {
        if (isFirstCondition)
            isFirstCondition = false;
        else
            filterString += arg.retrieveOperator();
        filterString += arg.retrieveConditionString();
    }

    // Create the filter strings
    void processArgs(Args... args) {processSingleArg(args...);}
    template <typename T>
    void processSingleArg(const T arg) {
        makeGroupConditionString(arg);
    }
    template <typename T, typename... Rest>
    void processSingleArg(const T arg, Rest... rest) {
        makeGroupConditionString(arg);
        processSingleArg(rest...);
    }

    OperatorType operator_ = And;
    std::string filterString = "";
    bool isFirstCondition = true;
};

class IdColumn
{
public:
    ColumnType getColumn() const
    {
        return ColumnType::Id;
    }
};

class FirstNameColumn
{
public:
    ColumnType getColumn() const
    {
        return ColumnType::FirstName;
    }
};

class LastNameColumn
{
public:
    ColumnType getColumn() const
    {
        return ColumnType::LastName;
    }
};

class AgeColumn
{
public:
    ColumnType getColumn() const
    {
        return ColumnType::Age;
    }
};

class BuildingColumn
{
public:
    ColumnType getColumn() const
    {
        return ColumnType::Building;
    }
};

class GenreColumn
{
public:
    ColumnType getColumn() const
    {
        return ColumnType::Genre;
    }
};

template <typename Column>
class LesserThan
{
public:
    LesserThan(const std::string& value)
    {
        switch (Column{}.getColumn())
        {
        case ColumnType::Id:
            conditionString = "ID < " + value;
            break;
        case ColumnType::FirstName:
            conditionString = "first_name < " + value;
            break;
        case ColumnType::LastName:
            conditionString = "last_name < " + value;
            break;
        }
    }
    ~LesserThan() = default;

    const std::string& retrieveConditionString() const
    {
        return conditionString;
    }

    std::string retrieveOperator() const { return "";}

    std::string conditionString;
};

template <typename Column>
class GreaterThan
{
public:
    GreaterThan(const std::string& value)
    {
        switch (Column{}.getColumn())
        {
        case ColumnType::Id:
            conditionString = "ID > " + value;
            break;
        case ColumnType::FirstName:
            conditionString = "first_name > " + value;
            break;
        case ColumnType::LastName:
            conditionString = "last_name > " + value;
            break;
        }
    }
    ~GreaterThan() = default;

    const std::string& retrieveConditionString() const
    {
        return conditionString;
    }

    std::string retrieveOperator() const { return "";}

    std::string conditionString;
};

template <typename Column>
class EqualTo
{
public:
    EqualTo(const std::string& value)
    {
        switch (Column{}.getColumn())
        {
        case ColumnType::Id:
            conditionString = "ID = " + value;
            break;
        case ColumnType::FirstName:
            conditionString = "first_name = " + value;
            break;
        case ColumnType::LastName:
            conditionString = "last_name = " + value;
            break;
        }
    }

    const std::string& retrieveConditionString() const
    {
        return conditionString;
    }

    std::string retrieveOperator() const { return "";}

    std::string conditionString;
};

template <typename Column>
class NotEqualTo
{
public:
    NotEqualTo(const std::string& value)
    {
        switch (Column{}.getColumn())
        {
        case ColumnType::Id:
            conditionString = "ID != " + value;
            break;
        case ColumnType::FirstName:
            conditionString = "first_name != " + value;
            break;
        case ColumnType::LastName:
            conditionString = "last_name != " + value;
            break;
        }
    }

    ~NotEqualTo() = default;
    std::string retrieveConditionString() const
    {
        return conditionString;
    }
    std::string retrieveOperator() const { return "";}
    std::string conditionString = "";
};

template <typename Column>
class StartWith
{
public:
    StartWith(const std::string& value)
    {
        switch (Column{}.getColumn())
        {
        case ColumnType::Id:
            conditionString = "ID LIKE '" + value + "%'";
            break;
        case ColumnType::FirstName:
            conditionString = "first_name LIKE '" + value + "%'";
            break;
        case ColumnType::LastName:
            conditionString = "last_name LIKE '" + value + "%'";
            break;
        }
    }
    ~StartWith() = default;

    std::string retrieveConditionString() const
    {
        return conditionString;
    }
    std::string retrieveOperator() const { return "";}
    std::string conditionString = "";
};

template <typename Column>
class EndWith
{
public:
    EndWith(const std::string& value)
    {
        switch (Column{}.getColumn())
        {
        case ColumnType::Id:
            conditionString = "ID LIKE '%" + value + "'";
            break;
        case ColumnType::FirstName:
            conditionString = "first_name LIKE '%" + value + "'";
            break;
        case ColumnType::LastName:
            conditionString = "last_name LIKE '%" + value + "'";
            break;
        }
    }
    ~EndWith() = default;

    std::string retrieveConditionString() const
    {
        return conditionString;
    }
    std::string retrieveOperator() const { return "";}
    std::string conditionString = "";
};

template <typename Column>
class NotStartWith
{
public:
    NotStartWith(const std::string& value)
    {
        switch (Column{}.getColumn())
        {
        case ColumnType::Id:
            conditionString = "ID NOT LIKE '" + value + "%'";
            break;
        case ColumnType::FirstName:
            conditionString = "first_name NOT LIKE '" + value + "%'";
            break;
        case ColumnType::LastName:
            conditionString = "last_name NOT LIKE '" + value + "%'";
            break;
        }
    }
    ~NotStartWith() = default;

    std::string retrieveConditionString() const
    {
        return conditionString;
    }
    std::string retrieveOperator() const { return "";}
    std::string conditionString = "";
};

template <typename Column>
class NotEndWith
{
public:
    NotEndWith(std::string value)
    {
        switch (Column{}.getColumn())
        {
        case ColumnType::Id:
            conditionString = "ID NOT LIKE '%" + value + "'";
            break;
        case ColumnType::FirstName: 
            conditionString = "first_name NOT LIKE '%" + value + "'";
            break;
        case ColumnType::LastName:
            conditionString = "last_name NOT LIKE '%" + value + "'";
            break;
        }
    }
    ~NotEndWith() = default;

    std::string retrieveConditionString() const
    {
        return conditionString;
    }
    std::string retrieveOperator() const { return "";}
    std::string conditionString = "";
};

template <typename Column>
class Contain
{
public:
    Contain(const std::string& value)
    {
        switch (Column{}.getColumn())
        {
        case ColumnType::Id:
            conditionString = "ID LIKE '%" + value + "%'";
            break;
        case ColumnType::FirstName:
            conditionString = "first_name LIKE '%" + value + "%'";
            break;
        case ColumnType::LastName:
            conditionString = "last_name LIKE '%" + value + "%'";
            break;
        }
    }
    ~Contain() = default;

    const std::string& retrieveConditionString() const
    {
        return conditionString;
    }
    
    std::string retrieveOperator() const { return "";}
    std::string conditionString = "";
};

template <typename Column>
class NotContain
{
public:
    NotContain(const std::string& value)
    {
        switch (Column{}.getColumn())
        {
        case ColumnType::Id:
            conditionString = "ID NOT LIKE '%" + value + "%'";
            break;
        case ColumnType::FirstName:
            conditionString = "first_name NOT LIKE '%" + value + "%'";
            break;
        case ColumnType::LastName:
            conditionString = "last_name NOT LIKE '%" + value + "%'";
            break;
        }
    }
    ~NotContain() = default;

    const std::string& retrieveConditionString() const
    {
        return conditionString;
    }
    
    std::string retrieveOperator() const { return "";}
    std::string conditionString = "";
};

int main(int argc, char* argv[])
{
    Select_ a(TableType::User, Filter_(Filter_(EqualTo<IdColumn>("1")), Filter_(StartWith<FirstNameColumn>("x")), Filter_(StartWith<LastNameColumn>("y"))));
    std::cout << a.retrieveSelectString() << std::endl;   
}
