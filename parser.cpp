#include <parser.h>

//Operands
//Arg 1
#define A1 4
//Arg 2
#define A2 2
//Result
#define R  1

#define HAS_A1(x) 	((x & A1)>>2)
#define HAS_A2(x) 	((x & A2)>>1)
#define HAS_R(x) 	(x & R)

#define CHECK_ARG(id, x)	\
	(id==1?					\
		HAS_A1(x):			\
		(id==2?				\
			HAS_A2(x):		\
			(id==3?			\
				HAS_R(x):	\
				0			\
			)				\
		)					\
	)

#define SET_ARG(x)					\
	while(count<=3){				\
		if(CHECK_ARG(count, x)==1){	\
			if(count==1)			\
				a1=accum;			\
			if(count==2)			\
				a2=accum;			\
			if(count==3)			\
				r=accum;			\
			count++;				\
			break;					\
		}							\
		count++;					\
	}								\

int line_num=0;

std::string var_types_str[]={
	"int",
	"double",
	"bool",
	"string",
	"undefined"
};

int cmd_num=19;

std::string cmd_str[]={
	"PLUS",
	"SUB",
	"MULT",
	"DIV",
	"MOD",
	"ASSIGN",
	"PARAM",
	"CALL",
	"JUMP",
	"JUMPIF",
	"JUMPNIF",
	"LABEL",
	"EQUAL",
	"NEQUAL",
	"LESS",
	"LESSEQ",
	"GREAT",
	"GREATEQ",
	"RETURN"
};

int req_ops[]={
	A1|A2|R,	//PLUS
	A1|A2|R,	//SUB
	A1|A2|R,	//MULT
	A1|A2|R,	//DIV
	A1|A2|R,	//MOD
	A1|R,		//ASSIGN
	A1,			//PARAM
	A1|A2|R,	//CALL
	A1,			//JUMP
	A1|A2,		//JUMPIF
	A1|A2,		//JUMPNIF
	A1,			//LABEL
	A1|A2|R,	//EQUAL
	A1|A2|R,	//NEQUAL
	A1|A2|R,	//LESS
	A1|A2|R,	//LESSEQ
	A1|A2|R,	//GREAT
	A1|A2|R,	//GREATEQ
	A1			//RETURN
};

//See which operands the operator needs
int required_operands(std::string cmd){
	for(int i=0;i<cmd_num;i++)
		if(cmd_str[i]==cmd)
			return req_ops[i];
	std::cout<<"[ERROR] Unknown command "<<cmd<<"\n";
	exit(0);
}

cmd_type get_cmd(std::string cmd){
	if(cmd=="PLUS")
		return ADD;
	if(cmd=="SUB")
		return SUB;
	if(cmd=="MULT")
		return MULT;
	if(cmd=="DIV")
		return DIV;
	if(cmd=="MOD")
		return MOD;
	if(cmd=="ASSIGN")
		return ASSIGN;
	if(cmd=="PARAM")
		return PARAM;
	if(cmd=="CALL")
		return CALL;
	if(cmd=="JUMP")
		return JUMP;
	if(cmd=="JUMPIF")
		return JUMPIF;
	if(cmd=="JUMPNIF")
		return JUMPNIF;
	if(cmd=="LABEL")
		return LABEL;
	if(cmd=="EQUAL")
		return CEQ;
	if(cmd=="NEQUAL")
		return CNE;
	if(cmd=="LESS")
		return CLT;
	if(cmd=="LESSEQ")
		return CLE;
	if(cmd=="GREAT")
		return CGT;
	if(cmd=="GREATEQ")
		return CGE;
	if(cmd=="RETURN")
		return RET;
	else{
		std::cout<<"[ERROR] Unknown command "<<cmd<<"\n";
		exit(0);
	}
}

void parse(){
	std::string line;
	while(std::getline(inFile, line)){
		line_num++;
		parse_line(line);
	}
}

void parse_line(std::string line){
	std::string cmd, a1, a2, r, accum="";
	int req;
	bool in_string=false, begin=true, escape_sequence=false;
	int count=0;
	for(char ch : line){
		if(in_string){
			if(escape_sequence){
				if(ch=='a')
					accum+='\a';
				else if(ch=='b')
					accum+='\b';
				else if(ch=='f')
					accum+='\f';
				else if(ch=='n')
					accum+='\n';
				else if(ch=='r')
					accum+='\r';
				else if(ch=='t')
					accum+='\t';
				else if(ch=='v')
					accum+='\v';
				else if(ch=='\\')
					accum+='\\';
				else if(ch=='\'')
					accum+='\'';
				else if(ch=='"')
					accum+='"';
				else if(ch=='?')
					accum+='?';
				else{
					std::cout<<"[ERROR] Invalid escape sequence \\"
						<<ch<<" at line "<<line_num<<"\n";
				}
				escape_sequence=false;
			}
			else{
				if(ch=='"')
					in_string=false;
				else if(ch=='\\')
					escape_sequence=true;
				else
					accum+=ch;
			}
		}
		else{
			if(ch=='\\'){
				std::cout<<"[ERROR] Misplaced escape sequence at line "
					<<line_num<<"\n";
				exit(0);
			}
			if(ch=='"'){
				in_string=true;
				begin=false;
			}
			else if(ch>='a' && ch<='z'
					|| ch>='A' && ch<='Z'
					|| ch>='0' && ch<='9'
					|| ch=='_'){
				begin=false;
				accum+=ch;
			}
			else if(ch==' ' && !begin){
				if(count==0){
					cmd=accum;
					req=required_operands(cmd);
					count++;
				}
				else
					SET_ARG(req);
				accum="";
				begin=true;
			}
			else if(ch==' ' && begin){}
			else{
				std::cout<<"[ERROR] Invalid character "
					<<ch<<" at line "<<line_num<<"\n";
				exit(0);
			}
		}
	}
	if(accum!="")
		SET_ARG(req);
	
	std::cout<<"[CMD] "<<cmd<<":\n"
		<<"\ta1 = "<<a1<<"\n"
		<<"\ta2 = "<<a2<<"\n"
		<<"\tr  = "<<r<<"\n";
}