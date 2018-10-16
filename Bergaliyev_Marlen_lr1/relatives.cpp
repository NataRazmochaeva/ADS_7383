#include <unordered_map>
#include <set>
#include <iostream>


static void find_relatives(std::unordered_map<std::string, std::set<std::string>> &relatives, std::string const &person, std::string const &sub_relative, std::set<std::pair<std::string, std::string>> &result, std::set<std::string> &viewed){
    static std::string tabs;
    if(person != sub_relative && result.find(std::make_pair(sub_relative, person)) == result.end()){
	result.insert(std::make_pair(person, sub_relative));
	std::cout << tabs << "Insert " << sub_relative << std::endl;
    }
    if(person != sub_relative)
    	std::cout << tabs << "Sub relative " << sub_relative << "{" << std::endl;
    tabs.push_back('\t');
    viewed.insert(sub_relative);
    for(auto relative : relatives[sub_relative]){
	if(person != relative && viewed.find(relative) == viewed.end()){
	    find_relatives(relatives, person, relative, result, viewed);
	}
    }
    for(auto relation : relatives){
	auto children = std::get<1>(relation);
	auto parent = std::get<0>(relation);
        if(children.find(sub_relative) != children.end() && viewed.find(parent) == viewed.end()){
	    find_relatives(relatives, person, parent, result, viewed);
	}
    }
    tabs.pop_back();
    if(person != sub_relative)
    	std::cout << tabs << "}" << std::endl;
}

auto couple_relatives(std::unordered_map<std::string, std::set<std::string>> children){
    std::set<std::pair<std::string, std::string>> result;
    std::set<std::string> persons;
    for(auto relation : children){
        persons.insert(std::get<1>(relation).begin(), std::get<1>(relation).end());
	persons.insert(std::get<0>(relation));
    }
    for(auto person : persons){
	std::set<std::string> viewed;
	std::cout << "Person " << person << "{" << std::endl;
	find_relatives(children, person, person, result, viewed);
	std::cout << "}" << std::endl;
    }
    return result;
}

