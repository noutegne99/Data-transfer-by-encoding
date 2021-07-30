#include <iostream>
#include <windows.h>
#include <C:/Program Files (x86)/Dev-Cpp/MinGW64/include/mysql.h>
#include <sstream>
#include <bitset>
#include <fstream>
//#include <iostream>
//#include <stdio.h>
#include <vector>
#include <iomanip>
#include <errno.h>
#include <inttypes.h>

#include <string>
#include <map>

#include <iostream>
#include <iterator>
#include <vector>
//#include <C:/Users/bkoua/Desktop/huff/huff/huff.cpp>
//#include <C:/Users/bkoua/Desktop/huff/huff/huff-sep.cpp>

//#include <mysql.h>

//#include <string>  std::string, std::to_string
using namespace std;


//UPDATE `Tablebit2` set C1=1 where id=6;
//UPDATE `Tablebit2` set C3=1 where id=14;
//UPDATE `Tablebit2` set C4=1 where id=11;
//UPDATE `Tablebit2` set C5=1 where id=4;
//UPDATE `Tablebit2` set C6=1 where id=13;
//UPDATE `Tablebit2` set C7=1 where id=8;
//UPDATE `Tablebit2` set C8=1 where id=21;
//UPDATE `Tablebit2` set C9=1 where id=16;
//UPDATE `Tablebit2` set C10=1 where id=2;
//UPDATE `Tablebit2` set C11=1 where id=18;
//UPDATE `Tablebit2` set C12=1 where id=9;
//UPDATE `Tablebit2` set C13=1 where id=20;
//UPDATE `Tablebit2` set C14=1 where id=25;
//UPDATE `Tablebit2` set C15=1 where id=12;
//UPDATE `Tablebit2` set C16=1 where id=19;
//UPDATE `Tablebit2` set C17=1 where id=10;
//UPDATE `Tablebit2` set C18=1 where id=23;
//UPDATE `Tablebit2` set C19=1 where id=17;
//UPDATE `Tablebit2` set C20=1 where id=5;
//UPDATE `Tablebit2` set C21=1 where id=1;
//UPDATE `Tablebit2` set C22=1 where id=22;
//UPDATE `Tablebit2` set C23=1 where id=7;
//UPDATE `Tablebit2` set C24=1 where id=24;
//UPDATE `Tablebit2` set C25=1 where id=15;
//UPDATE `Tablebit2` set C1=0,  C2=1, C3=0,  C4=0, C5=0,  C6=0,  C7=0, C8=0,   C9=0,  C10=0,
//                       C11=0, C12=0,C13=0, C14=0,C15=0, C16=0, C17=0, C18=0, C19=0, C20=0,
//                       C21=0, C22=0,C23=0, C24=0,C25=0, C26=0, C27=0, C28=0, C29=0, C30=0,
//                       C31=0, C32=0,C33=0, C34=0,C35=0, C36=0, C37=0, C38=0, C39=0, C40=0,
//                       C41=0, C42=0,C43=0, C44=0,C45=0, C46=0, C47=0, C48=0, C49=0, C50=0,
//                       C51=0, C52=0,C53=0, C54=0,C55=0, C56=0, C57=0, C58=0, C59=0, C60=0,
//                       C61=0, C62=0,C63=0, C64=0,C65=0, C66=0, C67=0, C68=0, C69=0, C70=0,
//                       C71=0, C72=0,C73=0, C74=0,C75=0, C76=0, C77=0, C78=0, C79=0, C80=0,
//                       C81=0, C82=0,C83=0, C84=0,C85=0, C86=0, C87=0, C88=0, C89=0, C90=0,
//                       C91=0, C92=0,C93=0, C94=0,C95=0, C96=0, C97=0, C98=0, C99=0, C100=0 where id=1



//UPDATE `Tablebit2` set C10=0, C12=0 where id=1

string intToString(int x)
{
/**************************************/
/* This function is similar to itoa() */
/* "integer to alpha", a non-standard */
/* C language function. It takes an   */
/* integer as input and as output,    */
/* returns a C++ string.              */
/* itoa()  returned a C-string (null- */
/* terminated)                        */
/* This function is not needed because*/
/* the following template function    */
/* does it all                        */
/**************************************/
       string r;
       stringstream s;

       s << x;
       r = s.str();

       return r;

}
/*

int main(int argc, char **argv)
{

  MYSQL *conn;

  conn = mysql_init(NULL);



  if (mysql_real_connect(conn, "160.153.41.3", "rootuserdb", "rootuserdb", "bitDB", 3306, NULL, 0) == NULL) {
      printf("Error %u: %s\n", mysql_errno(conn), mysql_error(conn));
  }else{
     cout << "Good connection"<< endl ;

  }




  mysql_close(conn);

}*/


// Compress a string to a list of output symbols.

template <typename Iterator>
Iterator compress(const std::string &uncompressed, Iterator result) {
  // Build the dictionary.
  int dictSize = 256;
  std::map<std::string,int> dictionary;
  for (int i = 0; i < 256; i++)
    dictionary[std::string(1, i)] = i;

  std::string w;
  for (std::string::const_iterator it = uncompressed.begin();
       it != uncompressed.end(); ++it) {
    char c = *it;
    std::string wc = w + c;
    if (dictionary.count(wc))
      w = wc;
    else {
      *result++ = dictionary[w];
      // Add wc to the dictionary.
      dictionary[wc] = dictSize++;
      w = std::string(1, c);
    }
  }

  // Output the code for w.
  if (!w.empty())
    *result++ = dictionary[w];
  return result;
}



// Decompress a list of output ks to a string.
// "begin" and "end" must form a valid range of ints
template <typename Iterator>
std::string decompress(Iterator begin, Iterator end) {
  // Build the dictionary.
  int dictSize = 256;
  std::map<int,std::string> dictionary;
  for (int i = 0; i < 256; i++)
    dictionary[i] = std::string(1, i);

  std::string w(1, *begin++);
  std::string result = w;
  std::string entry;
  for ( ; begin != end; begin++) {
    int k = *begin;
    if (dictionary.count(k))
      entry = dictionary[k];
    else if (k == dictSize)
      entry = w + w[0];
    else
      throw "Bad compressed k";

    result += entry;

    // Add w+entry[0] to the dictionary.
    dictionary[dictSize++] = w + entry[0];

    w = entry;
  }
  return result;
}



MYSQL mysql, *conn;
MYSQL_RES *res;
MYSQL_ROW row;

int main()
{


        char tabIndex[] = {
                           'a','b','c','d','e','f','g','h','i','j',
                           'k','l','m','n','o','p','q','r','s','t',
                           'u','v','w','x','y','z', 'A','B','C','D',
			               'E','F','G','H','I','J','K', 'L','M','N',
			               'O','P','Q','R','S','T','U', 'V','W','X',
			               'Y','Z','1','2','3','4','5','6','7','8',
                           '9','0','!','@','#','$','%','?','&','*',
                           '(',')','-','=','+','~','|','/',',','.',
			               '>','<','{','}','[',']',';',':','_','`',
			               '\0'
                           };


     // MYSQL* conn;
      mysql_init(&mysql);
      MYSQL *conn;

      //conn = mysql_init(NULL);
      ////conn = mysql_real_connect(&mysql, "160.153.41.3", "rootuserdb", "rootuserdb", "bitDB", 3306, NULL, 0);
      //conn = mysql_real_connect(&mysql, "160.153.41.3", "rootuser0", "rootuser0", "dbtest", 3306, NULL, 0);
      conn = mysql_real_connect(&mysql, "160.153.41.3", "rootuserdb2", "rootuserdb2", "bitDB2", 3306, NULL, 0);
      if(conn == NULL){
       cout << "Mauvaise Connexion"<< endl;

     }else{
       cout << "Bonne Connexion"<< endl;
     }
//mysql_close(conn);


/*
    MYSQL db_name, db_user,db_pass,db_host;*/

//    int qstate =  mysql_query (conn,"select * from tablebit");
//     if(qstate!=0){
//
//            cout << mysql_error(conn)<< endl;
//            return 1;
//        }


//
    string sql;

}
//    vector<string> value1;
//    value1.push_back("00000000000000000000000000000000");
//    value1.push_back("00000000000000000000000000000001");
//    value1.push_back("00000000000000000000000000000011");
//    value1.push_back("00000000000000000000000000000111");
//    value1.push_back("00000000000000000000000000001111");
//    value1.push_back("00000000000000000000000000011111");
//    value1.push_back("00000000000000000000000000111111");
//    value1.push_back("00000000000000000000000001111111");
//    value1.push_back("00000000000000000000000011111111");
//    value1.push_back("00000000000000000000000111111111");
//
//    {"000000000", "0000000000000","00000000000000000000000"};
//
//    string temp ;
//    for (int  i=0; i<value1.size() ;i++){
//
//        char* query = sql.c_str();
//        const char* q = query.c_str();
//
//         temp = value1[i];
//         sql = "INSERT INTO tablebit(value) VALUES('"+temp+"')";
//         int qstate = mysql_query(conn, sql.c_str());
//         cout << " insert111..." << endl;
//          qstate = mysql_query(conn, "select value from tablebit Where id = 20" );
//
//        if(qstate == 0){
//            cout << " insert..." << value1[i] << endl;
//
//        }else{
//            cout <<mysql_error(conn) << endl;
//
//        }
//
//    }
 ///

//   vector<string> value2;
//    value2.push_back("10000110000000000000011100000000");
//    value2.push_back("10000110000000000000011100000001");
//    value2.push_back("10000110000000000000011100000011");
//    value2.push_back("10000110000000000000011100000111");
//    value2.push_back("10000110000000000000011100001111");
//
//    ifstream infile("origMess.txt");
//    if(!infile.is_open())
//    {
//      cout<<"ERROR... Could not open file!!!"<<endl;
//      return 1;
//    }
//    infile.seekg(0, infile.end);
//    int len=infile.tellg();
//    infile.seekg(0, infile.beg);
//    cout<<"Lenght of my file :"<<len<<endl;
//    cout<<"The file is open2222: "<<endl;
//    while(!infile.eof())
//    {
//      string read3c;
//      infile>>read3c;
//      cout<<read3c<<endl;
//      //string read=strToInt32Value(read3c);
//
//      char str2[32];
//      stringstream s;
//      s<<bitset<4>(read3c.c_str()[0]);
//      strcpy(str2, s.str().c_str());
//      for(size_t i=1; i<read3c.size();i++){
//
//            stringstream s2;
//            s2<<bitset<4>(read3c.c_str()[i]);
//            strcat(str2,s2.str().c_str());
//            cout<<s2.str()<<endl;
//      }
//      read3c=str2;
//      value2.push_back(read3c);
//      cout<<read3c<<endl;
//    }
//    infile.close();
//
//    cout<<"My original message is:"<<endl;
//    for (int  i=0; i<value2.size() ;i++){
//
//
//         string tempmes = value2[i];
//         string tmpid = intToString(5+i);
//
//         sql = "UPDATE tablebit set value='"+tempmes+"' where id='"+tmpid+"'";
//         //sql = "UPDATE tablebits set value='"+tempmes+"' where id='"+tmpid+"'";
//         int qstate = mysql_query(conn, sql.c_str());
//
//
//        if(qstate == 0){
//            cout << " dataBase updated succesfully..." << value2[i] << endl;
//
//        }else{
//            cout <<mysql_error(conn) << endl;
//
//        }
//     // mysql_free_result();
//    }
//
//    ///////////////////////////////////////////////////////////////
//   cout<<"My message from the database is:"<<endl;
//   const int T =6, initPoint = 30; // u_(n+1) = u_n +1; u30= value(30) T elements
//   for (int  i=0; i<T ;i++){
//       string tmpid = intToString(initPoint+i);
//       sql = "SELECT value FROM tablebit where id='"+tmpid+"'";
//       //sql = "SELECT value FROM tablebits where id='"+tmpid+"'";
//      // sql = "SELECT value FROM tablebit where id=30";
//       int qstate = mysql_query(conn, sql.c_str());
//       res = mysql_store_result(conn);
//
//       if((row=mysql_fetch_row(res))!=NULL)
//       {
//          cout<<left;
//          cout<<setw(32)<<row[0]<<endl;
//       }
//    }
//   cout<<endl<<endl;
//
//}





CREATE TABLE Tablebit4
(
//    id INT PRIMARY KEY NOT NULL,
//    C1 VARCHAR(1),
//    C2 VARCHAR(1),
//    C3 VARCHAR(1)=0,
//    C4 VARCHAR(1)=0,
//    C5 VARCHAR(1)=0,
//    C6 VARCHAR(1)=0,
//    C7 VARCHAR(1)=0,
//    C8 VARCHAR(1)=0,
//    C9 VARCHAR(1)=0,
//    C10 VARCHAR(1)=0,
//    C11 VARCHAR(1)=0,
//    C12 VARCHAR(1)=0,
//    C13 VARCHAR(1)=0,
//    C14 VARCHAR(1)=0,
//    C15 VARCHAR(1)=0,
//    C16 VARCHAR(1)=0,
//    C17 VARCHAR(1)=0,
//    C18 VARCHAR(1)=0,
//    C19 VARCHAR(1)=0,
//    C20 VARCHAR(1)=0,
//    C21 VARCHAR(1)=0,
//    C22 VARCHAR(1)=0,
//    C23 VARCHAR(1)=0,
//    C24 VARCHAR(1)=0,
//    C25 VARCHAR(1)=0,
//    C26 VARCHAR(1)=0,
//    C27 VARCHAR(1)=0,
//    C28 VARCHAR(1)=0,
//    C29 VARCHAR(1)=0,
//    C30 VARCHAR(1)=0,
//    C31 VARCHAR(1)=0,
//    C32 VARCHAR(1)=0,
//    C33 VARCHAR(1)=0,
//    C34 VARCHAR(1)=0,
//    C35 VARCHAR(1)=0,
//    C36 VARCHAR(1)=0,
//    C37 VARCHAR(1)=0,
//    C38 VARCHAR(1)=0,
//    C39 VARCHAR(1)=0,
//    C40 VARCHAR(1)=0,
//    C41 VARCHAR(1)=0,
//    C42 VARCHAR(1)=0,
//    C43 VARCHAR(1)=0,
//    C44 VARCHAR(1)=0,
//    C45 VARCHAR(1)=0,
//    C46 VARCHAR(1)=0,
//    C47 VARCHAR(1)=0,
//    C48 VARCHAR(1)=0,
//    C49 VARCHAR(1)=0,
//    C50 VARCHAR(1)=0,
//    C51 VARCHAR(1)=0,
//    C52 VARCHAR(1)=0,
//    C53 VARCHAR(1)=0,
//    C54 VARCHAR(1)=0,
//    C55 VARCHAR(1)=0,
//    C56 VARCHAR(1)=0,
//    C57 VARCHAR(1)=0,
//    C58 VARCHAR(1)=0,
//    C59 VARCHAR(1)=0,
//    C60 VARCHAR(1)=0,
//    C61 VARCHAR(1)=0,
//    C62 VARCHAR(1)=0,
//    C63 VARCHAR(1)=0,
//    C64 VARCHAR(1)=0,
//    C65 VARCHAR(1)=0,
//    C66 VARCHAR(1)=0,
//    C67 VARCHAR(1)=0,
//    C68 VARCHAR(1)=0,
//    C69 VARCHAR(1)=0,
//    C70 VARCHAR(1)=0,
//    C71 VARCHAR(1)=0,
//    C72 VARCHAR(1)=0,
//    C73 VARCHAR(1)=0,
//    C74 VARCHAR(1)=0,
//    C75 VARCHAR(1)=0,
//    C76 VARCHAR(1)=0,
//    C77 VARCHAR(1)=0,
//    C78 VARCHAR(1)=0,
//    C79 VARCHAR(1)=0,
//    C80 VARCHAR(1)=0,
//    C81 VARCHAR(1)=0,
//    C82 VARCHAR(1)=0,
//    C83 VARCHAR(1)=0,
//    C84 VARCHAR(1)=0,
//    C85 VARCHAR(1)=0,
//    C86 VARCHAR(1)=0,
//    C87 VARCHAR(1)=0,
//    C88 VARCHAR(1)=0,
//    C89 VARCHAR(1)=0,
//    C90 VARCHAR(1)=0,
//    C91 VARCHAR(1)=0,
//    C92 VARCHAR(1)=0,
//    C93 VARCHAR(1)=0,
//    C94 VARCHAR(1)=0,
//    C95 VARCHAR(1)=0,
//    C96 VARCHAR(1)=0,
//    C97 VARCHAR(1)=0,
//    C98 VARCHAR(1)=0,
//    C99 VARCHAR(1)=0,
//    C100 VARCHAR(1)
