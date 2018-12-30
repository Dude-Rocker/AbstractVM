#include "../inc/avm.hpp"
#include <fstream>
#include <iostream>

static 	std::string type_[] = {"int8", "int16", "int32", "float", "double"};
static 	std::string oper_[] = {"add", "sub", "mul", "div", "mod", "pop", "dump", "print"};

Avm::Avm() : war_(false) { gener_func(); }

Avm::Avm(Avm const &cpy) { *this = cpy; }

Avm &Avm::operator=(Avm const &cpy) {
	if (this != &cpy) {
		gener_func();
		war_ = cpy.war_;
		stack_ = cpy.stack_;
	}
	return *this;
}

Avm::~Avm() {
	for (auto i = stack_.begin(); i != stack_.end(); ++i)
		delete *i;
	stack_.clear();
}

void	Avm::gener_func() {

	operat_[Int8] = &IOperand::operator+;
	operat_[Int16] = &IOperand::operator-;
	operat_[Int32] = &IOperand::operator*;
	operat_[Float] = &IOperand::operator/;
	operat_[Double] = &IOperand::operator%;

	func_[Int8] = &Avm::createInt8;
	func_[Int16] = &Avm::createInt16;
	func_[Int32] = &Avm::createInt32;
	func_[Float] = &Avm::createFloat;
	func_[Double] = &Avm::createDouble;
	cmd_ = "\\s*(add|sub|mul|div|mod|pop|dump|print|exit)\\s*(;.*)?";
	dec_ = "\\s*(push|assert)\\s+(int8|int16|int32)\\((-?\\d+)\\)\\s*(;.*)?";
	dot_ = "\\s*(push|assert)\\s+(float|double)\\((-?\\d+\\.\\d+)\\)\\s*(;.*)?";
	com_ = "\\s*(;.*)?";
	
	/*
	spaces tabs etc.
	dec_ = "\\s*(push|assert)\\s+(int8|int16|int32)\\s*\\(\\s*([+-]?\\d+)\\s*\\)\\s*(;.*)?";
	dot_ = "\\s*(push|assert)\\s+(float|double)\\s*\\(\\s*([+-]?\\d+\\.\\d+)\\s*\\)\\s*(;.*)?";
	*/
}

void	Avm::arithmetic_func(int i)
{
	if (stack_.size() < 2)
		throw one_arg(std::to_string(ln_), str_, oper_[i]);
	auto tmp = stack_.begin();
	++tmp;
	try {
		const IOperand *result = (stack_.front()->*operat_[i])(*(*tmp));

		delete *stack_.begin();
		stack_.pop_front();
		delete *stack_.begin();
		stack_.pop_front();
		stack_.push_front(result);

	} catch (std::exception const &ex) {
		std::string view_ = "+-*/%";
		throw except_err("Error in line " + std::to_string(ln_) + ": " + stack_.front()->toString() +
			" " + view_[i] + " " + (*tmp)->toString() + " >>>" + ex.what() + "!\n");
	}
}

void	Avm::check_str() {
	int op = Int8;
	if (!ex_ && std::regex_match(str_.c_str(), res_, cmd_)) {
		if (res_[1] == "exit") {
			ex_ = true;
			return ;
		}
		if (stack_.empty())
			throw empty_stack(std::to_string(ln_), res_[1]);
		while (res_[1] != oper_[op])
			++op;
		if (op < Size_Op)
			arithmetic_func(op);
		else if (res_[1] == "pop") {
			delete *stack_.begin();
			stack_.pop_front();
		} else if (res_[1] == "dump") {
			for (auto i = stack_.begin(); i != stack_.end(); ++i)
				out_ += (*i)->toString() + "\n";
		} else {
			char pr = std::stoi(stack_.front()->toString());
			if (stack_.front()->getType() != Int8 || !std::isprint(pr))
				throw impos_print(std::to_string(ln_), stack_.front()->toString(), type_[stack_.front()->getType()]);
			out_ += pr;
			out_ += "\n";
		}
	} else if (!ex_ && (std::regex_match(str_.c_str(), res_, dec_) || std::regex_match(str_.c_str(), res_, dot_))) {
		while (res_[2] != type_[op])
			++op;
		try {
			const IOperand *tmp = createOperand(static_cast<eOperandType>(op), res_[3]);
			delete tmp;
		} catch (std::exception const &ex) {
			throw except_err("Error in line " + std::to_string(ln_) + ": " + res_[3].str() +
				" is" + ex.what() + "for " + type_[op] + " type\n");
		}
		const IOperand *tmp = createOperand(static_cast<eOperandType>(op), res_[3]);
		if (res_[1] == "push")
			stack_.push_front(tmp);
		else {
			if (stack_.empty())
				throw empty_stack(std::to_string(ln_), res_[1]);
			if (stack_.front()->getType() != tmp->getType())
				throw no_equal(std::to_string(ln_), type_[stack_.front()->getType()], type_[tmp->getType()]);
			if (stack_.front()->toString() != tmp->toString())
				throw no_equal(std::to_string(ln_), stack_.front()->toString(), tmp->toString());
		}
	} else if (!std::regex_match(str_.c_str(), res_, com_)) {
		if (ex_)
			throw after_end(std::to_string(ln_));
		throw syntax_err(std::to_string(ln_), str_);
	}
}

void	Avm::read_stream(const char *s, bool w) {
	ln_ = 1;
	err_ = "";
	out_ = "";
	ex_= false;
	war_ = w;
	std::ifstream ifs(s);

	if (s) {
		std::cin.rdbuf(ifs.rdbuf());
		if (!ifs.is_open())
			throw cant_open(s);
	}
	while (std::getline(std::cin, str_)) {
		if (!s && str_ == ";;")
			break ;
		try {
			check_str();
		} catch (const std::exception & ex) {
			if (war_)
				out_ += ex.what();
			else
				err_ += ex.what();
		}
		++ln_;
	}
	if (!ex_ && war_)
		out_ += "The program doesn't have an exit instruction\n";
	else if (!ex_)
		err_ += "The program doesn't have an exit instruction\n";
	if (err_[0])
		throw except_err(err_);
	std::cout << out_;
}

IOperand const * Avm::createInt8( std::string const & value ) const { return new Operand<int8_t>(value, Int8); }

IOperand const * Avm::createInt16( std::string const & value ) const { return new Operand<int16_t>(value, Int16); }

IOperand const * Avm::createInt32( std::string const & value ) const { return new Operand<int32_t>(value, Int32); }

IOperand const * Avm::createFloat( std::string const & value ) const { return new Operand<float>(value, Float); }

IOperand const * Avm::createDouble( std::string const & value ) const { return new Operand<double>(value, Double); }

IOperand const * Avm::createOperand( eOperandType type, std::string const & value ) const { return (this->*func_[type])(value); }
