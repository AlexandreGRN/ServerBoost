#define BOOST_TEST_MODULE ORMTest
#include <boost/test/included/unit_test.hpp>
#include "../src/libraries.hpp"
#include "../src/MySQL_orm/mysql_orm_libraries.hpp"
#include "../src/MySQL_orm/Actions/Select.hpp"
#include "../src/Servers/Server.hpp"

// Create a Basic Select_ object of every Column compared to a string
BOOST_AUTO_TEST_CASE(test_column)
{
    // IdColumn
    Select_ selectID(TableType::User, Filter_(GreaterThan<IdColumn>("1")));
    BOOST_CHECK_EQUAL(selectID.retrieveSelectString(), "SELECT * FROM user WHERE (ID > 1)");

    // AgeColumn
    Select_ selectAGE(TableType::User, Filter_(GreaterThan<AgeColumn>("1")));
    BOOST_CHECK_EQUAL(selectAGE.retrieveSelectString(), "SELECT * FROM user WHERE (age > 1)");

    // FirstNameColumn
    Select_ selectFIRSTNAME(TableType::User, Filter_(GreaterThan<FirstNameColumn>("1")));
    BOOST_CHECK_EQUAL(selectFIRSTNAME.retrieveSelectString(), "SELECT * FROM user WHERE (first_name > 1)");

    // LastNameColumn
    Select_ selectLASTNAME(TableType::User, Filter_(GreaterThan<LastNameColumn>("1")));
    BOOST_CHECK_EQUAL(selectLASTNAME.retrieveSelectString(), "SELECT * FROM user WHERE (last_name > 1)");

    // BuildingColumn
    Select_ selectBUILDING(TableType::User, Filter_(GreaterThan<BuildingColumn>("1")));
    BOOST_CHECK_EQUAL(selectBUILDING.retrieveSelectString(), "SELECT * FROM user WHERE (building > 1)");

    // GenreColumn
    Select_ selectGENRE(TableType::User, Filter_(GreaterThan<GenreColumn>("1")));
    BOOST_CHECK_EQUAL(selectGENRE.retrieveSelectString(), "SELECT * FROM user WHERE (genre > 1)");
}

// Create a Basic Select_ object + All comparison of IDColumn to a string
BOOST_AUTO_TEST_CASE(test_conditions_string)
{
    
     // Arithmetic
      // GreaterThan
        Select_ selectID(TableType::User, Filter_(GreaterThan<IdColumn>("1")));
        BOOST_CHECK_EQUAL(selectID.retrieveSelectString(), "SELECT * FROM user WHERE (ID > 1)");

      // LesserThan
        Select_ selectID2(TableType::User, Filter_(LesserThan<IdColumn>("1")));
        BOOST_CHECK_EQUAL(selectID2.retrieveSelectString(), "SELECT * FROM user WHERE (ID < 1)");

      // EqualTo
        Select_ selectID3(TableType::User, Filter_(EqualTo<IdColumn>("1")));
        BOOST_CHECK_EQUAL(selectID3.retrieveSelectString(), "SELECT * FROM user WHERE (ID = 1)");

      // NotEqualTo
        Select_ selectID4(TableType::User, Filter_(NotEqualTo<IdColumn>("1")));
        BOOST_CHECK_EQUAL(selectID4.retrieveSelectString(), "SELECT * FROM user WHERE (ID != 1)");

     // Character comparison
      // StartWith
        Select_ selectID5(TableType::User, Filter_(StartWith<IdColumn>("1")));
        BOOST_CHECK_EQUAL(selectID5.retrieveSelectString(), "SELECT * FROM user WHERE (ID LIKE '1%')");

      // EndWith
        Select_ selectID6(TableType::User, Filter_(EndWith<IdColumn>("1")));
        BOOST_CHECK_EQUAL(selectID6.retrieveSelectString(), "SELECT * FROM user WHERE (ID LIKE '%1')");

      // Contain
        Select_ selectID7(TableType::User, Filter_(Contain<IdColumn>("1")));
        BOOST_CHECK_EQUAL(selectID7.retrieveSelectString(), "SELECT * FROM user WHERE (ID LIKE '%1%')");

      // NotContain
        Select_ selectID8(TableType::User, Filter_(NotContain<IdColumn>("1")));
        BOOST_CHECK_EQUAL(selectID8.retrieveSelectString(), "SELECT * FROM user WHERE (ID NOT LIKE '%1%')");

      // NotStartWith
        Select_ selectID9(TableType::User, Filter_(NotStartWith<IdColumn>("1")));
        BOOST_CHECK_EQUAL(selectID9.retrieveSelectString(), "SELECT * FROM user WHERE (ID NOT LIKE '1%')");

      // NotEndWith
        Select_ selectID10(TableType::User, Filter_(NotEndWith<IdColumn>("1")));
        BOOST_CHECK_EQUAL(selectID10.retrieveSelectString(), "SELECT * FROM user WHERE (ID NOT LIKE '%1')");
}

// Create a Basic Select_ object + All comparison of IDColumn to an int
BOOST_AUTO_TEST_CASE(test_conditions_int)
{
    // Create a Basic Select_ object + All comparison of IDColumn to an int
     // Arithmetic
      // GreaterThan
        Select_ selectID(TableType::User, Filter_(GreaterThan<IdColumn>(1)));
        BOOST_CHECK_EQUAL(selectID.retrieveSelectString(), "SELECT * FROM user WHERE (ID > 1)");

      // LesserThan
        Select_ selectID2(TableType::User, Filter_(LesserThan<IdColumn>(1)));
        BOOST_CHECK_EQUAL(selectID2.retrieveSelectString(), "SELECT * FROM user WHERE (ID < 1)");

      // EqualTo
        Select_ selectID3(TableType::User, Filter_(EqualTo<IdColumn>(1)));
        BOOST_CHECK_EQUAL(selectID3.retrieveSelectString(), "SELECT * FROM user WHERE (ID = 1)");

      // NotEqualTo
        Select_ selectID4(TableType::User, Filter_(NotEqualTo<IdColumn>(1)));
        BOOST_CHECK_EQUAL(selectID4.retrieveSelectString(), "SELECT * FROM user WHERE (ID != 1)");

     // Character comparison
      // StartWith
        Select_ selectID5(TableType::User, Filter_(StartWith<IdColumn>(1)));
        BOOST_CHECK_EQUAL(selectID5.retrieveSelectString(), "SELECT * FROM user WHERE (ID LIKE '1%')");

      // EndWith
        Select_ selectID6(TableType::User, Filter_(EndWith<IdColumn>(1)));
        BOOST_CHECK_EQUAL(selectID6.retrieveSelectString(), "SELECT * FROM user WHERE (ID LIKE '%1')");

      // Contain
        Select_ selectID7(TableType::User, Filter_(Contain<IdColumn>(1)));
        BOOST_CHECK_EQUAL(selectID7.retrieveSelectString(), "SELECT * FROM user WHERE (ID LIKE '%1%')");

      // NotContain
        Select_ selectID8(TableType::User, Filter_(NotContain<IdColumn>(1)));
        BOOST_CHECK_EQUAL(selectID8.retrieveSelectString(), "SELECT * FROM user WHERE (ID NOT LIKE '%1%')");

      // NotStartWith
        Select_ selectID9(TableType::User, Filter_(NotStartWith<IdColumn>(1)));
        BOOST_CHECK_EQUAL(selectID9.retrieveSelectString(), "SELECT * FROM user WHERE (ID NOT LIKE '1%')");

      // NotEndWith
        Select_ selectID10(TableType::User, Filter_(NotEndWith<IdColumn>(1)));
        BOOST_CHECK_EQUAL(selectID10.retrieveSelectString(), "SELECT * FROM user WHERE (ID NOT LIKE '%1')");
}

// Create a filter containing a filter
BOOST_AUTO_TEST_CASE(test_filter_in_filter_select)
{
    // Create a longer Select_ object
    Select_ selectID(TableType::User, Filter_(Filter_(GreaterThan<IdColumn>("1"))));
    BOOST_CHECK_EQUAL(selectID.retrieveSelectString(), "SELECT * FROM user WHERE (ID > 1)");
}

// Create a filter containing multiples filter
BOOST_AUTO_TEST_CASE(test_filter_in_filter_select2)
{
    // Create a longer Select_ object
    Select_ selectID(TableType::User, Filter_(Filter_(GreaterThan<IdColumn>("1")), Filter_(LesserThan<IdColumn>("1"))));
    BOOST_CHECK_EQUAL(selectID.retrieveSelectString(), "SELECT * FROM user WHERE ((ID > 1) AND (ID < 1))");
}

// Filter type tests
BOOST_AUTO_TEST_CASE(test_filter_type)
{
    // Ignore operator
      // Filter_
      Select_ selectID11(TableType::User, Filter_(GreaterThan<IdColumn>("1")));
      BOOST_CHECK_EQUAL(selectID11.retrieveSelectString(), "SELECT * FROM user WHERE (ID > 1)");

      // ORFilter_
      Select_ selectID12(TableType::User, ORFilter_(GreaterThan<IdColumn>("1")));
      BOOST_CHECK_EQUAL(selectID12.retrieveSelectString(), "SELECT * FROM user WHERE (ID > 1)");

      // ANDFilter_
      Select_ selectID13(TableType::User, ANDFilter_(GreaterThan<IdColumn>("1")));
      BOOST_CHECK_EQUAL(selectID13.retrieveSelectString(), "SELECT * FROM user WHERE (ID > 1)");
    
    // Don't ignore operator
      // Filter_
      Select_ selectID21(TableType::User, Filter_(GreaterThan<IdColumn>("1")), Filter_(LesserThan<IdColumn>("1")));
      BOOST_CHECK_EQUAL(selectID21.retrieveSelectString(), "SELECT * FROM user WHERE (ID > 1) AND (ID < 1)");

      // ORFilter_
      Select_ selectID22(TableType::User, ORFilter_(GreaterThan<IdColumn>("1")), ORFilter_(LesserThan<IdColumn>("1")));
      BOOST_CHECK_EQUAL(selectID22.retrieveSelectString(), "SELECT * FROM user WHERE (ID > 1) OR (ID < 1)");

      // ANDFilter_
      Select_ selectID23(TableType::User, ANDFilter_(GreaterThan<IdColumn>("1")), ANDFilter_(LesserThan<IdColumn>("1")));
      BOOST_CHECK_EQUAL(selectID23.retrieveSelectString(), "SELECT * FROM user WHERE (ID > 1) AND (ID < 1)");

    // Create a longer Select_ object
    Select_ selectID(TableType::User, Filter_(Filter_(GreaterThan<IdColumn>("1")), ORFilter_(Filter_(GreaterThan<IdColumn>("1")), ANDFilter_(StartWith<IdColumn>("1")))));
    BOOST_CHECK_EQUAL(selectID.retrieveSelectString(), "SELECT * FROM user WHERE ((ID > 1) OR ((ID > 1) AND (ID LIKE '1%')))");
}

// Create a filter containing multiples nested filter and a filter with condition
BOOST_AUTO_TEST_CASE(test_filter_in_filter_select3)
{
    // Create a longer Select_ object
    Select_ selectID(TableType::User, Filter_(Filter_(Filter_(GreaterThan<IdColumn>("1")), Filter_(StartWith<IdColumn>("1"))), ORFilter_(Filter_(GreaterThan<IdColumn>("1")), Filter_(StartWith<IdColumn>("1"))), Filter_(EqualTo<IdColumn>("1"))));
    BOOST_CHECK_EQUAL(selectID.retrieveSelectString(), "SELECT * FROM user WHERE (((ID > 1) AND (ID LIKE '1%')) OR ((ID > 1) AND (ID LIKE '1%')) AND (ID = 1))");
}

// Create a filter containing multiples nested filter and a filter with condition
BOOST_AUTO_TEST_CASE(test_very_long_filter_select)
{
    // Create a longer Select_ object
    Select_ selectID(TableType::User, Filter_(Filter_(Filter_(GreaterThan<IdColumn>("1")), Filter_(StartWith<IdColumn>("1"))), ORFilter_(Filter_(GreaterThan<IdColumn>("1")), Filter_(StartWith<IdColumn>("1"))), Filter_(EqualTo<IdColumn>("1"))));
    BOOST_CHECK_EQUAL(selectID.retrieveSelectString(), "SELECT * FROM user WHERE (((ID > 1) AND (ID LIKE '1%')) OR ((ID > 1) AND (ID LIKE '1%')) AND (ID = 1))");
}

// Test MySQL Connection
BOOST_AUTO_TEST_CASE(test_mysql_connection)
{
    // Create a sql connection object
    MySQLConnector connector;
    connector.connect("127.0.0.1:3306", "user", "1234", "DB1");
    Select_ select(TableType::User, Filter_(Filter_(GreaterThan<IdColumn>("1"))));
    std::vector<std::vector<std::string>> users = connector.select_from_db(select);
    connector.disconnect();

    // Check if the connection worked
    BOOST_CHECK_NE(users.size(), 0);
}
