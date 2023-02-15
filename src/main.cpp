#include <ios>
#include <iostream>
#include <pugixml.hpp>
#include <utils/result.h>
#include <CppNode/NodeFactory.h>
#include <sstream>
#include <fstream>
#include <format>

int main(int argc,char* argv[]){

	if(argc == 1)
	{
		std::cout << "Arg count: " << argc << std::endl;
		return -1;
	}
	pugi::xml_document RootNode;
	pugi::xml_parse_result result = RootNode.load_file(argv[1]);
	if(!result)
	{
		std::cout << "Cannot Parse file \"" << std::endl;
		return -1;
	}
	

	NodeFactory factory;
	CreateNodeResult createNodeResult = factory.CreateTree(RootNode);
	if(createNodeResult != VuxNguyen::success)
	{
		std::cout << createNodeResult.error().what() << std::endl;
		return -1;
	}

	auto root  = createNodeResult.extract_payload();


	std::cout << root->toString() << std::endl;
	std::cout << root->getSource() << std::endl;

	std::ofstream header(std::format("{}.hpp",root->GetName()));
	std::ofstream source(std::format("{}.cpp",root->GetName()));

	header << root->toString();
	source << root->getSource();


	//std::cout << "Parsing Success" << std::endl;
	/*std::stringstream ss;
	ss.write(reinterpret_cast<>;);*/

	return 0;
}
