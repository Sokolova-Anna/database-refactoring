#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <list>
#include <iterator>
#include <string>
#include <sstream>

enum field {none, first_name, last_name, phone, car, id, times_used, fstatus};
enum status {active, disabled, vacation, lost, broken};
std::string g_strStatuses[5] = { "active", "disabled", "vacation", "lost", "broken" };
status g_Statuses[5] = { active, disabled, vacation, lost, broken };
std::string g_strFields[7] = { "first_name", "last_name", "call", "car", "id", "used", "status" };
field g_Fields[7] = { first_name, last_name, phone, car, id, times_used, fstatus };

class Record
{
private:
	std::string first_name_;
	std::string last_name_;
	std::string phone_;
	std::string car_;
	enum status status_;
	int id_;
	int times_used_;

	std::string statToStr(status st)
	{
		std::string statuses[5] = { "active", "disabled", "vacation", "lost", "broken" };
		return statuses[st];
	}

public:
	Record(std::string& first_name, std::string& last_name, std::string& phone, std::string& car, int id, int times_used, status _status)
	{
		first_name_ = first_name;
		last_name_ = last_name;
		phone_ = phone;
		car_ = car;
		id_ = id;
		times_used_ = times_used;
		status_ = _status;
	}
	
	bool update(field change_field, std::string& new_value)
	{
		switch (change_field)
		{
		case first_name:
			first_name_ = new_value;
			break;
		case last_name:
			last_name_ = new_value;
			break;
		case phone:
			phone_ = new_value;
			break;
		case car:
			car_ = new_value;
			break;
		default:
			return 1;
		}
		return 0;
	}
	bool update(field change_field, int new_value)
	{
		switch (change_field)
		{
		case id:
			id_ = new_value;
			break;
		case times_used:
			times_used_ = new_value;
			break;
		default:
			return 1;
		}
		return 0;
	}
	bool update(field change_field, status new_value)
	{
		if (change_field != fstatus)
			return 1;
		status_ = new_value;
		return 0;
	}

	status Status() const
	{
		return status_;
	}

	std::string getStrField(field Field)
	{
		std::string e = "error";
		switch (Field)
		{
		case first_name:
			return first_name_;
		case last_name:
			return last_name_;
		case phone:
			return phone_;
		case car:
			return car_;
		default:
			return e;
		}
	}
	int getIntField(field Field)
	{
		switch (Field)
		{
		case id:
			return id_;
		case times_used:
			return times_used_;
		default:
			return -1;
		}
	}

	void output(bool fn, bool ln, bool ph, bool cr, bool st, bool i, bool tu)
	{
		if (fn) std::cout << "first_name: " << first_name_ << std::endl;
		if (ln) std::cout << "last_name: " << last_name_ << std::endl;
		if (ph) std::cout << "call: " << phone_ << std::endl;
		if (cr) std::cout << "car: " << car_ << std::endl;
		if (st) std::cout << "status: " << statToStr(status_) << std::endl;
		if (i) std::cout << "id: " << id_ << std::endl;
		if (tu) std::cout << "used: " << times_used_ << std::endl;
		std::cout << std::endl;
	}

	void output()
	{
		output(1, 1, 1, 1, 1, 1, 1);
	}

};

class Condition
{
public:
	virtual int check(Record& rec) = 0;
};

class Condition_comparison : public Condition
{
private:
	field Field = none;
	std::string sign;
	std::string str_value;
	int int_value = -1;
	status stat_value = active;

	void init(field Field_in, std::string& sign_in)
	{
		if (sign_in != "<" && sign_in != ">" && sign_in != "=" && sign_in != "!=" && sign_in != ">=" && sign_in != "<=")
			return;
		Field = Field_in;
		sign = sign_in;
	}

public:
	Condition_comparison(field Field_in, std::string sign_in, std::string value_in)
	{
		if (Field_in != first_name && Field_in != last_name && Field_in != phone && Field_in != car)
			return;
		init(Field_in, sign_in);
		str_value = value_in;
	}
	Condition_comparison(field Field_in, std::string sign_in, int value_in)
	{
		if (Field_in != id && Field_in != times_used)
			return;
		init(Field_in, sign_in);
		int_value = value_in;
	}
	Condition_comparison(field Field_in, std::string sign_in, status value_in)
	{
		if (Field_in != fstatus)
			return;
		init(Field_in, sign_in);
		stat_value = value_in;
	}

	int check(Record& rec)
	{
		if (rec.getStrField(Field) != "error")
		{
			if (sign == "=" && rec.getStrField(Field) == str_value) return 1;
			if (sign == ">" && rec.getStrField(Field) > str_value) return 1;
			if (sign == "<" && rec.getStrField(Field) < str_value) return 1;
			if (sign == "!=" && rec.getStrField(Field) != str_value) return 1;
			if (sign == "<=" && rec.getStrField(Field) <= str_value) return 1;
			if (sign == ">=" && rec.getStrField(Field) >= str_value) return 1;
		}
		else if (rec.getIntField(Field) != -1)
		{
			if (sign == "=" && rec.getIntField(Field) == int_value) return 1;
			if (sign == ">" && rec.getIntField(Field) > int_value) return 1;
			if (sign == "<" && rec.getIntField(Field) < int_value) return 1;
			if (sign == "!=" && rec.getIntField(Field) != int_value) return 1;
			if (sign == "<=" && rec.getIntField(Field) <= int_value) return 1;
			if (sign == ">=" && rec.getIntField(Field) >= int_value) return 1;
		}
		else
		{
			if (sign == "=" && rec.Status() == stat_value) return 1;
			if (sign == ">" && rec.Status() > stat_value) return 1;
			if (sign == "<" && rec.Status() < stat_value) return 1;
			if (sign == "!=" && rec.Status() != stat_value) return 1;
			if (sign == "<=" && rec.Status() <= stat_value) return 1;
			if (sign == ">=" && rec.Status() >= stat_value) return 1;
		}
		return 0;
	}
};

class in_Condition : public Condition
{
private:
	field Field;
	std::string in_values;
	std::string* string_values = new std::string[20];
	int* int_values  = new int[20];
	status* stat_values = new status[20];

	bool strToStat(std::string str, status* stat)
	{
		for (int i = 0; i < 5; ++i)
			if (str == g_strStatuses[i])
			{
				*stat = g_Statuses[i];
				return 0;
			}
		return 1;
	}

	int getValues()
	{
		std::istringstream iss(in_values);
		std::string token;
		int i = 0;
		int_values[0] = -1;
		string_values[0] = "null";

		while (std::getline(iss, token, ','))
		{
			if (Field > 0 && Field < id) string_values[i] = token;
			else if (Field > 0 && Field < fstatus) int_values[i] = std::stoi(token);
			else if (Field == fstatus)
			{
				if (strToStat(token, stat_values + i)) return -1;
			}
			else return -1;
			++i;
		}

		return i;
	}

public:
	in_Condition(field Field_in, std::string& values_in)
	{
		Field = Field_in;
		in_values = values_in;
	}

	int check(Record& rec)
	{
		int n_values = getValues();
		if (n_values == -1) return -1;
		if (!n_values) return 0;

		for (int i = 0; i < n_values; ++i)
		{
			if (string_values[0] != "null" && rec.getStrField(Field) == string_values[i]) return 1;
			else if (int_values[0] != -1 && rec.getIntField(Field) == int_values[i]) return 1;
			else if (rec.Status() == stat_values[i]) return 1;
		}
		return 0;
	}
};

class inputConditions
{
private:
	std::string conditions;
	int cond_num;
	std::string* conds = new std::string[50];

	int separate(std::string& strm, std::string* tokens, const char sep)
	{
		std::istringstream iss(strm);
		std::string token;
		int i = 0;
		while (std::getline(iss, token, sep))
		{
			tokens[i] = token;
			++i;
		}
		return i;
	}

	bool checkValue(field Field, char* value_in, char* sign)
	{
		char* value = new char[strlen(value_in)];
		strcpy(value, value_in);
		int n_values = 1;
		std::string* values = new std::string[50];

		if (value[0] == '[')
		{
			if ((strcmp(sign, "!=") == 0 || strcmp(sign, "/in/") == 0) && value[strlen(value) - 1] == ']')
			{
				int i;
				for (i = 0; i < strlen(value_in) - 2; ++i)
					value_in[i] = value_in[i + 1];
				value_in[i] = '\0';
				strcpy(value, value_in);

				char* token = strtok(value, ",");
				i = 0;
				while (token != NULL)
				{
					values[i] = token;
					token = strtok(NULL, ",");
					++i;
				}
				n_values = i;
			}
			else return 1;
		}
		else
			values[0] = value;

		if (Field == first_name || Field == last_name)
		{
			for (int j = 0; j < n_values; ++j)
			{
				int i = 1;
				if (values[j][0] < 'A' || values[j][0] > 'Z') return 1;
				while (values[j][i] != '\0')
				{
					if (values[j][i] < 'a' || values[j][i] > 'z') return 1;
					++i;
				}
			}
			return 0;
		}
		if (Field == phone || Field == id || Field == times_used)
		{
			for (int j = 0; j < n_values; ++j)
			{
				int i = 0;
				while (values[j][i] != '\0')
				{
					if (values[j][i] < '0' || values[j][i] > '9') return 1;
					++i;
				}
			}
			return 0;
		}
		if (Field == car)
		{
			for (int j = 0; j < n_values; ++j)
			{
				int i = 0;
				while (values[j][i] != '\0')
				{
					if ((values[j][i] >= '0' && values[j][i] <= '9') || (values[j][i] >= 'A' && values[j][i] <= 'Z')) {}
					else return 1;
					++i;
				}
			}
			return 0;
		}
		if (Field == fstatus)
		{
			for (int j = 0; j < n_values; ++j)
			{
				if (values[j] != "active" && values[j] != "disabled" && values[j] != "vacation" && values[j] != "lost" && values[j] != "broken")
					return 1;
			}
			return 0;
		}
		else return 1;
		return 0;
	}

	field strToField(std::string sField)
	{
		for (int i = 0; i < 7; ++i)
			if (sField == g_strFields[i]) return g_Fields[i];
		return none;
	}

	bool strToStat(std::string str, status* stat)
	{
		for (int i = 0; i < 5; ++i)
			if (str == g_strStatuses[i])
			{
				*stat = g_Statuses[i];
				return 0;
			}
		return 1;
	}

public:
	inputConditions(std::string in)
	{
		conditions = in;
	}

	bool parse(std::list <Condition*>* condition_list)
	{
		int cond_num = separate(conditions, conds, ' ');
		if (!cond_num) return 1;

		for (int i = 0; i < cond_num; ++i)
		{
			char* dup = _strdup(conds[i].c_str());
			char* c_field = strtok(dup, "= ! < > /");
			conds[i].erase(0, strlen(c_field));
			dup = _strdup(conds[i].c_str());
			char* c_sign;
			if (conds[i][0] == '/') c_sign = strtok(dup, "[");
			else c_sign = strtok(dup, "[ a b c d e f g h i j k l m n o p q r s t u v w x y z A B C D E F G H I J K L M N O P Q R S T U V W X Y Z 0 1 2 3 4 5 6 7 8 9");
			conds[i].erase(0, strlen(c_sign));
			char* c_value = _strdup(conds[i].c_str());

			field Field = strToField(c_field);
			if (Field == none) return 1;
			if (strcmp(c_sign, "=") != 0 && strcmp(c_sign, "!=") != 0 && strcmp(c_sign, ">") != 0 && strcmp(c_sign, "<") != 0 &&
				strcmp(c_sign, ">=") != 0 && strcmp(c_sign, "<=") != 0 && strcmp(c_sign, "/in/") != 0) return 1;

			if (checkValue(Field, c_value, c_sign)) return 1;
			
			std::string value = c_value;
			std::string sign = c_sign;

			if (strcmp(c_sign, "/in/") == 0)
			{
				Condition* cond_ptr = new in_Condition(Field, value);
				//in_Condition cond(Field, value);
				condition_list->push_back(cond_ptr);
				continue;
			}

			std::string* values = new std::string[50];
			int n_val = separate(value, values, ',');
			if (n_val > 1 && sign != "!=") return 1;


			if (Field == first_name || Field == last_name || Field == phone || Field == car)
			{
				for (int j = 0; j < n_val; ++j)
				{
					Condition* cond_ptr = new Condition_comparison(Field, sign, values[j]);
					condition_list->push_back(cond_ptr);
				}
			}
			else if (Field == id || Field == times_used)
			{
				for (int j = 0; j < n_val; ++j)
				{
					Condition* cond_ptr = new Condition_comparison(Field, sign, std::stoi(values[j]));
					condition_list->push_back(cond_ptr);
				}
			}
			else if (Field == fstatus)
			{
				for (int j = 0; j < n_val; ++j)
				{
					status st;
					if (strToStat(values[j], &st)) return 1;
					Condition* cond_ptr = new Condition_comparison(Field, sign, st);
					condition_list->push_back(cond_ptr);
				}
			}
			else return 1;

			delete[] values;
		}
		return 0;
	}

};

class DataBase
{
private:
	std::list <Record> DB;

	field getField(std::string sField)
	{
		for (int i = 0; i < 7; ++i)
			if (sField == g_strFields[i]) return g_Fields[i];
		return none;
	}

	bool checkStatus(std::string sStatus, status& Status)
	{
		for (int i = 0; i < 5; ++i)
			if (sStatus == g_strStatuses[i])
			{
				Status = g_Statuses[i];
				return 0;
			}
		return 1;
	}

	bool checkValue(field Field, std::string value)
	{
		if (Field == first_name || Field == last_name)
		{
			for (int i = 0; i < value.size(); ++i)
				if (!((value[i] >= 'A' && value[i] <= 'Z') || (value[i] >= 'a' && value[i] <= 'z'))) return 1;
		}
		else if (Field == phone || Field == id || Field == times_used)
		{
			for (int i = 0; i < value.size(); ++i)
				if (value[i] < '0' || value[i] > '9') return 1;
		}
		else if (Field == car)
		{
			for (int i = 0; i < value.size(); ++i)
				if (!((value[i] >= 'A' && value[i] <= 'Z') || (value[i] >= '0' && value[i] <= '9'))) return 1;
		}
		else if (Field == fstatus)
		{
			status st;
			bool res = checkStatus(value, st);
			if (res) return 1;
		}
		else return 1;
		return 0;
	}

	bool parseFV(bool ins, std::istringstream& iss, std::string* Values)
	{
		std::string loc_sFields[7] = { "", "", "", "", "", "", "" };
		std::string sValues[7] = { "", "", "", "", "", "", "" };
		field loc_Fields[7];

		for (int i = 0; i < 7; ++i)
		{
			std::getline(iss, loc_sFields[i], '=');
			std::getline(iss, sValues[i], ',');
			loc_Fields[i] = getField(loc_sFields[i]);
			if (!ins && loc_sFields[i] == "" && sValues[i] == "") break;
			if ((loc_sFields[i] == "" || sValues[i] == "" || loc_Fields[i] == none || checkValue(loc_Fields[i], sValues[i])) && ins)
				return 1;
			if (!ins && (loc_Fields[i] == none || checkValue(loc_Fields[i], sValues[i]) || (loc_sFields[i] != "" && sValues[i] == "")))
				return 1;
			Values[loc_Fields[i] - 1] = sValues[i];
		}
		if (ins)
		{
			for (int i = 0; i < 7; ++i)
				if (Values[i] == "") return 1;
		}
		return 0;
	}

	int strToFields(std::istringstream& strm, field* fields)
	{
		for (int j = 0; j < 7; ++j)
			fields[j] = none;
		std::string loc_sFields[7];
		int i = 0;
		while (std::getline(strm, loc_sFields[i], ','))
			++i;
		for (int j = 0; j < i; ++j)
		{
			fields[j] = getField(loc_sFields[j]);
			if (fields[j] == none) return 1;
		}
		return i;
	}

	std::list <std::list<Record>::iterator> iterByConditions(std::string sConditions)
	{
		inputConditions Conditions(sConditions);
		std::list <Condition*> condition_list;
		//std::list <in_Condition> in_condition_list;

		Conditions.parse(&condition_list);

		std::list <std::list<Record>::iterator> rec_iter;
		rec_iter = find(condition_list, DB.begin(), DB.end());
		return rec_iter;
	}

public:
	DataBase(std::list <Record> List)
	{
		auto start = List.begin();
		auto end = List.end();
		DB.assign(start, end);
	}
	DataBase()
	{
		DB = {};
	}

	std::list <std::list<Record>::iterator> find(std::list <Condition*> condition_list, 
		std::list<Record>::iterator begin, std::list<Record>::iterator end)
	{
		std::list <std::list<Record>::iterator> found;

		for (auto iter = begin; iter != end; ++iter)
		{
			bool res = 1;
			for (auto i = condition_list.begin(); i != condition_list.end(); ++i)
			{
				res = (*i)->check(*iter);
				if (!res) break;
			}
			if (!res) continue;

			found.push_back(iter);
		}
		return found;
	}

	int uniq(field Field1, field Field2, field Field3, field Field4, field Field5, field Field6, field Field7)
	{
		field Fields[7] = { Field1, Field2, Field3, Field4, Field5, Field6, Field7 };
		int n = 0;

		for (int i = 0; i < 7; ++i)
		{
			if (Fields[i] == none) ++n;
			for (int j = i + 1; j < 7; ++j)
				if (Fields[i] == Fields[j] && Fields[i] != none) return -1;
		}
		if (n == 7) return 0;

		std::list <std::list<Record>::iterator> to_delete;
		auto iter = DB.begin();
		int dn = 0;
		while (iter != DB.end())
		{
			std::list <Condition*> condition_list;
			//std::list <in_Condition> in_condition_list;

			for (int i = 0; i < 7; ++i)
				if (Fields[i] != none)
				{
					if (iter->getStrField(Fields[i]) != "error") {
						Condition* cond_ptr = new Condition_comparison(Fields[i], "=", iter->getStrField(Fields[i]));
						condition_list.push_back(cond_ptr);
					}
					else if (iter->getIntField(Fields[i]) != -1) {
						Condition* cond_ptr = new Condition_comparison(Fields[i], "=", iter->getIntField(Fields[i]));
						condition_list.push_back(cond_ptr);
					}
					else {
						Condition* cond_ptr = new Condition_comparison(Fields[i], "=", iter->Status());
						condition_list.push_back(cond_ptr);
					}
				}

			to_delete = find(condition_list, std::next(iter), DB.end());

			for (auto del_iter = to_delete.begin(); del_iter != to_delete.end(); ++del_iter)
			{
				DB.erase(*del_iter);
				++dn;
			}

			++iter;
		}
		return dn;
	}

	void output()
	{
		for (auto iter = DB.begin(); iter != DB.end(); ++iter)
		{
			iter->output();
		}
	}

	bool insert(std::istringstream& iss)
	{
		std::string Values[7] = { "", "", "", "", "", "", "" };
		if (parseFV(1, iss, Values)) return 1;
		status st;
		if (checkStatus(Values[6], st)) return 1;

		Record newRecord(Values[0], Values[1], Values[2], Values[3], std::stoi(Values[4]), std::stoi(Values[5]), st);
		DB.push_back(newRecord);
		return 0;
	}

	bool select(std::istringstream& iss)
	{
		std::string fields;
		std::getline(iss, fields, ' ');
		std::istringstream strm(fields);
		field* loc_Fields = new field[7];

		int i = strToFields(strm, loc_Fields);
		if (i < 0) return 1;

		bool fields_out[7] = { 0 };
		for (int j = 0; j < i; ++j)
			fields_out[loc_Fields[j] - 1] = 1;

		std::string sConditions;
		std::getline(iss, sConditions, '\n');
		std::list <std::list<Record>::iterator> rec_iter = iterByConditions(sConditions);

		std::cout << "select: " << rec_iter.size() << std::endl;
		for (auto i = rec_iter.begin(); i != rec_iter.end(); ++i)
			(*i)->output(fields_out[0], fields_out[1], fields_out[2], fields_out[3], fields_out[6], fields_out[4], fields_out[5]);

		return 0;
	}

	bool del(std::istringstream& iss)
	{
		std::string sConditions;
		std::getline(iss, sConditions, '\n');
		std::list <std::list<Record>::iterator> rec_iter = iterByConditions(sConditions);

		for (auto i = rec_iter.begin(); i != rec_iter.end(); ++i)
			DB.erase(*i);

		std::cout << "delete: " << rec_iter.size() << std::endl;
		return 0;
	}

	bool update(std::istringstream& iss)
	{
		std::string Values[7] = { "", "", "", "", "", "", "" };
		std::string flds;
		std::getline(iss, flds, ' ');
		std::istringstream strm_flds(flds);
		if (parseFV(0, strm_flds, Values)) return 1;
		status st;
		if (Values[6] != "" && checkStatus(Values[6], st)) return 1;

		std::string sConditions;
		std::getline(iss, sConditions, '\n');
		std::list <std::list<Record>::iterator> rec_iter = iterByConditions(sConditions);

		for (auto i = rec_iter.begin(); i != rec_iter.end(); ++i)
		{
			for (int j = 0; j < 4; ++j)
				if (Values[j] != "")
					if ((*i)->update(g_Fields[j], Values[j])) return 1;
			for (int j = 4; j < 6; ++j)
				if (Values[j] != "")
					if ((*i)->update(g_Fields[j], std::stoi(Values[j]))) return 1;
			if (Values[6] != "")
				if ((*i)->update(fstatus, st)) return 1;
		}

		std::cout << "update: " << rec_iter.size() << std::endl;
		return 0;
	}

	bool uniq(std::istringstream& iss)
	{
		field* loc_Fields = new field[7];

		int i = strToFields(iss, loc_Fields);
		if (i < 0) return 1;

		int res = uniq(loc_Fields[0], loc_Fields[1], loc_Fields[2], loc_Fields[3], loc_Fields[4], loc_Fields[5], loc_Fields[6]);
		if (res == -1) return 1;

		std::cout << "uniq: " << res << std::endl;
		return 0;
	}
};

int main()
{
	DataBase data_base;
	while (1)
	{
		std::string s_command, command_name;
		getline(std::cin, s_command);
		std::istringstream iss(s_command);
		std::getline(iss, command_name, ' ');

		bool res = 0;
		if (command_name == "insert")
			res = data_base.insert(iss);
		else if (command_name == "select")
			res = data_base.select(iss);
		else if (command_name == "delete")
			res = data_base.del(iss);
		else if (command_name == "update")
			res = data_base.update(iss);
		else if (command_name == "uniq")
			res = data_base.uniq(iss);
		else if (command_name == "output")
			data_base.output();
		else
			std::cout << "incorrect command" << std::endl;
		
		if (res) std::cout << "incorrect command" << std::endl;
	}
	return 0;
}
