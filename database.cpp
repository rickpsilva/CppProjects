#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h> 
#include <iostream>
#include <string>

struct Company
{
	int Id;
	std::string Name;
	int Age;
	std::string Address;
	double Salary;
	 
	 Company (
		 const int id, 
		 const std::string name, 
		 const int age, 
		 const std::string address, 
		 const double salary) : 
			Id(id),
			Name(name),
			Age(age),
			Address(address),
			Salary(salary){}
};

static int callback_print_row(void *NotUsed, int argc, char **argv, char **azColName) {
   int i;
   for(i = 0; i<argc; i++) {
      std::cout << azColName[i] << " = " << (argv[i] ? argv[i] : "NULL" ) <<std::endl;
   }
   std::cout << std::endl;
   return 0;
};

template <class T>
class  Database
{
    public:
        Database()
        {
        	OpenConnection();
        }
        ~Database()
        {
        	CloseConnection();
        }
        
        template <typename Callback>
        void ExecuteQuery(const std::string& query, const Callback&& callback)
        { 
		   rc = sqlite3_exec(db, query.c_str(), &callback, 0, &zErrMsg);
		   PrintStatus();
        };
        
    private:
    
    	void OpenConnection()
        {
        	rc = sqlite3_open("test.db", &db);
 		   if( rc ) {
		       std::cout << "Can't open database: "<<sqlite3_errmsg(db) <<std::endl;
		    } else {
		       std::cout <<  "Opened database successfully" << std::endl;
		    }
        };
        
        void CloseConnection()
        {
        	sqlite3_close(db);
        	std::cout <<  "Closed database successfully" << std::endl;
        };
    
        void PrintStatus()
        {
        	if(rc != SQLITE_OK)
        	{
        		std::cout<<"SQL error:"<<zErrMsg<<std::endl;
        		sqlite3_free(zErrMsg);
        	}else {
		      std::cout<<"Execution query successfully"<<std::endl;
		   }
        };

    private:
        T* db;
        char* zErrMsg;
        int rc;
};

template <typename EntityType>
class DbEntity : public Database<sqlite3>
{
    public:
    	virtual void Create(EntityType&)=0;
};

class CompanyEntity : public DbEntity<Company>
{
    public:
        void Create(Company& c);
        
        template <std::size_t  NROWS>
        void Select();
};

template <std::size_t  NROWS>
void CompanyEntity::Select()
{
	std::string query  = "SELECT * FROM COMPANY LIMIT  "+std::to_string(NROWS)+"";
	std::cout << query.c_str() << std::endl;
	
	ExecuteQuery(query, callback_print_row);
}

void CompanyEntity::Create(Company& c)
{
	std::string query  = "CREATE TABLE IF NOT EXISTS COMPANY("  \
      "ID INT PRIMARY KEY AUTOINCREMENT    NOT NULL," \
      "NAME           TEXT    NOT NULL," \
      "AGE            INT     NOT NULL," \
      "ADDRESS        CHAR(50)," \
      "SALARY         REAL );";
      
      
      
const   auto id =  [&](void *NotUsed, int argc, char **argv, char **azColName) ->int {
       // auto value = (argv[0] ? argv[0] : 0);
        //c.Id = atoi(value);
        
        c.Id =3;
       return 0;
    };
    
	ExecuteQuery(query,id);

/*	std::string insert_row = "INSERT INTO COMPANY " \
	             "(ID, NAME, AGE, ADDRESS, SALARY) " \
	             "VALUES ("+std::to_string(c.Id)+", '"+c.Name+"', "+std::to_string(c.Age)+", '"+c.Address+"', "+
	             std::to_string(c.Salary)+");";*/
	             
	std::string insert_row = "INSERT INTO COMPANY " \
	             "(NAME, AGE, ADDRESS, SALARY) " \
	             "VALUES ('"+c.Name+"', "+std::to_string(c.Age)+", '"+c.					Address+"', "+ std::to_string(c.Salary)+");";
	             
//	ExecuteQuery(insert_row,  NULL);
	std::cout <<  "CompanyEntity::Create successfully" << std::endl;
}

int main(int argc, char* argv[]) {
   
   Company company {1, "Ricardo", 40, "Ermesinde", 1000};
   
   CompanyEntity c;
   c.Create(company);
   c.Select<10>();
   return 0;
}