#ifndef OPERAND_HPP
#define OPERAND_HPP

#include <iomanip>
#include "IOperand.hpp"
#include "exceptions.hpp"

template <typename T>
class Operand : public IOperand
{
private:
	T		v_;
	eOperandType type_;
	std::string str_;

	IOperand const * creat_type(std::string const & s, eOperandType type) const {
		if (type_ >= type)
			return new Operand<T>(s, getType());
		if (type == Int16)
			return new Operand<int16_t>(s, type);
		if (type == Int32)
			return new Operand<int32_t>(s, type);
		if (type == Float)
			return new Operand<float>(s, type);
		return new Operand<double>(s, type);
	}

public:
	Operand(std::string const & val, eOperandType type) : type_(type) {
		T mm = std::numeric_limits<T>::max();

		long double ld = std::stold(val);
		if (ld > mm)
			throw overflow();
		mm = (type < Float ? std::numeric_limits<T>::min() : -mm);
		if (ld < mm)
			throw underflow();
		if (type < Float) {
			v_ = std::stoll(val);
			str_ = std::to_string(v_);
		} else {
			v_ = std::stod(val);
			std::ostringstream strs;
			strs << std::setprecision((type_ == Float ? 7 : 16)) << v_;
			str_ = strs.str();
		}
	}

	Operand(Operand const & rhs) { *this = rhs; }

	Operand	&operator=(Operand const & rhs) {
		v_ = rhs.v_;
		type_ = rhs.type_;
		str_ = rhs.str_;
		return *this;
	}

	~Operand() { }

	int getPrecision() const {
		if (type_ < Float)
			return 0;
		if (type_ == Float)
			return 7;
		return 16;
	}

	eOperandType getType() const { return type_; }


	IOperand const * operator+( IOperand const & rhs ) const {
		if (type_ < Float && rhs.getType() < Float)
			return creat_type(std::to_string(v_ + std::stoll(rhs.toString())), rhs.getType());
		return creat_type(std::to_string(v_ + std::stold(rhs.toString())), rhs.getType());
	}

	IOperand const * operator-( IOperand const & rhs ) const {
		if (type_ < Float && rhs.getType() < Float)
			return creat_type(std::to_string(v_ - std::stoll(rhs.toString())), rhs.getType());
		return creat_type(std::to_string(v_ - std::stold(rhs.toString())), rhs.getType());
	}

	IOperand const * operator*( IOperand const & rhs ) const {
		if (type_ < Float && rhs.getType() < Float)
			return creat_type(std::to_string(v_ * std::stoll(rhs.toString())), rhs.getType());
		return creat_type(std::to_string(v_ * std::stold(rhs.toString())), rhs.getType());
	}

	IOperand const * operator/( IOperand const & rhs ) const {
		if (!std::stold(rhs.toString()))
			throw div_mod_by_zero();
		if (type_ < Float && rhs.getType() < Float)
			return creat_type(std::to_string(v_ / std::stol(rhs.toString())), rhs.getType());
		return creat_type(std::to_string(v_ / std::stod(rhs.toString())), rhs.getType());
	}

	IOperand const * operator%( IOperand const & rhs ) const {
		if (!std::stold(rhs.toString()))
			throw div_mod_by_zero();
		if (type_ < Float && rhs.getType() < Float)
			return creat_type(std::to_string(static_cast<long long>(v_) % std::stoll(rhs.toString())), rhs.getType());
		return creat_type(std::to_string(fmod(static_cast<double>(v_), std::stod(rhs.toString()))), rhs.getType());
	}

	std::string const & toString() const { return str_; }

};

#endif
