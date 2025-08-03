#include <iostream>      
#include <utility>
#include <vector>        
#include <cassert>
#include <map>
using namespace std;


class SqlSelectQueryBuilder
{
    vector<string> columns_;
    string table_name_;
    bool up = false;
    vector<pair<string, string>> where_conditions_;
public:

    SqlSelectQueryBuilder()
    {

        columns_ = { "*" };

    }

    SqlSelectQueryBuilder& AddColumns(const std::vector<std::string>& columns) noexcept
    {
        for (auto i : columns)
        {
            if (up == false)
            {
                columns_ = { i };
                up = true;
            }
            else {

                columns_.push_back(i);
            }

        }
       

        return *this;

    }


    SqlSelectQueryBuilder& AddFrom(const string& table_name)
    {
        table_name_ = table_name;
        return *this;


    }
  
    SqlSelectQueryBuilder& AddWhere(const std::map<std::string, std::string>& kv) noexcept
    {
        for (auto i : kv)
        {
            where_conditions_.push_back({ i.first, i.second });

       }
     
        return *this;
    }
    string BuildQuery()
    {
        string query;

        query += "SELECT";

        for (size_t i = 0; i < columns_.size(); ++i)
        {

            query += " " + columns_[i];
            if (i != columns_.size() - 1) {

                query += ",";
            }
        }
        query += " FROM " + table_name_;

        query += " WHERE ";

        for (size_t i = 0; i < where_conditions_.size(); ++i)
        {
            if (i > 0)
            {

                query += "AND " + where_conditions_[i].first + "=" + where_conditions_[i].second + " ";
            }
            else
            {

                query += where_conditions_[i].first + "=" + where_conditions_[i].second + " ";
            }
            if (i == where_conditions_.size() - 1)
            {
                query.pop_back();
                query += ";";
            }
        }

        return query;


    }
};



int main()
{
    SqlSelectQueryBuilder query_builder;
   const std::vector<std::string> columns = { "name", "phone", "email" };
    query_builder.AddColumns(columns);
    query_builder.AddFrom("students");
    std::map<std::string, std::string> where_conditions = {
          {"status", "active"},
          {"age", "25"},
          {"city", "Moscow"}
    };
    query_builder.AddWhere(where_conditions);

    cout << query_builder.BuildQuery();
  
    return 0;
}