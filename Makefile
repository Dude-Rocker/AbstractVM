NAME	=	avm
CXX		=	g++
FLAGS	=	-Wall -Wextra -Werror -std=c++11
DIRSR	=	./src/
DIROB	=	./obj/
DIRIN	=	./inc/
SRCS	=	main.cpp avm.cpp exceptions.cpp
HEADS	=	avm.hpp IOperand.hpp Operand.hpp exceptions.hpp
OBJCS	=	$(addprefix $(DIROB), $(SRCS:.cpp=.o))
INCS	=	$(addprefix $(DIRIN), $(HEADS))

all: $(NAME)

$(NAME): $(OBJCS)
	@$(CXX) $(OBJCS) -o $(NAME)
	@echo "$(NAME) ready"

$(DIROB)%.o: $(DIRSR)%.cpp $(INCS)
	@mkdir -p $(DIROB)
	@$(CXX) $(FLAGS) -I $(DIRIN) -c -o $@ $<

clean:
	@rm -rf $(DIROB)
	@echo "all objects deleted"

fclean: clean
	@rm -f $(NAME)
	@echo "$(NAME) deleted"

re: fclean all
