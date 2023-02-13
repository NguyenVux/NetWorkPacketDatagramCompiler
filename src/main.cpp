#include <iostream>
#include <pugixml.hpp>
#include <utils/result.h>
#include <CppNode/NodeFactory.h>

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
	std::cout << root->toString();

	//std::cout << "Parsing Success" << std::endl;


	return 0;
}
