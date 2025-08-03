#include <iostream>      
#include <utility>
#include <vector>        
#include <cassert>
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
    SqlSelectQueryBuilder& AddColumn(const string& column)
    {
   
        if (up == false)
        {
            columns_ = { column };
            up = true;
        }
        else {

            columns_.push_back(column);
        } 
      
        return *this;
       
      

    }



    SqlSelectQueryBuilder& AddFrom(const string& table_name)
    {
        table_name_ = table_name;
        return *this;


    }
    SqlSelectQueryBuilder& AddWhere(const string& column, const string& value)
    {
        where_conditions_.push_back({ column,value });
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
        query += " FROM "+ table_name_;
       
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
            if (i == where_conditions_.size()-1)
            {
                query.pop_back();
                query += ";";
           }
        }
        
        return query;


    }
};



int main_1()
{
    SqlSelectQueryBuilder query_builder;
   query_builder.AddColumn("name").AddColumn("phone");
    query_builder.AddFrom("students");
    query_builder.AddWhere("id", "42").AddWhere("name", "John");

   
    assert(query_builder.BuildQuery() == "SELECT name, phone FROM students WHERE id=42 AND name=John;");
    return 0;
 }