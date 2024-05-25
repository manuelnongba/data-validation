#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <regex>

using namespace std;

unordered_map <string, bool> is_valid_data(string field, string value);
unordered_map <string, bool> is_complete_data(string field, string value);
unordered_map <string, unordered_map<string, bool> > data_validation(string field, string value);

unordered_map <string, bool> is_valid_data(string field, string value){
  unordered_map <string, bool> data_map;

  if (field == "UserId"){
    bool is_valid_userid = value.length() == 11;
    data_map.insert(pair<string, bool>("Test for valid user id.", is_valid_userid));
  }

  if (field == "UserName"){
    const regex username_pattern("^[a-zA-Z0-9_-]+$");

    bool is_valid_username = regex_search(value, username_pattern);

    data_map.insert(pair<string, bool>("Test for valid user name.", is_valid_username));
  }

  if(field == "DateOfBirth"){
    regex date_pattern("^\\d{4}-\\d{2}-\\d{2}$");

    bool is_valid_date = regex_search(value, date_pattern);
    data_map.insert(pair<string, bool>("Test for valid date.", is_valid_date));
  }

  if(field == "Email"){
    regex email_pattern("^[\\w\\.-]+@[a-zA-Z\\d\\.-]+\\.[a-zA-Z]{2,}$");
    bool is_valid_email = regex_search(value, email_pattern);
    data_map.insert(pair<string, bool>("Test for valid email.", is_valid_email));
  }

  if(field == "Country"){
    regex country_pattern("^[\\w\\.-]+");
    bool is_valid_country = regex_search(value, country_pattern);
    data_map.insert(pair<string, bool>("Test for valid country", is_valid_country));
  }

  if(field == "MobileNo"){
    regex mobile_number_pattern("^((,\\s*)?((0\\d{9})|\\+\\d{5,14}))+$");
    bool is_valid_mobile_no = regex_search(value, mobile_number_pattern);
    data_map.insert(pair<string, bool>("Test for valid mobile number.", is_valid_mobile_no));
  }

  if(field == "ResidentialAddress"){
    regex address_pattern("[^A-Za-z\\- \\|\\/\\#]");
    bool is_valid_mobile_no = regex_search(value, address_pattern);
    data_map.insert(pair<string, bool>("Test for valid address.", is_valid_mobile_no));
  }

  return data_map;
};


unordered_map <string, bool> is_complete_data(string field, string value){
  unordered_map <string, bool> data_map;

  if (field == "UserId"){
    bool is_complete_userid = value != "";
    data_map.insert(pair<string, bool>("Test for valid user id.", is_complete_userid));
  }

  if (field == "UserName"){
    bool is_complete_username = value != "";
    data_map.insert(pair<string, bool>("Test for complete user name.", is_complete_username));
  }

  if(field == "DateOfBirth"){
    bool is_complete_date = value != "";
    data_map.insert(pair<string, bool>("Test for complete date.", is_complete_date));
  }

  if(field == "Email"){
    bool is_complete_email = value != "";
    data_map.insert(pair<string, bool>("Test for complete email.", is_complete_email));
  }

  if(field == "Country"){
    bool is_complete_country = value != "";
    data_map.insert(pair<string, bool>("Test for complete country", is_complete_country));
  }

  if(field == "MobileNo"){
    bool is_complete_mobile_no = value != "";
    data_map.insert(pair<string, bool>("Test for complete mobile number.", is_complete_mobile_no));
  }

  if(field == "ResidentialAddress"){
    bool is_complete_mobile_no = value != "";
    data_map.insert(pair<string, bool>("Test for complete address.", is_complete_mobile_no));
  }

  return data_map;
};

unordered_map <string, unordered_map<string, bool> > data_validation(string field, string value){
  unordered_map <string, unordered_map<string, bool> > data_map;

  data_map.insert(pair <string, unordered_map<string, bool> > ("validity", is_valid_data(field, value)));
  data_map.insert(pair <string, unordered_map<string, bool> > ("completeness", is_complete_data(field, value)));
  
  return data_map;
}

void display(unordered_map <string, bool> data_map){
  for(auto const &val: data_map){
      cout << boolalpha;
      cout << val.first << " --- " << (val.second ? "Passed ✅": "Failed ❌") << endl;
    }
}

int main(){
  ifstream data;
  string line;
  unordered_map <string, unordered_map<string, bool> > results;

  data.open("./db.txt");

  if(!data.is_open()){
    cout << "Error: Couldn't open file" << endl;
    return 1;
  }

  while(getline(data, line)){
    string field;
    string value;
    size_t position = line.find("-");

    if(position != string::npos){
     field = line.substr(0, position);
     value = line.substr(position + 1, line.length());
    }
    results = data_validation(field, value);

    display(results["validity"]);
    display(results["completeness"]);
  }
  
  data.close();

  return 0;
}