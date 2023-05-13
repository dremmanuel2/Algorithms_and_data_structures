//#include"stackskh.cpp"
//
//#define N_OPTR 9
//typedef enum { ADD, SUB, DIV, POW, FAC, L_P, R_P, EOE }Operator;
//const char pri[N_OPTR][N_OPTR] = {
//	'>','>','<','<','<','<','<','>','>',
//	'>','>','<','<','<','<','<','>','>',
//	'>','>','>','>','<','<','<','>','>',
//	'>','>','>','>','<','<','<','>','>',
//	'>','>','>','>','>','<','<','>','>',
//	'>','>','>','>','>','>',' ','>','>',
//	'<','<','<','<','<','<','<','=',' ',
//	' ',' ',' ',' ',' ',' ',' ',' ',' ',
//	'<','<','<','<','<','<','<',' ','=',
//};
//float evaluate(char* S, char*& RPN)
//{
//	stackskh<float>opnd;stackskh<char>optr;
//	optr.push('\0');
//	while (!optr.empty())
//	{
//		if (isdigit(*S))
//		{
//			readnNumber(S, opnd);append(RPN, opnd.top());
//		}
//	}
//}