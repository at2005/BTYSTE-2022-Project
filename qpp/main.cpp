

#include "compiler.h"


using namespace std;


int main() {

	
	vector<Pair> token_values = execute_lex("program.qpp").getLex().dict_output;
	vector<vector<Pair>> expressions = getEachExpression(token_values);
	
	
	free_regs = {0,0,0,0,0,0};
	file << "[extern printh]\n[extern printf]\n[extern scanf]\n[extern zero_buffer]\n";
	file << "section .text:\nglobal main\n";
	
	std::unordered_map<string,int> mtable = {};
	symtab* main_table = new symtab;
	main_table->table = mtable;
	
	main_table->parent_table = nullptr;	

	
	SyntaxTree* main_tree;
	for(int i = 0; i < expressions.size(); i++) {
		SyntaxTree* st = new SyntaxTree(expressions[i]);
//		if(st->getRoot()->getTValue() == "main") {
			//*main_tree = *st;
			file << st->getRoot()->getTValue() << ":\n";
			for(int i = 0; i < st->get_child_trees().size(); i++) { 
				compile(&(st->get_child_trees()[i]), main_table);	
			}

			
			file << "add esp," << var_counter*4 << endl;	
			file << "ret\n";	
				
//		}
	
	}

	/*Node* root = main_tree->getRoot();
	
	free_regs = {0,0,0,0,0,0};
	file << "[extern printh]\n[extern printf]\n[extern scanf]\n[extern zero_buffer]\n";
	file << "section .text:\nglobal main\nmain:\n";
	
	std::unordered_map<string,int> mtable = {};
	symtab* main_table = new symtab;
	main_table->table = mtable;
	
	main_table->parent_table = nullptr;	

	for(int i = 0; i < main_tree->get_child_trees().size(); i++) { 
		compile(&(main_tree->get_child_trees()[i]), main_table);	
	}
	
	file << "add esp," << var_counter*4 << endl;	
	file << "ret\n";	
*/
	file << data_section << endl;
	file << bss_section;
	return 0;



}
