#ifndef ADD_H

#define ADD_H




class Add {

private:

	ast_t lOperand,
		  rOperand;


public:


	Add(ast_t&& lOperandParam, ast_t&& rOperandParam)

		:lOperand(std::move(lOperandParam)), rOperand(std::move(rOperandParam))

	{}




}; // Add



#endif