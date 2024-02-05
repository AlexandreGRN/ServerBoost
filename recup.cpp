
class GreaterThan : public Condition<GreaterThan>
{
public:
    GreaterThan(std::string column, std::string value)
    {
        conditionString = column + " > " + value;
    }
    ~GreaterThan() = default;

    std::string retrieveConditionString()
    {
        return conditionString;
    }

private:
    std::string conditionString = "";
};

class EqualTo : public Condition<EqualTo>
{
public:
    EqualTo(std::string column, std::string value)
    {
        conditionString = column + " = " + value;
    }
    ~EqualTo() = default;

    std::string retrieveConditionString()
    {
        return conditionString;
    }

private:
    std::string conditionString = "";
};

class NotEqualTo : public Condition<NotEqualTo>
{
public:
    NotEqualTo(std::string column, std::string value)
    {
        conditionString = column + " != " + value;
    }
    ~NotEqualTo() = default;

    std::string retrieveConditionString()
    {
        return conditionString;
    }

private:
    std::string conditionString = "";
};

class StartWith : public Condition<StartWith>
{
public:
    StartWith(std::string column, std::string value)
    {
        conditionString = column + " LIKE '" + value + "%'";
    }
    ~StartWith() = default;

    std::string retrieveConditionString()
    {
        return conditionString;
    }

private:
    std::string conditionString = "";
};

class EndWith : public Condition<EndWith>
{
public:
    EndWith(std::string column, std::string value)
    {
        conditionString = column + " LIKE '%" + value + "'";
    }
    ~EndWith() = default;

    std::string retrieveConditionString()
    {
        return conditionString;
    }

private:
    std::string conditionString = "";
};

class NotStartWith : public Condition<NotStartWith>
{
public:
    NotStartWith(std::string column, std::string value)
    {
        conditionString = column + " NOT LIKE '" + value + "%'";
    }
    ~NotStartWith() = default;

    std::string retrieveConditionString()
    {
        return conditionString;
    }

private:
    std::string conditionString = "";
};

class NotEndWith : public Condition<NotEndWith>
{
public:
    NotEndWith(std::string column, std::string value)
    {
        conditionString = column + " NOT LIKE '%" + value + "'";
    }
    ~NotEndWith() = default;

    std::string retrieveConditionString()
    {
        return conditionString;
    }

private:
    std::string conditionString = "";
};

class Contain : public Condition<Contain>
{
public:
    Contain(std::string column, std::string value)
    {
        conditionString = column + " LIKE '%" + value + "%'";
    }
    ~Contain() = default;

    std::string retrieveConditionString()
    {
        return conditionString;
    }

private:
    std::string conditionString = "";
};

class NotContain : public Condition<NotContain>
{
public:
    NotContain(std::string column, std::string value)
    {
        conditionString = column + " NOT LIKE '%" + value + "%'";
    }
    ~NotContain() = default;

    std::string retrieveConditionString()
    {
        return conditionString;
    }

private:
    std::string conditionString = "";
};


{"Contain", &makeCondition<Contain>},
            {"NotContain", &makeCondition<NotContain>},
            {"StartWith", &makeCondition<StartWith>},
            {"EndWith", &makeCondition<EndWith>},
            {"NotStartWith", &makeCondition<NotStartWith>},
            {"NotEndWith", &makeCondition<NotEndWith>},
            {"EqualTo", &makeCondition<EqualTo>},
            {"NotEqualTo", &makeCondition<NotEqualTo>},
            {"GreaterThan", &makeCondition<GreaterThan>},