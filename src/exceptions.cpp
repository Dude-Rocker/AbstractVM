#include "../inc/exceptions.hpp"

except_err::except_err(std::string const & s) : err_(s) { }

const char *except_err::what() const throw() { return (err_.c_str()); }

cant_open::cant_open(std::string const & s) : err_("ERROR: can't open/read: " + s + "\n") { }

const char *cant_open::what() const throw() { return (err_.c_str()); }

syntax_err::syntax_err(const std::string & c, std::string const & s) : err_("Syntax error in line " + c + ": " + s + "\n") { }

const char *syntax_err::what() const throw() { return (err_.c_str()); }

one_arg::one_arg(const std::string & c, std::string const & s, std::string const & t) : err_("Lexical error in line " + c +
	": " + s + ": can't use " + t + " instruction when stack contains only one values\n") { }

const char *one_arg::what() const throw() { return (err_.c_str()); }

empty_stack::empty_stack(const std::string & c, std::string const & t) : err_("Error in line " + c + ": " + t + " on empty stack\n") { }

const char *empty_stack::what() const throw() { return (err_.c_str()); }

no_equal::no_equal(const std::string & c, std::string const & l, std::string const & r) : err_("Assert error: " + l + " (line " +
	c + ") no equal " + r + " (from stack)\n") { }

const char *no_equal::what() const throw() { return (err_.c_str()); }

after_end::after_end(const std::string & c) : err_("Error in line " + c + ": after \"exit\" instruction can be nothing except comments\n") { }

impos_print::impos_print(const std::string & c, std::string const & s, std::string const & t) :
	err_("Error in line " + c + ": unable to print " + t + "(" + s + ") value\n") { }

const char *impos_print::what() const throw() { return (err_.c_str()); }

const char *after_end::what() const throw() { return (err_.c_str()); }

const char *overflow::what() const throw() { return " overflow "; }

const char *underflow::what() const throw() { return " underflow "; }

const char *div_mod_by_zero::what() const throw() { return " division/modulo by 0 "; }
