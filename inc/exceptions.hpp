#ifndef EXCEPTIONS_HPP
#define EXCEPTIONS_HPP

#include <string>

struct except_err : public std::exception {
private:
	const std::string err_;

public:
	except_err(std::string const & s);
	const char	*what(void) const throw();
};

struct cant_open : public std::exception {
private:
	const std::string err_;

public:
	cant_open(std::string const & s);
	const char	*what(void) const throw();
};

struct syntax_err : public std::exception {
private:
	const std::string err_;

public:
	syntax_err(const std::string & c, std::string const & s);
	const char	*what(void) const throw();
};

struct one_arg : public std::exception {
private:
	const std::string err_;

public:
	one_arg(const std::string & c, std::string const & s, std::string const & t);
	const char	*what(void) const throw();
};

struct empty_stack : public std::exception {
private:
	const std::string err_;

public:
	empty_stack(const std::string & c, std::string const & t);
	const char	*what(void) const throw();
};

struct no_equal : public std::exception {
private:
	const std::string err_;

public:
	no_equal(const std::string & c, std::string const & l, std::string const & r);
	const char	*what(void) const throw();
};

struct after_end : public std::exception {
private:
	const std::string err_;

public:
	after_end(const std::string & c);
	const char	*what(void) const throw();
};

struct impos_print : public std::exception {
private:
	const std::string err_;

public:
	impos_print(const std::string & c, std::string const & s, std::string const & t);
	const char	*what(void) const throw();
};

struct overflow : public std::exception { const char *what(void) const throw(); };

struct underflow : public std::exception { const char *what(void) const throw(); };

struct div_mod_by_zero : public std::exception { const char *what(void) const throw(); };

#endif
