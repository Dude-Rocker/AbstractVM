#ifndef AVM_HPP
#define AVM_HPP

#include <list>
#include <regex>
#include "Operand.hpp"

class Avm
{
private:
	typedef IOperand const *(Avm::*creat_func)(std::string const &) const;
	typedef IOperand const *(IOperand::*oper_func)(IOperand const &) const;
	std::list<const IOperand *> stack_;
	creat_func func_[Size_Op];
	oper_func operat_[Size_Op];
	size_t ln_;
	std::string out_;
	std::string err_;
	std::string str_;
	bool	ex_;
	bool	war_;

	std::cmatch	res_;
	std::regex	cmd_;
	std::regex	dec_;
	std::regex	dot_;
	std::regex	com_;

	void	gener_func();
	void	check_str();
	void	arithmetic_func(int i);


	IOperand const * createInt8( std::string const & value ) const;
	IOperand const * createInt16( std::string const & value ) const;
	IOperand const * createInt32( std::string const & value ) const;
	IOperand const * createFloat( std::string const & value ) const;
	IOperand const * createDouble( std::string const & value ) const;

public:
	Avm();
	Avm(Avm const &cpy);
	Avm &operator=(Avm const &cpy);
	~Avm();

	void	read_stream(const char *s, bool w);

	IOperand const * createOperand( eOperandType type, std::string const & value ) const;

};

#endif
